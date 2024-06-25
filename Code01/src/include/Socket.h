#pragma once

#include <arpa/inet.h>
#include <sys/socket.h>
#include <string>

class Socket
{
private:
	int mFd{ -1 };

public:
	Socket();
	~Socket();

	Socket(const Socket& other) = delete;
	Socket& operator=(const Socket& other) = delete;

	int getFd() const;
	void setFd(int fd);

	int create();
	int connect(std::string const &ip, uint16_t port) const;
	int bind(std::string const &ip, uint16_t port) const;
	int listen() const;
	int accept(int &clientFd) const;

	bool isNonBlocking() const;
	int setNonBlocking() const;
};