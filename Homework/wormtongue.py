from fractions import Fraction

def suma(p1, p2):
    N = max(len(p1), len(p2))
    res = [0 for _ in range(N)]
    for i in range(N):
        if (i < len(p1)): res[i] += p1[i]
        if (i < len(p2)): res[i] += p2[i]
    return res

def multiplicar(p1, p2):
    N = len(p1) + len(p2) - 1
    res = [0 for i in range(N)]

    for i in range(len(p1)):
        for j in range(len(p2)):
            res[i+j] += (p1[i]*p2[j])
    return res

def dfs(v, adj, s):
    if (len(adj[v]) == 0): #Con una hoja retorno el polinomio de grado 1
        return [0, 1]

    cdf1 = dfs(adj[v][0], adj, s)
    cdf2 = dfs(adj[v][1], adj, s)

    productoCDF = multiplicar(cdf1, cdf2)

    if (s[v] == 'M'): # Maximo
        return productoCDF
    else: # Minimo
        productoCDF = [-x for x in productoCDF] # Multiplico por -1 a los coeficientes para simular la resta
        return suma(cdf1, suma(cdf2, productoCDF))

def solve():
    s = input()
    n = len(s)

    stack = []
    adj = [[] for _ in range(n)]

    for i in range(n):
        if stack:
            adj[stack[-1]].append(i)

        if (s[i] != "x"):
            stack.append(i)
        else:
            while (stack and len(adj[stack[-1]]) == 2):
                stack.pop()

    cdf = dfs(0, adj, s)
    integral = Fraction(0, 1)
    for i in range(len(cdf)):
        integral += Fraction(cdf[i], i + 1)

    res = Fraction(1, 1) - integral
    return res

t = int(input())
for _ in range(t):
    print("{:.10f}".format(solve()))