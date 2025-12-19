import threading
import socket

host = '127.0.0.1' # local host
port = 12344

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind((host, port))
server.listen()

clients = []
nicknames = []
moves = {}

def win(p1, p2):
    if p1 == p2:
        message = f"Both have selected {p1}. Tie\n"
        return message, message
    elif p1 == "1":
        if p2 == "3":
            return f"Rock breaks Scissors. You won this round\n", f"Rock breaks Scissors.You lost this round\n"
        else:
            return f"Paper hides Rock. You lost this round\n", f"Paper hides Rock. You won this round\n"

    elif p1 == "2":
        if p2 == "1":
            return f"Paper hides Rock. You won this round\n", f"Paper hides Rock.You lost this round\n"
        else:
            return f"Scissors cut Paper. You lost this round\n", f"Scissors cut Paper. You won this round\n"

    elif p1 == "3":
        if p2 == "2":
            return f"Scissors cut Paper. You won this round\n", f"Scissors cut Paper.You lost this round\n"
        else:
            return f"Rock breaks Scissors. You lost this round\n", f"Rock breaks Scissors. You won this round\n"
    return "Invalid input", "Invalid input"

def handle(client, nickname):
    global moves
    global nicknames
    while True:
        try:
            move = client.recv(1024).decode()
            moves[nickname] = move
            print(f"{nickname} played: {move}")
            if len(moves) == 2:
                P1 = nicknames[0]
                P2 = nicknames[1]
                P1_move = moves[P1]
                P2_move = moves[P2]
                msg1, msg2 = win(P1_move, P2_move)

                clients[0].send(msg1.encode())
                clients[1].send(msg2.encode())
                moves = {}
        except:
            index = clients.index(client)
            clients.remove(client)
            client.close()
            nickname = nicknames[index]
            win(f'{nickname} left the chat'.encode())
            nicknames.remove(nickname)
            break

def receive():
    print("Server is listening...")
    while True:
        print("Waiting for 2 players...")
        while len(clients) < 2:
            client, address = server.accept()
            print(f'Connected with {str(address)}')

            client.send("Nick".encode())
            nickname = client.recv(1024).decode()
            nicknames.append(nickname)
            clients.append(client)
            print(f'Nickname of the client is {nickname}')
            for client in clients:
                client.send(f'{nickname} joined the chat'.encode())
        print("Two players are connected. Starting game...")
        for client in clients:
            client.send("\nMake your move: ".encode())
        for i in range(2):
            thread = threading.Thread(target=handle, args=(clients[i], nicknames[i]))
            thread.start()
        break
receive()