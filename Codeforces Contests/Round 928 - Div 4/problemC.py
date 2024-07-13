def sumDigit (n):
    if n < 10:
        return n
    else:
        return (n % 10) + sumDigit (n//10)

res = 0
n = int(input())

k = 45
s = 46
i = 0
p = 0

for i in range (1, n+1):
    res += sumDigit(i)

for j in range (19, n, 10):
    if (p % 9) == 0:
        pass
    
    res += s + 10*i
    i+=1

print(res)