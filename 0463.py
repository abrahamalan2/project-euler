import math
from functools import lru_cache 
'''
Not sure how necessary this was, but with a bit of algebra one can derive
For n >= 1
f(4n+1)-f(4n)=2(f(2n+1)-f(2n))
f(4n+3)-f(4n+2)=2(f(2n+1)-f(2n))
f(4n+1)+f(4n+3)=f(2n)+f(2n+1) + 4(f(2n+1)-f(2n))
f(4n)+f(4n+1)+f(4n+2)+f(4n+3)=6f(2n+1)-2f(2n)


So for n >= 1
S(4n+3)=f(1)+f(2)+f(3)+\sum_{k=1}^{n} f(4k)+...+f(4k+3)
S(4n+3)=f(1)+f(2)+f(3)+\sum_{k=1}^{n} 6f(2k+1)-2f(2k)
S(4n+3)=f(1)+f(2)+f(3)+6\sum_{k=1}^{n} f(2k+1)+f(2k)-8\sum_{k=1}^{n} f(2k)
S(4n+3)=f(1)+f(2)+f(3)+6S(2n+1)-6f(1)-8S(n)
S(4n+3)=6S(2n+1)-8S(n)-1
'''

N = 1000000000

@lru_cache
def f(n):
    if(n == 1):
        return 1
    if(n == 3):
        return 3
    if(n%2 == 0):
        return f(n//2)
    if(n%4 == 1):
        return (2*f(2*(n//4)+1)-f(n//4)) % N
    if(n%4 == 3):
        return (3*f(2*(n//4)+1)-2*f(n//4)) % N
    
@lru_cache
def S(n):
    if(n == 1):
        return 1
    if(n == 2):
        return 2
    if(n == 3):
        return 5
    if(n%4 == 3):
        return (6*S(n//2)-8*S(n//4)-1) % N
    return (f(n)+S(n-1)) % N

print(S(3**37))
