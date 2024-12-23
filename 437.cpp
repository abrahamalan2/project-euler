#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <cmath>
/*
3 is always a fibonacci primitive root of 5
for any prime p > 5, the solutions to x^2=x+1 are (1 +- sqrt(5))/2
For this to be a primitive root it is necessary that 5 is a qr mod p. We see that this implies p is +- 1 mod 10
So for all these primes, we find the solutions to x^2=x+1 and then test if they are a generator.
Finding the solutions is another problem. It turns out that brute force searching for solutions is too long for the input so we use tonelli shanks
*/


#define MOD 1307674368000
typedef unsigned long long T;

void print_vec(std::vector<T> vec) {
    std::cout << "[\n";
    for (T x: vec) {
        std::cout << x << ", ";
    }
    std::cout << "\n]\n";
}

//returns a sieve Q so that for 2 <= n <= N, Q[n] stores the largest prime factor of n
std::vector<T> sieve(T N) {
    std::vector<T> Q = std::vector<T>(N+1,0);

    T p = 2;
    while (p <= N) {
        if (Q[p] == 0) {
            for (T q = p; q <= N; q += p) {
                Q[q] = p;
            }
        }
        p += 1;
    }

    return Q;
}

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

//returns true iff i is a generator mod p
bool is_gen(std::vector<T> &Q, T p, T i) {
    T q = Q[p-1];
    T ne = (p-1)/q;
    while(ne != 1) {
        if (pow(i,(p-1)/q,p) == 1) {
            return false;
        }
        q = Q[ne];
        ne = (ne)/q;
    }
    return true;
}

//returns legendre symbol (a/p) 
T is_qr(T a,T p) {
    a = a%p;
    if(a == 0) {
        return 0;
    }
    return pow(a,(p-1)/2,p);

}

//returns r so that r^2 = n mod p via tonelli shanks
//https://en.wikipedia.org/wiki/Tonelli%E2%80%93Shanks_algorithm
T sqrt(T n,T p) {
    T Q = p-1;
    T S = 0;
    while(Q % 2 == 0) {
        Q /= 2;
        S += 1;
    }

    T z = 2;
    while(is_qr(z,p) == 1) {
        z += 1;
    }

    T M = S;
    T c = pow(z,Q,p);
    T t = pow(n,Q,p);
    T R = pow(n,(Q+1)/2,p);

    while(t > 1) {
        T i = 0;
        T temp = t;
        while(temp != 1) {
            temp = (temp * temp) % p;
            i += 1; 
        }
        T b = pow(c,1 << (M-i-1),p);

        M = i;
        c = (b*b) % p;
        t = (t*c) % p;
        R = (R*b) % p;
    }

    return R;


}


bool fib_prim_root(std::vector<T> &Q, T p) {

    //the two possible solutions to x^2=x+1 are 1 +- sqrt(5) / 2
    // in particular they sum to 1

    T sqrt5 = sqrt(5,p);
    T fib = 1+sqrt5;
    if (fib % 2 == 0) {
        fib = fib/2;
    } else {
        fib = ((fib+p)/2) % p;
    }
    return is_gen(Q,p,fib) || is_gen(Q,p,p+1-fib);
}



int main () {
    T N = 1e8;

    std::vector<T> Q = sieve(N);


    T s = 5;

    for (T n = 9; n <= N; n += 10) {
        if(Q[n] == n) {
            if(fib_prim_root(Q,n)) {
                s += n;
            }
        }
    }

    for (T n = 11; n <= N; n += 10) {
        if(Q[n] == n) {
            if(fib_prim_root(Q,n)) {
                s += n;
            }
        }
        
    }

    std::cout << s << std::endl;

    return 0;
}
