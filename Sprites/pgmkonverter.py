""" .pgm Bilddatei in ein aray umwandeln

"""
import math

if __name__ == '__main__':
    #WO soll das Bild beginnen Linkes Eck
    x=0
    y=0

    picsize = 16  #wquatratisches Bild

    pagesize = 4 #Fix

    #pic = [[2]*picsize for i in range(picsize)]
    picmirror = [[2]*picsize for i in range(picsize)]
    pages = []
    k=0
    h=0
    buffer = "33"
    file = open("Hero.pgm", "r")

    for line in file: #Werte werden 2bit weise angeordnet
        if k > 3:
            h = k-4

            if line.rstrip() == "255":   buffer="00"
            elif line.rstrip() == "162": buffer="01"
            elif line.rstrip() == "114": buffer="10"
            elif line.rstrip() == "62": buffer="11"
            else:
                print("wert nicht erfasst")
                break
            # pic[Y-wert][X-Wert] Jeder Y-Wert bildet eine neue Liste in pic
            #pic[math.floor(h/picsize)][h%picsize]=buffer

            #Bild wird an der Hauptachse gespiegelt gespeichert
            picmirror[h%picsize][math.floor(h/picsize)]=buffer
        k=k+1

    file.close()

    for i in range(len(picmirror)):
        for j in range(0,len(picmirror[i]), 4):
            #print(elem, end=' ')
            print(i,"|",j,"  ")
            pages.append(str(hex(int(picmirror[i][j]+picmirror[i][j+1]+
            picmirror[i][j+2]+picmirror[i][j+3],2))) )

        print(pages)

    file2 = open("sprits.txt", "w")
    for row in pages:
        file2.write("page(")
        file2.write(str(x))
        file2.write(",")
        file2.write(str(y))
        file2.write(",")
        for elem in row:
            file2.write(elem)
            file2.write("")
        x=x+1
        if x == 16:
            x=0
            y=y+1
        file2.write(")\n")


"""
    file2.close()

    file3 = open("sprits2.txt", "w")

    for i in range(picsize):
        for j in range(picsize):
            file3.write(pic[j][i])
            file3.write(" ")
        file3.write("\n")

    file3.close()
"""
