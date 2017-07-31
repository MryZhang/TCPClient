//
// Created by omrih on 21-Jun-17.
//

#ifndef UNTITLED_DISPATCHER_H
#define UNTITLED_DISPATCHER_H


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
#include"../utils/MultipleTCPSocketListener.h"
using namespace std;
namespace npl {

    class Dispatcher : public MThread{
        vector<TCPSocket*>peers;
        bool running ;
    public:
        Dispatcher();
        void add(TCPSocket* peer);
        void remove();
        void run();
        void listPeer();
        void close();
        TCPSocket  *FindPeer (TCPSocket * peer);

        virtual ~Dispatcher();
    };

}

#endif //UNTITLED_DISPATCHER_H
