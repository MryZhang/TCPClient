#include <cstring>
#include "UDPGame.h"

using namespace std;
using namespace npl;

static bool running;

void UDPGAME::run() {
    // receiver thread...
    while (running) {
//        char buffer[1024];
        memset(buffer, '\0', sizeof(buffer));
        int n = udpSocket->recv(buffer, sizeof(buffer));
        if(n < 0){
            break;
        }
//        buffer[n] = '\0';
        if (strcmp(buffer,"xxx") == 0){
            close();
        }
        else{
            this->remote_choose->copy(buffer, sizeof(buffer),0);
            cout<<endl<<"buffer--->"<< buffer<<endl;
            cout<<endl<<"remote_choose--->"<< remote_choose<<endl;
        }
    }
    cout << "closing receiver thread" << endl;

}

UDPGAME::UDPGAME(string ip , bool * flag , string * remote_choose, string * local_choose,int * local_choose_int) {
    // init the messenger
    udpSocket = new UDPSocket(GAME_PORT);
    running = flag;
    this->remote_choose = remote_choose;
    this->local_choose = local_choose;
    this->local_choose_int = local_choose_int;
    sendtoip = ip;
    this->start();
}

void UDPGAME::sendTo(const string& msg) {
    cout << "sending " << msg << endl;
    udpSocket->sendTo(msg, sendtoip, GAME_PORT);
    if (msg.compare("xxx") == 0){
        close();
    }
}

void UDPGAME::reply(const string& msg) {
    udpSocket->reply(msg);
}

void UDPGAME::close() {
    udpSocket->close();
    waitForThread();
    delete udpSocket;
    udpSocket = NULL;
    running = false;
}

bool UDPGAME::isRunning() {
    return running;
}


