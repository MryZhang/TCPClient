#ifndef UNTITLED_FILEINTERFACE_H
#define UNTITLED_FILEINTERFACE_H

#include <iostream>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

using namespace std;

namespace npl {

    class FileInterface {
    protected:
        int socket_fd;
    public:
        virtual void close()=0;
        virtual int read(char* buffer, int length);
        virtual int write(const char* buffer, int length);

        virtual ~FileInterface();
    };
}

#endif
