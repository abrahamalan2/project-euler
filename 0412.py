'''
With some manipulations, we see this is just hooklength formula. In particular L(n,m)=(m! * (m+1)!/1! *  ... * (n-1)!/(n-m-1)!)^2 * some more stuff that I don't feel like writing, just look at the code
And then there are some modulo optimizations you can make
'''
N = 76543217 #this is a prime

def pow(a,b):
    if(a == 0):
        return 0
    if(b == 0):
        return 1
    if(b%2 == 0):
        return pow(a*a,b//2)
    if(b%2 == 1):
        return (a*pow((a*a) % N,b//2)) % N
    


def mod_inv (n):
    return pow(n,N-2)



def factorial (n):
    prod = 1
    for i in range(1,n+1):
        prod = (prod * i) % N
    return prod

n = 10000
m = 5000


#factorial(n*n-m*m)
#using wilson's theorem, we see that (n*n-m*m)! = (-1)^(N-(n*n-m*m))*((N-(n*n-m*m)-1)!)^-1
numer = mod_inv(factorial(N-(n*n-m*m)-1))
if ((N-(n*n-m*m))%2 == 1):
    numer = N - numer
    

denom = 1
F = [1]*(2*n)
for i in range(1,2*n):
    F[i] = (F[i-1]*i) % N


for i in range(m,n):
    temp = F[i] * mod_inv(F[i-m])
    denom = (denom * temp * temp) % N
for i in range(m+n,2*n):
    temp = F[i] * mod_inv(F[i-n+m])
    denom = (denom * temp) % N

print((numer * mod_inv(denom)) % N)
