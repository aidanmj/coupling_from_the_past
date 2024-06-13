#ifndef MODEL_HPP_GUARD
#define MODEL_HPP_GUARD

#include <iostream>
#include <memory>

using std::shared_ptr;


class Model{
    public:

    Model(){}


    virtual shared_ptr<Model> copy() = 0;

    virtual void transition_rule(long double randNum) = 0;
    
    virtual bool const equals(shared_ptr<Model> other) = 0;

    virtual void resetToOne() = 0;

    virtual void resetToZero() = 0;

    virtual void print() = 0;
};

#endif