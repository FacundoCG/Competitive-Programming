n: int = int(input())
colors: set = {input() for _ in range(n)}
gauntlet = {"purple":"Power", "green":"Time", "blue":"Space","orange":"Soul","red":"Reality","yellow":"Mind"}
 
all_colors: set = set(gauntlet.keys())
 
other_colors: set = all_colors - colors
 
print(len(other_colors))
 
for color in other_colors:
    print(gauntlet[color])