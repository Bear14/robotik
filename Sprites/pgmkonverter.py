""" .pgm Bilddatei in ein aray umwandeln

"""
import math

if __name__ == '__main__':
    x = 4
    y = 64
    sprite = [[2]*x for i in range(y)]
    pages = [[2]*y for i in range(x)]
    k=0
    file = open("Hero.pgm", "r")

    for line in file:
        if k > 3:
            print(k)
            if line.rstrip() == "255":
                sprite[math.floor((k-4)/y)][(k-4)%x] ="00"
            elif line.rstrip() == "162":
                sprite[math.floor((k-4)/x)][(k-4)%y]  ="01"
            elif line.rstrip() == "114":
                sprite[math.floor((k-4)/x)][(k-4)%y] ="10"
            elif line.rstrip() == "62":
                sprite[math.floor((k-4)/x)][(k-4)%y] ="11"
            else:
                print("wert nicht erfasst")
                break
        k=k+1

    file.close()

    print (sprite)

    k=0
    for row in sprite:
        for elem in row:
            print(elem, end=' ')
        print()

    file2 = open("sprits.txt", "w")

    file2.close()
