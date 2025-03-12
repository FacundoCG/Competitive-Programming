nHouses, girlHouse, money = [int(x) for x in input().split()]
girlHouse -= 1
houses = [int(x) for x in input().split()]
ideal_house: int = 0

for k in range(1,nHouses):
    if 0<=girlHouse+k<nHouses:
        if houses[girlHouse+k]!=0 and houses[girlHouse+k] <= money:
            ideal_house += k*10
            break
    if  0<=girlHouse-k<nHouses:
        if houses[girlHouse-k]!=0 and houses[girlHouse-k] <= money:
            ideal_house += k*10
            break

print(ideal_house)
