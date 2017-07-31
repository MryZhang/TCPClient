cmake_minimum_required(VERSION 3.7)
project(client)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Client/TCPMessengerClient.cpp
        Client/TCPMessengerClient.h
        Server/Broker.cpp
        Server/Broker.h
        Server/Dispatcher.cpp
        Server/Dispatcher.h
        Server/TCPMessengerServer.cpp
        Server/TCPMessengerServer.h
        utils/File.cpp
        utils/File.h
        utils/FileInterface.cpp
        utils/FileInterface.h
        utils/MThread.cpp
        utils/MThread.h
        utils/MultipleTCPSocketListener.cpp
        utils/MultipleTCPSocketListener.h
        utils/Socket.cpp
        utils/Socket.h
        utils/TCPMessengerProtocol.h
        utils/TCPSocket.cpp
        utils/TCPSocket.h
        client_main.cpp
        server_main.cpp)

add_executable(client ${SOURCE_FILES})