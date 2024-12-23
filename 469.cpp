#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <cmath>

#include <iomanip>
/*
Let f(n) denote the expected number of chairs occupied if we do this procedure on a row of n chairs.
f(0) = 0
f(1) = 1
f(2) = 1
f(3) = (1/3) + 2(2/3) = 5/3
f(4) = 2(1/2) + 2(1/2) = 2

For n > 4, let's say the first knight picks chair a. If a is 1 or n, then the expected number of chairs occupied is f(n-2). Else it is f(a-2)+f(n-3-(a-2)) = f(a-2)+f(n-1-a)
If we let f(-1)=0 Then we get that f(n) = 1+(1/n)\sum_{a=1}^n f(a-2)+f(n-1-a). Simplifying this is f(n)=1+(2/n)\sum_{a=0}^{n-2} f(a). This formula actually works for n >= 2.
Now we need to solve this recurrence.
Let g(n)=\sum_{k=0}^n f(n). Then we have g(n)-g(n-1)=1+(2/n)g(n-2) with g(0)=0, g(1)=1

We see that ng_n-ng_{n-1}-2g_{n-2}=n
Let G(x) = \sum_{n=0}^\infty g_nx^n
Then doing some finaggling we get
(xG'-g_1x) - (xG+x^2G'-g_0x) - 2(x^2G) = x/(1-x)^2 - x
Combining like terms gives
(x-x^2)G' - (x+2x^2)G = x/(1-x)^2

Using a diffeq solver we get for some constant C
G(x) = Ce^{2-2x}/(1-x)^3 - 2/(x-1)^3
Using G(0)=0, this means C=-2/e^2;
G(x) = (1-e^{-2x})/(2(1-x)^3)
Then we can explicitly calculate g(n) as the coefficient of x^n of this product

The coefficients of (1-e^{-2x}) decrease much faster than the coefficients of 1/(2(1-x)^3) increase, so we don't need to do the full convolution.
I chose to only go up to at most 300 terms

Going from g(n) to our actual answer is explained later.

I had a lot of trouble with doubles not being large enough to store the answer (double trouble if you may). Made this problem kind of annoying.
*/

typedef unsigned long long T;
typedef __float128 D;

//coefficient of x^n in (1-e^{-2x})/(2(1-x)^3)
// 1/2(1-x)^3 = \sum_{n=0}^\infty (n+2)(n+1)/4 x^n
// 1-e^{-2x} = \sum_{n=1}^\infty -(-2)^n/n! x^n
D G(T n) {
    if(n == 0) {
        return 0.0;
    }
    if(n == 1) {
        return 1.0;
    }
    D res = 0.0;
    D factorial = 1.0;
    D exp = 2.0;
    for(int i = 1; i < std::min(n+1,300ULL); i ++) {
        res += exp * (n-i+1) * (n-i+2)/(4*factorial);
        exp = -2.0 * exp;
        factorial = (i+1)*factorial;
    }

    return res;
}



int main () {
    T N = 1e18;
    T M = N-3;
    
    // the expected number of chairs occupied will be G(M)-G(M-1)+1
    // so our result is (N - G(M) + G(M-1) - 1) / N
    std::cout << std::fixed << std::setprecision(30) << (long double)((N-G(M)+G(M-1)-1)/(N)) << std::endl;

    
    std::cout << std::fixed << std::setprecision(14) << (long double)((N-G(M)+G(M-1)-1)/(N)) << std::endl;

    return 0;
}
