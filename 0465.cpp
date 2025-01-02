#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <string>
#include <cmath>



/*
We can construct the polar polygons by taking all the rays that pass through the origin and lattice points in the rectangle
Then for each ray picking at most one point on it as the vertex of the polygon. Then go around the grid to construct our polygon
The only problem here is we somehow manage to pick all our vertices in a way so that they're all on one half of the plane.
For each ray i that passes through a lattice point, let P[i] denote the number of lattice points it passes through.
But actually since any ray i and it's negative have some interplay, only count P[i] for exactly one of each pair.

Let P denote the set of all these equivalence classes of rays. Let Pi = \prod_{i in P} (1+P[i])
There are Pi^2-1 ways to choose a nonempty set of points from each ray.
Now we want to subtract out any of these that don't contain the origin

One such way to not contain the origin is if I pick a point from one ray and its opposite, and the rest of my points lie in one half plane made by these two rays.
Because there will be at most one ray and its opposite that are contained in this set, there is no double counting here
For any i in P, there are P[i]^2 ways to choose the two points on the ray and its opposite.
There are 2*Pi/(P[i]+1) - 1 ways to choose the rest of the points from either halfplane (-1 from double counting when we pick no additional points)
So we need to subtract out \sum_{i\in P} P[i]^2*(2*Pi/(P[i]+1) - 1)

The other such way to not contain the origin is if we pick some subset S of P and then exactly one point from each pair of rays in S and then somehow this doesn't contain the origin.
It's a well known result (adjacent to some 3b1b video about a putnam problem) that |S|/2^{|S|-1} of these will not contain the origin.
So we need to subtract an additional \sum_{S\subset P} 2|S|*2^{-|S|}(\prod_{i\in S} 2*P[i])
Using some generating functions this is equivalent to \sum_{i\in P} 2*P[i]*Pi/(P[i]+1)

Combining these results gives our answer of
Pi^2 - 1 + \sum_{i\in P} P[i]^2 - 2*Pi\sum_{i\in P} P[i]

The hard part now is determining P[i].
Yeh turns out determining P[i] is too slow, but...
What we need to determine is Pi, S1=\sum_{i\in P} P[i] and S2=\sum_{i\in P} P[i]^2. Our result is
Pi^2 - 1 + S2 - 2*Pi*S1

A simple counting argument shows that S1 = 2*N*(N+1). But also one can see that
S1=4*\sum_{a=1}^N\sum_{b=1}^N 1_{gcd(a,b)=1} floor(N/a)
  =4*\sum_{a=1}^N phi(a)*floor(N/a)
Which simplifies to above. Similarly,
S2=4*\sum_{a=1}^N phi(a)*floor(N/a)^2
Pi=(\prod_{a=1}^N (floor(N/a)+1)^(phi(a)))^4

So all we really need to do is calculate phi(a) for all a <= N

welp actually turns out that is also too slow and also requires way too much memory (100Gb ish :E)
We can make use of the fact that floor(N/a) takes few values 

Algorithm for computing the sum mostly copied from
https://www.rishabhxchoudhary.com/blog/sum-of-euler-totient-functions
https://math.stackexchange.com/questions/316376/how-to-calculate-these-totient-summation-sums-efficiently

again lots of overflow issues :(
*/

#define MOD 1000000007
typedef unsigned long long T;



//returns x^n mod p
T pow(T x,T n,T p) {
    if (n == 0) {
        return 1;
    }
    if (n % 2 == 0) {
        return pow((x*x) % p,n/2,p);
    }
    else {
        return (x*(pow((x*x) % p,n/2,p))) % p;
    }
}

std::vector<T> sieve(T N) {

    //Q[n] is 1 iff n is composite
    //P[n] stores phi(n)
    std::vector<char> Q = std::vector<char>(N+1,0);
    std::vector<T> P = std::vector<T>(N+1,0);
    
    for (T p = 1; p <= N; p ++) {
        P[p] = p;
    }

    T p = 2;
    for (T p = 2; p <= N; p ++) {
        if (Q[p] == 0) {
            for (T q = p; q <= N; q += p) {
                Q[q] = 1;
                P[q] /= p;
                P[q] *= (p-1);
            }
        }
    }

    return P;
}


void print_vec(std::vector<T> vec) {
    std::cout << "[\n";
    for (T x: vec) {
        std::cout << x << ", ";
    }
    std::cout << "\n]\n";
}

std::map<std::pair<T,T>,T> Phi_cache = std::map<std::pair<T,T>,T>();

T Phi(T n, std::vector<T>& pre,T mod) {
    if(n < pre.size()) {
        return pre[n] % mod;
    }

    if(Phi_cache.count(std::make_pair(n,mod))) {
        return Phi_cache[std::make_pair(n,mod)];
    }
    
    T res = (((n % mod)*((n+1) % mod))/2) % mod;

    T i = 2;
    while (i <= n) {
        T coeff = n/i;
        T nexti = (n/coeff)+1;

        res = (mod + res - (Phi(coeff,pre,mod)*((nexti-i) % mod) % mod)) % mod;

        i = nexti;
    }

    Phi_cache[std::make_pair(n,mod)] = res;
    return res;
} 


int main () {
    T N = 96889010407;

    T pre_len = sqrt(N)+1;

    std::vector<T> phi = sieve(pre_len);
    std::vector<T> Phi_pre = std::vector<T>(pre_len+1,0);


    for (T p = 1; p <= pre_len; p ++) {
        Phi_pre[p] = Phi_pre[p-1] + phi[p];
    }

    

    T Pi = 1;
    T s1 = (2*(N % MOD)*((N+1) % MOD)) % MOD;
    T s2 = 0;

    T a = 1;

    while (a <= N) {
        T coeff = N/a;
        T nexta = (N/coeff)+1;


        s2 = (s2 + 4*((Phi(nexta-1,Phi_pre,MOD)+MOD-Phi(a-1,Phi_pre,MOD)) % MOD)*(((coeff % MOD)*(coeff % MOD)) % MOD)) % MOD;
        Pi = (Pi * pow((1 + coeff) % MOD,4*((Phi(nexta-1,Phi_pre,MOD-1)+(MOD-1)-Phi(a-1,Phi_pre,MOD-1)) % (MOD-1)), MOD)) % MOD;

        a = nexta;

    }


    T s = ((Pi*(Pi + 2*(MOD-s1)) % MOD) + MOD - 1 + s2) % MOD;
    
    
    std::cout << s << std::endl;



    return 0;
}
