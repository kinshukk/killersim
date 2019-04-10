#include <vector>

namespace Brain{
    class Neuron{
        //0: not assigned
        //1: input node:
        //2: intermediate node
        //3: output node
        short type = 0;

        bool visited;

        float value;

        //pair: first is the node number, second is the edge weight
        std::vector<std::pair<size_t, double> > in_nodes;
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
