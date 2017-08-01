//
// Created by omrih on 21-Jun-17.
//
#include "TCPMessengerClient.h"
#include "../utils/TCPMessengerProtocol.h"

using namespace npl;


TCPMessengerClient::TCPMessengerClient(){
    this->sock = NULL;
    this->stopRun = false;

}



void TCPMessengerClient::connect(const string& ip) {
    if (this->stopRun==false)
    {
        sock = new TCPSocket(ip, MSNGR_PORT);
        this->start();
        cout << "connecting to server" << ip << endl << flush;
    }else
        cout<<"server already connected!"<<endl<<flush;
}

void TCPMessengerClient::openSession(const string& ipAndPort) {
    cout << "openSession with server" << ipAndPort << endl << flush;
    TCPMessengerProtocol::sendToServer(OPEN_SESSION_WITH_PEER, ipAndPort, sock);

}
void TCPMessengerClient::send(const string msg) {
    cout << "sending msg to server" << msg << endl << flush;
    TCPMessengerProtocol::sendToServer(SEND_MSG_TO_PEER, msg, sock);
}

void TCPMessengerClient::send(int cmd, string msg) {
    cout << "sending message cmd = "<< cmd << endl << flush;
    TCPMessengerProtocol::sendToServer(cmd, msg, sock);
}

void TCPMessengerClient::login_or_register() {
    string msg;
    msg.clear();
    //selection - 1-login 2-register
    cin >> msg;
    TCPMessengerProtocol::sendToServer(LOGIN_OR_REGISTER, msg, sock);
    while (!this->isConnected){
        //username
        cin >> msg;
        TCPMessengerProtocol::sendToServer(LOGIN_OR_REGISTER, msg, sock);
        //password
        cin >> msg;
        TCPMessengerProtocol::sendToServer(LOGIN_OR_REGISTER, msg, sock);
    }

}

void TCPMessengerClient::closeSession() {
    cout << "closeSession with server" << endl << flush;
    TCPMessengerProtocol::sendToServer(CLOSE_SESSION_WITH_PEER, "", sock);
}

void TCPMessengerClient::disconnect() {
    cout << "disconnect from server" << endl << flush;
    stopRun = false;
    TCPMessengerProtocol::sendToServer(EXIT, "", sock);
}

void TCPMessengerClient::run(){
    int command ;
    string data ;
    stopRun = true;
    while(stopRun){
        TCPMessengerProtocol::readFromServer(command,data,sock);
        switch (command){
            case SESSION_REFUSED:
                break;
            case SUCCESS:
                this->isConnected = true;
                break;
        }
    }
    cout<< "stop receiving data"<<endl;
}

TCPMessengerClient::~TCPMessengerClient() {
    // TODO Auto-generated destructor stub
}
