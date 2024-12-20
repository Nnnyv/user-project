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
#include<vector>
#include"data.h"

#include"userclass.h"
//class message_lyh;
//#pragma comment(lib,"WS2_32")/*

//class message_lyh {
//public:
//	message_lyh();
//	message_lyh(string);
//	void reload(string );
//	void add(string );
//	void add_num(string);
//	void add_end();
//	int send(SOCKET);
//	int recv(SOCKET);
//	void putout_num(int);
//	const string str();
//	void clear(int iff=1);
//private:
//	string all;
//};*/
class message_lyh {
public:
	//message_lyh() {};
	message_lyh(SOCKET, std::string);
	message_lyh(SOCKET);
	static int waitsending();
	static int waitrecving();
	static int waitboth();
	static int send1();
	static int send0();
	static int recv1();
	static int recv0();
	int setsocket(SOCKET);
	//int sign(char a[]);
	int sign(std::string);
	int recvsign();
	char* const nowsignal();
	void reload(std::string );
	void add(std::string );
	void add_num(std::string);
	void add_end();
	int send();
	int recv();
	void replace();
	void putout_num(int );
	std::string word();
	std::string str();
	void clear();
private:
	int now = 0;
	static int RECVING;
	static int SENDING;
	SOCKET socket;
	std::string all;
	char signal[3];
};
