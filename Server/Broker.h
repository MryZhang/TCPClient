//
// Created by omrih on 21-Jun-17.
//

#ifndef UNTITLED_BROCKER_H
#define UNTITLED_BROCKER_H


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
using namespace npl;

class Broker : public MThread{
    TCPSocket* peer1;
    TCPSocket* peer2;
    bool running ;
public:
    Broker();
    void add(TCPSocket* peer1 , TCPSocket * peer2);
    void run();
    void close();
    virtual ~Broker();
};



#endif //UNTITLED_BROCKER_H
