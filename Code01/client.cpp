#include "src/include/Socket.h"
#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <cstring>
#include <unistd.h>

int main()
{
	Socket client;
	client.create();

	client.connect("127.0.0.1", 1234);

	std::string msg = "";

	while (true)
	{
		std::getline(std::cin, msg);

		write(client.getFd(), msg.c_str(), msg.size());
		char buffer[1024] = { 0 };
		int n = read(client.getFd(), buffer, 1024);
		
		if(n <= 0)
		{
			break;
		}

		std::cout << buffer << std::endl;
		memset(buffer, 0, 1024);
	}

	return 0;
}