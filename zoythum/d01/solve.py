from sys import exit

with open('input.txt') as f:
	data = [x.strip() for x in f.readlines()]

def part_one(data):
	curr_max = 0
	curr = 0

	for cal in data:
		
		if cal == '':
			curr_max = curr_max if curr < curr_max else curr
			curr = 0
			continue

		curr += int(cal)

	print(curr_max)

def part_two(data):
	calories = []
	curr = 0

	for cal in data:
		
		if cal == '':
			calories.append(curr)
			curr = 0
			continue

		curr += int(cal)

	print(sum(sorted(calories, reverse=True)[:3]))


part_two(data)