#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <cmath>

#include <boost/multiprecision/cpp_int.hpp>  
/*
For any x, we can see the recurrence F_n(x)=x+xF_{n-1}(x)+x^2F_{n-2}(x)
To quickly compute F_n(x) we use matrix multiplication. If we let V_n=[F_n(x),F_{n-1}(x),1] and M be the matrix

x x^2 x
1 0   0
0 0   1

Then we have V_n=MV_{n-1}. So V_n=M^{n-1}V_1 and V_1=[x,0,1].

this one had me in debugging hell for a while because turns out unsigned long long wasn't enough for the matrix multiplications
*/


#define MOD 1307674368000
typedef boost::multiprecision::uint128_t T;

class M3 {
    public:
        std::vector<std::vector<T>> M;
        static M3 I;
        static M3 Z;

        M3 (std::vector<std::vector<T>> M) {
            this->M = M;
        }

        M3 operator+(M3 M) {
            std::vector<std::vector<T>> sum = {{0,0,0},{0,0,0},{0,0,0}};

            for(int i = 0; i < 3; i ++) {
                for(int j = 0; j < 3; j ++) {
                    sum[i][j] = (this->M[i][j] + M.M[i][j]) % MOD;
                }
            }

            return M3(sum);
        }

        M3 operator*(M3 M) {
            std::vector<std::vector<T>> prod = {{0,0,0},{0,0,0},{0,0,0}};

            for(int i = 0; i < 3; i ++) {
                for(int j = 0; j < 3; j ++) {
                    for(int k = 0; k < 3; k ++) {
                        prod[i][j] = (prod[i][j] + (this->M[i][k] * M.M[k][j]) % MOD) % MOD;
                    }
                }
            }

            return M3(prod);
        }

        M3 pow(T n) {
            if (n == 0) {
                return M3::I;
            } else if ((n & 1ULL) == 0) {
                return (*this**this).pow(n/2);
            } else {
                return (*this)*(((*this)*(*this)).pow(n/2));
            }
        }

        M3 pow2(T n) {
            if (n == 0) {
                return M3::I;
            }
            return *this*((*this).pow2(n-1));
        }

        std::vector<T> operator*(std::vector<T> v) {
            std::vector<T> prod = {0,0,0};

            for(int i = 0; i < 3; i ++) {
                for(int j = 0; j < 3; j ++) {
                    prod[i] = (prod[i] + (this->M[i][j] * v[j]) % MOD) % MOD;
                }
            }

            return prod;
        }

        void print() {
            std::cout << "[\n";

            for(int i = 0; i < 3; i ++) {
                std::cout << "[";
                for(int j = 0; j < 3; j ++) {
                    std::cout << this->M[i][j] << ", ";
                }
                std::cout << "],\n";
            }
            std::cout << "]\n\n";
        }
};

M3 M3::I = M3({{1,0,0},{0,1,0},{0,0,1}});
M3 M3::Z = M3({{0,0,0},{0,0,0},{0,0,0}});

T F(T n,T x) {
    M3 M = M3({{x,x*x,x},{1,0,0},{0,0,1}});
    M3 Mn = M.pow(n);
    //init contains [F_1,F_0,1]
    std::vector<T> init = {x,0,1};
    std::vector<T> u = Mn*init;

    return u[1];
}

int main () {
    T N = 1000000000000000;

    T s = 0;

    for (T x = 0; x <= 100; x ++) {
        s = (s + F(N,x)) % MOD;
    }
    std::cout << s << std::endl;
    return 0;
}
