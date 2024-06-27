'''
We can represent the state of the envelope as a quadruple (a,b,c,d) where a represents the number of A2 papers and so on.
We start at (1,1,1,1). At each batch we take one step and according to the given rules until we reach the state (0,0,0,0) after 15 steps.
We can see that on this random walk any state can only be visited at most once using a lexographical ordering argument, so this means that the expected number of times we see the state (1,0,0,0), (0,1,0,0), or (0,0,1,0) is just the sum of the probabilities we visit this state during our random walk.
We use a DP approach to do this where for each possible state we store the probability we visit that state.
'''

DP = dict()
DP[(1,1,1,1)] = 1.0

def prob(a,b,c,d):
    if 8*a+4*b+2*c+d >= 16:
        return 0
    if (a,b,c,d) in DP:
        return DP[(a,b,c,d)]
    
    #predecessor states
    L = [(a,b,c,d+1), (a,b,c+1,d-1), (a,b+1,c-1,d-1), (a+1,b-1,c-1,d-1)]

    p = 0
    for n in range(4):
        (x,y,z,w) = L[n]
        if x < 0 or y < 0 or z < 0 or w < 0:
            continue
        match n:
            case 0:
                p += prob(x,y,z,w) * w/(x+y+z+w)
            case 1:
                p += prob(x,y,z,w) * z/(x+y+z+w)
            case 2:
                p += prob(x,y,z,w) * y/(x+y+z+w)
            case 3:
                p += prob(x,y,z,w) * x/(x+y+z+w)
    
    DP[(a,b,c,d)] = p
    return p

prob(0,0,0,0)
print(DP[(1,0,0,0)] + DP[(0,1,0,0)] + DP[(0,0,1,0)])
