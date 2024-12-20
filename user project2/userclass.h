#pragma once
//#include<stdio.h> 
//#include<iostream>
//#include<fstream>
//#include<filesystem>
//#include<string>
//#include<ctime>
//#include<vector>
//#include<thread>
//#include<mutex>
//#include<ctime>
//#include <conio.h>
//#include"main.h"
//
//#include"data.h"
//
//#include"login.h"
//
//
//
//#include"recving.h"
//
//#include"face.h"
//
//#include"internet.h"
#include<iostream>
class user_lyh {
public:
	user_lyh();
	virtual ~user_lyh();
	int way;//1:qq,2:webo,3:wechat
	std::string ID;//6位
	std::string name;//最多20位
	std::string birth;//8位
	std::string useage;//8位
	std::string place; //最多40位
	std::string key;
};
class qq_lyh :public user_lyh {
public:
	qq_lyh();
	~qq_lyh();
};
class webo_lyh :public user_lyh {
public:
	webo_lyh();
	~webo_lyh();
};
class wechat_lyh :public user_lyh {
public:
	wechat_lyh();
	~wechat_lyh();
};
