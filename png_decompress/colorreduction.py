import heapq

heap = []
dic = {}

f = open("rainpixels.txt", "r")
things = f.read().replace("\n", "").replace("]", "").split("[")

for thing in things:
        if thing in dic:
                dic[thing]+=1
        else:
                dic[thing] = 1

diclist = list(filter(lambda x : dic[x] > 1, list(dic.keys())))

def euc_dst(v0, v1):
        l0 = list(map(lambda x: int(x), v0.split(",")))
        l1 = list(map(lambda x: int(x), v1.split(",")))
        r = (l0[0] - l1[0])
        g = (l0[1] - l1[1])
        b = (l0[2] - l1[2])
        return r * r + g * g + b * b

for i in range(len(diclist)):
        for j in range(i + 1, len(diclist)):
                dst = euc_dst(diclist[i], diclist[j])
                heapq.heappush(heap, (dst, (diclist[i], diclist[j])))

for i in range(33):
        smol = heapq.heappop(heap)
        print(smol)
