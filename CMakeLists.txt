cmake_minimum_required(VERSION 3.7)
project(client)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Client/TCPMessengerClient.cpp
        Client/TCPMessengerClient.h
        utils/File.cpp
        utils/File.h
        utils/FileInterface.cpp
        utils/FileInterface.h
        utils/MThread.cpp
        utils/MThread.h
        utils/MultipleTCPSocketListener.cpp
        utils/MultipleTCPSocketListener.h
        utils/UDPMessenger.h
        utils/UDPMessenger.cpp
        utils/Socket.cpp
        utils/Socket.h
        utils/TCPMessengerProtocol.h
        utils/TCPSocket.cpp
        utils/TCPSocket.h
        client_main.cpp)

add_executable(client ${SOURCE_FILES})