f = open("Rainfallintensitylegend.txt", "r")
things = f.read().split("|")
counter = 1

for thing in things:
        if len(thing.split(",")) == 3:
                print(str(counter) + " " + thing)
                counter += 1
