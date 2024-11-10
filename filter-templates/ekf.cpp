#include <Eigen/Dense>
#include <iostream>

class ExtendedKalmanFilter {
public:
    ExtendedKalmanFilter(int state_dim, int meas_dim)
        : state_dim_(state_dim), meas_dim_(meas_dim) {
        x_ = Eigen::VectorXd::Zero(state_dim_);
        P_ = Eigen::MatrixXd::Identity(state_dim_, state_dim_);
        Q_ = Eigen::MatrixXd::Identity(state_dim_, state_dim_);
        R_ = Eigen::MatrixXd::Identity(meas_dim_, meas_dim_);
    }

    void setProcessNoise(const Eigen::MatrixXd& Q) { Q_ = Q; }
    void setMeasurementNoise(const Eigen::MatrixXd& R) { R_ = R; }
    void setState(const Eigen::VectorXd& x) { x_ = x; }
    void setCovariance(const Eigen::MatrixXd& P) { P_ = P; }

    void predict(const Eigen::VectorXd& u, double dt) {
        // State transition model
        x_ = f(x_, u, dt);
        
        // Jacobian of the state transition model
        Eigen::MatrixXd F = calculateJacobianF(x_, u, dt);
        
        // Predict the state covariance
        P_ = F * P_ * F.transpose() + Q_;
    }

    void update(const Eigen::VectorXd& z) {
        Eigen::VectorXd y = z - h(x_); // Measurement model
        Eigen::MatrixXd H = calculateJacobianH(x_); // Jacobian of the measurement model
        Eigen::MatrixXd S = H * P_ * H.transpose() + R_; // Innovation covariance
        Eigen::MatrixXd K = P_ * H.transpose() * S.inverse(); // Kalman gain
        x_ = x_ + K * y; // Update the state estimate
        P_ = (Eigen::MatrixXd::Identity(state_dim_, state_dim_) - K * H) * P_; // Update the state covariance
    }

    Eigen::VectorXd getState() const { return x_; }

private:
    int state_dim_;
    int meas_dim_;
    Eigen::VectorXd x_;
    Eigen::MatrixXd P_;
    Eigen::MatrixXd Q_;
    Eigen::MatrixXd R_;

    // Define the state transition function
    Eigen::VectorXd f(const Eigen::VectorXd& x, const Eigen::VectorXd& u, double dt) {
        // Example for a simple constant velocity model
        Eigen::VectorXd x_new = x;
        x_new(0) += x(1) * dt + 0.5 * u(0) * dt * dt;
        x_new(1) += u(0) * dt;
        return x_new;
    }

    // Define the measurement function
    Eigen::VectorXd h(const Eigen::VectorXd& x) {
        // Example measurement function
        Eigen::VectorXd z(1);
        z(0) = x(0);  // Example: measuring position
        return z;
    }

    // Calculate the Jacobian of the state transition function
    Eigen::MatrixXd calculateJacobianF(const Eigen::VectorXd& x, const Eigen::VectorXd& u, double dt) {
        Eigen::MatrixXd F = Eigen::MatrixXd::Identity(state_dim_, state_dim_);
        F(0, 1) = dt;
        return F;
    }

    // Calculate the Jacobian of the measurement function
    Eigen::MatrixXd calculateJacobianH(const Eigen::VectorXd& x) {
        Eigen::MatrixXd H = Eigen::MatrixXd::Zero(meas_dim_, state_dim_);
        H(0, 0) = 1.0;
        return H;
    }
};

