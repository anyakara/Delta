# Image Processing
Image processing &amp; parallelization modules in C/C++ with CUDA for camera feeds. 

## Purpose
Sensor-based systems in self-driving cars utilize camera feeds to make decisions about current state and response to environmental changes. Computer Vision is the primary choice for companies like Tesla for visual perception and self-driving tasks. State estimation will provide an autonomous system ability to approximate conditions to make predictive decisions. Visual perception allows for the system to observe the environment and make decisions based on that information. We want to build a pipeline that can process camera feeds, preferrably in real-time, extract features and classify/segment (depending on the task) the image for corrective action and return output.

## Architecture
![Screenshot 2024-04-27 at 2 16 02 PM](https://github.com/anyakara/Image-Processing/assets/66985689/79044398-14f2-4f1a-9df9-54401ff0e203)

This pipeline can be reused for image processing in general, as modules that are built for image processing, including the small linear algebra framework for image feature extraction task and the process parallelization with CUDA framework. The modules can be used for an existing system where real time camera feeds are being serialized by a microcontroller, and the serialized information can be used for segmentation task down the line. The architecture includes the following:
### Custom library built for operations with linear algebra in C++
In this module, we will work with data structures that make linear algebra computations abstracted for general, high-level application/use case.

### Filters Directory
Depending on the task, different filters may be more useful for feature extraction, the most common will be provided.

### Image Classification/Segmentation
This is a cumulation of NVIDIA's course material for CNN's, PyTorch documenation & the course on Visual Perception of Self-Driving Cars. Material is **applied** as tools written in Python. Again, depending on the task, different types of models may be used for classification and segmentation.
