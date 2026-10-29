#include <SPI.h>
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

// --- Pin Definitions ---
const int PIN_BTN_LEFT   = D0; // SW1
const int PIN_BTN_SELECT = D1; // SW3
const int PIN_BTN_RIGHT  = D2; // SW2
const int PIN_VIBE       = D3; // BZ1 slot replaced with Vibration Motor

// --- Pet State Variables ---
enum PetState {
  STATE_IDLE,
  STATE_SLEEPING,
  STATE_HUNGRY,
  STATE_HAPPY,
  STATE_SICK
};

PetState currentPetState = STATE_IDLE;

int hunger   = 80; 
int happiness = 80; 
int energy   = 80; 

unsigned long lastTickTime = 0;
const unsigned long tickInterval = 5000; 

// Eye animation parameters
unsigned long lastBlinkTime = 0;
int blinkDuration = 150;
bool isBlinking = false;
unsigned long nextBlinkInterval = 3000;

// Menu / UI selection
int menuSelection = 0; 
bool menuActive = false;

// Function Prototypes
void updateStats();
void handleButtons();
void drawPetFace();
void drawUI();
void triggerVibration(int duration);

void setup() {
  Serial.begin(115200);

  // Initialize Pins
  pinMode(PIN_BTN_LEFT, INPUT_PULLUP);
  pinMode(PIN_BTN_SELECT, INPUT_PULLUP);
  pinMode(PIN_BTN_RIGHT, INPUT_PULLUP);
  pinMode(PIN_VIBE, OUTPUT);
  digitalWrite(PIN_VIBE, LOW);

  // Initialize Display
  tft.init();
  tft.setRotation(1); 
  tft.fillScreen(TFT_BLACK);

  // Startup feedback buzz
  triggerVibration(80);
  delay(100);
  triggerVibration(150);
  
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(2);
  tft.setCursor(40, 100);
  tft.print("HatchiXIAO v1.0");
  delay(1500);
  tft.fillScreen(TFT_BLACK);
}

void loop() {
  unsigned long currentMillis = millis();

  // 1. Time-based stat decay & state updates
  if (currentMillis - lastTickTime >= tickInterval) {
    lastTickTime = currentMillis;
    updateStats();
  }

  // 2. Handle user button inputs
  handleButtons();

  // 3. Handle blinking timers
  if (!isBlinking && currentMillis - lastBlinkTime >= nextBlinkInterval) {
    isBlinking = true;
    lastBlinkTime = currentMillis;
    nextBlinkInterval = random(2500, 6000); 
  } else if (isBlinking && currentMillis - lastBlinkTime >= (unsigned long)blinkDuration) {
    isBlinking = false;
  }

  // 4. Render Graphics
  tft.startWrite();
  drawPetFace();
  drawUI();
  tft.endWrite();

  delay(30);
}

// --- Stat Management ---
void updateStats() {
  if (currentPetState != STATE_SLEEPING) {
    hunger = max(0, hunger - 2);
    happiness = max(0, happiness - 1);
    energy = max(0, energy - 1);
  } else {
    energy = min(100, energy + 5); 
  }

  if (hunger < 20 || happiness < 20) {
    currentPetState = STATE_HUNGRY;
  } else if (energy < 10) {
    currentPetState = STATE_SLEEPING;
  } else if (currentPetState == STATE_HUNGRY && hunger > 50 && happiness > 50) {
    currentPetState = STATE_IDLE;
  }
}

// --- Button Input Handling ---
void handleButtons() {
  static bool lastLeftState = HIGH;
  static bool lastSelectState = HIGH;
  static bool lastRightState = HIGH;

  bool currLeft = digitalRead(PIN_BTN_LEFT);
  bool currSelect = digitalRead(PIN_BTN_SELECT);
  bool currRight = digitalRead(PIN_BTN_RIGHT);

  // LEFT Button
  if (currLeft == LOW && lastLeftState == HIGH) {
    triggerVibration(40); // Quick haptic tick
    if (!menuActive) {
      menuActive = true;
    } else {
      menuSelection = (menuSelection - 1 + 3) % 3;
    }
    delay(200); 
  }

  // RIGHT Button
  if (currRight == LOW && lastRightState == HIGH) {
    triggerVibration(40);
    if (!menuActive) {
      menuActive = true;
    } else {
      menuSelection = (menuSelection + 1) % 3;
    }
    delay(200); 
  }

  // SELECT Button
  if (currSelect == LOW && lastSelectState == HIGH) {
    triggerVibration(60);
    if (!menuActive) {
      menuActive = true; 
    } else {
      if (menuSelection == 0) {
        // FEED
        hunger = min(100, hunger + 30);
        happiness = min(100, happiness + 10);
        triggerVibration(100);
      } else if (menuSelection == 1) {
        // PLAY
        happiness = min(100, happiness + 25);
        energy = max(0, energy - 10);
        currentPetState = STATE_HAPPY;
        // Double haptic pulse for joy
        triggerVibration(60);
        delay(80);
        triggerVibration(60);
      } else if (menuSelection == 2) {
        // SLEEP / WAKE Toggle
        if (currentPetState == STATE_SLEEPING) {
          currentPetState = STATE_IDLE;
        } else {
          currentPetState = STATE_SLEEPING;
        }
      }
      menuActive = false; 
    }
    delay(200); 
  }

  lastLeftState = currLeft;
  lastSelectState = currSelect;
  lastRightState = currRight;
}

// --- Graphics & Rendering ---
void drawPetFace() {
  tft.fillRect(10, 40, tft.width() - 20, tft.height() - 90, TFT_BLACK);

  int centerX = tft.width() / 2;
  int centerY = (tft.height() / 2) - 10;

  if (currentPetState == STATE_SLEEPING) {
    tft.fillRect(centerX - 55, centerY - 10, 35, 8, TFT_CYAN);
    tft.fillRect(centerX + 20, centerY - 10, 35, 8, TFT_CYAN);
    
    tft.setTextSize(2);
    tft.setTextColor(TFT_BLUE, TFT_BLACK);
    tft.drawString("Z", centerX + 40, centerY - 40);
    tft.drawString("z", centerX + 55, centerY - 55);
  } 
  else if (isBlinking) {
    tft.fillRect(centerX - 55, centerY - 5, 35, 6, TFT_WHITE);
    tft.fillRect(centerX + 20, centerY - 5, 35, 6, TFT_WHITE);
  } 
  else {
    uint16_t eyeColor = (currentPetState == STATE_HUNGRY) ? TFT_RED : TFT_GREEN;
    
    tft.fillRoundRect(centerX - 60, centerY - 25, 40, 50, 8, eyeColor);
    tft.fillRoundRect(centerX + 20, centerY - 25, 40, 50, 8, eyeColor);

    tft.fillCircle(centerX - 45, centerY - 10, 6, TFT_BLACK);
    tft.fillCircle(centerX + 35, centerY - 10, 6, TFT_BLACK);

    if (currentPetState == STATE_HAPPY) {
      tft.drawSmoothArc(centerX, centerY + 25, 18, 14, 0, 180, TFT_WHITE, TFT_BLACK);
    } else if (currentPetState == STATE_HUNGRY) {
      tft.fillRect(centerX - 15, centerY + 25, 30, 4, TFT_RED);
    } else {
      tft.fillCircle(centerX, centerY + 25, 4, TFT_WHITE);
    }
  }
}

void drawUI() {
  tft.drawString("H:", 10, 10, 1);
  tft.drawRect(30, 10, 60, 8, TFT_WHITE);
  tft.fillRect(31, 11, (map(hunger, 0, 100, 0, 58)), 6, TFT_RED);

  tft.drawString("F:", 100, 10, 1);
  tft.drawRect(120, 10, 60, 8, TFT_WHITE);
  tft.fillRect(121, 11, (map(happiness, 0, 100, 0, 58)), 6, TFT_YELLOW);

  tft.drawString("E:", 190, 10, 1);
  tft.drawRect(210, 10, 60, 8, TFT_WHITE);
  tft.fillRect(211, 11, (map(energy, 0, 100, 0, 58)), 6, TFT_CYAN);

  int screenW = tft.width();
  int screenH = tft.height();

  tft.fillRect(0, screenH - 30, screenW, 30, TFT_DARKGREY);
  
  if (menuActive) {
    const char* menuItems[] = {"[FEED]", "[PLAY]", "[SLEEP]"};
    tft.setTextSize(1);
    
    int startX = 35;
    for (int i = 0; i < 3; i++) {
      if (i == menuSelection) {
        tft.setTextColor(TFT_BLACK, TFT_WHITE); 
      } else {
        tft.setTextColor(TFT_WHITE, TFT_DARKGREY);
      }
      tft.drawString(menuItems[i], startX + (i * 80), screenH - 22);
    }
  } else {
    tft.setTextColor(TFT_LIGHTGREY, TFT_DARKGREY);
    tft.setTextSize(1);
    tft.drawString("Press any button to interact", screenW / 2 - 70, screenH - 22);
  }
}

// --- Haptic Feedback Control ---
void triggerVibration(int duration) {
  digitalWrite(PIN_VIBE, HIGH);
  delay(duration);
  digitalWrite(PIN_VIBE, LOW);
}