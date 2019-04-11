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

    float timeSinceLastIteration;

    Population(){}

    void initialize_random(int n){
        timeSinceLastIteration = ofGetElapsedTimef();

        num_actors = n;

        for(int i=0; i<num_actors; i++){
            //random genome initially
            std::cout << "making " << i << "th genome\n";
            Brain::Genome genome;
            pool.push_back(genome);
            pool[pool.size()-1].initialize(5, 2, 2);
            pool[pool.size()-1].print_genome();

            Creature creature(
                0,      //X
                0,      //Y
                0,      //vx
                0       //vy
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
            cout << "\n";
            actors[i].net.evaluate(inp, outp);
        }
    }

    vector<pair<double, int> > getFittestN(int n){
        n = clampValI(n, 1, num_actors);

        vector<pair<double, int> > res;

        for(int i=0; i<num_actors; i++){
            res.push_back(make_pair(actors[i].health, i));
            cout << "creature " << i << " health: " << actors[i].health << "\n";
        }

        sort(res.begin(), res.end(), greater<pair<double, int> >());

        res.resize(n);

        return res;
    }

    void init_next_generation(int n, int screenW, int screenH){
        vector<pair<double, int> > fittest = getFittestN(n);

        vector<Brain::Genome> pool_new;

        //fittest first
        for(auto c : fittest){
            pool_new.push_back(pool[c.second]);
            cout << "next fittest: " << c.second << " fitness: " << c.first << "\n";
        }

        //create mutated copies of fittest genomes, rotate
        for(int i=0; pool_new.size() < pool.size(); i = (i+1) % fittest.size()){
            Brain::Genome genome;
            genome.copy(pool[fittest[i].second]);
            genome.mutate();
            pool_new.push_back(genome);
        }

        std::cout << "new pool created\n";

        pool = pool_new;
        pool_new.resize(0);

        std::cout << "new pool copied\n";

        std::random_device rd;
        std::mt19937 gen(rd()); //mersenne twister
        std::uniform_int_distribution<> random_dis(50, min(screenW, screenH) - 50);
        std::uniform_real_distribution<> random_angle(0, 2*PI);

        // for(int i=0; i<num_actors; i++){
        //     std::cout << "generating net for actor " << i << "\n";
        //     actors[i].net.generateFromGenome(pool[i]);
        //     actors[i].health = 100;
        //     actors[i].alive = true;
        //     actors[i].food_eaten = 0;
        //     actors[i].position_x = random_dis(gen);
        //     actors[i].position_y = random_dis(gen);
        // }

        // std::normal_distribution<> random_normal()

        // double probability_random_creature =

        actors.clear();

        for(int i=0; i<num_actors; i++){
            std::cout << "initializing actor " << i << "\n";
            Creature creature(
                0,   //X
                0,   //Y
                0,      //vx
                0       //vy
            );

            actors.push_back(creature);

            // actors[actors.size()-1].net();
            actors[actors.size()-1].net.generateFromGenome(
                pool[pool.size()-1]
            );
            actors[actors.size()-1].position_x = random_dis(gen);
            actors[actors.size()-1].position_y = random_dis(gen);
            actors[actors.size()-1].angle = random_angle(gen);
        }
    }
};

#endif
