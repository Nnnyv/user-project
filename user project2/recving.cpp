#include"recving.h"
//int waitrecving() {
//	if (RECVING == 1) {
//		this_thread::sleep_for(chrono::seconds(1));
//		return 1;
//	}
//	else return 0;
//}
//int waitsending() {
//	if (SENDING == 1) {
//		this_thread::sleep_for(chrono::seconds(1));
//		return 1;
//	}
//	else return 0;
//}
//int waitboth() {
//	if (SENDING == 1||RECVING==1) {
//		this_thread::sleep_for(chrono::seconds(1));
//		return 1;
//	}
//	else return 0;
//}
using namespace std;
	void reciver_lyh::getit() {
		string str;
		int timecontrol = 500;//0.5Ãë
		int normaltime = 20000;//20Ãë
		int iff;
		while (1) {
			message_lyh::waitrecving();
			message_lyh::recv1();
			setsockopt(socket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timecontrol, sizeof(timecontrol));
			iff = message.recvsign();
			if(iff==SOCKET_ERROR){
				message_lyh::recv0();
				setsockopt(socket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&normaltime, sizeof(normaltime));
				this_thread::sleep_for(chrono::seconds(1));
			}
			else  {
				if (str == "\0\0\1") {
					putindata();
				}
			}
			message_lyh::recv0();
		}
	}
	int reciver_lyh::putindata() {
		string str, str1, str2;
		time_t ti;
		mutex mtx;
		int normaltime = 20000;
		setsockopt(socket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&normaltime, sizeof(normaltime));
		message.recv();
		str = message.str();
		message.recv();
		str1 = message.str();
		ti = stoi(str);
		message.recv();
		str2 = message.str();
		mtx.try_lock();
		data->in(str, ti, str2);
		mtx.unlock();
		return 1;
	}
	void reciver_lyh::start() {
		thread putin([this]() {getit(); });
		putin.detach();
	}
	reciver_lyh::reciver_lyh(SOCKET soc):message(soc) {
		socket = soc;
	};
	void reciver_lyh::set(SOCKET s, data_lyh* daaa) {
		socket = s;
		//data = daaa;
	}
