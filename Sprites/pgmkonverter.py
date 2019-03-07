""" .pgm Bilddatei in ein aray umwandeln

"""
import math

if __name__ == '__main__':
    #WO soll das Bild beginnen Linkes Eck

    picsize = 16  #wquatratisches Bild

    x=0
    y=0
    pic = [[2]*picsize for i in range(picsize)]
    pages = []
    k=0 #zaehlt die Zeilen
    h=0 #zaehlt ab dem ersten Pixel'
    buffer = "33"

    quell = input("Quelldatei: (nur .pgm)")
    ziel = input("Name der Zieldatei: ")
    quellfile = open(quell, "r")
    zielfile = open(ziel, "w")
    for line in quellfile: #Werte werden 2bit weise angeordnet
        #Die ersten 4 Zeilen dienern der Beschreibung der Datei
        #Sind fuer uns irrelevant
        if k > 3:
            if line.rstrip() == "255": buffer="00"
            elif line.rstrip() == "162": buffer="01"
            elif line.rstrip() == "114": buffer="10"
            elif line.rstrip() == "62": buffer="11"
            else:
                print("wert nicht erfasst")
                break

            #Bild wird an der Hauptachse gespiegelt gespeichert
            pic[h%picsize][int(math.floor(h/picsize))] =str(buffer)

            h=h+1
        k=k+1
    quellfile.close()

    for i in range(len(pic)):
        for j in range(0,len(pic[i]), 4):
            #Das das Display von unten nach oben die Pages Schreibt
            pages.append(int(pic[i][j+3] + pic[i][j+2] + pic[i][j+1] + pic[i][j] ,2))

    for elem in pages:
        zielfile.write("page(x+"+str(x)+",y+"+str(y)+",0x%02X" %(elem))

        y=y+1
        #Am ende der ersten Pixelzeile in die naechste Pixelzeile springen
        if y == int(picsize/4):
            y=0
            x=x+1
        zielfile.write(");\n")

    zielfile.close()
