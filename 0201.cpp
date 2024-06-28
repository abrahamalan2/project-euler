#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <cmath>

#define MAX_LEN 51
typedef unsigned long long T;

/*
This is pretty straight forward if you are familiar with generating functions.
We compute the product (1+xy)(1+x^4y)(1+x^9y)...(1+x^{10000}y). Determine the coefficient of y^50.
From that polynomial in x, determine the coefficients who are 1 and sum those powers of x together.
The Poly class is only used to store the polynomials in y while a normal vector is used for the coefficients of powers of x. This is only because I didn't feel like figuring out how to parametrize the Poly class.
We make a couple optimizations when computing the product that reflect our end goal.
*/

class Poly {
    public:
        std::vector<T> P;
        static Poly Z;
        static Poly I;
        static Poly X;

        Poly (std::vector<T> P) {
            this->P = P;
        }

        int size() {
            return std::min(size_t(MAX_LEN),this->P.size());
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
                    sum[i] = this->access(i)+Q.access(i);
            }
            return Poly(sum);
        }

        Poly operator*(Poly Q) {
            int n = this->size();
            int m = Q.size();
            int len = std::min(MAX_LEN,n+m-1);
            std::vector<T> prod(len, 0);
            for (int i = 0; i < n; i ++) {
                for (int j = 0; j < m; j ++) {
                    if (i+j < len) {
                        prod[i+j] += this->access(i)*Q.access(j);
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


int main () {
    int M = 100;
    int N = 0;
    std::vector<int> A (M);
    for(int i = 0; i < M; i ++) {
        A[i] = (i+1)*(i+1);
        N += A[i];
    }
    std::vector<Poly> P (N+1,Poly::Z);
    P[0] = Poly::I;
    int len = 0;
    for (int n = 0; n < M; n ++) {
        int x = A[n];
        
        for (int i = std::min(len,N-x); i >= 0; i --) {
            P[i+x] = P[i+x] + Poly::X*P[i];
        }
        len += x;
    }
    T s = 0;
    for (int x = 0; x < N+1; x ++) {
        if(P[x].access(MAX_LEN-1) == 1) {
            s += x;
        }
    }
    std::cout << s << std::endl;
    
    return 0;
}
