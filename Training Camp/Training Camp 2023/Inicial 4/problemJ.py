n = int(input())
puntos = 0
turnos = 1
diccionario = {}

for i in range(n):
    punto, turno = [int(x) for x in input().split()]

    if turno in diccionario.keys():
        diccionario[turno].append(punto)
    else:
        diccionario[turno] = [punto]

for key, value in diccionario.items():
    diccionario[key].sort()


while turnos != 0:

    turnos -= 1
    turnos_posibles = list(diccionario.keys())
    
    if turnos_posibles == []:
        break
    else:
        max_turnos = max(turnos_posibles)

        turnos += max_turnos
        puntos += diccionario[max_turnos][-1]

        diccionario[max_turnos].pop()

        if diccionario[max_turnos] == []:
            del diccionario[max_turnos]

print(puntos)
