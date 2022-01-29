#ifndef XSOCKET_H
#define XSOCKET_H

#include <iostream>
#include <stdexcept> //try catch
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
//#pragma comment(lib, "ws2_32.lib")

#define READ_MAX_SIZE 1024
#define XSOCKET_UDP 0
#define XSOCKET_TCP IPPROTO_TCP

#ifdef WIN32
#include <winsock2.h>
#define socklen_t int
#else
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#define SOCKET int
#define INVALID_SOCKET -1
#define LPSOCKADDR sockaddr*
#define SOCKET_ERROR -1
#define SOCKADDR sockaddr
#define Sleep(n) sleep(n/1000);
#endif
namespace xstd{
namespace XSOCKET{
	SOCKET slisten;
	void xsocketInit(){
#ifdef WIN32
		WSADATA data;
		if (WSAStartup(MAKEWORD(2,2), &data) != 0)
			throw "WSA资源创建失败";
#endif
	}
	std::vector<std::string> getHostByName(std::string& name){
	    struct hostent *host = gethostbyname(name.c_str());
	    if(!host){
	        throw "Get IP address error!";
	    }
	    //别名
//	    for(int i=0; host->h_aliases[i]; i++){
//	        printf("Aliases %d: %s\n", i+1, host->h_aliases[i]);
//	    }
	    //地址类型
//	    printf("Address type: %s\n", (host->h_addrtype==AF_INET) ? "AF_INET": "AF_INET6");

        //IP地址
        std::vector<std::string> hosts;
		hosts.reserve(4);
	    for(int i=0; host->h_addr_list[i]; ++i)
	        hosts.push_back(inet_ntoa( *(struct in_addr*)host->h_addr_list[i]));
	    return hosts;
	}
	std::vector<std::string> getHostByName(const char* host){
		std::string _host(host);
		return getHostByName(_host);
	}
	void bind(int port,int mode=XSOCKET_TCP){
		sockaddr_in sin;
		sin.sin_family = AF_INET;
		sin.sin_port = htons(port);
#ifdef WIN32
		sin.sin_addr.S_un.S_addr = INADDR_ANY;
#else
		sin.sin_addr.s_addr = INADDR_ANY;
#endif
		XSOCKET::slisten = socket(AF_INET, SOCK_STREAM, mode);
		if (XSOCKET::slisten == INVALID_SOCKET)
			throw "socket创建失败";
		if (bind(XSOCKET::slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
			throw "绑定失败";
		if (::listen(XSOCKET::slisten, 5) == SOCKET_ERROR)
			throw "listen失败";
	}
}



class xsocket
{
	public:
		xsocket(){}
		xsocket(const char *str, int p){connect(str,p);};

		void connect(std::string&, int, int=XSOCKET_TCP);
		void connect(const char*,int, int=XSOCKET_TCP);

		void listen();

		void send(const std::string);

		int read(std::string&, int);
		
		int read(char *, int);
		
		void close();
		
		bool operator==(xsocket&);
		bool operator==(int);
		bool operator!=(xsocket&);
		bool operator!=(int);

	private:
		SOCKET Socket;
};
}

void xstd::xsocket::listen()
{
	sockaddr_in remoteAddr;
	socklen_t len=sizeof(remoteAddr);
	Socket = accept(xstd::XSOCKET::slisten, (SOCKADDR*)&remoteAddr, &len);
	if (Socket == INVALID_SOCKET)
		throw "与客户端连接失败!";
}

void xstd::xsocket::connect(std::string& host, int port, int mode)
{
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
#ifdef WIN32
	sin.sin_addr.S_un.S_addr = inet_addr(host.c_str());
#else
	sin.sin_addr.s_addr = inet_addr(host.c_str());
#endif
	Socket = socket(AF_INET, SOCK_STREAM, mode);
	if (Socket == INVALID_SOCKET)
		throw "socket创建失败!";
	unsigned short i;
	for(i=0;i<3&&::connect(Socket, (sockaddr*)&sin, sizeof(sin)) == SOCKET_ERROR;++i)
		Sleep(100); //每100ms重复连接服务器 默认尝试3次 
	if(i==3)throw "连接服务器失败!";
}
void xstd::xsocket::connect(const char* host,int port,int mode){
	std::string Host(host);
	connect(Host,port,mode);
}

void xstd::xsocket::send(const std::string val)
{
	if(::send(Socket, val.c_str(), val.length(), 0)==-1)
		throw "连接断开!";
}

int xstd::xsocket::read(std::string& str, int size)
{
	char *in=new char[size+1];
	int rev=0;
	rev = recv(Socket, in, size, 0);
	if (!((rev > 0) || ((rev == -1) && (Socket == EWOULDBLOCK))))
		throw "连接断开!";
	in[rev] = 0x00;
	str = in;
	delete[] in;
	return rev;
}

int xstd::xsocket::read(char *in,int size){
	int rev = recv(Socket, in, size, 0);
	in[rev] = 0x00;
	if (!((rev > 0) || ((rev == -1) && (Socket == EWOULDBLOCK))))
		throw "连接断开!";
	return rev;
}

bool xstd::xsocket::operator==(xsocket& a){
	return a.Socket==Socket;
}
bool xstd::xsocket::operator==(int a){
	return a==int(Socket);
}
bool xstd::xsocket::operator!=(xsocket& a){
	return !(*this==a);
}
bool xstd::xsocket::operator!=(int a){
	return !(*this==a);
}
xstd::xsocket& operator<<(xstd::xsocket& s,std::string& str){
	s.send(str);
	// Sleep(100); //缓冲
	return s;
}
xstd::xsocket& operator<<(xstd::xsocket& s,const char* str){
	s.send(str);
	return s;
}
xstd::xsocket& operator>>(xstd::xsocket& s,std::string& str){
	s.read(str,READ_MAX_SIZE);
	return s;
}
xstd::xsocket& operator>>(xstd::xsocket& s,char *str){
	s.read(str,READ_MAX_SIZE);
	return s;
}
void xstd::xsocket::close(){
#ifdef WIN32
	closesocket(Socket);
#else
	::close(Socket);
#endif
}
#endif