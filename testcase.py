import string
import random
 
# initializing size of string

with open('TestCase.txt', 'w') as f:

	for i in range(0,10000000):
		N = random.randint(7,14)
		 
		# using random.choices()
		# generating random strings
		res = ''.join(random.choices(string.ascii_lowercase, k=N))
		 
		# print result
		#print(str(res)," ",random.randint(10,100000))
		f.write(str(res) + " " + str(random.randint(10,100000)) + '\n')
