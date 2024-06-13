#ifndef GRAPH_HPP_GUARD
#define GRAPH_HPP_GUARD




#include <iostream>
#include <set>
#include<vector>
#include <array>
#include<cmath>
#include <stdexcept>
#include <string>
#include<memory>
#include<utility>
#include <set>
#include <algorithm>

using std::vector;
using std::array;
using std::set;
using std::shared_ptr;
using std::unique_ptr;
using std::string;


template<typename VertexType>
class Graph{

    protected:

    typedef vector<VertexType> v_vec;
    typedef shared_ptr< vector< array<unsigned int, 2> > > e_ptr;
    typedef shared_ptr< vector< vector<unsigned int> > > vemap_ptr;

    public:

    v_vec V;
    e_ptr E;
    vemap_ptr VEMap;

    Graph(){
        e_ptr e(new vector< array<unsigned int, 2> >);
        E = e;
        VEMap = std::make_shared<vector<vector<unsigned int>>>(vector<vector<unsigned int>>());
    }

    Graph(unsigned int vsize){
        V.resize(vsize);
        e_ptr e(new vector< array<unsigned int, 2> >);
        E = e;
        VEMap = std::make_shared<vector<vector<unsigned int>>>(vector<vector<unsigned int>>());
    }

    Graph(v_vec vertex_vec, e_ptr edge_ptr){
        V = vertex_vec;
        E = edge_ptr;
        easy_access();
    }

    Graph(v_vec vertex_vec, e_ptr edge_ptr, vemap_ptr ve_ptr){
        V = vertex_vec;
        E = edge_ptr;
        VEMap = ve_ptr;
    }

    void easy_access(){

        for (int i = 0; i < E->size(); i++){
            (*VEMap)[(*E)[i][0]].push_back((*E)[i][1]);
            (*VEMap)[(*E)[i][1]].push_back((*E)[i][0]);
        }

        for (int i = 0; i < VEMap->size(); i++){
            set<unsigned int> s;
            unsigned int size = (*VEMap)[i].size();
            for(int j = 0; j < size; j++) s.insert( (*VEMap)[i][j] );
            (*VEMap)[i].assign( s.begin(), s.end() );
        }
    }

    void operator= (Graph<VertexType> g){
        E = g.E;
        VEMap = g.VEMap;
        V = g.V;
    }

    void printE(){
        for (int i = 0; i < E->size(); i++){
            std::cout << (*E)[i][0] << "," << (*E)[i][1] <<std::endl;
        }
    }

    void printVEMap(){
        for (int i = 0; i < VEMap->size(); i++){
            for (int j = 0; j < (*VEMap)[i].size(); j++) std::cout << (*VEMap)[i][j] << ",";
            std::cout << std::endl;
        }
    }

    string filename(){
        int maxDeg = 0;
        for (int i = 0; i < VEMap->size(); i++){
            maxDeg = ((*VEMap)[i].size() > maxDeg) ? (*VEMap)[i].size() : maxDeg;
        }
        return "graph-" + std::to_string(V.size()) + "-" + std::to_string(maxDeg);
    }
};



template<typename VertexType>
class SquareLattice : public Graph<VertexType> {

    private:

    unsigned int len;
    unsigned int dim;

    vector<unsigned int> id_to_point(unsigned int id){
        vector<unsigned int> point(dim);
        for (int d = 0; d < dim; d++){
            id = id / static_cast<unsigned int>(std::pow(len, d));
            point[d] = id % len;
        }

        return point;
    }

    unsigned long long factorial(int n) {
        if (n == 0 || n == 1)
            return 1;
        else
            return n * factorial(n - 1);
    }

    unsigned long long nChooseK(int n, int k) {
        return factorial(n) / (factorial(k) * factorial(n - k));
    }

    unsigned int squareLattice_connections(unsigned int length, unsigned int dimen){
        unsigned int edges = 0;
        for (int i = 0; i <= dimen; i++){
            edges += (dim - i) * std::pow(length - 1, dim - i) * nChooseK(dim, i);
        }
        return edges;
    }

    public:
    SquareLattice(unsigned int length, unsigned int dimension) : Graph<VertexType>(std::pow(length, dimension)) {
        len = length;
        dim = dimension;
        init();
    }

    void init(){
        unsigned int elen = std::pow(len, dim);
        unsigned int s = squareLattice_connections(len, dim);
        this->E->resize(s);
        this->VEMap->resize(elen);
        int iter = 0;

        for (unsigned int i = 0; i < elen; i++){
            vector<unsigned int> point = id_to_point(i);
            for (unsigned int d = 0; d < dim; d++){
                if (point[d] != len - 1){

                    unsigned int add = static_cast<unsigned int>(std::pow(len, d));
                    (*(this->E))[iter][0] = i;
                    (*(this->E))[iter][1] = i + add;

                    (*(this->VEMap))[i].push_back(i + add);
                    (*(this->VEMap))[i + add].push_back(i);

                    iter++;
                }
            }
        }
    }

    string filename(){
        return "latt-" + std::to_string(len) + "-" + std::to_string(dim);
    }


};

#endif