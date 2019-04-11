#ifndef _POPULATION_HPP_
#define _POPULATION_HPP_

#include "ofMain.h"
#include "ann.hpp"
#include "Creature.h"

class Population{
public:
    //both these are assumed to have same indices for corresponding items
    vector<Creature> actors;
    vector<Brain::Genome> pool;
    int num_actors;

    Population(){}

    void initialize_random(int n){
        num_actors = n;

        for(int i=0; i<num_actors; i++){
            //random genome initially
            std::cout << "making " << i << "th genome\n";
            Brain::Genome genome;
            pool.push_back(genome);
            pool[pool.size()-1].initialize(5, 2, 2);
            pool[pool.size()-1].print_genome();

            Creature creature(
                0,   //X
                0,   //Y
                0,      //vx
                0
            );

            actors.push_back(creature);

            // actors[actors.size()-1].net();
            actors[actors.size()-1].net.generateFromGenome(
                pool[pool.size()-1]
            );
        }

        for(int i=0; i<num_actors; i++){
            //NOTE: debugging only, remove later
            std::vector<double> inp = {1, 1, 1, 1, 1};
            std::vector<double> outp = {0, 0};

            cout << i << "th actor: \n";
            // pool[i].print_genome();
            cout << "\n";
            actors[i].net.evaluate(inp, outp);
        }
    }
};

#endif
