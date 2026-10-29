<h1>Joseppe!</h1>

<h3>Hey there!</h3>
Virtual pets from the 90s always intrigued me, and i've wanted one ever since I saw the tamagotchi but never got my hands on one cuz it was too expensive or not available for purchase and so I decided to build my own.
So here's Joseppe my own virtual pet!

## Features

### 1. Interactive Pet Lifecycle & Core Stats
* **Real-time Stat Decay:** The pet's **Hunger**, **Happiness**, and **Energy** degrade automatically over time via a non-blocking tick loop.
* **Dynamic States:** The pet transitions across multiple autonomous states (`IDLE`, `HUNGRY`, `SLEEPING`, `HAPPY`) depending on how well it is cared for.
* **Smart Sleep Management:** When energy levels drop critically low, the pet automatically enters a sleeping state to passively recover energy over time.

### 2. Procedural Facial Animations & Expressions
* **Dynamic Eye Rendering:** Dual animated eyes rendered natively via SPI instructions that shift colors and expressions based on mood (e.g., green when healthy, flashing red when starving or low on stats).
* **Automated Blinking:** Periodic random blinking intervals make the digital companion feel alive.
* **Emotive States:** Displays animated expressions including floating "Zzz" marks while resting, joyful arc smiles, or flat warning lines when unhappy.

### 3. Interactive 3-Button Menu System
* **Seamless Navigation:** Use the **Left** and **Right** buttons to dynamically cycle through footer actions (`[FEED]`, `[PLAY]`, `[SLEEP]`).
* **Action Confirmation:** Pressing the **Select** center button executes the highlighted choice:
  * **`[FEED]`**: Boosts hunger levels and improves happiness.
  * **`[PLAY]`**: Increases happiness at the cost of slight energy depletion, triggering a joyful expression.
  * **`[SLEEP]`**: Manually toggles sleep or wake states on demand.

### 4. Haptic Feedback Integration
* **Tactile Responses:** Integrated coin vibration motor triggers distinct haptic pulses and double-taps to confirm button clicks, successful menu actions, and startup sequences.

<h1>CAD</h1>

<img width="1920" height="722" alt="af597854-a211-4d1d-8939-3bf9ae8501c2" src="https://github.com/user-attachments/assets/7da5f154-5f44-4097-9838-473eebb5d43d" />

<img width="1920" height="722" alt="Joseppe_(Assembly)_2026-Oct-29_11-34-24AM-000_CustomizedView14371881487" src="https://github.com/user-attachments/assets/0576e09c-d015-46f0-9a0a-879e28d230f2" />

<h1>PCB</h1>

<img width="1279" height="672" alt="PCBRedesign#1" src="https://github.com/user-attachments/assets/6c0bf63e-f1cc-4e89-9f99-d96142b9a5ef" />

<img width="858" height="511" alt="PCBCircuitRedesign#1" src="https://github.com/user-attachments/assets/badf96cb-3b61-4888-9cb3-a2f497d71ee1" />

## Bill of Materials (BOM)

| Component | Qty | Source | Price (USD) | Link |
| :--- | :---: | :---: | :---: | :--- |
| **Seeed Studio XIAO ESP32-C3** | 1 | Online | $8.71 | [Robu.in](https://robu.in/product/seeed-studio-xiao-esp32c3-tiny-mcu-board-with-wi-fi-and-ble-battery-charge-supported-power-efficiency-and-rich-interface/) |
| **2.25-inch SPI TFT Screen** | 1 | Online | $5.56 | [Robu.in](https://robu.in/product/225-inch-tft-lcd-st7789-small-screen-76284-module-lcd-full-view-spi-color-screen-with-soldering/) |
| **Standard 6x6mm Tactile Switch** | 3 | Local | ~$5.00 | Local Market |
| **Passive Buzzer** | 1 | Online | $0.53 | [Robu.in](https://robu.in/product/1-month-warranty-1248/) |
| **LiPo Battery (3.7V 2500mAh)** | 1 | Online | $6.61 | [Robu.in](https://robu.in/product/wly104050-2500mah-3-7v-single-cell-rechargeable-lipo-battery/) |
| **3D Printed Case & Button Caps** | 1 set | Online | ~$11.00 | Robu.in |
| **M3 Screws (16mm length)** | 4 | Local | $1.00 | Local Market |
| **Custom PCB Board** | 1 | Online | ~$3.00 | [JLCPCB](https://jlcpcb.com/) |
| **TP4056 Charging Module** | 1 | Online | $0.20 | [Robu.in](https://robu.in/product/tp4056-1a-li-ion-lithium-battery-charging-module-with-current-protection-type-c/) |
| **Subtotal (Online Purchases)** | **7** | **Online** | **~$25.61** | — |
| **Subtotal (Local Purchases)** | **2** | **Local** | **~$6.00** | — |
| **Grand Total** | **14 pcs** | **All** | **~$31.61** | — |
