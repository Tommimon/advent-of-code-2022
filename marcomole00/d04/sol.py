import re
f = open("marcomole00/d04/input","r").read().split("\n")

set_a,set_b = set(),set()

fully_contained_sets =0
number_of_overlaps =0
for l in f:
    elf1,elf2 = l.split(",")
   # elf1lb, elf1ub = map( lambda s: int(s) ,elf1.split("-"))
    elf1lb, elf1ub,elf2lb, elf2ub = map(int, re.findall(r'\d+',l))

    set_a = set(range(elf1lb,elf1ub+1))


   # elf2lb, elf2ub = map( lambda s: int(s) ,elf2.split("-"))
    set_b = set( range(elf2lb,elf2ub+1))

    if any(set_a & set_b):
        number_of_overlaps+=1

    if set_a <= set_b or set_b<=set_a:
        fully_contained_sets +=1
        

print(fully_contained_sets)
print(number_of_overlaps)