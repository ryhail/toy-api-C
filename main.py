import socket
import os

def startServer():
    server_socket = socket.create_server(("localhost", 4221))
    print("Server started")
    while True:
        conn, addr = server_socket.accept()   # wait for client
        data = conn.recv(1024)
        req_file = open("reqFile.txt", "w")
        req_file.write(data.decode("utf-8"))
        req_file.close()
        os.system("chandler\cmake-build-debug\chandler.exe")
        resp_file = open("respFile.bin", 'r')
        response = bytes(resp_file.read(), encoding="utf-8")
        conn.sendall(response)


if __name__ == '__main__':
    startServer()