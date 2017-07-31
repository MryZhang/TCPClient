//
// Created by omrih on 21-Jun-17.
//
#include "Broker.h"
#include "../utils/TCPMessengerProtocol.h"
using namespace npl ;

Broker::Broker() {
    running = false;
}

void Broker:: add(TCPSocket* peer1,TCPSocket* peer2){
    this->peer1 = peer1;
    this->peer2 = peer2;
    if(!running){
        running = true;
        start();
    }

}

void Broker:: run(){
    while(true){
        MultipleTCPSocketListener listener;
        listener.add(peer1);
        listener.add(peer2);
        TCPSocket*peer = listener.listen(5);
        if(peer != NULL){
            int command;
            string data = "";
            TCPMessengerProtocol::readFromServer(command, data,peer);
            cout<< "read command from peer"<< command << " " << data <<endl;
        }
    }
}



void Broker:: close(){
    running = false;
    peer1->close();
    peer2->close();
    cout<<"Brocker closing connection" <<endl;

}


Broker::~Broker() {
    // TODO Auto-generated destructor stub
}
