#ifndef ISING_HPP_GUARD
#define ISING_HPP_GUARD

#include <iostream>
#include <vector>
#include <memory>
#include <utility>
#include <cmath>
#include <numeric>
#include <string>
#include <fstream>

#include "Model.h"
#include "Graph.h"

using std::vector;
using std::string;
using std::shared_ptr;

class IsingModel : public Model{
    private:
        Graph<short> graph;
        double b;

    public:
    IsingModel(Graph<short> g, double beta) : Model(){
        graph = g;
        b = beta;
    };

    void resetToOne(){
        std::fill(graph.V.begin(), graph.V.end(), 1);
    }

    void resetToZero(){
        std::fill(graph.V.begin(), graph.V.end(), -1);
    }

    void transition_rule(long double randNum){
        randNum *= graph.V.size();
        long long int randIndex = std::floor(randNum);
        long double randVal = randNum - randIndex;

        int s = 0;
        int size = (*(graph.VEMap))[randIndex].size();
        for (int i = 0; i < size; i++){
            s += (graph.V)[(*(graph.VEMap))[randIndex][i]];
        }
        long double p = (1 + std::tanh(b * s)) / 2;

        graph.V[randIndex] = (randVal <= p) ? 1 : -1;

    }

    bool const equals(shared_ptr<Model> other){
        return (this->graph.V == (std::dynamic_pointer_cast<IsingModel>(other))->graph.V);
    }

    shared_ptr<Model> copy(){
        shared_ptr<IsingModel> c(new IsingModel(graph, b));
        return std::dynamic_pointer_cast<Model>(c);
    };

    void print(){
        for (int i = 0; i < graph.V.size(); i++){
            std::cout << graph.V[i] << ",";
        }
        std::cout << std::endl;
    }

    void save(string name){
        std::ofstream outfile(name);
        for (const auto &e : graph.V) outfile << e << ",";
    }

    string filename(){
        return "Ising_" + graph.filename() + std::to_string(b);
    }

};

#endif