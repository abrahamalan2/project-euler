def is_palindrome(n):
    s = str(n)
    for i in range(len(s)):
        if s[i] != s[len(s)-1-i]:
            return False
    return True


M = 0
for a in range(900,1000):
    for b in range(900,1000):
        if is_palindrome(a*b):
            M = max(M,a*b)
print(M)
