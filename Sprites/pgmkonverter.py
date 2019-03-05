""" .pgm Bilddatei in ein aray umwandeln

"""
if __name__ == '__main__':
    sprite = []
    k=0
    file = open("Hero.pgm", "r")

    for line in file:
        if k > 3:
            if line.rstrip() == "255":
                sprite.append("00")
            elif line.rstrip() == "162":
                sprite.append("01")
            elif line.rstrip() == "114":
                sprite.append("10")
            elif line.rstrip() == "62":
                sprite.append("11")
        k=k+1
    k=0
    print(sprite)
    file.close()
    file2 = open("sprits.txt", "w")
    for i in range (16):
        for j in range (16):
            file2.write(sprite[k])
            k=k+1
        file2.write("\n")
    file2.close()
