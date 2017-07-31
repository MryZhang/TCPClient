//
// Created by omrih on 21-Jun-17.
//

#include "Client/TCPMessengerClient.h"
#include "utils/TCPMessengerProtocol.h"
#include<iostream>
#include<string.h>
using namespace std;
using namespace npl;

void printInstructions() {
    cout << "c <ip> - connect" << endl;
    cout << "o <ip>:<port> - open session with peer" << endl;
    cout << "cs - close session with peer" << endl;
    cout << "d - disconnect from server" << endl;
    cout << "s <msg> - send a message" << endl;
    cout << "x - exit the program" << endl;
}

int main() {

    cout << "Welcome to TCP Client messenger" << endl;
    TCPMessengerClient* client = new TCPMessengerClient();
    printInstructions();
    while (true) {
        string msg;
        msg.clear();
        string command;
        command.clear();
        cin >> command;

        if (command == "c") {
//            string ip;
//            cin >> ip;
//            getline(std::cin, msg);
//            if (msg.size() > 0 && msg[0] == ' ')
//                msg.erase(0, 1);
//            client->connect(ip);
            client->connect("127.0.0.1");
            client->login_or_register();
        } else if (command == "o") {
            string ipAndPort;
            cin >> ipAndPort;
            client->openSession(ipAndPort);
        } else if (command == "s") {
            getline(std::cin, msg);
            if (msg.size() > 0 && msg[0] == ' ')
                client->send(msg);
        } else if (command == "cs") {
            client->closeSession();
        } else if (command == "d") {
            client->disconnect();
        } else if (command == "x") {
            break;
        } else {
            cout << "wrong input" << endl;
            printInstructions();
        }
    }
    //client->close();
    //delete client;
    cout << "messenger was closed" << endl;
    return 0;
}