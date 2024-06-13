#ifndef MONOCFTP_HPP_GUARD
#define MONOCFTP_HPP_GUARD


#include <iostream>
#include <random>
#include "Model.h"
#include <cmath>
#include <thread>
#include <set>
#include<vector>
#include <array>
#include <utility>
#include <memory>
#include<string>

using std::string;
using std::vector;
using std::array;
using std::set;
using std::shared_ptr;

class MonoCFTP{

    private:
        shared_ptr<Model> model;
        shared_ptr<Model> max;
        shared_ptr<Model> min;


    void sequence(unsigned int iter, unsigned int seed, unsigned int r, unsigned int t0, bool one){

        if (one)
            max->resetToOne();
        else
            min->resetToZero();

        shared_ptr<Model> mod = (one) ? max : min;

        for (int i = 1; i <= iter; i++){
            unsigned int ti = t0 * std::pow(r, iter - i);
            std::mt19937_64 rng(seed * (iter - i + 2));
            std::uniform_real_distribution<long double> distribution(0.0, 1.0);

            for (int t = 0; t < ti; t++){
                mod->transition_rule(distribution(rng));
            }
        }

        std::mt19937_64 rng(seed);
        std::uniform_real_distribution<long double> distribution(0.0, 1.0);
        unsigned int ti = t0 * r;

        for (int t = 0; t < ti; t++){
            mod->transition_rule(distribution(rng));
        }

    }

    public:

    MonoCFTP(shared_ptr<Model> mod){
        model = mod;
        max = model->copy();
        min = model->copy();
        
        


        this->max->resetToOne();
        this->min->resetToZero();
    };
    
    shared_ptr<Model> sample(unsigned int seed, unsigned int r, unsigned int t0){
        unsigned int iter = 0;

        while (!(max->equals(min))){
            iter++;
            std::cout << t0 * std::pow(r, iter) << std::endl;

            std::thread thread1(&MonoCFTP::sequence, &(*this), iter, seed, r, t0, 1);
            std::thread thread2(&MonoCFTP::sequence, &(*this), iter, seed, r, t0, 0);

            thread1.join();
            thread2.join();
        };

        return max;
    }

};

#endif