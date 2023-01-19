#pragma once
#include "Eigen/Core"

typedef float Scalar;
typedef Eigen::MatrixXf Matrix;
typedef Eigen::RowVectorXf RowVector;
typedef Eigen::VectorXf ColVector;


class GFGNeuralNetwork
{
public:
    // constructor
    GFGNeuralNetwork(std::vector<unsigned int> topology, Scalar learningRate = Scalar(0.005));
 
    // function for forward propagation of data
    void propagateForward(RowVector& input);
 
    // function for backward propagation of errors made by neurons
    void propagateBackward(RowVector& output);
 
    // function to calculate errors made by neurons in each layer
    void calcErrors(RowVector& output);
 
    // function to update the weights of connections
    void updateWeights();
 
    // function to train the GFGNeural network give an array of data points
    void train(std::vector<RowVector*> data);
 
    // storage objects for working of GFGNeural network
    /*
          use pointers when using std::vector<Class> as std::vector<Class> calls destructor of
          Class as soon as it is pushed back! when we use pointers it can't do that, besides
          it also makes our GFGNeural network class less heavy!! It would be nice if you can use
          smart pointers instead of usual ones like this
        */
    std::vector<RowVector*> neuronLayers; // stores the different layers of out network
    std::vector<RowVector*> cacheLayers; // stores the unactivated (activation fn not yet applied) values of layers
    std::vector<RowVector*> deltas; // stores the error contribution of each neurons
    std::vector<Matrix*> weights; // the connection weights itself
    Scalar learningRate;

};
