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


#include"data.h"

#include"login.h"

#include"userclass.h"

#include"recving.h"

#include"face.h"

#include"internet.h"

SOCKET getlink();
int start();