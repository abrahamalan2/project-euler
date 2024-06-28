#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <cmath>

/*
We can represent our position and orientation as a 4-vector and then the moves R,F,L are linear transforms represented as 4x4 matrices
Now with this in hand we can let a_0=b_0 be the identity transform and recursively define sequences of transforms a_n,b_n based on the rules.
Then we just use a sort of binary split algorithm to recursively determine what the transformation is after 10^12 Fs
*/

class M2 {
    public:
        std::vector<std::vector<long>> M;
        static M2 I;
        static M2 Z;
        static M2 R;
        static M2 L;

        M2 (std::vector<std::vector<long>> M) {
            this->M = M;
        }

        M2 operator+(M2 M) {
            std::vector<std::vector<long>> sum = {{0,0},{0,0}};

            for(int i = 0; i < 2; i ++) {
                for(int j = 0; j < 2; j ++) {
                    sum[i][j] = this->M[i][j] + M.M[i][j];
                }
            }

            return M2(sum);
        }

        M2 operator*(M2 M) {
            std::vector<std::vector<long>> prod = {{0,0},{0,0}};

            for(int i = 0; i < 2; i ++) {
                for(int j = 0; j < 2; j ++) {
                    for(int k = 0; k < 2; k ++) {
                        prod[i][j] += this->M[i][k] * M.M[k][j];
                    }
                }
            }

            return M2(prod);
        }

        std::vector<long> operator*(std::vector<long> v) {
            std::vector<long> prod = {0,0};

            for(int i = 0; i < 2; i ++) {
                for(int j = 0; j < 2; j ++) {
                    prod[i] += this->M[i][j] * v[j];
                }
            }

            return prod;
        }
};
M2 M2::I = M2({{1,0},{0,1}});
M2 M2::Z = M2({{0,0},{0,0}});
M2 M2::R = M2({{0,1},{-1,0}});
M2 M2::L = M2({{0,-1},{1,0}});


class M4 {
    public:
        std::vector<std::vector<M2>> M;
        static M4 I;
        static M4 Z;
        static M4 R;
        static M4 L;
        static M4 F;

        M4 (std::vector<std::vector<M2>> M) {
            this->M = M;
        }

        M4 operator+(M4 M) {
            std::vector<std::vector<M2>> sum = {{M2::Z,M2::Z},{M2::Z,M2::Z}};

            for(int i = 0; i < 2; i ++) {
                for(int j = 0; j < 2; j ++) {
                    sum[i][j] = this->M[i][j] + M.M[i][j];
                }
            }

            return M4(sum);
        }

        M4 operator*(M4 M) {
            std::vector<std::vector<M2>> prod = {{M2::Z,M2::Z},{M2::Z,M2::Z}};

            for(int i = 0; i < 2; i ++) {
                for(int j = 0; j < 2; j ++) {
                    for(int k = 0; k < 2; k ++) {
                        prod[i][j] = prod[i][j] + this->M[i][k] * M.M[k][j];
                    }
                }
            }

            return M4(prod);
        }

        std::vector<long> operator*(std::vector<long> v) {
            std::vector<std::vector<long>> prod = {{0,0},{0,0}};
            std::vector<std::vector<long>> w = {{v[0],v[1]},{v[2],v[3]}};

            for(int i = 0; i < 2; i ++) {
                for(int j = 0; j < 2; j ++) {
                    prod[i][0] += (this->M[i][j] * w[j])[0];
                    prod[i][1] += (this->M[i][j] * w[j])[1];
                }
            }

            return {prod[0][0],prod[0][1],prod[1][0],prod[1][1]};
        }
};
M4 M4::I = M4({{M2::I,M2::Z},{M2::Z,M2::I}});
M4 M4::Z = M4({{M2::Z,M2::Z},{M2::Z,M2::Z}});
M4 M4::R = M4({{M2::R,M2::Z},{M2::Z,M2::I}});
M4 M4::L = M4({{M2::L,M2::Z},{M2::Z,M2::I}});
M4 M4::F = M4({{M2::I,M2::Z},{M2::I,M2::I}});

enum move {A = 0, B = 1};

std::vector<std::vector<M4>> moves_dict (2, std::vector<M4> (51, M4::Z));

// determines the linear transformation that is equivalent to walking num_steps using the expansion of m_degree
M4 walk_rec(long num_steps, move m, int degree) {
    if(num_steps == 0 || degree == 0) {
        return M4::I;
    }
    switch(m) {
        case A:
            if (num_steps < (1L << (degree-1)) - 1) {
                return walk_rec(num_steps, A, degree-1);
            } else {
                return walk_rec(num_steps - ((1L << (degree-1)) - 1), B, degree-1) * M4::R * moves_dict[A][degree-1];
            }
            break;
        case B:
            if (num_steps < (1L << (degree-1))) {
                return walk_rec(num_steps-1, A, degree-1) * M4::F * M4::L;
            } else {
                return walk_rec(num_steps - (1L << (degree-1)), B, degree-1) * M4::L * moves_dict[A][degree-1] * M4::F * M4::L;
            }
            break;
    }
}


int main () {
    moves_dict[A][0] = M4::I;
    moves_dict[B][0] = M4::I;

    for(int i = 1; i < 51; i ++) {
        moves_dict[A][i] = M4::R * M4::F * moves_dict[B][i-1] * M4::R * moves_dict[A][i-1];
        moves_dict[B][i] = moves_dict[B][i-1] * M4::L * moves_dict[A][i-1] * M4::F * M4::L;
    }

    std::vector<long> v0 = {0,1,0,0};
    long N = round(pow(10,12))-1;
    std::vector<long> output = walk_rec(N, A, 50)*M4::F*v0;
    std::cout << output[2] << " " << output[3] << std::endl;
    
    return 0;
}
