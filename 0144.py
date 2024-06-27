'''
For a point (a,b) on the ellipse, let mi be the slope of the incoming ray as it hits this point and let mo be the slope of the reflected ray. Let mt be the slope of the tangent at this point. Using tangent difference formula we see
mo-mt/1+mo*mt = mt-mi/1+mi*mt
mo = 2mt-mi+mi*mt^2/2mi*mt-mt^2+1

The equation of the new line is y = mo(x-a)+b
We want to find where this intersects with 4x^2+y^2=100. Substituting gives us
4x^2+m0^2(x-a)^2+2b*mo(x-1)+b^2=100
(4+m0^2)x^2+(2b*mo-2a*mo^2)...
We know x=a is a root to this. So the other root must be 2a*mo^2-2b*mo/4+mo^2 - a
'''
n = 0
a = 1.4
b = -9.6
mi = (10.1-b)/(0-a)

while (abs(a) > .01 or b < 0):
    mt = -4*a/b
    mo = (2*mt-mi+mi*mt*mt)/(2*mi*mt-mt*mt+1)
    x = (2*a*mo*mo - 2*b*mo)/(4 + mo*mo) - a
    b = mo*(x-a)+b
    a = x
    mi = mo
    n += 1

print(n)
