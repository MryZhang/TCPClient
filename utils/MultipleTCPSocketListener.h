//
// Created by omrih on 21-Jun-17.
//

#ifndef UNTITLED_MULTIPLETCPSOCKETLISTENER_H
#define UNTITLED_MULTIPLETCPSOCKETLISTENER_H



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
#define max_clients 30

using namespace std;

namespace npl {

    class MultipleTCPSocketListener {

        vector<TCPSocket*> sockVec;
    protected:

    public:
        MultipleTCPSocketListener();
        /*
         * add socket to listen
         */
        void add(TCPSocket* sock);


        void add(vector<TCPSocket*> sockVec);

        /*
         * listen to
         */
        TCPSocket* listen(int timeout=0);

        virtual ~MultipleTCPSocketListener();
    };

}

#endif //UNTITLED_MULTIPLETCPSOCKETLISTENER_H
