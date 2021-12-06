levels = list(map(int, open("input.txt")))

count = 0;
last = -1;

for i in levels:
    if (last >= 0 and i > last):
        count+=1
        print(i, "Higher");
    last = i 

print(count)