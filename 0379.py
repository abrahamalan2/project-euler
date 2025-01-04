import math

'''
This was definitely not the intended solution as it took quite a time.
The gist was that g(n) is the number of (x,y) with 1 <= x <= y <= n and xy <= n*gcd(x,y)
If we partition based off the gcd of (x,y), g, then this means g(n) = \sum_{g=1}^n\sum_{x=1}^{n//g}\sum_{y=x}^{n//g} [gcd(x,y) == 1, xy <= n//g]

Now let h(n) be the number of (x,y) with 1 <= x <= y <= n, gcd(x,y)=1 and xy <= n. So this means g(n) = \sum_{g=1}^n h(n//g)
and let k(n) be the number of (x,y) with 1 <= x <= y <= n and xy <= n

We can compute k(n) in O(sqrt(n)) time
We see again by partitioning off the gcd, g, k(n) = \sum_{g=1}^n h(n//g^2) so this gives us the recurrence
h(n) = k(n) - \sum_{g=2}^n h(n//g^2)
Assuming we cache h(n), this takes at least O(sqrt(n)) time

And then combining this all gives us that computing g(n) takes about maybe some time between O(sqrt(n)log(n)) and O(n). Not really sure about the specifics since the caching.
Considering this took quite a while, I'd say more closer to O(n)
'''

def k(n):
    s = 0
    x = 1
    while (x*x <= n):
        coeff = n//x
        xnext = (n//coeff)+1
        s += (coeff + 1)*(xnext-x)-(x+xnext-1)*(xnext-x)//2
        x = xnext
    return s
    

hcache = dict()
def h(n):
    if n in hcache:
        return hcache[n]
    s = k(n)
    g = 2
    while(g*g <= n):
        coeff = n//(g*g)
        nextg = math.isqrt(n//coeff)+1
        s -= h(coeff)*(nextg-g)
        g = nextg

    hcache[n] = s
    return s
    
def g(n):
    s = 0
    g = 1
    while g <= n:
        coeff = n//g
        gnext = (n//coeff)+1
        s += h(coeff)*(gnext-g)
        g = gnext
    return s
    
    

N = int(1e12)

print(g(N))
