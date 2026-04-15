<div align="center">

<br/>

<!-- BANNER -->
<picture>
  <source media="(prefers-color-scheme: dark)" srcset="https://readme-typing-svg.demolab.com?font=Fira+Code&weight=700&size=42&pause=1000&color=00C8FF&center=true&vCenter=true&width=700&lines=Image+Processor" />
  <img src="https://readme-typing-svg.demolab.com?font=Fira+Code&weight=700&size=42&pause=1000&color=0077CC&center=true&vCenter=true&width=700&lines=Image+Processor" alt="Image Processor" />
</picture>

### *Where pixel manipulation meets modern C++*

<br/>

<!-- BADGES -->
[![Language](https://img.shields.io/badge/Language-C%2B%2B20-blue?style=for-the-badge&logo=cplusplus&logoColor=white)](https://en.cppreference.com/w/cpp/20)
[![Build](https://img.shields.io/badge/Build-CMake-red?style=for-the-badge&logo=cmake&logoColor=white)](https://cmake.org/)
[![Standard](https://img.shields.io/badge/Standard-C%2B%2B20-orange?style=for-the-badge)](https://isocpp.org/)
[![Library](https://img.shields.io/badge/Library-stb__image-green?style=for-the-badge)](https://github.com/nothings/stb)
[![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey?style=for-the-badge&logo=linux)](https://cmake.org/)
![Formats](https://img.shields.io/badge/Formats-JPG%20%7C%20PNG%20%7C%20BMP%20%7C%20TGA-purple?style=for-the-badge)

<br/>

<!-- NAVIGATION PILLS -->
[ Overview](#-overview) &nbsp;•&nbsp;
[ Features](#-features) &nbsp;•&nbsp;
[ Architecture](#️-architecture) &nbsp;•&nbsp;
[ Build](#️-build) &nbsp;•&nbsp;
[ Usage](#-usage) &nbsp;•&nbsp;
[ Filters Gallery](#-filters-gallery) &nbsp;•&nbsp;
[ Contributors](#-contributors)

<br/>

---

</div>

##  Overview

**Image Processor** is a feature-rich, console-based image manipulation tool written in **C++20**. It is built on the lightweight [`stb_image`](https://github.com/nothings/stb) single-header library, giving it zero heavy-weight dependencies while supporting the most common image formats.

Load any photo, apply one or more filters/transformations interactively from the terminal menu, and save the result — all without installing a single external framework.

---

##  Features

<div align="center">

| # | Feature | Description |
|---|---------|-------------|
| 1 |  **Load Image** | Load any supported image from disk |
| 2 |  **Grayscale** | Convert image to greyscale using average channel intensity |
| 3 |  **Black & White** | Hard threshold (≥128 → white, <128 → black) |
| 4 |  **Invert** | Invert every channel value (`255 − value`) |
| 5 |  **Merge Images** | Blend two images (same size or auto-resize / crop to common area) |
| 6 |  **Flip** | Horizontal or vertical mirror flip |
| 7 |  **Rotate** | Rotate 90°, 180°, or 270° clockwise |
| 8 |  **Darken / Lighten** | Adjust brightness by a percentage |
| 9 |  **Crop** | Extract a rectangular region |
| 10 |  **Frame** | Add a decorative border (4 styles) |
| 11 |  **Edge Detection** | Sobel operator edge detection |
| 12 |  **Resize** | Scale to any width × height (nearest-neighbour) |
| 13 |  **Blur** | Box blur with adjustable radius (0–100 scale) |
| 14 |  **Sunlight Effect** | Warm, sun-drenched colour grading |
| 15 |  **Night Effect** | Cool blue-toned night colour grading |
| 16 |  **Skew** | Horizontal shear / skew by percentage |
| 17 | **Save Image** | Save to `.jpg`, `.png`, `.bmp`, or `.tga` |

</div>

---

##  Architecture

```
Image-Processor/
├── CMakeLists.txt           # CMake build configuration (C++20)
├── Image_Class.h            # Image class — load, save, pixel access
├── stb_image.h              # stb single-header image decoder
├── stb_image_write.h        # stb single-header image encoder
├── ImageProcessingDemo.cpp  # All filters + interactive main menu
├── FRAME.jpg                # Decorative frame asset (style 4)
└── luffy.jpg                # Sample image for quick testing
```

### Class overview — `Image`

```
Image
├── Constructors
│   ├── Image()                       — default
│   ├── Image(string filename)        — load from file
│   ├── Image(int width, int height)  — blank canvas
│   └── Image(const Image& other)     — deep copy
├── Pixel Access
│   ├── getPixel(x, y, channel)
│   ├── setPixel(x, y, channel, value)
│   └── operator()(row, col, channel)
└── I/O
    ├── loadNewImage(filename)
    └── saveImage(outputFilename)
```

Supported formats: **`.jpg`** · **`.jpeg`** · **`.png`** · **`.bmp`** · **`.tga`**

---

## ⚙️ Build

### Prerequisites

| Tool | Minimum Version |
|------|----------------|
| CMake | 3.29 |
| C++ Compiler (GCC / Clang / MSVC) | C++20 support |

### Steps

```bash
# 1. Clone the repository
git clone https://github.com/Ebrahem-Hassan-shabaan/Image-Processor.git
cd Image-Processor

# 2. Configure
cmake -B build -DCMAKE_BUILD_TYPE=Release

# 3. Build
cmake --build build --config Release

# 4. Run
./build/ImageFilters          # Linux / macOS
build\Release\ImageFilters.exe  # Windows
```

---

## Usage

When you launch the program, it first asks you to load an image, then presents an interactive menu:

```
Welcome to the Our Image Processor!
Please enter the filename of the image to load (e.g., photo.jpg): luffy.jpg

Please select an option:
 1. Load New Image
 2. Grayscale Filter
 3. Black and White filter
 4. Invert Image
 5. Merge Images
 6. Flip Image
 7. Rotate Image
 8. Darken and Lighten Image
 9. Crop Image
10. Frame
11. Edge Detecting
12. Resize Image
13. Blur Filter
14. Sun Light Effect
15. Night Effect
16. Skew Image
17. Save Image
18. Exit
Enter choice:
```

**Typical workflow:**

```
Load image → apply filters in any order → save result → exit
```

### Example session

```
Enter choice: 2          ← apply Grayscale
Enter choice: 13         ← apply Blur
  Please enter blur scale (a value from 0 to 100): 40
Enter choice: 17         ← save
  Please enter the filename to save your image as (e.g., result.png): result.png
  Image saved successfully!
Enter choice: 18         ← exit
```

---

##  Filters Gallery

### Grayscale & Black-and-White
> Grayscale averages the three channels. Black & White then thresholds at 128.

```
Original  →  Grayscale  →  Black & White
 (RGB)       (grey avg)    (hard threshold)
```

### Edge Detection
> Uses a **Sobel operator** — computes horizontal (Gx) and vertical (Gy) gradients, then `|G| = √(Gx²+Gy²)`. Pixels with gradient ≥ 128 become black (edge), the rest white.

### Blur
> Two-pass **box blur** (horizontal then vertical). Radius is mapped from a 0–100 user scale to an internal kernel half-width of 0–40 pixels.

### Lighting Effects

| Effect | Description |
|--------|-------------|
|  Sunlight | Boosts red by `brightness/3` and green by `brightness/4` |
|  Night | Applies a colour matrix emphasising blue tones |
|  Darken/Lighten | Multiplies every channel by `1 ± (percent/100)` |

### Frame Styles

| Style | Description |
|-------|-------------|
| 1 – Simple | Single solid-colour border (20 px) |
| 2 – Double | Outer + inner border with contrasting colours |
| 3 – Elegant | Matte outer frame with spaced inner white lines |
| 4 – Decorative | Overlays `FRAME.jpg` asset on the image |

### Merge Options
When the two images differ in size you can choose:
- **Resize to fit** — enlarge the smaller image to match the largest
- **Common area** — merge only the overlapping top-left region

---

##  Contributors

| Name | Role |
|------|------|
| **Ebrahem Hassan** | Grayscale, Load/Save, Edge Detection, Resize, Merge, Sunlight, Main Menu |
| **Mohamed Abdelmaqsoud** | Black & White, Flip, Darken/Lighten, Crop, Skew |
| **Youssef Ibrahim** | Invert, Blur, Night Effect, Rotate, Frame |
| **Shehab Diab** | Image Class design |
| **Nada Ahmed** | Image Class design |
| **Dr. Mohamed El-Ramely** | Academic Supervision |

> Faculty of Computers and Artificial Intelligence (FCAI), Cairo University  
> Image Class v2.0 — 27 March 2024

---

<div align="center">



[![C++](https://img.shields.io/badge/C%2B%2B20-✓-blue?style=flat-square&logo=cplusplus)](https://isocpp.org/)
[![stb_image](https://img.shields.io/badge/stb__image-✓-green?style=flat-square)](https://github.com/nothings/stb)
[![CMake](https://img.shields.io/badge/CMake-✓-red?style=flat-square&logo=cmake)](https://cmake.org/)

</div>
