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
We want to find solutions to m(m-1)/n(n-1) = 1/2 with n >= 10^12
This means 
2(m^2-m)=n^2-n
2(4m^2-4m)=4n^2-4n
2(4m^2-4m+1)=4n^2-4n+1+1
2(2m-1)^2-(2n-1)^2=1
Let u=2m-1 and v=2n-1. We want to solve the Pell's equation v^2-2u^2=-1. One such solution is (u,v)=(1,1)
Let the solutions for v be defined by the sequence v_n. We have that v_n is the coefficient of 1 in 
(1+sqrt(2))(3+2sqrt(2))^n
So v_0=1, v_1=7 and v_n satisfied the recurrence v_n=6v_{n-1}-v_{n-2}
Also we see that v_n is always odd

u_n will be the coefficient of sqrt(2) in the same expression and hence follows the same recurrence
u_0=1, u_1=5
'''

V = [1,7]
U = [1,5]
R = [-1,6]

k = len(V)
v = 7
u = 5
while ((v+1)//2 <= 10**12):
    v = 0
    u = 0
    for i in range(k-1):
        v += R[i]*V[i]
        V[i] = V[i+1]

        u += R[i]*U[i]
        U[i] = U[i+1]
    v += R[k-1]*V[k-1]
    u += R[k-1]*U[k-1]
    V[k-1] = v
    U[k-1] = u

print((u+1)//2)
