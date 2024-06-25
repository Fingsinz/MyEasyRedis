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

	Socket(const Socket &other) = delete;
	Socket &operator=(const Socket &other) = delete;

	/**
	 * @brief 获取Socket Fd
	 *
	 * @return int fd
	 */
	int getFd() const;

	/**
	 * @brief 设置Socket Fd
	 *
	 * @param fd fd
	 */
	void setFd(int fd);

	/**
	 * @brief 创建一个Socket
	 *
	 * @return int 0表示成功
	 */
	int create();

	/**
	 * @brief 连接到远程Socket
	 *
	 * @param ip IP地址
	 * @param port 端口
	 * @return int 0表示成功
	 */
	int connect(std::string const &ip, uint16_t port) const;

	/**
	 * @brief 将Socket绑定到IP地址和端口
	 *
	 * @param ip IP地址
	 * @param port 端口
	 * @return int 0表示成功
	 */
	int bind(std::string const &ip, uint16_t port) const;

	/**
	 * @brief 监听连接
	 *
	 * @return int 0表示成功
	 */
	int listen() const;

	/**
	 * @brief 接受连接
	 *
	 * @param clientFd 客户端fd
	 * @return int 0表示成功
	 */
	int accept(int &clientFd) const;

	/**
	 * @brief 是否非阻塞
	 *
	 * @return bool
	 */
	bool isNonBlocking() const;

	/**
	 * @brief 设置为非阻塞
	 *
	 * @return int 0表示成功
	 */
	int setNonBlocking() const;
};