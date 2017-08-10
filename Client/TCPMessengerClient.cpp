//
// Created by omrih on 21-Jun-17.
//
#include "TCPMessengerClient.h"
#include "../utils/TCPMessengerProtocol.h"

using namespace npl;


TCPMessengerClient::TCPMessengerClient(bool * reamMainCmd){
    this->sock = NULL;
    this->stopRun = false;
    this->reamMainCmd = reamMainCmd;
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
                *reamMainCmd = false;
                bool running = true;
                int local_choose_int = 0;
                int remote_choose_int = 0;
                string local_choose="0";
                string x = "0";
                string remote_choose="0";
                UDPGAME * udpgame = new UDPGAME(data , &running);
                while (running){
                    if (local_choose_int == 0){
                        cout<< "1.rock\n2.papre\n3.scissors"<<endl;
                        do{
                            cout << "start while" << endl;
                            cin.clear();
                            fflush(stdin);
                            local_choose.clear();
                            getline(cin,local_choose);
                            cout << local_choose<<endl;
                        }while (local_choose.empty());
                        local_choose_int = stoi(local_choose);
                        cout << "entrting switch" << endl;
                        switch (local_choose_int){
                            case 1:
                                udpgame->sendTo(to_string(ROCK));
                                local_choose_int = ROCK;
                                break;
                            case 2:
                                udpgame->sendTo(to_string(PAPER));
                                local_choose_int = PAPER;
                                break;
                            case 3:
                                udpgame->sendTo(to_string(SCISSORS));
                                local_choose_int = SCISSORS;
                                break;
                        }
                    }
                    cout << "before second if - maybe  i dot a remote message? udpgame->remote = " << udpgame->remote << endl;
                    if (local_choose_int != 0 && udpgame->remote != 0){
                        remote_choose_int = udpgame->remote;
                        cout << "cheking winner" << endl;
                        if(local_choose_int == ROCK && remote_choose_int == SCISSORS){
                            cout<< "you win" << endl;
                        }
                        else if(local_choose_int == ROCK && remote_choose_int == PAPER){
                            cout<< "you lost" << endl;
                        }
                        else if(local_choose_int == ROCK && remote_choose_int == ROCK){
                            cout<< "TIE!" << endl;
                        }
                        else if(local_choose_int == PAPER && remote_choose_int == ROCK){
                            cout<< "you win" << endl;
                        }
                        else if(local_choose_int == PAPER && remote_choose_int == SCISSORS){
                            cout<< "you lost" << endl;
                        }
                        else if(local_choose_int == PAPER && remote_choose_int == PAPER){
                            cout<< "TIE!" << endl;
                        }
                        else if(local_choose_int == SCISSORS && remote_choose_int == ROCK){
                            cout<< "you lost" << endl;
                        }
                        else if(local_choose_int == SCISSORS && remote_choose_int == PAPER){
                            cout<< "you win" << endl;
                        }
                        else if(local_choose_int == SCISSORS && remote_choose_int == SCISSORS){
                            cout<< "TIE!" << endl;
                        }
                        cout << "initializing .... after the winner if" << endl;
                        local_choose_int = 0;
                        remote_choose_int = 0;
                        local_choose = "0";
                        remote_choose = "0";
                    }
                }
                break;
        }
    }
    cout<< "stop receiving data"<<endl;
}

TCPMessengerClient::~TCPMessengerClient() {
    // TODO Auto-generated destructor stub
}
