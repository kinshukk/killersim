#include <vector>
#include <utility>

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

    //represents the connecting edges
    typedef struct{
        unsigned int from_node = -1;
        unsigned int to_node = -1;
        float weight = 0.0;
    } gene;

    class Genome{
        std::vector<gene> genes;
        int inputs, outputs, intermediate;

        Genome(int num_inputs, int num_outputs, int num_intermediate){
            inputs = num_inputs;
            outputs = num_outputs;
            intermediate = num_intermediate;

            int count = 0;
            for(int i=0; i<num_inputs; i++){

            }
        }
    };
}
