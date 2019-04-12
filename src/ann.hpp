#ifndef _ANN_HPP_
#define _ANN_HPP_

#include <vector>
#include <utility>
#include <random>
#include <iostream>
#include <stack>

#define MAX_W 0.6

namespace Brain{
    //represents the connecting edges
    typedef struct{
        unsigned int from_node = -1;
        unsigned int to_node = -1;
        double weight = 0.0;
    } gene;

    class Genome{
    public:
        std::vector<gene> genes;
        int num_inputs, num_outputs, num_intermediate;

        void initialize(int inputs, int outputs, int intermediate){
            std::random_device rd;
            std::mt19937 gen(rd()); //mersenne twister
            std::uniform_real_distribution<> random_dis(-0.1, 0.1);

            num_inputs = inputs;
            num_intermediate = intermediate;
            num_outputs = outputs;

            //fully connected nn
            for(int i=0; i<num_inputs; i++){
                for(int j=0; j<num_intermediate; j++){
                    gene g;
                    g.from_node = i;
                    g.to_node = num_inputs + j;
                    g.weight = random_dis(gen);

                    genes.push_back(g);
                }
            }

            for(int j=0; j<num_intermediate; j++){
                for(int k=0; k<num_outputs; k++){
                    gene g;

                    g.from_node = num_inputs + j;
                    g.to_node = num_inputs + num_intermediate + k;
                    g.weight = random_dis(gen);

                    genes.push_back(g);
                }
            }
        }

        void copy(Genome &old){
            num_outputs = old.num_outputs;
            num_intermediate = old.num_intermediate;
            num_inputs = old.num_inputs;

            for(gene g:old.genes){
                genes.push_back(g);
            }
        }


        //mutate a number of genes
        void mutateN(int n){
            std::random_device rd;
            std::mt19937 gen(rd()); //mersenne twister
            std::uniform_real_distribution<> random_dis(-0.4, 0.4);
            std::uniform_int_distribution<> random_int(0, genes.size()-1);

            //randomly select edge, add random value from [-0.5, 0.5] to weight
            for(int i=0; i<n; i++){
                int ind = random_int(gen);

                std::cout << "mutating " << ind << " from " << genes[ind].weight;

                genes[ind].weight += random_dis(gen);
                genes[ind].weight = clampValF(genes[ind].weight, 0, MAX_W);
                std::cout << " to " << genes[ind].weight << "\n";
            }
        }

        void mutate(){
            std::random_device rd;
            std::mt19937 gen(rd());
            //mean 3, variance 4
            std::normal_distribution<> random_normal{3, 4};

            int n = floor(random_normal(gen));
            if(n <= 0){
                n = 1;
            }

            mutateN(n);
        }

        void print_genome(){
            for(gene g: genes){
                std::cout << g.from_node << " to " << g.to_node << " weight: " << g.weight << std::endl;
            }
        }
    };

    typedef struct{
        //0: not assigned
        //1: input node:
        //2: intermediate node
        //3: output node
        short type = 0;

        bool visited;

        float value;

        //pair: first is the node number, second is the edge weight
        std::vector<std::pair<int, double> > in_nodes;
    } Neuron;

    class NeuralNet{
    public:
        //index of the node in this vector is what we'll use to refer to the node
        std::vector<Neuron> nodes;

        //indices of inputs and outputs in the nodes array
        std::vector<int> inputs;
        std::vector<int> outputs;
        std::vector<int> intermediates;

        NeuralNet(){}

        void generateFromGenome(Genome &genome){
            for(int i=0; i<genome.num_inputs; i++){
                Neuron n;
                n.type = 1;
                nodes.push_back(n);
                inputs.push_back(nodes.size()-1);
            }

            for(int j=0; j<genome.num_intermediate; j++){
                Neuron n;
                n.type = 2;
                nodes.push_back(n);
                intermediates.push_back(nodes.size()-1);
            }

            for(int j=0; j<genome.num_outputs; j++){
                Neuron n;
                n.type = 3;
                nodes.push_back(n);
                outputs.push_back(nodes.size()-1);
            }

            for(gene g: genome.genes){
                nodes[g.to_node].in_nodes.push_back(
                    std::make_pair(g.from_node, g.weight)
                );
            }
        }

        void initialize_dummy(){
            for(int i=0; i<nodes.size(); i++){
                for(int j=0; j<nodes[i].in_nodes.size(); j++){
                    nodes[i].in_nodes[j].second = 1.0;
                    std::cout << i << " to " << nodes[i].in_nodes[j].first << " value " << nodes[i].in_nodes[j].second << "\n";
                }
            }
        }

        double tanh(double x){
            double e2x = std::exp(2.0 * x);
            return (e2x - 1.0) / (e2x + 1.0);
        }

        double sigmoid(double x){
            return 1.0 / (1 + std::exp(-x));
        }

        //backwards DFS evaluation
        void evaluate(std::vector<double>& input, std::vector<double>& output){
            //prepare for showtime
            for(int i=0; i<nodes.size(); i++){
                nodes[i].value = 0;
                nodes[i].visited = false;
            }

            for(int ind : inputs){
                nodes[ind].value = input[ind];
                nodes[ind].visited = true;
            }

            std::stack<int> S;
            for(int ind: outputs){
                S.push(ind);
            }

            while(!S.empty()){
                int top_node = S.top();

                if(nodes[top_node].visited == true){
                    //all required previous nodes are calculated
                    double sum = 0.0;

                    for(std::pair<int, double> k : nodes[top_node].in_nodes){
                        sum += k.second * (nodes[k.first].value);
                    }

                    nodes[top_node].value = tanh(sum);
                    // std::cout << "value of " << top_node << " is " << nodes[top_node].value << "\n";

                    S.pop();
                }
                else {
                    for(std::pair<int, double> k: nodes[top_node].in_nodes){
                        //nodes whose value isn't calculated yet
                        if(nodes[k.first].visited == false){
                            S.push(k.first);
                        }
                    }

                    nodes[top_node].visited = true;
                }
            }

            for(int j=0; j<outputs.size(); j++){
                //proper offset
                // std::cout << "j: " << j << " value: " << nodes[inputs.size() + intermediates.size() + j].value;
                output[j] = nodes[inputs.size() + intermediates.size() + j].value;
            }
        }
    };
}

#endif
