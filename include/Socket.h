#include <winsock2.h>
#include <iostream>

#define IPADDRESS "127.0.0.1"
#define PORT 60070

class Socket {
public:
	bool socketConnect();
	void envia(char *s, int len);
	void recebe(char *ans);
	void quit();
};
