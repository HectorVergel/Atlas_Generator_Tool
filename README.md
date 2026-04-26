# AtlasTool

AtlasTool is a lightweight **C++ command-line texture atlas generator** created as a portfolio project focused on **Tools Development / Engine Programming**.

A texture atlas combines many small images into a single larger texture. This is commonly used in games to reduce draw calls, improve batching, and simplify asset management.

AtlasTool scans a folder of images, automatically packs them into one atlas using a rectangle packing algorithm, and exports the final result as a PNG file.

---

## Features

- Command-line workflow
- Automatic image discovery from folder
- PNG / JPG input support
- Rectangle bin packing
- Configurable atlas size
- Configurable padding between sprites
- PNG atlas export
- Basic validation (invalid images, duplicates, oversized files)

---

## Tech Stack

- **C++20**
- **CMake**
- **stb_image** / **stb_image_write**
- **rectpack2D**

---

## Build

```bash
git clone <repo_url>
cd AtlasTool
mkdir build
cd build
cmake ..
cmake --build .
```

## How to use it

```bash
AtlasTool <input_folder> --size <atlas_size> --out <output_file>
```
