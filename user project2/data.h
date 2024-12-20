#pragma once
//#include<WinSock2.h>
//#include <WS2tcpip.h> 
//#pragma comment(lib,"WS2_32")
#include<stdio.h> 
#include<iostream>
#include<fstream>
#include<filesystem>
#include<string>
#include<ctime>
#include<vector>
#include<thread>
#include<ctime>
#include <conio.h>

#include"userclass.h"
class allfile_lyh {
public:
	const std::string id();
	allfile_lyh(std::filesystem::path entry);
	void in(std::string str, time_t tm);
	void out(std::string& str, int num);
	void flush();
	void close();
protected:
	int row = 0;
	std::string ID;
	std::fstream file;
};
class data_lyh {
public:
	data_lyh(std::string id, char w);
	data_lyh();
	void start(std::string id, char w);
	void flush();
	int in(std::string str, time_t tm, std::string id);
	int out(std::string& str, int num, std::string id);
	int remove(std::string id);
	int newone(std::string id);
	static int creatfile(std::string ID, char w);
protected:
	std::string ID;
	char way;
	std::vector<allfile_lyh> file;
	allfile_lyh* find(std::string id);
};