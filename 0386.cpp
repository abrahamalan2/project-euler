#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <cmath>

/*
Let n have prime factorization p_1^{e_1}...p_d^{e_d}
Let N = e_1+...+e_d, then the size of the maximal antichain is the number of solutions to a_1+...+a_d=floor(N/2) where 0 <= a_i <= e_i
This is the coefficient of x^{floor(N/2)} in 
\prod_{i=1}^d (1+x+...x^{e_i})
(1-x)^{-d}\prod_{i=1}^d (1-x^{e_i+1})
(\sum_{i=0}^\infty \binom{i+d-1}{d-1} x^i)\prod_{i=1}^d (1-x^{e_i+1})
We expand the latter product and use that to compute the coefficient as a sum of 2^d binomial coefficients.
*/

typedef long long T;

std::vector<std::vector<T>> sieve(T N) {
    std::vector<unsigned char> L (N+1, 0);
    std::vector<std::vector<T>> Q (N+1);
    T p = 2;
    while (p <= N) {
        if (L[p] == 0) {
            for(T x = p; x < N+1; x += p) {
                L[x] += 1;
            }
        }
        Q[p].reserve(L[p]);
        p += 1;
    }
    p = 2;
    while (p <= N) {
        if (Q[p].size() == 0) {
            T q = p;
            while (q <= N) {
                for (T x = q; x < N+1; x += q) {
                    if (q == p) {
                        Q[x].push_back(1);
                    } else {
                        Q[x][Q[x].size()-1] += 1;
                    }
                }
                q *= p;
            }
        }
        p += 1;
    }
    for(std::vector<T>& x: Q) {
        std::sort(x.begin(), x.end());
    }
    return Q;
}

T binom(T n, T k) {
    if (n < 0 || k < 0 || k > n) {
        return 0;
    }
    if (k == 0 || k == n) {
        return 1;
    }
    return (n*(binom(n-1,k-1)))/k;
}

std::map<std::vector<T>,T> cache;
T max_anti(std::vector<T> L) {
    if(L.size() == 0) {
        return 1;
    }
    if(cache.count(L)) {
        return cache[L];
    } 
    T N = 0;
    T d = 0;
    T res = 0;
    for(T x : L) {
        N += x;
        d += 1;
    }
    for (int x = 0; x < (1 << d); x ++) {
        int y = x;
        int i = 0;
        int s = 0;
        bool sign = true;
        while(y > 0) {
            if (y & 1) {
                s += L[i]+1;
                sign = !sign;
            }
            i += 1;
            y = y >> 1;
        }
        if(sign) {
            res += binom((N/2)-s+d-1,d-1);
        } else {
            res -= binom((N/2)-s+d-1,d-1);
        }
    }
    cache[L] = res;
    return res;

}



int main() {
    T N = 100000000;
    std::vector<std::vector<T>> L = sieve(N);
    T res = 0;
    for (std::vector<T> x : L) {
        res += max_anti(x);
    }
    std::cout << res << std::endl;
    return 0;
}
