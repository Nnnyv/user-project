#include"login.h"
using namespace std;
void read_use(user_lyh*& make, int way,SOCKET socket) {
	int temp = 0, temp1 = 1;
	message_lyh message(socket);
	if (way == 1) {
		make = new qq_lyh;
	}
	else if (way == 2) {
		make = new webo_lyh;
	}
	else if (way == 3) {
		make = new wechat_lyh;
	}
	message.recv();
	make->ID = message.str();
	message.recv();
	make->name = message.str();
	message.recv();
	make->birth = message.str();
	message.recv();
	make->place = message.str();

}

user_lyh* login(SOCKET socket,data_lyh*& DATA) {
	user_lyh* use;
	message_lyh message(socket);
	char way;
	while (1) {
		cout << "ѡ���¼��ʽ" << endl << "1 qq|| 2 ΢��|| 3 ΢��" << endl;
		cin >> way;
		cout << "�����˺�:";
		string account;
		string password;
		string all;
		int temp = 1, temp1 = 1;
		cin >> account;
		if (account.size() != 6) {
			cout << "�˻�����" << endl;
			system("cls");
			continue;
		}
		cout << "��������:";
		cin >> password;
		message.sign("\0\0\0");
		all = way;
		message.clear();
		message.add_num(all);
		message.add_num(account);
		message.add_num(password);
		message.send();
		message.recv();
		all = message.str().c_str();
		if (all[0] == 0) {
			cout << "����" << endl;
			continue;
		}
		else {
			system("cls");
			cout << "��½�ɹ�" << endl;
		}
		read_use(use, way, socket);
		DATA = new data_lyh;
		DATA->start(account, way);
		use->key = password;
		return use;
	}
}