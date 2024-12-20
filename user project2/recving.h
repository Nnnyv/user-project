#pragma once
#include<WinSock2.h>
#include <WS2tcpip.h> 
//#pragma comment(lib,"WS2_32")
#pragma comment(lib, "ws2_32.lib")
#include<stdio.h> 
#include<iostream>
#include<string>
#include<ctime>
#include<vector>
#include<thread>
#include<mutex>
#include<ctime>
#include <conio.h>

#include"main.h"

#include"data.h"

#include"login.h"

#include"userclass.h"



#include"face.h"

#include"internet.h"

class reciver_lyh {
public:
	void start();
	reciver_lyh(SOCKET soc);
	void set(SOCKET s, data_lyh* daaa);
protected:
	void getit();
	int putindata();
	message_lyh message;
	SOCKET socket;
	data_lyh* data;
};