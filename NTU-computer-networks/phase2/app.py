import socket 
import threading
from database.access import*

BUFFER_SIZE = 1024
IP_ADDRESS = "0.0.0.0"
PORT = 8080
FORMAT = "utf-8"
LISTEN_NUM = 20

JSON_HEADER = \
    "HTTP/1.1 200 OK\n" \
    "Content-Type: application/json\n" \
    "\n".encode(FORMAT)

HTML_HEADER = \
    "HTTP/1.1 200 OK\n" \
    "Content-Type: text/html\n" \
    "\n".encode(FORMAT)

MP3_HEADER = \
    "HTTP/1.1 200 OK\n" \
    "Content-Type: audio/mpeg3\n"\
    "Accept-Ranges: none\n" \
    "Content-Length: 3329924\n" \
    "\n".encode(FORMAT)

MP4_HEADER = \
    "HTTP/1.1 200 OK\n" \
    "Content-Type: video/mpeg4\n" \
    "Accept-Ranges: none\n" \
    "Content-Length: 13004681\n" \
    "\n".encode(FORMAT)

ERROR_HEADER = \
    "HTTP/1.1 404 NOT FOUNDd\n" \
    "Content-Type: text/html\n"\
    "\n".encode(FORMAT)\

def read_file(filename):
    f = open(filename, mode="rb")
    data = f.read()
    f.close()
    return data

def handle_client(conn, addr):
    payload = conn.recv(BUFFER_SIZE).decode(FORMAT)
    method, endpoint = payload.split(" ")[0],payload.split(" ")[1]
    agent = addr[0]
    print(f"\n{addr,method,endpoint,agent}: \n{payload}\n")
    
    if endpoint == "/" and method == "GET":
        conn.send(HTML_HEADER)
        conn.send(read_file("./templates/index.html"))

    elif endpoint == "/agent" and method == "GET":
        conn.send(JSON_HEADER)
        username = login_status(agent)
        conn.send(username.encode(FORMAT))
        
    elif endpoint == "/login" and method == "GET":
        conn.send(HTML_HEADER)
        conn.send(read_file("./templates/login.html"))

    elif endpoint == "/auth/login" and method == "POST":
        data = conn.recv(BUFFER_SIZE).decode(FORMAT)
        p = data.split('&')
        username = p[0].split('=')[1]
        password = p[1].split('=')[1]
        conn.send(JSON_HEADER)
        if login(agent,username,password):
            conn.send("true".encode(FORMAT))
        else:
            conn.send("false".encode(FORMAT))

    elif endpoint == "/logout" and method == "POST":
        logout(agent)
        conn.send(HTML_HEADER)
        conn.send(read_file("./templates/login.html"))

    elif endpoint == "/register" and method == "GET":
        conn.send(HTML_HEADER)
        conn.send(read_file("./templates/register.html"))

    elif endpoint == "/auth/register" and method == "POST":
        data = conn.recv(BUFFER_SIZE).decode(FORMAT)
        p = data.split('&')
        username = p[0].split('=')[1]
        password = p[1].split('=')[1]
        register(username,password)
        conn.send("done".encode(FORMAT))

    elif endpoint == "/comment" and method == "POST":
        data = conn.recv(BUFFER_SIZE).decode(FORMAT)
        p = data.split('&')
        username = p[0]
        msg = p[1]
        comment(username,msg)
        conn.send(JSON_HEADER)

    elif endpoint == "/comment.json" and method == "GET":
        comment_data = get_comment_data()
        conn.send(JSON_HEADER)
        for c in comment_data:
            conn.send((c[0]+':'+c[1]+',').encode(FORMAT))


    elif endpoint == "/source.mp3" and method == "GET":
        conn.send(MP3_HEADER)
        conn.send(read_file("./assets/source.mp3"))

    elif endpoint == "/source.mp4" and method == "GET":
        conn.send(MP4_HEADER)
        conn.sendall(read_file("./assets/source.mp4"))

    else:
        conn.send(ERROR_HEADER)
        conn.send(read_file("./templates/404.html"))
    conn.close()
    
def main():
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # TCP protocol
    server.bind((IP_ADDRESS, PORT))
    server.listen(LISTEN_NUM)
    print(f"Server is listening on {IP_ADDRESS}:{PORT}")
    while True:
        conn, addr = server.accept()
        thread = threading.Thread(target=handle_client, args=(conn, addr))
        thread.start()
        print(f"[ACTIVE CONNECTIO NS] {threading.activeCount() - 1}")

if __name__ == "__main__":
    main()