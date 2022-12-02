def part1(filename):
	score = 0
	ascii = ord('A')
	dist = ord('X') - ord('A')
	with open(filename) as f:
		for l in f :
			#l.strip()
			#print(l[0])
			#print(l[2])
			if ord(l[0])==(ord(l[2]) - dist): 
				#draw
				
				score += ((ord(l[0]) - ascii + 1) + 3)
				#print(l[0], l[2], "score = ", ((ord(l[0]) - ascii + 1) + 3))
			if l[0]=='A' and l[2] == 'Y': 
				score += 2+6
			if l[0]=='A' and l[2] == 'Z': 
				score += 3+0
			if l[0]=='B' and l[2] == 'X': 
				score += 1+0
			if l[0]=='B' and l[2] == 'Z': 
				score += 3+6
			if l[0]=='C' and l[2] == 'X': 
				score += 1+6
			if l[0]=='C' and l[2] == 'Y': 
				score += 2+0
	print(score)

output_line = ['A', ' ', 'X']
out = open('marcoparadina/d02/out.txt', 'w')
with open('marcoparadina/d02/input.txt') as f:
	for l in f:
		output_line[0] = l[0]
		if l[2] == 'X': 
			#lose
			if l[0] == 'A':
				output_line[2] = 'Z'
			if l[0] == 'B':
				output_line[2] = 'X'
			if l[0] == 'C':
				output_line[2] = 'Y'
		if l[2] == 'Y':
			#draw
			if l[0] == 'A':
				output_line[2] = 'X'
			if l[0] == 'B':
				output_line[2] = 'Y'
			if l[0] == 'C':
				output_line[2] = 'Z'
		if l[2] == 'Z': 
			#win
			if l[0] == 'A':
				output_line[2] = 'Y'
			if l[0] == 'B':
				output_line[2] = 'Z'
			if l[0] == 'C':
				output_line[2] = 'X'
		for i in output_line:
			out.write(i)
		out.write('\n')
out.close()
part1('marcoparadina/d02/out.txt')
		