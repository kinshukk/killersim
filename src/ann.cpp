#include <vector>
#include <utility>
#include <random>

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
        std::vector<size_t> intermediates;

        NeuralNet(){}

        void generateFromGenome(Genome genome){
            for(int i=0; i<genome.num_inputs; i++){
                Neuron n;
                nodes.push_back(n);
                inputs.push_back(nodes.size()-1);
            }

            for(int j=0; j<genome.num_intermediate; j++){
                Neuron n;
                nodes.push_back(n);
                intermediates.push_back(nodes.size()-1);
            }

            for(int j=0; j<genome.num_outputs; j++){
                Neuron n;
                nodes.push_back(n);
                outputs.push_back(nodes.size()-1);
            }

            for(gene g: genome.genes){
                
            }
        }

        std::vector<double> calculate(std::vector input_vals){

        }
    };

    //represents the connecting edges
    typedef struct{
        unsigned int from_node = -1;
        unsigned int to_node = -1;
        double weight = 0.0;
    } gene;

    class Genome{
        std::vector<gene> genes;
        int num_inputs, num_outputs, num_intermediate;

        std::random_device rd;
        std::mt19937 gen(rd()); //mersenne twister
        std::uniform_real_distribution<> random_dis(-0.5, 0.5);

        //generates new genome
        Genome(int inputs, int outputs, int intermediate){
            num_inputs = inputs;
            num_intermediate = intermediate;
            num_outputs = outputs;

            //fully connected nn
            int count = 0;
            for(int i=0; i<num_inputs; i++){
                for(int j=0; j<num_intermediate; j++){
                    gene g;
                    g.from_node = i;
                    g.to_node = num_inputs + j;
                    g.weight = random_dis(gen);

                    genes.append(g);
                }
            }

            for(int j=0; j<num_intermediate; j++){
                for(int k=0; k<num_outputs; k++){
                    gene g;

                    g.from_node = j;
                    g.to_node = num_inputs + num_intermediate + k;
                    g.weight = random_dis(gen);

                    genes.append(g);
                }
            }
        }

        //mutate a number of genes
        void mutateN(int n){
            std::uniform_int_distribution<> dis(0, genes.size() - 1);

            //randomly select edge, add random value from [-0.5, 0.5] to weight
            for(int i=0; i<n; i++){
                int ind = dis(gen);

                genes[ind].weight += random_dis(gen);
            }
        }

        ///mutate 2 genes by default
        void mutate(){
            mutateN(2);
        }

        //TODO: copy one genome, mutate
    };
}
