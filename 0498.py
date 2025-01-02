

import math
from functools import lru_cache

'''
R_{n,m}(x) is defined as the polynomial R(x) satisfying:
x^n = Q(x)(x-1)^m+R(x)
R has degree at most m-1

We want to find [x^d] of R(x)

Note that we have
(x+1)^n=Q(x+1)x^m+R(x+1)
R(x+1)=\sum_{k=0}^{m-1} \binom{n}{k}x^k
R(x)=\sum_{k=0}^{m-1} \binom{n}{k}(x-1)^k
Expanding gives
R(x)=\sum_{k=0}^{m-1} \sum_{j=0}^k\binom{n}{k}\binom{k}{j}x^j(-1)^{k-j}
[x^d]R(x)=\sum_{k=0}^{m-1} \binom{n}{k}\binom{k}{d}(-1)^{k-d}

Now some combinatorial manipulations gives
[x^d]R(x)=\sum_{k=d}^{m-1} \binom{n}{k}\binom{k}{d}(-1)^{k-d}
[x^d]R(x)=\sum_{k=d}^{m-1} n!/d!(k-d)!(n-k)!(-1)^{k-d}
[x^d]R(x)=\binom{n}{d}\sum_{k=d}^{m-1} \binom{n-d}{k-d}(-1)^{k-d}
[x^d]R(x)=\binom{n}{d}\sum_{k=0}^{m-d-1} \binom{n-d}{k}(-1)^k
[x^d]R(x)=\binom{n}{d}[y^{m-d-1}]1/(1-y) (1-y)^{n-d}
[x^d]R(x)=\binom{n}{d}[y^{m-d-1}](1-y)^{n-d-1}
[x^d]R(x)=(-1)^{m-d-1}\binom{n}{d}\binom{n-d-1}{m-d-1}
'''

MOD = 999999937


#returns a^b % MOD
def pow(a,b):
    if(a == 0):
        return 0
    if(b == 0):
        return 1
    if(b%2 == 0):
        return pow((a*a) % MOD,b//2)
    if(b%2 == 1):
        return (a*pow((a*a) % MOD, b//2)) % MOD
    
#returns n^{-1} % MOD
def mod_inv(n):
    return pow(n,MOD-2)

#returns n! % MOD
def factorial(n):
    if n >= MOD:
        return 0
    if n > MOD//2:
        #wilson's theorem
        if (MOD-n) % 2 == 0:
            return mod_inv(factorial(MOD-n-1))
        else:
            return MOD-mod_inv(factorial(MOD-n-1))
        
    prod = 1
    for i in range(1,n+1):
        prod = (prod * i) % MOD
    return prod

#returns nCr % MOD
def binom(n,r):
    if r > n:
        return 0
    if n >= MOD:
        #lucas's theorem
        return (binom(n % MOD, r % MOD) * binom(n // MOD, r // MOD)) % MOD
    
    if r > n//2:
        return binom(n,n-r)
        
    numer = 1
    for i in range(r):
        numer = (numer * (n-i)) % MOD
    return (numer*mod_inv(factorial(r))) % MOD
    



n = int(1e13)
m = int(1e12)
d = int(1e4)

print(n)
print(m)
print(d)

print((binom(n,d)*binom(n-d-1,m-d-1)) % MOD)
