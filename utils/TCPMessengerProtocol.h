#ifndef UNTITLED_TCPMESSENGERPROTOCOL_H
#define UNTITLED_TCPMESSENGERPROTOCOL_H

/**
 * TCP Messenger protocol:
 * all messages are of the format [Command 4 byte int]
 * and optionally data follows in the format [Data length 4 byte int][ Data ]
 */
#define MSNGR_PORT 3346

#define CLOSE_SESSION_WITH_PEER 	1
#define OPEN_SESSION_WITH_PEER 		2
#define EXIT						3
#define SEND_MSG_TO_PEER			4
#define SESSION_REFUSED				5
#define SESSION_ESTABLISHED			6
#define LOGIN_OR_REGISTER           10
#define SUCCESS                     11
#define GET_USERS_LIST              12
#define GAME_SESSION                13
#define ROCK                        30
#define PAPER                       31
#define SCISSORS                    32
#define GAME_OVER                   14
#define OPEN_SESSION_WITH_RANDOM_PEER 15



#define TEST_PEER_NAME "test"
#define SESSION_REFUSED_MSG "Connection to peer refused, peer might be busy or disconnected, try again later"
#include "TCPSocket.h"
#include <pthread.h>
#include <unistd.h>
#include <vector>
#include <iostream>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <errno.h>
using namespace std;
namespace npl {
    class TCPMessengerProtocol {
    public:
        void static sendToServer(int command,const string& data, TCPSocket* sock) {
            char com[4];
            *((int*) com) = htonl(command);
            sock->write(com, 4);
            if (data.length() > 0) {
                char len[4];
                *((int*) len) = htonl(data.length());
                sock->write(len, 4);

                sock->write(data.c_str(), data.length());
            }
        }
        void static readFromServer(int& command, string& data,TCPSocket* sock) {
            int com;
            sock->read((char*) &com, 4);
            command = ntohl(com);
            char buff[1024];
            int len;
            sock->read((char*) &len, 4);
            len = ntohl(len);
            sock->read(buff, len);
            buff[len] = '\0';
            data = buff;
//            cout << data << endl;
        }
    };
}
#endif //UNTITLED_TCPMESSENGERPROTOCOL_H