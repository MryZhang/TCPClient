#include "UDPSocket.h"
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>

using namespace npl;
//UDP Constructor to initialize socket bind it
UDPSocket::UDPSocket(int port){
	/**
	 * int socket(int domain, int type, int protocol);
	 * creates a UDP socket
	 * AF_INET - IPv4 Internet protocols
	 * SOCK_DGRAM - UDP
	 * 0 - default protocol type fo UDP
	 */
	socket_fd = socket (AF_INET, SOCK_DGRAM, 0);
	if(port != 9999){
	struct sockaddr_in s_in;

	// clear the s_in struct
	bzero ((char *) &s_in, sizeof (s_in));

	//sets the sin address
	//in case a port is given, bind the socket on the specified address
	s_in.sin_family = (short)AF_INET;
	s_in.sin_addr.s_addr = htonl(INADDR_ANY);
	s_in.sin_port = htons(port);

	if(bind(socket_fd,(struct sockaddr*)&s_in,sizeof(s_in))<0){
		printf("Error naming channel");

	}
	}

}
//recv function to receive the messages from ant client
int UDPSocket::recv(char* buffer, int length){
	socklen_t fsize = sizeof(from);
	ssize_t res = recvfrom(socket_fd, buffer, length, 0,(struct sockaddr *)&from,&fsize);
	if(res<0){
		perror("Recive: error");
	}
	return res;
}
//sendTo function to send messages from any side (client or server)
int UDPSocket::sendTo(const string& msg,const string& ip, int port){
	struct sockaddr_in s_in;
	bzero ((char *) &s_in, sizeof (s_in));

	s_in.sin_family = (short)AF_INET;
	s_in.sin_addr.s_addr = inet_addr(ip.c_str());
	s_in.sin_port = htons(port);

	int n = sendto(socket_fd , msg.c_str() , msg.length() , 0 , (struct sockaddr*)&s_in , sizeof(s_in));
	if(n<0){
		perror("SendTo: error");
	}
	return n;
}
//reply function to send back the message from the server to the client
int UDPSocket::reply(const string& msg){
	int n = sendto(socket_fd,msg.data(),msg.length(),0,(struct sockaddr*)&from,sizeof(from));
	if(n < 0){
		perror("Reply: error");
	}
	return n;
}
//close function to close our connection
void UDPSocket::close(){
	cout<<"closing socket"<<endl;
	shutdown(socket_fd,SHUT_RDWR);
	::close(socket_fd);
}
string UDPSocket::fromAddr(){
	return inet_ntoa(from.sin_addr);
}



