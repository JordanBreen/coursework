# URL: http://127.0.0.1:9876/C:/Users/jorda/Desktop/Webserver/HelloWorld.html
# URL: http://174.197.200.43:9876/C:/Users/jorda/Desktop/Webserver/HelloWorld.html

# Import socket module
from socket import * 
import sys    # In order to terminate the program

# Create a TCP server socket
#(AF_INET is used for IPv4 protocols)
#(SOCK_STREAM is used for TCP)

serverSocket = socket(AF_INET, SOCK_STREAM)

# Assign a port number
serverPort = 9876
serverHost = ''

# Bind the socket to server address and server port
serverSocket.bind(("", serverPort))

# Listen to at most 1 connection at a time
serverSocket.listen(1)             

# Server should be up and running and listening to the incoming connections

while True:
     print('The server is ready to receive')

     # Set up a new connection from the client
     connectionSocket, addr = serverSocket.accept()              

     # If an exception occurs during the execution of try clause
     # the rest of the clause is skipped
     # If the exception type matches the word after except
     # the except clause is executed
     try:
         # Receives the request message from the client
         message = connectionSocket.recv(1024).decode()  
       
         # Extract the path of the requested object from the message
         # The path is the second part of HTTP header, identified by [1]
         filename = message.split()[1]

         # Because the extracted path of the HTTP request includes 
         # a character '\', we read the path from the second character 
         f = open(filename[1:])
        
         # Store the contenet of the requested file in a temporary buffer
         outputdata = f.read()
        
         # Send the HTTP response header line to the connection socket as 
         # per RFC2616 Sections 3.1 and 10.2.1.  Be sure to end the 
         # message with a pair of CRLFs as \r\n\r\n
         connectionSocket.send("HTTP/1.1 200 OK\r\n\r\n".encode())           
 
         # Send the content of the requested file to the connection socket
         for i in range(0, len(outputdata)):  
             connectionSocket.send(outputdata[i].encode())
         connectionSocket.send("\r\n".encode()) 
          
         # Close the client connection socket
         connectionSocket.close()

     except IOError:
         # Send HTTP response header for file not found as per RFC2616 
         # Sections 3.1 and 10.4.5.  Be sure to end the message with a 
         # pair of CRLFs as \r\n\r\n
         connectionSocket.send("HTTP/1.1 404 Not Found\r\n\r\n".encode())             
                        
         # Send an HTML response *message* with the error code and
         # description. End the message with a single CRLF as \r\n 
         connectionSocket.send("File not found.\r\n".encode())                
            
         # Close the client connection socket
         connectionSocket.close()

serverSocket.close()  
sys.exit()  #Terminate the program after sending the corresponding data
