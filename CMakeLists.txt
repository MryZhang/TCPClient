cmake_minimum_required(VERSION 3.8)
project(TCPClient)

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
        utils/Socket.cpp
        utils/Socket.h
        utils/TCPMessengerProtocol.h
        utils/TCPSocket.cpp
        utils/TCPSocket.h
        utils/UDPGame.cpp
        utils/UDPGame.h
        utils/UDPSocket.cpp
        utils/UDPSocket.h
        client_main.cpp utils/TCPMessengerProtocol.h)

add_executable(TCPClient ${SOURCE_FILES})