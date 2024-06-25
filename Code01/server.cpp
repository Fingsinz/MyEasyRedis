#include "src/include/Socket.h"
#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <cstring>
#include <unistd.h>

int main()
{
	Socket server;
	server.create();

	server.bind("127.0.0.1", 1234);
	server.listen();

	while (true)
	{
		char buffer[1024] = { 0 };
		int n = read(server.getFd(), buffer, 1024);
		
		std::cout << buffer << std::endl;
		memset(buffer, 0, 1024);
	}

	return 0;
}