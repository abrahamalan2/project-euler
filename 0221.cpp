#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

/*
Replace q and r with -q and -r respectively. Multiply by pqr to get 1+pr+pq=qr or (q-p)(q-r)=p^2+1
So we can see parametrize the Alexandrian integers for any p,x,y with xy=p^2+1 by p(x+p)(y+p)
The rest is annoying brute force/divisor stuff. I tried doing a sieve thing before, but couldn't get that to work efficiently.
*/

int main() {
    std::vector<unsigned long long> A;
    for(unsigned long long p = 1; p < 100000 /*large number*/; p ++) {
        unsigned long long n = p*p+1;
        for (unsigned long long d = 1; d <= p; d ++) {
            if(n%d == 0) {
                if(p*(d+p) < ULLONG_MAX/((n/d)+p)) {
                    A.push_back(p*(d+p)*((n/d)+p));
                } else {
                    A.push_back(ULLONG_MAX);
                }
            }
        }
    }
    std::sort(A.begin(), A.end());
    std::cout << A[150000-1] << std::endl;
}
