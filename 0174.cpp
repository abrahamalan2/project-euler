#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <cmath>



/*
You can form a lamina with t squares if you can write t as y^2-x^2 where y and x have same parity
\sum_{n=1}^{10} N(n) is equivalent to counting the number of t <= 10^6 so that t has at least 1 and at most 10 expressions of the form y^2-x^2
Note that this is equivalent to t=y^2-x^2=(y-x)(y+x). So t is divisible by 4.
We can find all solutions by taking a factor pair ab of t/4 with a>b and writing y = a+b and x = a-b
So if t/4 is a square then it must have between 3 and 21 divisors else it must have between 2 and 20 divisors
Recall a number has an odd number of divisors iff it is a square so basically we just require that t/4 has between 2 and 21 divisors
*/

//not entirely accurate, but good enough for our purposes
int num_divisors (int n) {
    int total = 0;
    for(int x = 1; x*x < n; x ++) {
        if (n%x == 0) {
            total += 1;
        }
        if(total > 10) {
            return 22;
        }
    }
    return 2*total;
}

int main() {
    long s = 0;
    for(int t = 2; t < 250000; t ++) {
        if(num_divisors(t) <= 21) {
            s += 1;
        }
    }
    std::cout << s << std::endl;
    return 0;
}
