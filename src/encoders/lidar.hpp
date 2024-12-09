#include<nvsal/sensors/LidarSensor.h>
#include<iostream>

class RealSenseLiDAR {
    public:
        RealSenseLiDAR() {
            pipeline_.start();
        }

        rs2::points getPointCloud() {
            rs2::frameset frames = pipeline_.wait_for_frames();
            rs2::frame depth = frames.get_depth_frame();

            rs2::pointcloud pc;
            rs2::points points = pc.calculate(depth);
            return points;
        }
    private:
        rs2::pipeline pipeline_;
};


// driver code for perception module
