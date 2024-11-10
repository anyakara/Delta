# Delta
![image](https://github.com/user-attachments/assets/7752fa2a-d8eb-4916-a07b-9c416b748f6c)
From NVIDIA DRIVE AGX Hyperion (very cool image)

## Perception Stack for the Modern Autonomous Agent
Delta is a high-performance C++ pipeline designed for real-time sensor data processing and AI model inference using ONNX Runtime and TensorRT. It's ideal for applications that require processing multiple sensor inputs (such as LiDAR, radar, and camera data) in autonomous systems, with a focus on low latency and high efficiency.

## Features
__Multi-Sensor Data Processing:__ handles data from sensors for sensor fusion (i.e. radar, LiDAR, IMU, GYRO, camera) task. Combines the encodings for a unified input for AI models.
__Real-Time Inference:__ leverages ONNX Runtime and TensorRT for optimized model execution on CPU and GPU.
__Design:__ built heavily templated at it's core, enhancing only features that can be adapted to the sensor being used with appropriate data to store.
__Data Preprocessing and Post-Processing:__ includes modules for data normalization, batching, and output interpretation. Concepts implemented for real-time embedded systems analysis.

## Prerequsites
* C++17 or higher
* CMake 3.14 or higher
* ONNX Runtime (with CUDA support for GPU inference)
* TensorRT (GPU acceleration)

## Setup
Step 1: Clone the repository:
```
git clone https://github.com/{username}/delta.git
cd delta
```
Step 2: Install dependencies: ONNX Runtime and TensorRT (if using) are installed and configured. Utilize vcpkg or another package manager to handle additional libraries. Update requirements in requirements.txt file.

Step 3: Build the project: run on bash
```
mkdir build && cd build
cmake ..
make
```
## Usage