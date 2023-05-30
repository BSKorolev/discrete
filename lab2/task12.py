from functools import lru_cache
array = ['к','о','м','б','и','н','а','т','о','р','и','к','а']
lenght = len(array)
words = set()

for i in range(0,lenght):
    for x in range(0, lenght):
        if i!=x:
            for y in range(0, lenght):
                if(y!=i) & (y!=x):
                    for z in range(0, lenght):
                        if(z!=i) & (z!=x) & (z!=y):
                            for c in range(0, lenght):
                                if(c!=i) & (c!=x) & (c!=y) & (c!=z):
                                    for d in range(0, lenght):
                                        if(d!=i) & (d!=x) & (d!=y) & (d!=z) & (d!=c):
                                            words.add(array[i]+array[x]+array[y]+array[z]+array[c]+array[d])
print("Количество слов = ", len(words))
# Вычисление сотого элемента
@lru_cache(maxsize=100)
def recurrent(k):
    if k < 1:
        return 1
    if k == 1:
        return -7
    else:
        return int(5 * recurrent(k - 1) + 6 * recurrent(k - 2))


def general(k):
    return int(13/7 * (-1) ** n - 6/7 * 6 ** n)

n = input("Введите номер элемента :")
n = int(n)
print("n =",n)
print("Реккурентная формула:",recurrent(n))
print("Общее решение:",general(n))
if (recurrent(n) == general(n)):
    print("Равны")

