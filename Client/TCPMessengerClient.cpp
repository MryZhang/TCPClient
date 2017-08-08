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

void TCPMessengerClient::openSession(const string& username) {
    cout << "openSession with server" << username << endl << flush;
    TCPMessengerProtocol::sendToServer(OPEN_SESSION_WITH_PEER, username, sock);

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
//    cin >> msg;
    getline(cin,msg);
    TCPMessengerProtocol::sendToServer(LOGIN_OR_REGISTER, msg, sock);
//    while (!this->isConnected){
    //username
//        cin >> msg;
    msg.clear();
    getline(cin,msg);
    TCPMessengerProtocol::sendToServer(LOGIN_OR_REGISTER, msg, sock);
    //password
//        cin >> msg;
    msg.clear();
    getline(cin,msg);
    TCPMessengerProtocol::sendToServer(LOGIN_OR_REGISTER, msg, sock);
//    }

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
        cout << "command ***** >>>> " << command << endl;
        switch (command){
            case SESSION_REFUSED:
                break;
            case SUCCESS:
                this->isConnected = true;
                break;
            case GAME_SESSION:
                bool running = true;
                int local_choose_int = 0;
                string local_choose="0";
                string remote_choose="0";
                UDPGAME * udpgame = new UDPGAME(data , &running,&remote_choose,&local_choose, & local_choose_int);
                while (running){
                    if (local_choose_int == 0){
                        cout<< "1.rock\n2.papre\n3.scissors"<<endl;
                        cin >> local_choose_int;
                        switch (local_choose_int){
                            case 1:
                                udpgame->sendTo(to_string(ROCK));
                                break;
                            case 2:
                                udpgame->sendTo(to_string(PAPER));
                                break;
                            case 3:
                                udpgame->sendTo(to_string(SCISSORS));
                                break;
                        }
                        //getline(cin,local_choose);
                    }
                    else{

                    }
//                    cin >> msg;
                    local_choose.clear();
                }
                break;
        }
    }
    cout<< "stop receiving data"<<endl;
}

TCPMessengerClient::~TCPMessengerClient() {
    // TODO Auto-generated destructor stub
}
