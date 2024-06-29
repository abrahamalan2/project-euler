#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <cmath>

typedef unsigned long long T;

/*
The equation of the circle is
(x-N/2)^2+(y-N/2)^2 = N^2/2
(2x-N)^2+(2y-N)^2=2N^2
If we consider the integer solutions to u^2+v^2=2N^2 we see that 
if N is even the RHS is divisible by 4 and hence both u,v must be even
if N is odd the RHS is 2 mod 4 and hence both u,v must be odd
So we can just find the number of integer solutions to u^2+v^2=2N^2
Let N=p_1^e_1...p_k^e_kq where q is a product of primes that are 3 mod 4 and powers of 2, then the number of integer solutions is given by
4(2e_1+1)...(2e_k+1)
Since 420/4=3*5*7, this means [e_1,...,e_k] must be equal to one of the following
[52]
[3,7]
[2,10]
[1,17]
[1,2,3]
The smallest prime that is 1 mod 4 is 5. This leaves only [3,7], [2,10], and [1,2,3] as possibilities.
*/



std::pair<std::vector<T>, std::vector<T>> sieve(T N) {
    std::vector<bool> L(N,true);
    L[0] = false;
    L[1] = false;
    T num_primes1mod4 = 0;
    T num_primes = 0;

    T p = 2;
    for (int p = 2; p < N; p ++) {
        if (L[p]) {
            num_primes += 1;
            if (p%4 == 1) {
                num_primes1mod4 += 1;
            }
        }
        for (int x = 2*p; x < N; x += p) {
            L[x] = false;
        }
    }

    std::vector<T> P (num_primes1mod4,0);
    std::vector<T> Q (num_primes - num_primes1mod4,0);
    int x = 0;
    int y = 0;
    for (int p = 2; p < N; p ++) {
        if (L[p]) {
            if(p%4 == 1) {
                P[x] = p;
                x += 1;
            } else {
                Q[y] = p;
                y += 1;
            }
        }
    }
    return std::make_pair(P,Q);
}

T sum_prods(std::vector<T>& P, T target, int n) {
    if(n >= P.size() || target <= 1 || target < P[n]) {
        return 1;
    }
    return P[n]*sum_prods(P,target/P[n],n) + sum_prods(P,target,n+1);
}

int main() {
    T N = 100000000000;
    T M = N/(T(pow(5,5)));
    std::vector<std::vector<int>> prime_fact = {{3,7},{7,3},{2,10},{10,2},{1,2,3},{1,3,2},{2,1,3},{2,3,1},{3,1,2},{3,2,1}};
    std::pair<std::vector<T>,std::vector<T>> PQ = sieve(M);
    std::vector<T> P,Q;
    P = PQ.first;
    Q = PQ.second;

    T s = 0;

    for(std::vector<int> pf: prime_fact) {
        switch(pf.size()) {
            int a,b,c;
            T x,y,z;
            case 2:
                a = pf[0];
                b = pf[1];
                for (int i = 0; i < P.size(); i ++) {
                    x = pow(P[i],a);
                    if (T(pow(P[i],a+b)) > N) {
                        break;
                    }
                    for (int j = i+1; j < P.size(); j ++) {
                        y = pow(P[j],b);
                        if (x * y > N) {
                            break;
                        }
                        s += x*y*sum_prods(Q, N/(x*y), 0);
                    }
                }
            break;
            case 3:
                a = pf[0];
                b = pf[1];
                c = pf[2];
                for (int i = 0; i < P.size(); i ++) {
                    x = pow(P[i],a);
                    if (T(pow(P[i],a+b+c)) > N) {
                        break;
                    }
                    for (int j = i+1; j < P.size(); j ++) {
                        y = pow(P[j],b);
                        if (x * T(pow(P[j],b+c)) > N) {
                            break;
                        }
                        for (int k = j+1; k < P.size(); k ++) {
                            z = pow(P[k],c);
                            if (x * y * z > N) {
                                break;
                            }
                            s += x*y*z*sum_prods(Q, N/(x*y*z), 0);
                        }
                    }
                }
            break;
        }
    }

    std::cout << s << std::endl;
    return 0;
}
