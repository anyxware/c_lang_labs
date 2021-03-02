file2 = ""
while(True):
	file = open("students.txt")
	file1 = file2
	file2 = file.read()
	if(file1 != file2):
		print(file2[:-1])

