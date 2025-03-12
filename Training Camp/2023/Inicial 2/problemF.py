import math 

R, d = [int(x) for x in input().split()]
n = int(input())
sausages = 0

for _ in range(n):
    x, y, r = [int(x) for x in input().split()]
    distancia_centro = math.sqrt(x**2+y**2)

    if distancia_centro+r<=R and distancia_centro>=(R-d)+r:
        sausages += 1

print(sausages)