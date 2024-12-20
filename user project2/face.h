#pragma once
//#include<WinSock2.h>
//#include <WS2tcpip.h> 
//#pragma comment(lib,"WS2_32")
#include<stdio.h> 
#include<iostream>
#include<string>
#include<ctime>
#include<vector>
#include<thread>
#include<mutex>
#include<ctime>
#include <conio.h>


#include"userclass.h"

#include"recving.h"

#include"internet.h"



class face_lyh {
public:
	face_lyh(SOCKET Socket, user_lyh* Use, data_lyh* da);
	void start();
private:
	const SOCKET socket;
	user_lyh* const user;
	data_lyh* data;
	void checkfriend_face();
	void addfriend_face();
	void deletefriend_face();
	void datamore_chatfriend_face(std::string id);
	void send_chatfriend_face();
	void chatfriend_face();
	void applyfriend_face();
	void friend_face();
	//////////////以下为group界面///////////////////////////////////////
	void checkgroup_face();
	void addgroup_face();
	void deletegroup_face();
	void datamore_chatgroup_face(std::string id);
	void send_chatgroup_face();
	void chatgroup_face();
	void newmanage_leader_managegroup_face(std::string id);
	void delmanage_leader_managegroup_face(std::string id);
	void kick_leader_managegroup_face(std::string id);
	void check_leader_managegroup_face(std::string id);
	void cname_leader_managegroup_face(std::string id);
	void ckind_leader_managegroup_face(std::string id);
	void leader_managegroup_face(std::string id);
	void manage_managegroup_face(std::string id);
	void creatgroup_face();
	void managegroup_face();
	void pullgroup_face();
	void songroup_face();
	void group_face();
	/// //////////////下为设置
	void name_dataset_face();
	void birth_dataset_face();
	void place_dataset_face();
	void dataset_face();
	void bindset_face();
	void delset_face();
	void set_face();
};