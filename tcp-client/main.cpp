#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

using namespace std;

#define PORT 54000
#define MAXBUFSIZ 4096
#define IP "127.0.0.1"

int main() {
    /* create a socket */
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1) {
        return 1;
    }
    /* create a hint structure for the server we're connecting with */
    string ipAddress = IP;

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(PORT);
    inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);
    
    /* connect to the server on the socket */
    int connectRes = connect(sock, (sockaddr*)&hint, sizeof(hint));
    if(connectRes == -1) {
        return 2;
    }

    char buf[MAXBUFSIZ];
    string userInput;

    do {
        cout << "> ";
        getline(cin, userInput);

        /* send to the server */
        int sendRes = send(sock, userInput.c_str(), userInput.size() + 1, 0);
        if(sendRes == -1) {
            cout << "could not send to server!\r\n";
            continue;
        }

        memset(buf, 0, MAXBUFSIZ);
        int bytesReceived = recv(sock, buf, MAXBUFSIZ, 0);

        /* display response */
        cout << "SERVER> " << string(buf, bytesReceived) << "\r\n";

    } while(true);

    /* close the socket */
    close(sock);

    return 0;
}