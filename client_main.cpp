//
// Created by omrih on 21-Jun-17.
//

#include "Client/TCPMessengerClient.h"
#include "utils/TCPMessengerProtocol.h"
#include<iostream>
#include<string.h>
#include <thread>

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
    bool game_on = false;
    bool is_o_pressed = false;

    cout << "Welcome to TCP Client messenger" << endl;
    TCPMessengerClient* client = new TCPMessengerClient(&game_on);
    printInstructions();

    while (true) {
        string msg;
//        msg.clear();
        string command;
//        command.clear();
        if (!is_o_pressed){
            getline(cin,command);
        }
//        cin >> command;

        if (command == "c") {
//            string ip;
//            cin >> ip;
//            getline(std::cin, msg);
//            if (msg.size() > 0 && msg[0] == ' ')
//                msg.erase(0, 1);
//            client->connect(ip);
            client->connect("192.168.1.13");
            client->login_or_register();
//            printInstructions();
        } else if ((command == "y" && game_on == true) || (is_o_pressed && game_on)) {
            bool running = true;
            int local_choose_int = 0;
            int remote_choose_int = 0;
            string local_choose="0";
            string x = "0";
            string remote_choose="0";
//            cout << "IN MAIN remote ip : " << client->remote_ip << endl;
            while (client->remote_ip.compare("") == 0){}
            UDPGAME * udpgame = new UDPGAME(client->remote_ip , &running);
            while (running){
                if (local_choose_int == 0){
                    cout<< "1.rock\n2.papre\n3.scissors"<<endl;
//                        cin >> local_choose;
//                        cin.clear();
//                        fflush(stdin);
//                        local_choose.clear();
                    getline(cin,local_choose);
                    local_choose_int = stoi(local_choose);
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
                    //getline(cin,local_choose);
                }
                if (local_choose_int != 0 && udpgame->remote != 0){
                    remote_choose_int = udpgame->remote;
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
                    local_choose_int = 0;
                    remote_choose_int = 0;
                    local_choose = "0";
                    remote_choose = "0";
                }
            }
        } else if (command == "o") {
            game_on = true;
            is_o_pressed = true;
            string username;
            username.clear();
            getline(cin,username);
//            cin >> username;
            client->openSession(username);
//            username.clear();
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