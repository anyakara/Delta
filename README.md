# Delta
![image](https://github.com/user-attachments/assets/7752fa2a-d8eb-4916-a07b-9c416b748f6c)
(Adopted image from NVIDIA DRIVE AGX Hyperion)

## Perception Stack for the Modern Autonomous Agent
Delta is a high-performance C++ pipeline designed for real-time sensor data processing and AI model inference using ONNX Runtime and TensorRT. It's ideal for applications that require processing multiple sensor inputs (such as LiDAR, radar, and camera data) in autonomous systems, with a focus on low latency and high efficiency.

Originally, was to be incorporated into EV racecar at university, was offered the resources to execute but team had different requirements, thus decided to write the high-level stack that in theory would be applicable to an autonomous EV. After assisting my seniors in remapping the entire car with a new Hercules board, I learned valuable information regarding the car's layout and optimal sensor placement. Additionally, asked the team lead and professor about the inclusion of AI to process the car's sensor data to be displayed on the dash, but that plan was dropped. This stack reflects my understanding of the components required to build an optimal EV perception stack.

## Features
* __Multi-Sensor Data Processing:__ handles data from sensors for sensor fusion (i.e. radar, LiDAR, IMU, GYRO, camera) task. Combines the encodings for a unified input for AI models.
* __Real-Time Inference:__ leverages ONNX Runtime and TensorRT for optimized model execution on CPU and GPU.
* __Design:__ built heavily templated at it's core, enhancing only features that can be adapted to the sensor being used with appropriate data to store.
* __Data Preprocessing and Post-Processing:__ includes modules for data normalization, batching, and output interpretation. Concepts implemented for real-time embedded systems analysis.

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
### Running Inference on Sensor Data
In summary, Delta allows systems engineers to process and run inference on sensor data, such as LiDAR, radar, and camera inputs through a streamlined pipeline.
1. Prepare sensor data: input data from sensors should be stored in compatible format (e.g. .bin or .csv).
2. Run the application:
```
./delta path/to/sensor_data_file
```

### Code High Level Overview
The stack comprises of the following main components.
* __SensorData:__ defines structures and methods for acquiring and preprocessing data from sensors.
* __InferenceEngine:__ loads AI model and runs inference using ONNX Runtime or TensorRT.
* __FusionModule:__ combines data from multiple sensors and applies filter models (provided in filters stack) or other fusion methods.
* __TasksScheduler+:__ uses OS processes to manage task execution priority, ensuring real-time performance.

### Configuration
Edit configuration settings in `config.yml` to specify paths for models, set GPU options, change sensor data parameters.

## Performance Optimization
To achieve higher performance, Delta can be configured to:
* __Enable CUDA Support__ in ONNX Runtime and TensorRT and GPU inference.
* __Adjust batch sizes__ and input shapes for specified models to improve throughput.
* __Utilize priority scheduling__ to maintain real-time performance for high-priority tasks.

## Contributing
Contributions are welcome! Please create an issue or pull request if you have suggestions or improvements.

## License
This project is licensed under the MIT License. See LICENSE for details.
