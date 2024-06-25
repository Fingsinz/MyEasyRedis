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

	int clientFd = -1;
	server.accept(clientFd);

	std::cout << "Clinet connected: " << clientFd << std::endl;

	while (true)
	{
		char buffer[1024] = { 0 };
		int n = read(clientFd, buffer, 1024);

		if (n > 0)
		{
			std::cout << buffer << std::endl;
			write(clientFd, buffer, 1024);
		}

		else if (n == 0)
		{
			std::cout << "Client disconnected" << std::endl;
			break;
		}

		memset(buffer, 0, 1024);
	}

	return 0;
}