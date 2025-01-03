#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <string>
#include <cmath>



/*
Using the freshman's dream, we get the idea that Q(2x)=Q(x) and Q(8x+1)=Q(x)*Q(1).
We can expand the Q(8x+1)=Q(x)*Q(1) idea to a more general notion that if x=a00b in binary, then Q(x)=Q(a)Q(b).
This gives us a decent amount of simplifications, we still need to bash a couple numbers out. For this we just do polynomial exponentation
It seems this isn't the quickest, but it works enough after ~5 minutes.

these two papers detail faster methods:
https://sites.math.rutgers.edu/~zeilberg/mamarim/mamarimPDF/CAcount.pdf
https://arxiv.org/pdf/0802.2654
*/

typedef unsigned long long T;

//polynomials in F2
class Poly {
    public:
        std::vector<T> P;
        static Poly Z;
        static Poly I;
        static Poly X;
        static Poly Q; //1+x+x^2+x^3+x^4

        Poly (std::vector<T> P) {
            this->P = P;
        }

        int size() {
            return this->P.size();
        }

        T access(int n) {
            if(n < 0 || n >= this->size()) {
                return 0;
            }
            if(this->P[n] >= 2) {
                return 2;
            }
            return this->P[n];
        }

        T sum() {
            T sum = 0;
            for (int i = 0; i < this->size(); i ++) {
                sum += this->access(i);
            }
            return sum;
        }

        Poly operator+(Poly Q) {
            int n = this->size();
            int m = Q.size();
            int len = std::max(n,m);
            std::vector<T> sum(len, 0);
            for (int i = 0; i < len; i ++) {
                    sum[i] = this->access(i) ^ Q.access(i);
            }
            return Poly(sum);
        }

        Poly operator*(Poly Q) {
            int n = this->size();
            int m = Q.size();
            int len = n+m-1;
            std::vector<T> prod(len, 0);
            for (int i = 0; i < n; i ++) {
                for (int j = 0; j < m; j ++) {
                    if (i+j < len) {
                        prod[i+j] ^= this->access(i) & Q.access(j);
                    }
                }
            }
            return Poly(prod);
        }

        Poly pow(int n) {
            if (n == 0) {
                return Poly::I;
            } else if (n%2 == 0) {
                return (*this**this).pow(n/2);
            } else {
                return *this*((*this**this).pow(n/2));
            }
        }

        void print() {
            for (int i = 0; i < this->size(); i ++) {
                std::cout << this->access(i) << "x^" << i <<" + ";
            }
            std::cout << std::endl;
        }
};

Poly Poly::Z = Poly({0});
Poly Poly::I = Poly({1});
Poly Poly::X = Poly({0,1});
Poly Poly::Q = Poly({1,1,1,1,1});


//returns the number whose binary representation is the reverse of that of x
T reverse(T x) {
    T res = 0;
    while (x > 0) {
        res <<= 1;
        res += x % 2;
        x >>= 1;
    }
    return res;
}


T bash(T x) {
    return Poly::Q.pow(x).sum();
}

T Q(T x) {
    if (x < 8) {
        switch(x) {
            case 0: return 1;
            case 1: return 5;
            case 3: return 7;
            case 5: return 17;
            case 7: return 19;
        }
    }
    if (x % 2 == 0) {
        return Q(x/2);
    }

    T rem = 0;
    while(x % 4 != 0) {
        rem <<= 1;
        rem += x % 2;
        x >>= 1;
    }

    if (x == 0) {
        return bash(reverse(rem));
    }

    return Q(reverse(rem))*Q(x);

}
int main () {
    T exp = 1;
    T s = 0;
    for(T i = 1; i <= 18; i ++) {
        exp *= 5;
        s += Q(exp);
    }

    std::cout << s << std::endl;



    return 0;
}
