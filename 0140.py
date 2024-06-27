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
We have that A_G(x)=3x^2+x/1-x-x^2. Note that this is increasing for positive x in its domain. Let A_G(x)=n an integer. Then the solution to x is (n+3)x^2+(n+1)x-n=0. This has rational solution iff (n+1)^2+4n(n+3) is a perfect square.
I.e. there exists integer k so that k^2=5n^2+14n+1
5k^2=25n^2+70n+5
5k^2=(5n+7)^2-44
Let u=5n+7
u^2-5k^2=44
Some exhaustive search shows that some primitive solutions is (u,k)=(7,1); (8,2); (13,5); (7,-1); (8,-2); (13,-5)
For each (a,b), let the integer solutions to u be defined by the sequence u_n with u_0=a and u_1=b. From the theory of Pell's equations we know u_n is the coefficient of 1 in (a+bsqrt(5))(9+4sqrt(5))^n
So u_n=18u_{n-1}-u_{n-2}
'''

P = [(7,1), (8,2), (13,5), (7,-1), (8,-2), (13,-5)]
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
solutions = [(x-7)//5 for x in solutions if x % 5 == 2]

print(sum(solutions[1:31]))

