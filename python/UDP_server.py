from socket import *                            # include Python's socket library
# Task: Print this for each message from the client
# The server is ready to receive

# Message from ('192.168.0.15', 63879)
# Message: hello world!

# Message from ('127.0.0.1', 63163)
# Message: there are 10 types of people in the world

def UDPServer():
    serverPort = 12000                          # specify the port number
    serverSocket = socket(AF_INET, SOCK_DGRAM)  # create the UDP socket
    serverSocket.bind(('', serverPort))         # bind the socket to the port; listening on the port 
    print("The server is ready to receive")     # message to let us know that the process started
    while True:                                 # loop forever
        message, clientAddress = serverSocket.recvfrom(2048)    # read from the UDP socket into the message; get's the clients IP and port #s
        modifiedMessage = message.decode().upper()              # converts the imput to all UPPER CASE - I KNOW, STOP YELLING

        print("Message from: ", clientAddress)
        print("Message: ", message.decode())
        print("")
    
        serverSocket.sendto(modifiedMessage.encode(), clientAddress)    # sends the string back to the client
        


# the following line invokes the funciton when this .py file is run
UDPServer()
