import math
'''
len(L)=len(R)=k
Given a sequence with initial conditions of a_0=L[0], a_1=L[1], ... a_{k-1}=L[k-1]
and satisfying recurrence a_m=R[k-1]*a_{m-1}+R[k-2]*a_{m-2}+...+R[0]a_{m-k}
return a_n
'''
def lin_rec(L,R,n):
    k = len(L)
    if n < k:
        return L[n]
    x = k-1
    while (x < n):
        temp = 0
        for i in range(k-1):
            temp += R[i]*L[i]
            L[i] = L[i+1]
        temp += R[k-1]*L[k-1]
        L[k-1] = temp
    return L[k-1]

'''
b must be an even integer. Let b=2a. We'll first do the case of h=b+1. We require that a^2+(2a+1)^2 is a perfect square.
I.e. there exists integer k so that k^2=5a^2+4a+1
5k^2=25a^2+20a+5
5k^2=(5a+2)^2+1
Let u=5a+2 (in the case that h=b-1, everything is the same except u=5a-2)
We want to find integer solutions to u^2-5k^2=-1
One solution to (u,k) is (2,1)
let the integer solutions to u be defined by the sequence u_n with u_0=c, k_0=d. From the theory of Pell's equations we know u_n is the coefficient of 1 in (c+dsqrt(5))(9+4sqrt(5))^n
So u_n=18u_{n-1}-u_{n-2}
'''

P = [(2,1)]
R = [-1,18]
solutions = []
for (a,b) in P:
    L = [a,a*9+b*4*5]
    solutions += [abs(x) for x in L]
    k = len(L)
    x = k-1
    while (x < 30): #just pick some sufficiently large number
        temp = 0
        for i in range(k-1):
            temp += R[i]*L[i]
            L[i] = L[i+1]
        temp += R[k-1]*L[k-1]
        L[k-1] = temp
        x += 1
        solutions += [abs(temp)]
solutions = sorted(list(set(solutions)))
L = [int(math.sqrt((x*x+1)//5)) for x in solutions if x % 5 == 2 or x % 5 == 3]

print(sum(L[1:13]))

