from socket import *                                    # include Python's socket library


def UDPClient():
    serverName = '127.0.0.1'                            # this is the loopback IP address
    serverPort = 12000                                  # specify the port number
    clientSocket = socket(AF_INET, SOCK_DGRAM)          # create the UDP socket
    quit = False
    print ("(Type quit to end UDP Session)\n")
    while(quit != True):
        message = input('Input lowercase sentence:')        # prompt the user and get keyboard inpur
        if(message != "quit"):
            clientSocket.sendto(message.encode(),(serverName, serverPort))  # attach server name and port to the message; drop it in the socket
            modifiedMessage, serverAddress = clientSocket.recvfrom(2048)    # read reply from the server
            print(modifiedMessage.decode())                     # display the received message
        else:
            quit = True
    clientSocket.close()

# the following line invokes the funciton when this .py file is run
UDPClient()
