'''
We can simplify the equation a bit to get that a_k,b_k,c_k are the roots of
P_k(x)=kx^3-k^2x^2+x-k^3
We know that
(a_k+b_k)(b_k+c_k)(c_k+a_k)
=(k-a_k)(k-b_k)(k-c_k)
=P_k(k)/k
=1-k^2
So we have
S(n)=\sum_{k=1}^n\sum_{p=1}^n (1-k^2)^p
S(n)=\sum_{k=1}^n\frac{-(1-k^2)^{n+1}+(1-k^2)}{1-(1-k^2)}
S(n)=\sum_{k=1}^n\frac{(1-k^2)^{n+1}-(1-k^2)}{k^2}
'''
MOD = 1000000007
N = 1000000

def exp(n,r):
    if(r == 0):
        return 1
    if(r%2 == 0):
        return exp((n*n)%MOD,r//2)
    else:
        return (n*exp((n*n)%MOD,r//2))%MOD

def mod_inv(n):
    return exp(n,MOD-2)

s = 0


for k in range(1,N+1):
    s = (s + (-exp((1-k*k)%MOD,N+1)+MOD+1-k*k)*mod_inv(k*k)) % MOD
print(s)
