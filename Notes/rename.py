import os
for root, dirs, files in os.walk("."):
    for file in files:
    	if file.endswith(".md.txt"):
    		os.rename(os.path.join(root,file),os.path.join(root,file.split(".")[0]+".md"))