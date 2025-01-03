'''
Similar to the fast algorithm in problem 73 and 465
We define C(n) to be the number of (a,b,c) in [n+1]^3 excluding (0,0,0)
And we define D(n) to be the number of (a,b,c) in [n+1]^3 with gcd(a,b,c) = 1, which is what we are trying to compute
We see that C(n) = \sum_{m=1}^n D(n // m). This gives us the recurrence D(n) = C(n) - \sum_{m=2}^n D(n//m)
'''
    
def C(n):
    return (n+1)*(n+1)*(n+1) - 1
    
cache = dict()
def D(n):
    if n in cache:
        return cache[n]
    s = C(n)
    
    m = 2
    while(m <= n):
        coeff = n//m
        nextm = (n//coeff)+1
        
        s -= (nextm-m)*D(coeff)
        
        m = nextm
    
    cache[n] = s
    
    return s
    

n = int(1e10)
print(str(D(n))[:9]+str(D(n))[-9:])
