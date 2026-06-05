import socket

HOST = "127.0.0.1"
PORT = 5000

server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server.bind((HOST, PORT))

print(f"UDP Server listening on {HOST}:{PORT}")

while True:
    data, addr = server.recvfrom(1024)
    print(f"Received from {addr}: {data.decode()}")

    message = "Hello from UDP Server"
    server.sendto(message.encode(), addr)