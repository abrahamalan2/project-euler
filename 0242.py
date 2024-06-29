import math
from functools import lru_cache 

'''
hmm guessed the pattern for this one.
We let n=2m+1 and k=2j+1. f(n,k) will be the coefficient of y^k in the expansion of [(1+y)^{2m+1} - (1-y)^m(1+y)^m(1-y)]/2
which comes out to half of nCr(2m+1,2j+1) + (-1)^j nCr(m,j). We want to count all m,j with 2*m+1 <= 10^12 so that this expression is 2 mod 4.
I tried computing this expression mod 4 some values of m,j and saw that it only occurs when m,j are both even and m,j satisfy mCj is odd.
Using Lucas' theorem, counting all such pairs is an easier version of problem 148.
'''


def f(d):
    return (d+1)*(d+2)//2

N = (10**12)//4 - 1
L = []
while (N > 0):
    L = [N % 2] + L
    N //= 2

s = 0
for n in range(len(L)):
    p = 1
    for i in range(n):
        p *= L[i]+1
    if n == len(L)-1:
        s += p * f(L[n]) * (f(1) ** (len(L)-1-n))
    else:
        s += p * f(L[n]-1) * (f(1) ** (len(L)-1-n))
print(s)
