#include "include/Socket.h"
#include <cassert>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>

Socket::Socket() : mFd(-1)
{}

Socket::~Socket()
{
	if (mFd != -1)
	{
		close(mFd);
		mFd = -1;
	}
}

int Socket::getFd() const
{
	return mFd;
}

void Socket::setFd(int fd)
{
	mFd = fd;
}

int Socket::create()
{
	assert(mFd == -1);
	mFd = socket(AF_INET, SOCK_STREAM, 0);
	if (mFd == -1)
	{
		perror("[Error]\tSocket create error");
		exit(1);
	}
	return 0;
}

int Socket::connect(std::string const &ip, uint16_t port) const
{
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(ip.c_str());	
	addr.sin_port = htons(port);

	if (::connect(mFd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
	{
		perror("[Error]\tSocket connect error");
		exit(1);
	}
	return 0;
}

int Socket::bind(std::string const &ip, uint16_t port) const
{
	assert(mFd != -1);

	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(ip.c_str());	
	addr.sin_port = htons(port);

	if (::bind(mFd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
	{
		perror("[Error]\tSocket bind error");
		exit(1);
	}
	return 0;
}

int Socket::listen() const
{
	assert(mFd != -1);

	if(::listen(mFd, SOMAXCONN) == -1)
	{
		perror("[Error]\tSocket listen error");
		exit(1);
	}
	return 0;
}

int Socket::accept(int &clientFd) const
{
	assert(mFd != -1);
	
	clientFd = ::accept(mFd, nullptr, nullptr);

	if (clientFd == -1)
	{
		perror("[Error]\tSocket accept error");
		exit(1);
	}
	return 0;
}

bool Socket::isNonBlocking() const
{
	return (fcntl(mFd, F_GETFL) & O_NONBLOCK) != 0;
}

int Socket::setNonBlocking() const
{
	if(fcntl(mFd, F_SETFL, fcntl(mFd, F_GETFL) | O_NONBLOCK) == -1)
	{
		perror("[Error]\tSocket set non blocking error");
		exit(1);
	}
	return 0;
}