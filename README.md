# Ant Object Tracker (C++ with OpenCV)

A simple real-time object segmentation and tracking system for ants walking on a white background. It detects ants using background subtraction (white background), applies contour-based segmentation, and draws both the **bounding boxes** and **precise object contours**.

## Features

- Works on video files or webcam
- Thresholding + Morphology for binary segmentation
- Contour-based segmentation
- Bounding box and precise outline rendering
- Easy to extend to persistent tracking or data export

## Dependencies

- OpenCV (v4.x or higher)
- C++ compiler with C++11 support

## Build Instructions

### Using CMake (recommended):

```bash
mkdir build
cd build
cmake ..
make
```

### Or compile manually:

```bash
g++ main.cpp -o ant_tracker `pkg-config --cflags --libs opencv4`
```

## Usage
### With webcam:
```bash
./ant_tracker
```
### With video file:
```bash
./ant_tracker path/to/video.mp4
```

## 🧠 How It Works
1. Converts each frame to grayscale and blurs it to reduce noise.
2. Performs inverse binary thresholding to extract dark ants on white background.
3. Applies morphological operations to clean small artifacts.
4. Detects contours and filters them based on area size.
5. Draws bounding boxes and accurate contours on the frame.

## 📈 Potential Extensions
- Multi-object tracking (with ID persistence)
- Trajectory logging in CSV/JSON
- Real-time behavior analysis
- Export as annotated datasets (e.g. COCO format)
- Replace segmentation with trained deep models (e.g. Mask R-CNN)

## 🐜 Sample Output

Green: Bounding Box
Red: Precise Contour
