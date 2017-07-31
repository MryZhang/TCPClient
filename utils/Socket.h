//
// Created by omrih on 21-Jun-17.
//

#ifndef UNTITLED_SOCKET_H
#define UNTITLED_SOCKET_H

#include "FileInterface.h"
#include <netinet/in.h>
#include <inttypes.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>



using namespace std;
namespace npl{
    class Socket:public FileInterface{
    protected:
        struct sockaddr_in from,dest;
    public:
        virtual int bind(int port);
        virtual int connect(const string& ip,int port);
        virtual void close();
        virtual string fromAddr();
        virtual void clean_up(int cond, int *sock);
        Socket();
        virtual ~Socket();
    };
}

#endif //UNTITLED_SOCKET_H
