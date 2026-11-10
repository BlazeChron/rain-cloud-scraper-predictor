f = open("rainpixels.txt", "r")
things = f.read().replace("\n", "").replace("]", "").split("[")
dic = {}
for thing in things:
        if thing in dic:
                dic[thing]+=1
        else:
                dic[thing] = 1

for key in dic.keys():
        if dic[key] > 1:
                print(key + ": " + str(dic[key]))

# section to print out [] arrays to check visualiser
for key in dic.keys():
        if dic[key] > 1:
                print("[" + key + "]", end="") 
        else:
                print("[0,0,0,0]",end="") 

f.close()
