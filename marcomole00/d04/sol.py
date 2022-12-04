f = open("marcomole00/d04/input","r").read().split("\n")

set_a,set_b = set(),set()

fully_contained_sets =0
number_of_overlaps =0
for l in f:
    elf1,elf2 = l.split(",")
    elf1lb, elf1ub = map( lambda s: int(s) ,elf1.split("-"))
    set_a = {x for x in range(elf1lb,elf1ub+1)}


    elf2lb, elf2ub = map( lambda s: int(s) ,elf2.split("-"))
    set_b = {x for x in range(elf2lb,elf2ub+1)}

    if len(set_a & set_b) > 0:
        number_of_overlaps+=1

    if (set_a & set_b) == set_a or (set_a & set_b) == set_b:
        fully_contained_sets +=1
        

print(fully_contained_sets)
print(number_of_overlaps)