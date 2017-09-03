#include <cstring>
#include "UDPGame.h"

using namespace std;
using namespace npl;

static bool running;

void UDPGAME::run() {
    // receiver thread...
    while (running) {
        memset(buffer, '\0', sizeof(buffer));
        int n = udpSocket->recv(buffer, sizeof(buffer));
        if(n < 0){
            break;
        }
        if (strcmp(buffer,"xxx") == 0){
            close();
        }
        else{
            remote = stoi(buffer);
        }
    }
    cout << "Closing receiver thread" << endl;

}

UDPGAME::UDPGAME(string ip, bool *flag) {
    // init the messenger
    udpSocket = new UDPSocket(GAME_PORT);
    running = flag;
    sendtoip = ip;
    cout << "remote ip IN UDP : " << ip << endl;
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
    cout << "Unexpected closing" << endl;
    udpSocket->close();
    waitForThread();
    delete udpSocket;
    udpSocket = NULL;
    running = false;
    cout << "Closed!" << endl;
}

bool UDPGAME::isRunning() {
    return running;
}


