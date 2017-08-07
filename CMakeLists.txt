cmake_minimum_required(VERSION 3.8)
project(TCPClient)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        .idea/inspectionProfiles/Project_Default.xml
        .idea/misc.xml
        .idea/modules.xml
        .idea/untitled.iml
        .idea/vcs.xml
        .idea/workspace.xml
        Client/TCPMessengerClient.cpp
        Client/TCPMessengerClient.h
        cmake-build-debug/client.cbp
        cmake-build-debug/cmake_install.cmake
        cmake-build-debug/CMakeCache.txt
        cmake-build-debug/gdb.exe.stackdump
        cmake-build-debug/Makefile
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
        .gitignore
        client_main.cpp
        CMakeLists.txt)

add_executable(TCPClient ${SOURCE_FILES})