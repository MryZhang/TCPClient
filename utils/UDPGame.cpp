#include "UDPGame.h"


using namespace npl;

void UDPGAME::run() {
	// receiver thread...
	while (runing) {
		char buffer[1024];
		int n = udpSocket->recv(buffer, sizeof(buffer));
		if(n < 0){
			break;
		}
		buffer[n] = '\0';
		cout<<endl<<"the msg--->"<< buffer<<endl;

	}
	cout << "closing receiver thread" << endl;

}

UDPGAME::UDPGAME(string ip , bool * flag) {
	// init the messenger
	udpSocket = new UDPSocket(GAME_PORT);
	runing = true;
    sendtoip = ip;
	this->start();
}

void UDPGAME::sendTo(const string& msg) {
	udpSocket->sendTo(msg, sendtoip, GAME_PORT);
}

void UDPGAME::reply(const string& msg) {
	udpSocket->reply(msg);
}

void UDPGAME::close() {
	runing = false;
	udpSocket->close();
	waitForThread();
	delete udpSocket;
	udpSocket = NULL;
}


