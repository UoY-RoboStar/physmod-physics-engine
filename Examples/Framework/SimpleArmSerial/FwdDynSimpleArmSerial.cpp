#include <iostream>
#include <Eigen/Dense>
#include <string>
#include <vector>

Eigen::Block<Eigen::Matrix<double, -1, 1>> SKOv(Eigen::VectorXd& systemVector, int x) {
    return systemVector.block(6 * x, 0, 6, 1); // Extracts a 6-element block starting at index 6*x
}


Eigen::Block<Eigen::MatrixXd> SKOm(Eigen::MatrixXd& systemMatrix, int x, int y) {
    return systemMatrix.block(6 * x, 6 * y, 6, 6);
}


//The following code is the result of techniques 4 and 5:

// datatypes
struct Frame {
    int number;                  // Integer to store the frame number
    Eigen::Matrix4d transform;   // 4x4 matrix for the transformation
    // Constructor to initialize the Frame
    Frame(int num, const Eigen::Matrix4d& mat) : number(num), transform(mat) {}
};

Eigen::Vector3d getFramePosition(int k, const std::vector<Frame>& Bn) {
    for (const Frame& Bk : Bn) {
        if (Bk.number == k) {
             Eigen::Vector3d framePosition = Bk.transform.block<3, 1>(0, 3);
                std::cout << "Frame Position: " << framePosition << std::endl;
                return framePosition;
        }
    }
    // If no such frame is found, throw an exception
    throw std::out_of_range("No frame with the specified number found");
}  
Eigen::Matrix3d skewSymmetric(const Eigen::Vector3d& vec) {
    Eigen::Matrix3d mat;
    mat <<     0, -vec.z(),  vec.y(),
            vec.z(),     0, -vec.x(),
           -vec.y(),  vec.x(),     0;
    return mat;
}
Eigen::MatrixXd SKO_cross(const Eigen::Matrix<double, 6, 1>& v) {
    Eigen::MatrixXd cross(6, 6);
    cross.setZero();
    
    // Top-left 3x3 block is the skew-symmetric matrix of the angular part
    cross.block<3, 3>(0, 0) = skewSymmetric(v.head<3>());
    
    // Top-right 3x3 block is the skew-symmetric matrix of the linear part
    cross.block<3, 3>(0, 3) = skewSymmetric(v.tail<3>());
    
    // Bottom-left and bottom-right 3x3 blocks remain zero
    return cross;
}

Eigen::MatrixXd SKO_bar(const Eigen::VectorXd& v) {
    assert(v.size() == 6 && "Input vector must be of size 6");
    Eigen::MatrixXd result(6, 6);
    result.setZero();

    // Filling the skew-symmetric matrix
    result(0, 1) = -v(2);
    result(0, 2) = v(1);
    result(1, 0) = v(2);
    result(1, 2) = -v(0);
    result(2, 0) = -v(1);
    result(2, 1) = v(0);

    result(3, 4) = -v(5);
    result(3, 5) = v(4);
    result(4, 3) = v(5);
    result(4, 5) = -v(3);
    result(5, 3) = -v(4);
    result(5, 4) = v(3);

    return result;
}
// Function to create a 3x3 skew-symmetric matrix


Eigen::Vector3d l(const Eigen::Vector3d& Pose1, const Eigen::Vector3d& Pose2) {
    Eigen::Vector3d result;
    
    result = Pose1 - Pose2;
    std::cout << "l: " << result << std::endl;
    return result;
}

Eigen::MatrixXd lx(const Eigen::Vector3d& x, const Eigen::Vector3d& y) {
    Eigen::Vector3d v = l(x, y);
    Eigen::Matrix3d result;
    result << 0, -v(2), v(1),
              v(2), 0, -v(0),
              -v(1), v(0), 0;
    std::cout << "lx: " << result << std::endl;
    return result;
}


Eigen::MatrixXd CalcPhi(int m, int n, const std::vector<Frame>& B_k) {
    Eigen::MatrixXd phi = Eigen::MatrixXd::Zero(6, 6);

    // Block (1,1): 3x3 identity matrix
    phi.block<3, 3>(0, 0) = Eigen::Matrix3d::Identity();

    // Block (1,4): lx(getFramePosition(m, B_k), getFramePosition(n, B_k))
    phi.block<3, 3>(0, 3) = lx(getFramePosition(m, B_k), getFramePosition(n, B_k));

    // Block (4,1): 3x3 identity matrix
    phi.block<3, 3>(3, 0) = Eigen::Matrix3d::Identity();

    return phi;
}

// State variables
class State {
public:
    // State variables required for solution
    Eigen::VectorXd tau;
    int n;
    int N;
    double h;
    Eigen::MatrixXd M_spatial;
    Eigen::MatrixXd M;
    Eigen::MatrixXd M_inv;
    Eigen::MatrixXd phi;
    Eigen::Matrix<double, 2, 18> H;
    Eigen::VectorXd dd_theta;
    Eigen::VectorXd d_theta;
    Eigen::VectorXd theta;
    Eigen::VectorXd alpha;
    Eigen::VectorXd V;
    Eigen::VectorXd a;
    Eigen::VectorXd b;
    Eigen::VectorXd f;
    Eigen::VectorXd C;
    Eigen::Matrix4d T_21;
    Eigen::Matrix4d T_32;
    Eigen::Matrix4d T_p3;
    std::vector<Frame> Bk;

    // Constructor
    State() : tau(Eigen::VectorXd::Zero(2)),
              n(3),
              N(2),
              h(0.1),
              M_spatial(Eigen::MatrixXd::Zero(18, 18)),              
              M(Eigen::MatrixXd::Zero(2, 2)),
              M_inv(Eigen::MatrixXd::Zero(2, 2)),
              phi(Eigen::MatrixXd::Zero(18, 18)),
              H(Eigen::Matrix<double, 2, 18>::Zero()),
              dd_theta(Eigen::VectorXd::Zero(2)),
              d_theta(Eigen::VectorXd::Zero(2)),
              theta(Eigen::VectorXd::Zero(2)),
              alpha(Eigen::VectorXd::Zero(18)),
              V(Eigen::VectorXd::Zero(18)),
              a(Eigen::VectorXd::Zero(18)),
              b(Eigen::VectorXd::Zero(18)),
              f(Eigen::VectorXd::Zero(18)),
              C(Eigen::VectorXd::Zero(2)){
                SKOm(M_spatial, 0,0) << 0.0208, 0, 0, 0, 0, 0,
                        0, 0.0208, 0, 0, 0, 0,
                        0, 0, 0.0208, 0, 0, 0,
                        0, 0, 0, 0.5, 0, 0,
                        0, 0, 0, 0, 0.5, 0,
                        0, 0, 0, 0, 0, 0.5;
                SKOm(M_spatial, 1,1) << 1.349, 0, 0, 0, 0, 0,
                        0, 1.349, 0, 0, 0, 0,
                        0, 0, 1.349, 0, 0, 0,
                        0, 0, 0, 1, 0, 0,
                        0, 0, 0, 0, 1, 0,
                        0, 0, 0, 0, 0, 1;
                SKOm(M_spatial, 2,2) << 10.417, 0, 0, 0, 0, 0,
                        0, 10.417, 0, 0, 0, 0,
                        0, 0, 10.417, 0, 0, 0,
                        0, 0, 0, 100, 0, 0,
                        0, 0, 0, 0, 100, 0,
                        0, 0, 0, 0, 0, 100;
                T_21 << 1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 4.75,
                0, 0, 0, 1;

        T_32 << 1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 2.5,
                0, 0, 0, 1;

        T_p3 << 1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0.25,
                0, 0, 0, 1;
              
        H << 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
             0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0; 

        Bk.push_back(Frame(1, T_21));
        Bk.push_back(Frame(2, T_32));
        Bk.push_back(Frame(3, T_p3));
              }
};

// Updates the state variables for a solution method
 void solution(State& state) {
    //Preprocess state variables for solution
    
    //Step 1:
    state.tau << 1.0, 0.0;
    std::cout << "tau " << std::endl << state.tau << std::endl;

    //Step 2:

    SKOm(state.phi, 0 ,0) = Eigen::MatrixXd::Identity(6, 6);
    SKOm(state.phi, 1 ,0) = CalcPhi(2, 1, state.Bk);
    SKOm(state.phi, 1,1) = Eigen::MatrixXd::Identity(6, 6);
    SKOm(state.phi, 2,0) = CalcPhi(3, 1, state.Bk);
    SKOm(state.phi, 2,1) = CalcPhi(3, 2, state.Bk);
    SKOm(state.phi, 2,2) = Eigen::MatrixXd::Identity(6, 6);

    std::cout << "Matrix phi:\n" << state.phi << std::endl;

    //Step 3:
    Eigen::VectorXd v_delta = Eigen::VectorXd::Zero(6 * state.n);
    Eigen::VectorXd f_zero = Eigen::VectorXd::Zero(6);
    Eigen::VectorXd d_theta(state.N +1);
    d_theta << state.d_theta, 0.0;
   for (int k = state.n - 2; k >= 0; --k) {
        SKOv(state.V, k) = (SKOm(state.phi, k + 1, k)).adjoint() * SKOv(state.V, k + 1) + state.H.block(k,6*k,1,6).adjoint() * state.d_theta(k);
        SKOv(v_delta, k) = state.H.block(k,6*k,1,6).adjoint() * state.d_theta(k);
        SKOv(state.a, k) = SKO_cross(SKOv(state.V, k)) * SKOv(v_delta, k);
        SKOv(state.alpha, k) = (SKOm(state.phi, k + 1, k)).adjoint() * SKOv(state.alpha, k + 1) + SKOv(state.a, k);
    }

    int k = 0;
    SKOv(state.b, k) = SKO_bar(SKOv(state.V, k)) * SKOm(state.M_spatial,k,k) * SKOv(state.V, k); 
    SKOv(state.f, k) = SKOm(state.phi, k + 1, k).adjoint() * f_zero + SKOm(state.M_spatial,k,k) * SKOv(state.alpha, k) + SKOv(state.b, k);
    state.C(k) =  (state.H.block(0,6*0,1,6) * SKOv(state.f, k))(0,0);

    for (int k = 1; k <= state.n-2; ++k) {
        SKOv(state.b, k) = SKO_bar(SKOv(state.V, k)) * SKOm(state.M_spatial,k,k) * SKOv(state.V, k); 
        SKOv(state.f, k) = SKOm(state.phi, k + 1, k).adjoint() * SKOv(state.f, k - 1) + SKOm(state.M_spatial,k,k) * SKOv(state.alpha, k) + SKOv(state.b, k);
        state.C(k) =  (state.H.block(k,6*k,1,6) * SKOv(state.f, k))(0,0);
    }
    
    std::cout << "C: " << state.C << std::endl;

    //Step 4:
    Eigen::MatrixXd R = Eigen::MatrixXd::Zero(6 * state.n, 6 * state.n);
    Eigen::VectorXd X = Eigen::VectorXd::Zero(6 * state.n);
    for (int k = 0; k <= state.n - 2; k++) {
        if (k == 0) {
            SKOm(R, k, k) = SKOm(state.M_spatial, k, k);
        } else {
            SKOm(R, k, k) = SKOm(state.phi, k, k-1) * SKOm(R, k-1, k-1) * SKOm(state.phi, k, k-1).adjoint() + SKOm(state.M_spatial, k, k);
        }
         std::cout << "R" << SKOm(R, k, k) << std::endl;
         std::cout << "H*(k): " << state.H.block(k,6*k,1,6).adjoint() << std::endl;
         SKOv(X, k) = SKOm(R, k, k) * state.H.block(k,6*k,1,6).adjoint();
         std::cout << "X" << SKOv(X, k) << std::endl;
        state.M(k, k) = (state.H.block(k,6*k,1,6) * SKOv(X, k))(0, 0);

        for (int j = k+1; j <= state.n - 2; j++) {
            SKOv(X, j) = SKOm(state.phi, j, j-1) * SKOv(X, j-1);
            std::cout << "X: " << SKOv(X, j) << std::endl;
            state.M(j, k) = (state.H.block(k,6*k,1,6) * SKOv(X, j))(0, 0);
            state.M(k, j) = state.M(j, k); 
        }
    }
    std::cout << "M: " << state.M << std::endl;

    //Step 5:
    Eigen::MatrixXd oldMass;
    oldMass = state.M;
    Eigen::LDLT<Eigen::MatrixXd> ldlt(state.M);
    if(ldlt.info() == Eigen::Success) {
        state.M_inv = ldlt.solve(Eigen::MatrixXd::Identity(state.M.rows(), state.M.cols()));
    } else {
        std::cout << "Decomposition was not successful. The provided matrix might not be positive definite." << std::endl;
    }
    std::cout << "M_inv " << std::endl << state.M_inv << std::endl;

    //Step 6:
    state.dd_theta = state.M_inv * (state.tau - state.C);
    std::cout << "dd_theta " << std::endl << state.dd_theta << std::endl;

    //Step 7:
    state.d_theta = state.d_theta + state.h * state.dd_theta;
    std::cout << "d_theta " << std::endl << state.d_theta << std::endl;

    //Step 8:
    state.theta = state.theta + state.h * state.d_theta;
    std::cout << "theta " << std::endl << state.theta << std::endl;

    //Step 9:
    state.T_21 << cos(state.theta(0)), -sin(state.theta(0)), 0, 0,
                sin(state.theta(0)), cos(state.theta(0)), 0, 0,
                0, 0, 1, 4.75,
                0, 0, 0, 1;
    
    std::cout << "T_21 " << std::endl << state.T_21 << std::endl;

    //Step 10:
    state.T_32 << cos(state.theta(1)), -sin(state.theta(1)), 0, 0,
                sin(state.theta(1)), cos(state.theta(1)), 0, 0,
                0, 0, 1, 2.5,
                0, 0, 0, 1;

    std::cout << "T_32 " << std::endl << state.T_32 << std::endl;

    //Step 11:
    state.Bk[1].transform = state.Bk[2].transform * state.T_32;
    state.Bk[0].transform = state.Bk[1].transform * state.T_21;

    for (const Frame& frame : state.Bk) {
        std::cout << "Frame " << frame.number << ":\n" << frame.transform << std::endl;
    }

 };
    
int main() {
    State state;
    solution(state);
    return 0;
}
