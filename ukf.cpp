#include <Eigen/Dense>
#include <iostream>
#include <vector>

class UnscentedKalmanFilter {
public:
    UnscentedKalmanFilter(int state_dim, int meas_dim)
        : state_dim_(state_dim), meas_dim_(meas_dim) {
        x_ = Eigen::VectorXd::Zero(state_dim_);
        P_ = Eigen::MatrixXd::Identity(state_dim_, state_dim_);
        Q_ = Eigen::MatrixXd::Identity(state_dim_, state_dim_);
        R_ = Eigen::MatrixXd::Identity(meas_dim_, meas_dim_);
        
        lambda_ = 3 - state_dim_;
        weights_mean_ = Eigen::VectorXd(2 * state_dim_ + 1);
        weights_cov_ = Eigen::VectorXd(2 * state_dim_ + 1);

        weights_mean_(0) = lambda_ / (state_dim_ + lambda_);
        weights_cov_(0) = weights_mean_(0) + (1 - alpha_ * alpha_ + beta_);
        for (int i = 1; i < 2 * state_dim_ + 1; ++i) {
            weights_mean_(i) = weights_cov_(i) = 0.5 / (state_dim_ + lambda_);
        }
    }

    void setProcessNoise(const Eigen::MatrixXd& Q) { Q_ = Q; }
    void setMeasurementNoise(const Eigen::MatrixXd& R) { R_ = R; }
    void setState(const Eigen::VectorXd& x) { x_ = x; }
    void setCovariance(const Eigen::MatrixXd& P) { P_ = P; }

    void predict(const Eigen::VectorXd& u, double dt) {
        auto sigma_points = generateSigmaPoints(x_, P_);
        auto transformed_sigma_points = transformSigmaPoints(sigma_points, u, dt, &UnscentedKalmanFilter::f);

        x_ = calculateMean(transformed_sigma_points);
        P_ = calculateCovariance(transformed_sigma_points, x_) + Q_;
    }

    void update(const Eigen::VectorXd& z) {
        auto sigma_points = generateSigmaPoints(x_, P_);
        auto predicted_measurements = transformSigmaPoints(sigma_points, Eigen::VectorXd(), 0, &UnscentedKalmanFilter::h);

        Eigen::VectorXd z_pred = calculateMean(predicted_measurements);
        Eigen::MatrixXd S = calculateCovariance(predicted_measurements, z_pred) + R_;

        Eigen::MatrixXd Tc = calculateCrossCovariance(sigma_points, x_, predicted_measurements, z_pred);
        Eigen::MatrixXd K = Tc * S.inverse();

        x_ = x_ + K * (z - z_pred);
        P_ = P_ - K * S * K.transpose();
    }

    Eigen::VectorXd getState() const { return x_; }

private:
    int state_dim_;
    int meas_dim_;
    double lambda_;
    double alpha_ = 1e-3; // Default value
    double beta_ = 2;     // Default value
    Eigen::VectorXd x_;
    Eigen::MatrixXd P_;
    Eigen::MatrixXd Q_;
    Eigen::MatrixXd R_;
    Eigen::VectorXd weights_mean_;
    Eigen::VectorXd weights_cov_;

    Eigen::MatrixXd generateSigmaPoints(const Eigen::VectorXd& x, const Eigen::MatrixXd& P) {
        Eigen::MatrixXd sigma_points(state_dim_, 2 * state_dim_ + 1);
        Eigen::MatrixXd sqrt_P = P.llt().matrixL();

        sigma_points.col(0) = x;
        for (int i = 0; i < state_dim_; ++i) {
            sigma_points.col(i + 1) = x + sqrt((lambda_ + state_dim_)) * sqrt_P.col(i);
            sigma_points.col(i + 1 + state_dim_) = x - sqrt((lambda_ + state_dim_)) * sqrt_P.col(i);
        }
        return sigma_points;
    }

    template <typename Func>
    Eigen::MatrixXd transformSigmaPoints(const Eigen::MatrixXd& sigma_points, const Eigen::VectorXd& u, double dt, Func f) {
        Eigen::MatrixXd transformed_sigma_points(state_dim_, sigma_points.cols());
        for (int i = 0; i < sigma_points.cols(); ++i) {
            transformed_sigma_points.col(i) = (this->*f)(sigma_points.col(i), u, dt);
        }
        return transformed_sigma_points;
    }

    Eigen::VectorXd calculateMean(const Eigen::MatrixXd& sigma_points) {
        Eigen::VectorXd mean = Eigen::VectorXd::Zero(state_dim_);
        for (int i = 0; i < sigma_points.cols(); ++i) {
            mean += weights_mean_(i) * sigma_points.col(i);
        }
        return mean;
    }

    Eigen::MatrixXd calculateCovariance(const Eigen::MatrixXd& sigma_points, const Eigen::VectorXd& mean) {
        Eigen::MatrixXd covariance = Eigen::MatrixXd::Zero(state_dim_, state_dim_);
        for (int i = 0; i < sigma_points.cols(); ++i) {
            Eigen::VectorXd diff = sigma_points.col(i) - mean;
            covariance += weights_cov_(i) * diff * diff.transpose();
        }
        return covariance;
    }

    Eigen::MatrixXd calculateCrossCovariance(const Eigen::MatrixXd& sigma_points_x, const Eigen::VectorXd& mean_x,
                                             const Eigen::MatrixXd& sigma_points_z, const Eigen::VectorXd& mean_z) {
        Eigen::MatrixXd cross_covariance = Eigen::MatrixXd::Zero(state_dim_, meas_dim_);
        for (int i = 0; i < sigma_points_x.cols(); ++i) {
            Eigen::VectorXd diff_x = sigma_points_x.col(i) - mean_x;
            Eigen::VectorXd diff_z = sigma_points_z.col(i) - mean_z;
            cross_covariance += weights_cov_(i) * diff_x * diff_z.transpose();
        }
        return cross_covariance;
    }

    // Define the state transition function
    Eigen::VectorXd f(const Eigen::VectorXd& x, const Eigen::VectorXd& u, double dt) {
        // Example for a simple constant velocity model
        Eigen::VectorXd x_new = x;
        x_new(0) += x(1) * dt + 0.5 * u(0) * dt * dt;
        x_new(1) += u(0) * dt;
        return x_new;
    }

    // Define the measurement function
    Eigen::VectorXd h(const Eigen::VectorXd& x, const Eigen::VectorXd& u, double dt) {
        // Example measurement function
        Eigen::VectorXd z(meas_dim_);
        z(0) = x(0); // Example: measuring position
        return z;
    }
};
