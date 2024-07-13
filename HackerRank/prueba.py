def chequearAsegura(a,b):
    for i in range(51):
        if 50 - i != 0:
            if a // (i+1) <= b // 50-i:
                print("Caso 1")
                return (i, 50-i)
            elif i != 0 and b // (51-i) <= a // i:
                print("Caso 2")
                return (51-i, i)
    return "No existe tal par"



def sinRepetidos(lista):
    nuevoSet = set(lista)
    lista1 = lista.copy()

    return len(set(lista1)) == len(lista)


a = 97999999
b = 2000000
i = 0

listaA = []
listaB = []

for i in range(1, 99):  # En la banca 49 se rompe 
    listaA.append(a // i)
    listaB.append(b // i)

    #if a // i  < b:
    #    print(i)
    #    break

print(sinRepetidos(listaA))

#for i in range(len(listaA)):
#    if listaA[i]<b:
#        print(i)
#        break;


#print(chequearAsegura(a,b))

n = 97
m = 1

if (a // (n + 1) <= b // m) and (b // (m+1) <= a // n):
    print(a // (n + 1))
    print(b // m)
    print("PASA EL ASEGURA :(")
else:
    print("VAMOS")