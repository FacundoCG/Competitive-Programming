n, m = [int(x) for x in input().split()]
 
matriz = [input() for _ in range(n)]
face = {'f','a','c','e'}
number_faces = 0
 
for i in range(0, n-1):
    for j in range(0, m-1):
        test = set()
 
        test.add(matriz[i][j])
        test.add(matriz[i][j+1])
        test.add(matriz[i+1][j])
        test.add(matriz[i+1][j+1])
 
        if test == face:
            number_faces += 1
 
print(number_faces)