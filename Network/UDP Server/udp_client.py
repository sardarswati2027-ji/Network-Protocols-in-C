import socket

HOST = "127.0.0.1"
PORT = 5000

client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

message = "Hello from UDP Client"
client.sendto(message.encode(), (HOST, PORT))

data, addr = client.recvfrom(1024)
print("Server:", data.decode())

client.close()