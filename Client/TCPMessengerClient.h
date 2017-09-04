#ifndef UNTITLED_TCPMESSENGERCLIENT_H
#define UNTITLED_TCPMESSENGERCLIENT_H

#include <iostream>
#include <string.h>
#include <pthread.h>
#include "../utils/MThread.h"
#include "../utils/TCPSocket.h"
#include <unistd.h>
#include "../utils/TCPMessengerProtocol.h"
#include "../utils/UDPGame.h"


using namespace std;

namespace npl {

    class TCPMessengerClient :public MThread{
        TCPSocket* sock;
        bool stopRun ;
        bool isConnected = false;
        bool * game_on;
        int *ref_acc;
    public:
        string remote_ip;
        TCPMessengerClient(bool * game_on,int *ref_acc);
        void connect(const string& ip);
        void openSession(const string& username);
        void send(const string msg);
        void login_or_register();
        void send (int cmd , string msg);
        void closeSession();
        void disconnect();

        void run();

        virtual ~TCPMessengerClient();
    };

}
#endif
