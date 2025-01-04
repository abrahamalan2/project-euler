import math
import numpy as np

'''
This is just finding spanning trees in a rectangular grid. Turns out mathematicians have already solved all the relevant tools.
Mostly copied from https://math.stackexchange.com/questions/1972907/computing-all-spanning-trees-of-an-undirected-regular-grid-lattice
but the given answer has some mistakes, which can be easily fixed with some googling.
'''


n = 100
m = 500

def f(i):
    return 2-2*math.cos(math.pi*i/n)
def g(i):
    return 2-2*math.cos(math.pi*i/m)

p = np.log10(1/(n*m))
for i in range(n):
    for j in range(m):
        if i == 0 and j == 0:
            continue
        p += np.log10(f(i)+g(j))
print(np.power(10,p-np.floor(p)),"e",np.floor(p))
