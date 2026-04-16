from functools import cmp_to_key

def cmp(x, y):
    d1 = x[0]
    v1 = x[1]

    d2 = y[0]
    v2 = y[1]

    if (d1/v1 < d2/v2): return -1
    if (d1/v1 > d2/v2): return 1
    return 0

class Solution:
    

    def eliminateMaximum(self, dist: List[int], speed: List[int]) -> int:
        res:int = 0

        A = [(dist[i], speed[i]) for i in range(len(dist))]
        A.sort(key=cmp_to_key(cmp)) # Ordenar A 

        minutes = 0

        for i in range(len(A)):
            # Chequear si puedo eliminar al i-esimo monstruo o no
            distanciaAcortada: int = A[i][0] - minutes*A[i][1]
            if (distanciaAcortada <= 0): break

            res += 1
            minutes += 1

        return res
