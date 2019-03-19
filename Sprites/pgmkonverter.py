
#.pgm Bilddatei in ein aray umwandeln
import math

if __name__ == '__main__':
    #WO soll das Bild beginnen Linkes Eck

    quell = input("Quelldatei: (nur .pgm)")
    ziel = input("Name der Zieldatei: ")

    quellfile = open(quell, "r")
    zielfile = open("Sprites", "a")

    quelllines = quellfile.read().splitlines()
    picwidth = int(quelllines[2].split(" ")[0])
    picheight = int(quelllines[2].split(" ")[1])

    x=0
    y=0
    pages = []
    pic = [[2]*picheight for i in range(picwidth)]

    buffer = '33'
    quelllines=quelllines[4:]
    quellfile.close()
    for i in range(len(quelllines)): #Werte werden 2bit weise angeordnet
        #Die ersten 4 Zeilen dienern der Beschreibung der Datei
        #Sind fuer uns irrelevant
        if 196 < int(quelllines[i])   <= 255: buffer="00"
        elif 138 < int(quelllines[i]) <= 196: buffer="01"
        elif 88 < int(quelllines[i]) <= 138: buffer="10"
        elif int(quelllines[i]) <= 88: buffer="11"
        else:
            print("wert nicht erfasst \n In Zeile", i+5)
            break
        #Bild wird an der Hauptachse gespiegelt gespeichert
        pic[i%picwidth][int(math.floor(i/picwidth))] =str(buffer)


    for i in range(len(pic)):
        for j in range(0,len(pic[i]), 4):
            #Das das Display von unten nach oben die Pages Schreibt
            pages.append(int(pic[i][j+3] + pic[i][j+2] + pic[i][j+1] + pic[i][j] ,2))

    
    for elem in pages:
        if elem != 0:
            zielfile.write("drawCorrect(x+"+str(x)+",y+"+str(y)+",0x%02X" %(elem)+");")
        y=y+4
        #Am ende der ersten Pixelzeile in die naechste Pixelzeile springen
        if y == int(picheight):
            y=0
            x=x+1
        elif y > int(picheight):
            print("Error: Hoehe ueberlaufen")

    zielfile.write("\n")
    zielfile.close()
