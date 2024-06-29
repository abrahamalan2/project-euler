#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <cmath>

/*
We can represent the problem as an infinite triangular grid by repeatedly reflecting the triangle along its edges.
The vertices are generated by all integer combinations of the unit vectors a,b
where a is to the right and b is 120 degree counter clockwise of that.
Let's say C is at the origin. We need to find where the remaining mirror copies of C are. They are at all points (a,b) with a+b=0 mod 3
So we can draw the ray from the origin to (a,b) where a+b=0 mod 3. We see it does not exit before this if gcd(a,b)=1. 
Assuming neither a,b are 0, the number of walls it reflects off (i.e. the number of edges of the lattice the ray intersects) is |a|-1 + |b|-1 + |a-b|-1
But also the laser must be shot upward, so we divide by 6.
Actually some more observations leads to us seeing that we can just take one the sextants(?) where a > b > 0
If n is the number of wall bounces, this means a = (n+3)/2. We want to find the number of b such that gcd(a,b)=1 and 0 < b < a and b = 1 mod 3
There are some nice properties of the sample inputs that make some shortcuts available
*/
int main() {
    long n = 12017639147;
    long a = (n+3)/2;
    std::vector<int> P = {5,11,17,23,29,41,47};
    std::vector<bool> L (a,true);
    long s = a/3;

    for (int x : P) {
        for (long i = x; i < a; i += 3*x) {
            if(L[i]) {
                s -= 1;
                L[i] = false;
            }
        }
    }
    std::cout << s << std::endl;
    return 0;
}