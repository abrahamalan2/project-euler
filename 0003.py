N = 600851475143
p = 2
while (p*p <= N):
    if N % p == 0:
        N //= p
    else:
        p += 1
print(N)
