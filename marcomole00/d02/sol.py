
ref = ["A","B","C"]

## part11
# ROCK beats SCISSORS   A beats C  0,2
# PAPER  beats ROCK   B beats A   1,0
# SCISSORS beats PAPER  C beats B  2,1

points = {
    "A" : {
        "A": 1+3,
        "B": 2+6,
        "C": 3+0
    },
    "B" : {
        "A": 1+0,
        "B": 2+3,
        "C": 3+6
    },
    "C" : {
        "A": 1+6,
        "B": 2+0,
        "C": 3+3
    },
    

}


f = open("marcomole00/d02/input.txt","r").readlines()

f1 = list(map(lambda s: s.replace("\n", "").replace("X", "A").replace("Y", "B").replace("Z", "C"),f))


my_points1 = 0

for p in f1:
    opponent, me = p.split(" ")
    my_points1+= points[opponent][me]


print(my_points1)



### part 2

my_points2 =0

# X lose, Y draw, Z wins

f2 = list(map(lambda s: s.strip(),f))

for p in f2:
    opponent, result = p.split(" ")
    
 
    if (result == "X"):
        my_points2 += points[opponent][ref[ref.index(opponent)-1]]
    if (result == "Y"):
        my_points2 += points[opponent][ref[ref.index(opponent)]]
    if (result == "Z"):
        my_points2 += points[opponent][ref[(ref.index(opponent)+1)%3]]

print(my_points2)