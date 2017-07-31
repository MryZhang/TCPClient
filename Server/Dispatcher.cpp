//
// Created by omrih on 21-Jun-17.
//


#include <string>
#include "Dispatcher.h"
#include "Broker.h"
#include "../utils/TCPMessengerProtocol.h"
using namespace npl ;
using namespace std;

Dispatcher::Dispatcher() {
    running = false;
}

void Dispatcher:: add(TCPSocket* peer){
    peers.push_back(peer);
    cout<< "new connection FROM ADDRESS : " << inet_ntoa(peer->get_from().sin_addr) << " FROM PORT : " << peer->get_from().sin_port << endl;
    if(!running){
        running = true;
        start();
    }

}

void Dispatcher::remove(){

}

void Dispatcher:: run(){
    while(true){
        if(peers.size() == 0){
            running = false;
            break;
        }
        MultipleTCPSocketListener listener;
        listener.add(peers);
        TCPSocket*peer = listener.listen(5);
        if(peer != NULL){
            int command;
            string data = "";
            TCPMessengerProtocol::readFromServer(command, data,peer);
            cout<< "read command from peer"<< command << " " << data <<endl;
            if (command == EXIT){
                vector<TCPSocket*>::iterator iter = peers.begin();
                vector<TCPSocket*>::iterator endIter = peers.end();
                for (;iter != endIter;iter++) {
                    if ((*iter)->get_fd() == peer->get_fd()){
                        break;
                    }
                }
                peer->close();
                peers.erase(iter);
            }
            else if (command == OPEN_SESSION_WITH_PEER) {
                Broker * broker = new Broker();
                int portInt;
                cout<< "read command from peer "<< command << " " << data <<endl;
                cout<< "FROM ADDRESS : " << inet_ntoa(peer->get_from().sin_addr) << " FROM PORT : " << peer->get_from().sin_port << endl;
                string ip = data.substr(0, data.find(":"));
                string port = data.substr(data.find(":")+1,data.length());
                portInt = atoi(port.c_str());
                broker->add(peer, FindPeer(new TCPSocket(ip,portInt)));
            }
        }
    }

}

TCPSocket * Dispatcher::FindPeer (TCPSocket * peer){
    vector<TCPSocket*>::iterator iter = peers.begin();
    vector<TCPSocket*>::iterator endIter = peers.end();
    for (;iter != endIter;iter++) {
        if ((*iter)->get_fd() == peer->get_fd()){
            return  (*iter);
        }
    }
    return NULL;
}
void Dispatcher:: listPeer(){
    vector<TCPSocket*>::iterator iter = peers.begin();
    vector<TCPSocket*>::iterator endIter = peers.end();
    for (;iter != endIter;iter++) {
        cout << *iter << endl;
    }

}
void Dispatcher:: close(){
    running = false;
    peers.clear();
    cout<<"Dispatcher stop join clients and close safely" <<endl;

}


Dispatcher::~Dispatcher() {
    // TODO Auto-generated destructor stub
}


