import numpy as np
import math

class IsingModel:
    def __init__(self, graph, b, init):
        self.graph = graph.copy()
        self.graph.easy_access()
        self.b = b

        if 0 < init and init < 1:
            for i in range(len(self.graph.V)):
                self.graph.V[i] = np.random.binomial(1, init)
        elif init == 1:
            self.graph.V = [1 for i in self.graph.V]
        elif init == -1:
            self.graph.V = [-1 for i in self.graph.V]
        else:
            self.graph.V = self.graph.V

    def copy(self):
        g = self.graph.copy()
        i = IsingModel(g, self.b, init=False)
        return i

    def equals(self, model):
        if self.graph.V == model.graph.V:
            return True
        else:
            return False

    def print(self):
        print(self.graph.V)

    @staticmethod
    def H(model):
        H = 0
        for e in model.graph.E:
            H -= model.graph.V[e[0]] * model.graph.V[e[1]]

    @staticmethod
    def glaubner_coupling(model, randnum):

        size = len(model.graph.V)
        randnum *= size
        randindex = math.floor(randnum)
        randval = randnum - randindex

        s = sum([model.graph.V[i] for i in model.graph.V_E_map[randindex]])
        p = (1 + np.tanh(model.b * s)) / 2
        
        if randval <= p:
            model.graph.V[randindex] = 1
            
        else:
            model.graph.V[randindex] = -1

        return model
