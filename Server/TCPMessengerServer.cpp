//
// Created by omrih on 21-Jun-17.
//



#include "TCPMessengerServer.h"
using namespace npl ;

TCPMessengerServer::TCPMessengerServer() {
    sock = new TCPSocket(3346);
    dispacher = new Dispatcher();
    start();
}

void TCPMessengerServer::listpeer(){
    dispacher->listPeer();
}
void TCPMessengerServer::exit(){
    sock->close();
    waitForThread();
    dispacher->close();


}
void TCPMessengerServer::run(){

    while(true){
        TCPSocket* peer = sock->listenAndAccept();
        if (peer == NULL){
            break;
        }
        dispacher->add(peer);

    }

}

TCPMessengerServer::~TCPMessengerServer() {
    // TODO Auto-generated destructor stub
}
