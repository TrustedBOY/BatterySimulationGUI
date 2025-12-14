# C++ Project Template

This project was generated using the **C++ Project Maker Script** by TrustedBOY.  
It provides a clean, modular structure with `src/`, `include/`, and `CMake` build support.

---

## 🚀 Getting Started

### 1️⃣ Build the project

```bash
mkdir build
cd build
cmake ..
make

The compiled executable will be located in:

build/bin/App

Run it with:

./bin/App

ProjectName(App) can be change in CMakeLists.txt

🧱 Project Structure

ProjectName/
├── src/             # Source files (.cpp)
├── include/         # Header files (.h / .hpp)
├── build/           # Build output (not tracked in Git)
├── .gitignore       # Ignore compiled files and build folders
├── CMakeLists.txt   # CMake configuration
└── README.md        # Project documentation

🧩 Requirements

    C++17 or later

    CMake 3.10+

    GCC / Clang / MSVC
