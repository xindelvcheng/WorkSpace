import os

for root, dirs, files in os.walk('.'):
	for file in files:
		if file.endswith(".ipynb"):
			os.system("jupyter nbconvert --to html {}".format(os.path.join(root,file)))
