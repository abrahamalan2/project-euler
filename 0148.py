'''
nCk is not divisible by 7 iff the digits of k are at most the digits of n when both are expressed in base 7
10^9 in base 7 is 33531600616
Note that for any digit d, there are (d+1)(d+2)/2 ways to choose a pair of two nonnegative digits at most d with the first at most the second
We can case on whether n is in [0,26666666666]; [30000000000,32666666666]; etc.
'''

def f(d):
    return (d+1)*(d+2)//2
def g(d):
    return (d+1)*(d+2)//2

N = 10 ** 9 - 1
L = []
while (N > 0):
    L = [N % 7] + L
    N //= 7

s = 0
for n in range(len(L)):
    p = 1
    for i in range(n):
        p *= L[i]+1
    if n == len(L)-1:
        s += p * f(L[n]) * (f(6) ** (len(L)-1-n))
    else:
        s += p * f(L[n]-1) * (f(6) ** (len(L)-1-n))
print(s)
