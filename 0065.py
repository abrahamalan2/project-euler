'''
Ha I actually did a project on continued fractions. The numerators and denominators 
follow a nice recurrence dependent on the coefficients of the continued fraction
'''

p1=2
p2=3
q1=1
q2=1
for n in range(3,101):
    a = 1
    if(n%3 == 0):
        a = 2*(n//3)
    pn = a*p2 + p1
    p1 = p2
    p2 = pn

    qn = a*q2 + q1
    q1 = q2
    q2 = qn

print(sum([int(x) for x in str(pn)]))
