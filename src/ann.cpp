#include <vector>

namespace Brain{
    class Neuron{
        bool visited;
        float value;
        std::vector<size_t> in_nodes;
    };

    class NeuralNet{
        //index of the node in this vector is what we'll use to refer to the node
        std::vector<Neuron> nodes;

        //indices of inputs and outputs in the nodes array
        std::vector<size_t> inputs;
        std::vector<size_t> outputs;


    };

    class Genome{

    };
}
