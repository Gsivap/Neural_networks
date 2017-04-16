import csv 
import sys
import numpy as np
 
f1 = open(sys.argv[1])

a =[]
labels =[]
i = 0
j=0
k=0
reader = csv.reader(f1)

with open('file.txt', 'w') as fi:
	for row in reader:
			if(k <10000):
				a= row[1:784]
				for s in a:
					fi.write(s +' ')
				fi.write("\n")
				k = k +1;

fi.close()
'''
for rows in reader:
	if ( j <10000):
	
		labels.append(int(rows[0]))
		j = j + 1;
	#print(rows[0])



arr = np.array(labels)
print(np.shape(arr))

b = np.zeros((10000, 10))
b[np.arange(10000), arr] = 1

with open('onehot.txt', 'w') as fil:
	for i in range(0,10000):
		for j in range(0,10):
			fil.write(str(int(b[i][j])) + ' ')
		fil.write("\n")


fil.close()
'''		
f1.close()

