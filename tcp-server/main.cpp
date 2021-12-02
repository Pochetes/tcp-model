#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

using namespace std;

#define MAXBUFSIZE 4096

int main() {
    /* create a socket */
    int listening = socket(AF_INET, SOCK_STREAM, 0);
    if(listening == -1) {
        cerr << "can't create a socket!";
        return -1;
    }
    
    /* bind the socket to a IP / port */
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(54000);
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);

    if(bind(listening, (sockaddr*)&hint, sizeof(hint)) == -1) {
        cerr << "can't bind to IP/port";
        return -2;
    }

    /* mark the socket for listening in */
    if(listen(listening, SOMAXCONN) == -1) {
        cerr << "can't listen!";
        return -3;
    }
    /* accept a call */
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);
    char host[NI_MAXHOST];
    char svc[NI_MAXSERV];

    int clientSocket = accept(listening, (sockaddr*)&client, &clientSize);
    if(clientSocket == -1) {
        cerr << "problem with client connecting!";
        return -4;
    }
    /* close the listening socket */
    close(listening);

    memset(host, 0, NI_MAXHOST);
    memset(svc, 0 , NI_MAXSERV);

    int result = getnameinfo((sockaddr*)&client, clientSize, host, NI_MAXHOST, svc, NI_MAXSERV, 0);

    if(result) {
        cout << host << " connected on " << svc << endl;
    } else {
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        cout << host << " connected on " << ntohs(client.sin_port) << endl;
    }

    /* while receiving - display & echo message */
    char buf[MAXBUFSIZE];
    while(true) {
        // clear the buffer
        memset(buf, 0, MAXBUFSIZE);
        // wait for a message
        int bytesReceived = recv(clientSocket, buf, MAXBUFSIZE, 0);
        if(bytesReceived == -1) {
            cerr << "there was a connection issue" << endl;
            break;
        }

        if(!bytesReceived) {
            cout << "the client disconnected" << endl;
            break;
        }
        // display message
        cout << "Received: " << string(buf, 0, bytesReceived) << endl;
        // resend message
        send(clientSocket, buf, bytesReceived + 1, 0);
    }
    /* close socket */
    close(clientSocket);

    return 0;
}