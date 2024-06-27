'''
len(L)=len(M)=k
Given a sequence with initial conditions of a_0=L[0], a_1=L[1], ... a_{k-1}=L[k-1]
and satisfying recurrence a_m=R[k-1]*a_{m-1}+R[k-2]*a_{m-2}+...+R[0]a_{m-k}
return a_n
'''
def lin_rec(L,R,n):
    M = L
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
F_1 = 1
F_2 = 2
Let G_n = F_{3n+2}
G_n = 4G_{n-1} + G_{n-2}
'''
R = [1,4]
L = [2,8]
k = 2
s = sum(L)
x = 0
while (x <= 4000000):
    s += x
    x = 0
    for i in range(k-1):
        x += R[i]*L[i]
        L[i] = L[i+1]
    x += R[k-1]*L[k-1]
    L[k-1] = x
print(s)
