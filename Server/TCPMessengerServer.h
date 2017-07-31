//
// Created by omrih on 21-Jun-17.
//

#ifndef UNTITLED_TCPMESSENGERSERVER_H
#define UNTITLED_TCPMESSENGERSERVER_H

#include "../utils/TCPSocket.h"
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
#include "../utils/MThread.h"
#include "../utils/TCPMessengerProtocol.h"
#include "Dispatcher.h"
using namespace std;
namespace npl {

    class TCPMessengerServer :public MThread{
        TCPSocket* sock;
        Dispatcher* dispacher;
    public:

        TCPMessengerServer();

        void listpeer();
        void exit();
        void run();




        virtual ~TCPMessengerServer();
    };

}
#endif //UNTITLED_TCPMESSENGERSERVER_H
