f = open("OfficialRainfallIntensityNEA.txt", "r")
things = f.read().split("|")
counter = 1
f.close()

f = open("RainfallIntensityParsed.txt", "w+")
for thing in things:
        if len(thing.split(",")) == 3:
                f.write(str(counter) + " " + thing + "\n")
                counter += 1
f.close()
