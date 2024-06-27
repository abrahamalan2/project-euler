'''
Using a sieve of eratosthenes type of approach, compute a list of prime numbers less than N
'''
def prime_sieve(N):
    L = [True]*N
    L[0] = False
    L[1] = False
    P = []
    p = 2
    while p < N:
        if L[p] == True:
            P += [p]
            for x in range(2*p,N,p):
                L[x] = False
        p += 1
    return P


print(prime_sieve(10**6)[10**4])
