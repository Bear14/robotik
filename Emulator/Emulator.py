from graphics import *
import socket
import time

UDP_IP = "127.0.0.1"
UDP_PORT = 5005

RUNTIME = 20 #In seconds

SCALE = 5
BLACK = color_rgb(0,0,0)
DARKGREY = color_rgb(100,100,100)
LIGHTGREY = color_rgb(200,200,200)
WHITE = color_rgb(255,255,255)

def getColor(h,px):


    lala = str(bin(h))

    nex = lala[2:]

    if(len(nex) < 8):
        #nex = (8 - len(nex)) * "0" + nex
        #print((8 -len(nex)) * "0" + nex)
        nex = (8 - len(nex)) * "0" + nex
        pass

    #print(nex)
    #print(nex)
    ne = nex[px*2:px*2+2]
    #print("wad",ne)

    if(ne == "00"):
        return WHITE
    elif(ne == "01"):
        return LIGHTGREY
    elif(ne == "10"):
        return DARKGREY
    elif(ne == "11"):
        return BLACK
    pass

def page(x,y,h,window):
    y = y*4 * SCALE
    x = x * SCALE
    px_1 = Rectangle(Point(x,y),Point(x + SCALE-1,y + SCALE-1))
    px_1.setFill(getColor(h,3))
    px_1.setOutline(getColor(h,3))
    px_1.draw(window)

    px_2 = Rectangle(Point(x,y+1*SCALE),Point(x + SCALE-1,y+1*SCALE + SCALE-1))
    px_2.setFill(getColor(h,2))
    px_2.setOutline(getColor(h,2))
    px_2.draw(window)

    px_3 = Rectangle(Point(x,y+2*SCALE),Point(x + SCALE-1,y+2*SCALE +SCALE-1))
    px_3.setFill(getColor(h,1))
    px_3.setOutline(getColor(h,1))
    px_3.draw(window)

    px_4 = Rectangle(Point(x,y+3*SCALE),Point(x +SCALE-1,y+3*SCALE + SCALE-1))
    px_4.setFill(getColor(h,0))
    px_4.setOutline(getColor(h,0))
    px_4.draw(window)
    pass



sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP
sock.bind((UDP_IP, UDP_PORT))

win = GraphWin(width = 160 * SCALE, height = 104 * SCALE) # create a window
#win.setCoords(0, 0, 10, 10) # set the coordinates of the window; bottom left is (0, 0) and top right is (10, 10)

count = 0

win.setBackground(WHITE)

endTime = time.time() + RUNTIME


while(time.time() < endTime):
    count+=1
    data, addr = sock.recvfrom(1024) # buffer size is 1024 bytes

    out = data.decode().split(",")
    page(int(out[0]),int(out[1]),int(out[2]),win)

    #print("received message:", data)#.decode("Utf-8"))
    pass
win.close()