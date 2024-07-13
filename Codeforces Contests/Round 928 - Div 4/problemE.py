import math

def kthCard (n, k, i):
    if (k <= math.ceil(n/2)):
        return (2*k-1) * 2**i
    else:
        return kthCard(math.ceil(n/2), k - math.ceil(n/2), i+1)
    
print(kthCard(7,5,0))