def insertionSort(lista: list)->list:
    
    for j in range(1, len(lista)):
        key = lista[j]

        i = j-1

        while i>-1 and lista[i]>key:
            lista[i+1] = lista[i]
            i = i - 1
        
        lista[i+1] = key
    
    return lista


lista = [5,2,4,6,1,3]
print(insertionSort(lista))