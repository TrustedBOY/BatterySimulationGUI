# Battery Pack Simulator

## Project Overview
This project is a C++ Qt Application that simulates the electrical behavior of a battery pack. It allows users to dynamically construct a pack of individual battery cells, configure their connection type (Series vs. Parallel), and visualize the results of discharging and recharging over time.

This project was generated using the **C++ Project Maker Script** by TrustedBOY.  
It provides a clean, modular structure with `src/`, `include/`, and `CMake` build support.

---

## 🚀 Getting Started

### 1️⃣ Build the project

```bash
mkdir build
```
```bash
cd build
```
```bash
cmake ..
```
```bash
make
```

The compiled executable will be located in:

build/bin/App

Run it with:
```bash
./bin/App
```

ProjectName(App) can be change in CMakeLists.txt

## Key Features
* **Dynamic Battery Creation:** Users can add batteries with custom **Voltage**, **Capacity**, and **Initial Charge** values.
* **Flexible Configurations:**
    * **Series (Vertical):** Voltage adds up; Capacity is limited by the smallest battery.
    * **Parallel (Horizontal):** Capacity adds up; Voltage remains constant.
* **Interactive Simulation:**
    * **Dynamic Time Control:** Users can input a specific duration (in hours) using a precise spin box to simulate usage or recharging.
    * **Physics Logic:** Calculates charge depletion based on discharge rates and prevents overcharging or negative charge.
* **Visual Feedback:**
    * **Color-Coded Status:** Batteries change color based on charge level:
        * <span style="color:green">**Green**</span>: > 50%
        * <span style="color:orange">**Orange**</span>: > 20%
        * <span style="color:red">**Red**</span>: < 20%
    * **Real-Time Drawing:** The canvas automatically redraws to show the correct layout (stacked for Series, side-by-side for Parallel).
    * **Interactive Deletion:** Clicking on a battery in the visualization instantly removes it from the pack.

## Code Architecture
The application follows Object-Oriented Programming (OOP) principles, utilizing inheritance, polymorphism, and the Qt Framework for the GUI.

### 1. Core Logic (`Battery` & `BatteryPack`)
* **`Battery` (Base Class):**
    * Represents a single electrochemical cell.
    * Handles the basic math for `use()` (drain) and `recharge()` (fill) using defined rates (`DISCHARGE_RATE = 100`, `RECHARGE_RATE = 150`).
    * Contains safeguards to ensure charge never exceeds capacity or drops below zero.
* **`BatteryPack` (Derived Class):**
    * Inherits from `Battery` but acts as a container (Composite Pattern).
    * Manages a `std::vector<Battery*>` of cells.
    * **Polymorphism:** Overrides standard getters (`getVoltage`, `getCapacity`) to apply electrical laws based on the `ConnectionType`:
        * **Series Mode:** Returns the sum of voltages.
        * **Parallel Mode:** Returns the sum of capacities.

### 2. Visualization (`BatteryCanvas`)
* **Custom Widget:** Inherits from `QWidget` to perform custom 2D graphics.
* **Dynamic Rendering:** Inside `paintEvent`, it iterates through the battery pack and calculates the exact screen coordinates for each cell based on the selected mode (Series vs. Parallel).
* **Mouse Interaction:** Implements `mousePressEvent` to detect if a user clicks on a specific battery's rectangle, triggering its deletion.

### 3. User Interface (`MainWindow`)
* **Central Hub:** Connects the logic (backend) with the visualizer (frontend).
* **Signal & Slots:** Uses Qt's event system to handle user inputs (e.g., clicking "Add Battery" or changing the "Hours" spin box) and instantly update the simulation state.
* **Memory Management:** Tracks all created battery pointers to ensure proper memory cleanup upon application exit.

## Usage
1.  **Add Batteries:** Enter voltage and capacity on the left panel and click "Add Battery".
2.  **Configure Pack:** Use the dropdown to switch between **Series** and **Parallel** modes.
3.  **Simulate:** Enter a time duration in the "Hours" box, then click **Use** to drain power or **Recharge** to restore it.
4.  **Edit:** Click directly on any battery in the diagram to remove it.

## Dependencies
* C++11 or higher
* Qt 5 or Qt 6 Framework
* CMake (optional, for building)
* CMake 3.10+
