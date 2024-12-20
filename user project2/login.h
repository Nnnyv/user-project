#pragma once
#include<stdio.h> 
#include<iostream>
#include<fstream>
#include<filesystem>
#include<string>
#include<ctime>
#include<vector>
#include<thread>
#include<mutex>
#include<ctime>
#include <conio.h>
#include"main.h"

#include"data.h"



#include"userclass.h"

#include"recving.h"

#include"face.h"

#include"internet.h"
//#pragma comment(lib,"WS2_32")

//void read_use(user_lyh* (& make), int way);
//int login();
void read_use(user_lyh*& make,int way, SOCKET socket);
user_lyh* login(SOCKET, data_lyh*&);
