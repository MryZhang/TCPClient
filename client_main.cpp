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
    cout << "l - list all available players" << endl;
}

int main() {

    cout << "Welcome to TCP Client messenger" << endl;
    TCPMessengerClient* client = new TCPMessengerClient();
    printInstructions();
    while (true) {
        string msg;
//        msg.clear();
        string command;
//        command.clear();
        getline(cin,command);
//        cin >> command;

        if (command == "c") {
//            string ip;
//            cin >> ip;
//            getline(std::cin, msg);
//            if (msg.size() > 0 && msg[0] == ' ')
//                msg.erase(0, 1);
//            client->connect(ip);
            client->connect("10.0.0.10");
            client->login_or_register();
//            printInstructions();
        } else if (command == "o") {
            string username;
            username.clear();
            getline(cin,username);
//            cin >> username;
            client->openSession(username);
//            username.clear();
            while(true){
//                cout << "inside" << endl;
                // wait;
            }
        } else if (command == "s") {
            getline(cin, msg);
            if (msg.size() > 0 && msg[0] == ' ')
                client->send(msg);
        } else if (command == "cs") {
            client->closeSession();
        } else if (command == "d") {
            client->disconnect();
        } else if (command == "l") {
            client->send(GET_USERS_LIST,"");
        }
        else if (command == "x") {
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