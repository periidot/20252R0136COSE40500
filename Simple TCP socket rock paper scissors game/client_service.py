import threading
import socket
from _ast import While

host = '127.0.0.1' # local host
port = 12344

nickname = input("Choose a nickname: ")

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect((host, port))

def receive():
    print("Game of Rock Paper Scissors. Available actions:")
    print("1 = Rock,  2 = Paper,  3 = Scissors\n")
    while True:
        try:
            message = client.recv(1024).decode()
            if message == 'Nick':
                client.send(nickname.encode())
            else:
                print(message)
        except:
            print("An error has occurred...")
            client.close()
            break


def write():
    while True:
        move = input("")
        client.send(move.encode())


receive_thread = threading.Thread(target=receive)
receive_thread.start()

write_thread = threading.Thread(target=write)
write_thread.start()