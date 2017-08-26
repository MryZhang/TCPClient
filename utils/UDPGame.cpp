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
        cout << "in udpgame - run n = " << n <<endl;
        cout << "buffer = " << buffer << endl;
        if(n < 0){
            break;
        }
//        buffer[n] = '\0';
        if (strcmp(buffer,"xxx") == 0){
            close();
        }
        else{
//            *(this->remote_choose) = stoi(buffer);
            remote = stoi(buffer);
            cout << "remote = " << remote << endl;
//            cout<<endl<<"buffer--->"<< buffer<<endl;
//            cout<<endl<<"remote_choose--->"<< *remote_choose<<endl;
        }
    }
    cout << "closing receiver thread" << endl;

}

UDPGAME::UDPGAME(string ip , bool * flag ) {
    // init the messenger
    udpSocket = new UDPSocket(GAME_PORT);
    running = flag;
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
    cout << "closing for some reason" << endl;
    udpSocket->close();
    waitForThread();
    delete udpSocket;
    udpSocket = NULL;
    running = false;
    cout << "closed!" << endl;
}

bool UDPGAME::isRunning() {
    return running;
}


