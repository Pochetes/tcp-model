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
    /* mark the socket for listening in */
    /* accept a call */
    /* close the listening socket */
    /* while receiving - display & echo message */
    /* close socket */

    return 0;
}