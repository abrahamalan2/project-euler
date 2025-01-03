#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <string>
#include <cmath>



/*
We can see that a(n)=e-1 + \sum_{k=1}^n (a(n-k)-1)/k!
Manipulating a bit gives

a(n)=e-1 + \sum_{k=1}^n A(n-k)e/((n-k)!k!) + B(n-k)/((n-k)!k!) - 1/k!
a(n)=e(1+\sum_{k=1}^n A(n-k)/(k!(n-k)!)) + (\sum_{k=1}^n B(n-k)/(k!(n-k)!) - 1/k!)
A(n)/n! = 1 + \sum_{k=0}^{n-1} (A(k)/k!)*(1/(n-k)!)
B(n)/n! = \sum_{k=0}^{n-1} (B(k)/k!)*(1/(n-k)!) - \sum_{k=0}^n 1/k!

Now this is a good sign to use egfs. We define F and G as the egfs for A(n) and B(n) respectively. So
F(x)=\sum_n A(n)x^n/n!
[x^n] F(x) e^x = \sum_{k=0}^n (A(k)/k!)*(1/(n-k)!) = 2A(n)/n! - 1 = [x^n] 2F(x)- 1/1-x
F(x)(2-e^x) = 1/1-x
F(x) =  1/((1-x)(2-e^x))

G(x)=\sum_n B(n)x^n/n!
[x^n] G(x) e^x = \sum_{k=0}^n (B(k)/k!)*(1/(n-k)!) = 2B(n)/n! + \sum_{k=0}^n 1/k! = [x^n] 2G(x) + e^x/1-x
G(x)(2-e^x) = -e^x/1-x
G(x) =  -e^x/((1-x)(2-e^x))

F(x)+G(x) = (1-e^x)/((1-x)(2-e^x))

Let H(x) = F(x)+G(x). We see that

H(x)(1-x) = 1 - 1/(2-e^x)
H(x) = 1/1-x - 1/1-x * 1/2-e^x
Note that 1/2-e^x is the egf of the fubini numbers, denoted as f_n. Hence,

H(x) = -\sum_{n=0}^\infty (n! + \sum_{k=0}^n f_k n!/k!) x^n/n!
A(n)+B(n) = -n! - \sum_{k=0}^n f_k (n-k)! nCk
A(n)+B(n) = -n! - \sum_{k=0}^n f_{n-k} (k)! nCk

Now we want to compute A(10^9)+B(10^9) mod 77777777. There doesn't seem to be any easy way to compute A(10^9)+B(10^9), but we see that 
77777777=7*11*73*101*137

https://oeis.org/A000670 tells us that for odd prime p, f_{p-1} = 0 mod p and for n >= 1: f_{n+p-1} = f_n mod p 
For a prime p, and n > p this means that
A(n)+B(n) mod p = -\sum_{k=0}^{p-1} f_{(n-k) % (p-1)} * (k!) * (n%p)Ck mod p

We can compute f_n via the recurrence f_n=\sum_{i=0}^{n-1} \binom{n}{i} f_i 


*/

#define MOD 77777777
typedef unsigned long long T;

//returns b^e % p
T pow(T b, T e, T p) {
    b %= p;
    if(e == 0) {
        return 1;
    }
    if (e % 2 == 0) {
        return pow((b*b) % p, e/2, p);
    } else {
        return (b*pow((b*b) % p, e/2, p)) % p;
    }
}

//returns x^{-1} % p
T mod_inv(T x, T p) {
    return pow(x,p-2,p);
}

std::map<std::pair<T,T>,T> factorial_cache;
//returns x! % p
T factorial(T x, T p) {
    if (x >= p) {
        return 0;
    }
    if (x == 0) {
        return 1;
    }
    if (factorial_cache.count(std::make_pair(x,p))) {
        return factorial_cache[std::make_pair(x,p)];
    }

    T res = (x * factorial(x-1, p)) % p;
    factorial_cache[std::make_pair(x,p)] = res;

    return res;
}

//returns \binom{n}{r} % p
T binom(T n, T r, T p) {
    if (r > n) {
        return 0;
    }

    return (factorial(n,p) * mod_inv(factorial(r,p) * factorial(n-r,p), p)) % p;
}


std::map<std::pair<T,T>,T> fubini_cache;
//returns the nth fubini number mod p
T fubini(T n, T p) {
    if(n == 0) {
        return 1;
    }
    if (n % (p-1) == 0) {
        return 0;
    }
    if (n >= p) {
        return fubini(n % (p-1), p);
    }

    if (fubini_cache.count(std::make_pair(n,p))) {
        return fubini_cache[std::make_pair(n,p)];
    }


    T res = 0;
    
    for (T i = 0; i <= n-1; i ++) {
        res = (res + ((binom(n,i,p)*fubini(i,p)) % p)) % p;
    }

    
    fubini_cache[std::make_pair(n,p)] = res;
    return res;
}


int main () {
    
    std::vector<T> primes = {7,11,73,101,137};
    std::vector<T> residues = std::vector<T>(5,0);
    T N = 1e9;
    
    for(T i = 0; i < primes.size(); i ++) {
        T p = primes[i];
        T sum = 0;
        for (T k = 0; k <= p-1; k ++) {
            sum = (sum + ((((fubini(N-k,p) * factorial(k,p)) % p) * binom(N%p,k,p)) % p)) % p;
        }
        residues[i] = sum;
    }

    //CRT bash
    for (T x = residues[primes.size()-1]; x <= MOD; x += primes[primes.size()-1]) {
        bool is_correct = true;
        for (T i = 0; i < primes.size(); i ++) {
            if (x % primes[i] != residues[i]) {
                is_correct = false;
                break;
            }
        }

        if(is_correct) {
            //need to negate it since this is -(A(n)+B(n))
            std::cout << MOD-x << std::endl;
            break;
        }
    }



    return 0;
}
