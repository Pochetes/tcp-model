#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

using namespace std;

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
    /* accept a call */
    /* close the listening socket */
    /* while receiving - display & echo message */
    /* close socket */

    return 0;
}