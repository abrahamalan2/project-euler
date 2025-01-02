#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <string>
#include <cmath>



/*
Pretty self explanatory, just loop through all n/d pairs and keep track of nonreduced ones.
*/

typedef unsigned long long T;


int main () {
    T N = 12000;
    T s = 0;

    //sieve so that P[d][n] is false iff n/d is reduced
    std::vector<std::vector<bool>> P = std::vector<std::vector<bool>>(N+1,std::vector<bool>(N+1,false));

    for (T d = 1; d <= N; d ++) {
        for (T n = 0; n <= d; n ++) {
            if (d < 3*n && d > 2*n && !P[d][n]) {
                s ++;
                for (T k = 2; k*d <= N && k*n <= N; k ++) {
                    P[k*d][k*n] = true;
                }
            }
        }
    }

    std::cout << s << std::endl;



    return 0;
}
