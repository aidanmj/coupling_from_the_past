import math

class Graph:
    def __init__(self, vertex_set, edge_set):
        self.V = vertex_set
        self.E = edge_set
    
    def easy_access(self):
        self.V_E_map = []
        for v in range(len(self.V)):
            self.V_E_map.append([])
        for e in self.E:
            self.V_E_map[e[0]].append(e[1])
            if e[1] != e[0]: 
                self.V_E_map[e[1]].append(e[0])

    def copy(self):
        v = self.V.copy()
        e = self.E.copy()
        g = Graph(v, e)
        if hasattr(self, 'V_E_map'):
            g.easy_access()
        return g

class SquareLattice(Graph):
    def __init__(self, dimension, length):

        self.dim = dimension
        self.len = length

        v = []
        e = []
        for i in range(self.len ** self.dim):
            v.append(self.base_convert(i))
            for d in range(self.dim):
                if v[i][d] < self.len - 1:
                    e += [[i, i + length ** d]]
        
        self.V = v
        self.E = e

    def base_convert(self, value, reverse = False):
        if reverse:
            v = 0
            for d in range(self.dim):
                v += value[d] * (self.len ** self.dim)
            return v

        else:
            v = []
            for d in range(self.dim):
                value = value // (self.len ** d)
                v += [value % self.len]
            return v