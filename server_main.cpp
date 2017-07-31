//#include <iostream>
//#include "server/TCPMessengerServer.h"
//#include<string.h>
//using namespace std;
//using namespace npl;
//
//void printInstructions() {
//    cout << "To send a message type: s <ip> <message>" << endl;
//    cout << "To reply to a message type: r <message>" << endl;
//    cout << "To exit type: x" << endl;
//}
//
//
//int main() {
//    cout << "Welcome to TCP Server messenger" << endl;
//    TCPMessengerServer* server = new TCPMessengerServer();
////		printInstructions();
//    while (true) {
//        string msg;
//        msg.clear();
//        string command;
//        command.clear();
//        cin >> command;
//
//        if (command == "lp") {
////				string ip;
////				cin >> ip;
////				getline(std::cin, msg);
////				if (msg.size() > 0 && msg[0] == ' ')
////					msg.erase(0, 1);
//            server->listpeer();
//        } else if (command == "x") {
//            server->exit();
//        } else {
//            cout << "wrong input" << endl;
//            printInstructions();
//        }
//    }
//    delete server;
//    cout << "messenger was closed" << endl;
//    return 0;
//}