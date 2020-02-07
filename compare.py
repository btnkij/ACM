
if __name__ == '__main__':
	with open('out.txt','r') as out, open('out1.txt','r') as out1:
		i = 1
		while True:
			line = out.readline()
			line1 = out1.readline()
			if line and line1:
				if line != line1:
					print('第{}行'.format(i))
					print(line)
					print(line1)
					print()
			elif not line and not line1:
				break
			else:
				print('行数不一致')
				break
			i+=1