'''
Let r_n(a) denote the remainder of (a-1)^n+(a+1)^n when divided by a^2. Note that r_0(a)=2, r_1(a)=2a and for n >= 2 r_n(a)=(-1)^n+1+na((-1)^{n-1}+1) mod a^2
So when n is even this is 2. When n is odd this is 2na. 2 is not very big, so we're going to assume the max is obtained when n is odd.
When a is even (and n is odd) 2na can at most be a(a-2) mod a^2. When a is odd 2na can at most be a(a-1) mod a^2
'''
s = 0
for a in range(3,1001):
    if a % 2 == 0:
        s += a*(a-2)
    else:
        s += a*(a-1)
print(s)
