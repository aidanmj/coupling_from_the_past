import numpy as np
from matplotlib import pyplot as plt


class MonoCFTP:
    def __init__(self, transition_rule, one, zero):
        self.one = one
        self.zero = zero
        self.max = one.copy()
        self.min = zero.copy()
        self.transition_rule = transition_rule

    def next(self, randnum):
        self.min = self.transition_rule(self.min, randnum)
        self.max = self.transition_rule(self.max, randnum)
    
    def sequence(self, r, T0, seed, iter):
        self.min = self.zero.copy()
        self.max = self.one.copy()

        for i in reversed(range(iter)):
            t = T0 * r ** i
            rng = np.random.default_rng(seed = seed * (i + 2))
            rands = rng.random(t)
            for randnum in rands:
                self.next(randnum)

        t = T0
        rng = np.random.default_rng(seed = seed)
        rands = rng.random(t)
        for randnum in rands:
            self.next(randnum)
            
    def sample(self, seed, r, T0):
        iter = 0
        self.max = self.one.copy()
        self.min = self.zero.copy()
        while not self.max.equals(self.min):
            iter += 1
            self.sequence(r, T0, seed, iter)
            print(T0 * (r ** iter))
        return self.max