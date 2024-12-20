#include"face.h"

using namespace std;
using std::cout;
/////////////����Ϊfriend����//////////////////////////////
//���ID  �ǳ�\n
	face_lyh::face_lyh(SOCKET Socket, user_lyh* Use,data_lyh *da) :socket(Socket), user(Use),data(da) {}
	void face_lyh::start() {
		char input;
		while (1) {
			system("cls");
			cout << "1������" << endl;
			cout << "2��Ⱥ��" << endl;
			cout << "3������" << endl;
			cout << "4���˳�" << endl;
			cin >> input;
			if (input == '1') {
				friend_face();
			}
			else if (input == '2') {
				group_face();
			}
			else if (input == '3') {
				set_face();
			}
			else if (input == '4') {
				return;
			}
		}
	}
	void face_lyh::checkfriend_face() {
		char receive[128];
		message_lyh temp(socket);
		message_lyh::waitboth();
		message_lyh::send1();
		message_lyh::recv1();
		temp.sign("\0\0\1");
		temp.recv();
		temp.putout_num(2);
		/*recv(socket, receive, 128, 0);
		while (1) {
			cout.write(receive + temp + 1, receive[temp]);
			cout << "  ";
			temp += receive[temp] + 1;
			if (receive[temp] == -1) {
				recv(socket, receive, 128, 0);
				temp = 0;
			}
			else if (receive[temp] == 0) {
				break;
			}
			cout.write(receive + temp + 1, receive[temp]);
			cout << endl;
			temp += receive[temp] + 1;
			if (receive[temp] == -1) {
				recv(socket, receive, 128, 0);
				temp = 0;
			}
			else if (receive[temp] == 0) {
				break;
			}
		}*/
		message_lyh::send0();
		message_lyh::recv0();
		_getch();
	}
	void face_lyh::addfriend_face() {
		string newid;
		string say;
		int check = 0;
		message_lyh message(socket);
		system("cls");
		cout << "ID��";
		cin >> newid; 
		message_lyh::waitboth();
		message_lyh::send1();
		message_lyh::recv1();
		check += message.sign("\0\0\2");
		message.reload(newid);
		message.send();
		message.recv();
		if (message.str()[0] == '\0') {
			cout << "���޴���" << endl;
			_getch();
			system("cls");
			return;
		}
		message.clear();
		message.add_num(user->ID);
		message.add_num(user->name);
		cout << "��������:";
		cin >> say;
		message.add_num(say);
		check += message.send();
		if (check > 0) {
			cout << "���ʧ��" << endl;
		}
		else {
			cout << "�ѷ�������" << endl;
		}
		message_lyh::send0();
		message_lyh::recv0();
		_getch();
	}
	void face_lyh::deletefriend_face() {
		string newid;
		int check = 0;
		message_lyh message(socket);
		message_lyh::waitboth();
		message_lyh::send1();
		message_lyh::recv1();
		system("cls");
		cout << "ID��";
		cin >> newid;
		check += message.sign("\0\0\3");
		message.add(newid.c_str());
		check += message.send();
		if (check > 0) {
			cout << "ɾ��ʧ��" << endl;
		}
		else {
			cout << "��ɾ����" << newid << endl;
			//use->del_friend(newid);
		}
		message_lyh::send0();
		message_lyh::recv0();
		_getch();
	}
	void face_lyh::datamore_chatfriend_face(string id) {
		string str;
		data->out(str, -1, id);
		cout << str;
	}
	void face_lyh::send_chatfriend_face() {
		string tt;
		int temp = 0;
		//message_lyh::waitsending();
		//message_lyh::send1();
		cout << "������:";
		cin >> tt;
		message_lyh tempm(socket);
		tempm.setsocket(socket);
		tempm.sign("\0\0\5");
		tempm.add_num(tt);
		tempm.send();
		//while (1) {
		//	if (temp + 126 >= tt.size()) {
		//		tt.copy(putout, tt.size() - temp, temp);
		//		putout[tt.size() - temp] = '\0';
		//		putout[127] = '\0';//127λΪ0�����ѽ���
		//		send(socket, putout, 128, 0);
		//		break;
		//	}
		//	tt.copy(putout, 126, temp);
		//	putout[126] = '\0';
		//	putout[127] = '\1';
		//	send(socket, putout, 128, 0);
		//	temp += 126;
		//}
		 
		
		//message_lyh::send0();
	}
	void face_lyh::chatfriend_face() {
		system("cls");
		string id;
		char iff;
		message_lyh message(socket);
		message_lyh::waitboth();
		message_lyh::send0();
		message_lyh::recv0();
		cout << "ѡ����ѣ�";
		cin >> id;
		message.sign("\0\0\4");
		message.add(id.c_str());
		message.send();
		message.recv();
		iff = message.str().c_str()[0];//����1���Ǻ��ѣ����Խ�����һ��
		message_lyh::send0();
		message_lyh::recv0();
		if (iff != 1) {
			cout << "��������ĺ���" << endl;
			_getch();
			return;
		}
		while (1) {
			cout << "1���鿴������Ϣ" << endl;
			cout << "2��������Ϣ" << endl;
			cout << "3���˳�" << endl;
			cin >> iff;
			if (iff == 1) {
				datamore_chatfriend_face(id);//�����ݿ��ڶ���һ�ܵ�������Ϣ
			}
			else if (iff == 2) {
				send_chatfriend_face();
			}
			else if (iff == 3) {
				message.sign("\0\0\0");//��ʾ�˴� ͨ�Ž��� 
				return;
			}
		}
	}
	void face_lyh::applyfriend_face() {
		system("cls");
		string str, id;
		char iff;
		message_lyh message(socket);
		message_lyh::waitboth();
		message_lyh::send0();
		message_lyh::recv0();
		message.sign("\0\0\6");
		message.recv();
		cout << "������ ����"<<endl;
		message.putout_num(1);
		id = message.word();
		//message.replace();
		//cout << "��������:";
		//message.recv();
		//message.putout_num(5);
		cout << endl << "����1ͬ�⣬����2�ܾ���";
		cin >> str;
		message.reload(str);
		message.send();
		if (str[0] == '1') {
			data_lyh::creatfile(id, user->way);
		}
		_getch();
		system("cls");
	}
	void face_lyh::friend_face() {
		char input;
		while (1) {
			system("cls");
			cout << "1���鿴����" << endl;
			cout << "2����Ӻ���" << endl;
			cout << "3��ɾ������" << endl;
			cout << "4����������" << endl;
			cout << "5����������" << endl;
			cout << "0������" << endl;
			cin >> input;
			if (input == '1') {
				checkfriend_face();
			}
			else if (input == '2') {
				addfriend_face();
			}
			else if (input == '3') {
				deletefriend_face();
			}
			else if (input == '4') {
				chatfriend_face();
			}
			else if (input == '5') {
				applyfriend_face();
			}
			else if (input == '0') {
				return;
			}
		}
	}
	//////////////����Ϊgroup����///////////////////////////////////////
	void face_lyh::checkgroup_face() {
		message_lyh temp(socket);
		message_lyh::waitboth();
		message_lyh::send1();
		message_lyh::recv1();
		temp.sign("\0\1\1");
		temp.recv();
		message_lyh::send0();
		message_lyh::recv0();
		temp.putout_num(2);
		/*char receive[128];
		int temp = 0, temp1;
		send(socket, "\0\1\1", 3, 0);
		recv(socket, receive, 128, 0);
		while (1) {
			cout.write(receive + temp + 1, receive[temp]);
			cout << "  ";
			temp += receive[temp] + 1;
			if (receive[temp] == -1) {
				recv(socket, receive, 128, 0);
				temp = 0;
			}
			else if (receive[temp] == 0) {
				break;
			}
			cout.write(receive + temp + 1, receive[temp]);
			cout << endl;
			temp += receive[temp] + 1;
			if (receive[temp] == -1) {
				recv(socket, receive, 128, 0);
				temp = 0;
			}
			else if (receive[temp] == 0) {
				break;
			}
		}*/
		_getch();
	}
	void face_lyh::addgroup_face() {
		string newid;
		string say;
		int check = 0;
		message_lyh message(socket);
		system("cls");
		cout << "ID��";
		cin >> newid;
		message_lyh::waitboth();
		message_lyh::send1();
		message_lyh::recv1();
		check += message.sign("\0\1\2");
		message.reload(newid);
		message.send();
		message.recv();
		if (message.str()[0] == '\0') {
			cout << "���޴�Ⱥ" << endl;
			_getch();
			system("cls");
			return;
		}
		message.clear();
		message.add_num(user->ID);
		message.add_num(user->name);
		cout << "��������:";
		cin >> say;
		message.add_num(say);
		check += message.send();
		if (check > 0) {
			cout << "���ʧ��" << endl;
		}
		else {
			cout << "�ѷ�������" << endl;
		}
		message_lyh::send0();
		message_lyh::recv0();
		_getch();
	}
	void face_lyh::deletegroup_face() {
		string newid;
		int check = 0;
		message_lyh mess(socket);
		system("cls");
		cout << "ID��";
		cin >> newid;
		message_lyh::waitsending();
		message_lyh::send1();
		check+=mess.sign("\0\1\3");
		mess.add(newid.c_str());
		check += mess.send();
		message_lyh::send0();
		if (check > 0) {
			cout << "�˳�Ⱥ��ʧ��" << endl;
		}
		else {
			cout << "���˳�Ⱥ�ģ�" << newid << endl;
			//use->del_friend(newid);
		}
		_getch();
	}
	void face_lyh::datamore_chatgroup_face(string id) {
		string str;
		data->out(str, -1, id);
		cout << str;
	}
	void face_lyh::send_chatgroup_face() {
		string tt;
		int temp = 0;
		//message_lyh::waitsending();
		//message_lyh::send1();
		cout << "������:";
		cin >> tt;
		message_lyh tempm(socket);
		tempm.setsocket(socket);
		tempm.sign("\0\1\5");
		tempm.add_num(tt);
		tempm.send();

	/*	string tt;
		message_lyh mess(socket);
		int temp = 0;
		cout << "������:";
		message_lyh::waitsending();
		message_lyh::send1();
		mess.sign("\0\1\5");
		cin >> tt;
		message_lyh tempm(socket,tt);
		tempm.send();
		message_lyh::send0();*/
	}
	void face_lyh::chatgroup_face() {
		system("cls");
		string id;
		message_lyh mess(socket);
		char iff;
		cout << "ѡ��Ⱥ�ģ�";
		cin >> id;
		message_lyh::waitboth();
		message_lyh::recv1();
		message_lyh::send1();
		mess.sign("\0\1\4");
		mess.add(id.c_str());
		mess.recv();
		iff = mess.str().c_str()[0];//����1���Ǻ��ѣ����Խ�����һ��
		message_lyh::recv0();
		message_lyh::send0();
		if (iff != 1) {
			cout << "δ�����Ⱥ��" << endl;
			_getch();
			return;
		}
		//�����ݿ��ڶ���һ�ܵ�������Ϣ
		while (1) {
			cout << "1���鿴������Ϣ" << endl;
			cout << "2��������Ϣ" << endl;
			cout << "3���˳�" << endl;
			cin >> iff;
			if (iff == 1) {
				datamore_chatgroup_face(id);//�����ݿ��ڶ���100��������Ϣ
			}
			else if (iff == 2) {
				send_chatfriend_face();
			}
			else if (iff == 3) {
				mess.sign("\0\0\0");//��ʾ�˴� ͨ�Ž��� 
				return;
			}
		}
	}
	void face_lyh::newmanage_leader_managegroup_face(string id) {
		message_lyh message(socket);
		//message_lyh::waitboth();
		//message_lyh::recv1();
		//message_lyh::send1();
		message.sign("\0\1\7");
		string newid;
		char temp;
		cout << "�¹���ԱID��";
		cin >> newid;
		message.add_num(user->key);//ԭʼ����
		//message.add_num(id);//Ⱥid
		message.add_num(newid);//�¹���Աid
		message.add_end();
		message.send();
		message.recv();
		temp = message.str().c_str()[0];
		//message_lyh::recv0();
		//message_lyh::send0();
		if (temp == 1) {
			cout << "�������" << endl;
			_getch();
			system("cls");
		}
		else {
			cout << "����" << endl;
			_getch();
			system("cls");
		}
	}
	void face_lyh::delmanage_leader_managegroup_face(string id) {
		message_lyh message(socket);
		//message_lyh::waitboth();
		//message_lyh::recv1();
		//message_lyh::send1();
		message.sign("\0\1\010");
		string newid;
		char temp;
		cout << "��Ҫɾ���Ĺ���ԱID��";
		cin >> newid;
		message.add_num(user->key);//ԭʼ����
		//message.add_num(id);//Ⱥid
		message.add_num(newid);//����Աid
		message.add_end();
		message.send();
		message.recv();
		temp = message.str().c_str()[0];
		//message_lyh::recv0();
		//message_lyh::send0();
		if (temp == 1) {
			cout << "�������" << endl;
			_getch();
			system("cls");
		}
		else {
			cout << "����" << endl;
			_getch();
			system("cls");
		}
	}
	void face_lyh::kick_leader_managegroup_face(string id) {
		message_lyh message(socket);
		//message_lyh::waitboth();
		//message_lyh::recv1();
		//message_lyh::send1();
		message.sign("\000\001\011");
		string newid;
		char temp;
		cout << "ID��";
		cin >> newid;
		message.add_num(user->key);//ԭʼ����
		//message.add_num(user->ID);//�û�id
		//message.add_num(id);//Ⱥid
		message.reload(newid);// ������id
		message.add_end();
		message.send();
		message.recv();
		temp = message.str().c_str()[0];
		//message_lyh::recv0();
		//message_lyh::send0();
		if (temp == 1) {
			cout << "�������" << endl;
			_getch();
			system("cls");
		}
		else {
			cout << "����" << endl;
			_getch();
			system("cls");
		}
	}
	void face_lyh::check_leader_managegroup_face(string id) {
		//message_lyh::waitboth();
		//message_lyh::recv1();
		//message_lyh::send1();
		message_lyh message(socket);
		message.sign("\0\1\012");
		string put, put1;
		char iff;
		message.add(user->key);
		message.send();
		//message.add_num(user->ID);
		//message.add_num(id);
		//message.add_end();
		//message.recv();
		//iff = message.str().c_str()[0];
		//if (iff == 0) {
		//	cout << "����";
		//	_getch();
		//	system("cls");
		//}
		message.recv();
		message.putout_num(1);//������д    name id pname
		cout << endl;
		cout << "����1ͬ�� ����0�ܾ� ��";
		cin >> put;
		message.reload(put);
		message.send();
		system("cls");
		return;
		/*while (1) {
			cout << "����0���أ�����1����:";
			cin >> iff;
			if (iff == 0) {
				system("cls");
				return;
			}
			cout << "ѡ��ID��";
			cin >> put;
			cout << "����1ͬ��  ����0�ܾ�";
			cin >> put1;
			message.add_num(user->key);
			message.add_num(user->ID);
			message.add_num(id);
			message.add_num(put);
			message.add_num(put1);
			message.add_end();
			message.send();
			message.recv();
			put = message.str();
			if (put[0] == 1) {
				cout << "���" << endl;
			}
			else {
				cout << "����" << endl;
			}
		}*/
	}
	void face_lyh::cname_leader_managegroup_face(string id) {
		//message_lyh::waitboth();
		//message_lyh::recv1();
		//message_lyh::send1();
		message_lyh message(socket);
		message.sign("\0\1\014");
		string newid;
		char temp;
		cout << "�����ƣ�";
		cin >> newid;
		message.add_num(user->key);//ԭʼ����
		//message.add_num(user->ID);//�û�id
		//message.add_num(id);//Ⱥid
		message.add_num(newid);//������
		message.add_end();
		message.send();
		message.recv();
		temp = message.str().c_str()[0];
		//message_lyh::recv0();
		//message_lyh::send0();
		if (temp == 1) {
			cout << "�������" << endl;
			_getch();
			system("cls");
		}
		else {
			cout << "����" << endl;
			_getch();
			system("cls");
		}
	}
	void face_lyh::ckind_leader_managegroup_face(string id) {
		//message_lyh::waitboth();
		//message_lyh::recv1();
		//message_lyh::send1();
		message_lyh message(socket);
		message.sign("\0\001\016");
		string newid;
		char temp;
		cout << "1����ͨȺ" << endl;
		cout << "2������Ⱥ" << endl;
		cout << "3����УȺ" << endl;
		cout << "�����ͣ�";
		cin >> newid;
		message.add_num(user->key);//ԭʼ����
		//message.add_num(user->ID);//�û�id
		//message.add_num(id);//Ⱥid
		message.add_num(newid);//������
		message.add_end();
		message.send();
		message.recv();
		temp = message.str().c_str()[0];
		//message_lyh::recv0();
		//message_lyh::send0();
		if (temp == 1) {
			cout << "�������" << endl;
			_getch();
			system("cls");
		}
		else {
			cout << "����" << endl;
			_getch();
			system("cls");
		}
	}
	void face_lyh::leader_managegroup_face(string id) {
		char iff;
		if (user->way == 1) {
			message_lyh message(socket);
			message.recv();
			cout << "Ⱥ��Ա��:" << endl;
			message.putout_num(2);
			message.recv();
			cout << "����Ա��:" << endl;
			message.putout_num(2);
			while (1) {
				cout << "1�������µĹ���Ա(qq����)" << endl;
				cout << "2��ȡ������Ȩ��(qq����)" << endl;
				cout << "3������Ա�߳�Ⱥ��" << endl;
				cout << "4�������Ⱥ����" << endl;
				cout << "5������Ⱥ������" << endl;
				cout << "6������Ⱥ������(qq����)" << endl;
				cout << "0������" << endl;
				cin >> iff;
				if (iff == 0) {
					return;
				}
				else if (iff == 1) {
					newmanage_leader_managegroup_face(id);
				}
				else if (iff == 2) {
					delmanage_leader_managegroup_face(id);
				}
				else if (iff == 3) {
					kick_leader_managegroup_face(id);
				}
				else if (iff == 4) {
					check_leader_managegroup_face(id);
				}
				else if (iff == 5) {
					cname_leader_managegroup_face(id);
				}
				else if (iff == 6) {
					ckind_leader_managegroup_face(id);
				}
			}
		}
		else if (user->way == 2 || user->way == 3) {
			message_lyh message(socket);
			message.recv();
			cout << "Ⱥ��Ա��:" << endl;
			message.putout_num(2);
			message.recv();
			cout << "1������Ա�߳�Ⱥ��" << endl;
			cout << "2���鿴��Ⱥ����" << endl;
			cout << "3������Ⱥ������" << endl;
			cout << "0������" << endl;
			cin >> iff;
			if (iff == 0) {
				return;
			}
			else if (iff == 1) {
				kick_leader_managegroup_face(id);
			}
			else if (iff == 2) {
				check_leader_managegroup_face(id);
			}
			else if (iff == 3) {
				cname_leader_managegroup_face(id);
			}
		}
	}
	void face_lyh::manage_managegroup_face(string id) {
		char iff;
		if (user->way == 1) {
			message_lyh message(socket);
			message.recv();
			cout << "Ⱥ��Ա��:" << endl;
			message.putout_num(2);
			message.recv();
			cout << "����Ա��:" << endl;
			message.putout_num(2);
			while (1) {
				cout << "1������Ա�߳�Ⱥ��" << endl;
				cout << "2�������Ⱥ����" << endl;
				cout << "3������Ⱥ������" << endl;
				cout << "0������" << endl;
				cin >> iff;
				if (iff == 0) {
					return;
				}
				else if (iff == 1) {
					kick_leader_managegroup_face(id);
				}
				else if (iff == 2) {
					leader_managegroup_face(id);
				}
				else if (iff == 3) {
					cname_leader_managegroup_face(id);
				}
			}
		}
		else if (user->way == 2 || user->way == 3) {
			return;
		}
	}//////////////////////////////////////////////////////////δ���
	void face_lyh::creatgroup_face() {
		message_lyh message(socket);
		string id, name;
		message_lyh::waitboth();
		message_lyh::recv1();
		message_lyh::send1();
		message.sign("\0\1\11");
		system("cls");
		cout << "Ⱥ�����ƣ�";
		cin >> name;
		message.add_num(name);
		message.add_num(user->key);
		message.add_end();
		message.send();
		message.recv();
		id = message.str();
		cout << "���ȺIDΪ:" << id;
		message_lyh::recv0();
		message_lyh::send0();
		_getch();
		system("cls");
	}
	void face_lyh::managegroup_face() {
		message_lyh message(socket);
		string temp;
		char chartemp;
		message_lyh::waitboth();
		message_lyh::recv1();
		message_lyh::send1();
		message.sign("\0\1\6");
		message.recv();
		message.putout_num(2);
		while (1) {
			cout << "ѡ��Ⱥ�Ļ�0����";
			cin >> temp;
			if (temp.size() == 1 && temp[0] == 1) {
				message_lyh::recv0();
				message_lyh::send0();
				message.sign("\0\1\6");
				return;  
			}
			else if (temp.size() != 7) {
				cout << "id����" << endl;
				_getch();
				system("cls");
			}
			else {
				message.reload(temp.c_str());
				message.send();
				message.recv();//0��Ȩ�� 1��Ⱥ�� 2�ǹ���
				char chartmp = message.str()[0];
				if (chartemp == 0) {
					cout << "id����:";
					_getch();
					system("cls");
					message.sign("\0\1\6");
					message_lyh::recv0();
					message_lyh::send0();
					return;
				}
				else if (chartemp == 1) {
					leader_managegroup_face(temp);
				}
				else if (chartemp == 2) {
					manage_managegroup_face(temp);
				}
			}
		}
	}
	void face_lyh::pullgroup_face() {
		system("cls");
		message_lyh message(socket);
		string fid, gid, temp;
		message.waitboth();
		message.recv1();
		message.send1();
		message.sign("\0\1\017");
		cout << "�������ID��";
		cin >> fid;
		cout << "����ȺID��";
		cin >> gid;
		message.add_num(user->key);
		//message.add_num(user->ID);
		message.add_num(fid);
		message.add_num(gid);
		message.add_end();
		message.send();
		message.recv();
		temp = message.str();
		if (temp[0] == 1) {
			cout << "�������" << endl;
			_getch();
			system("cls");
		}
		else {
			cout << "����" << endl;
			_getch();
			system("cls");
		}
		message.recv0();
		message.send0();
	}
	void face_lyh::songroup_face() {
		system("cls");
		message_lyh message(socket);
		message_lyh::waitboth();
		message_lyh::recv1();
		message_lyh::send1();
		message.sign("\0\1\13");
		string fid, id, temp;
		cout << "���븸Ⱥ��ID��";
		cin >> fid;
		message.clear();
		message.add_num(user->key);
		message.add_num(fid);
		message.send();
		message.recv();
		if (message.str()[0] == 0) {
			cout << "����";
			message_lyh::recv0();
			message_lyh::send0();
			_getch();
			system("cls");
			return;
		}
		message.clear();
		cout << "�����û�ID��";
		cin >> id;
		message.add_num(id);
		while (1) {
			cout << "����0���  ����1����";
			cin >> temp;
			if (temp[0] == 0) {
				break;
			}
			cout << "�����û�ID��";
			cin >> id;
			message.add_num(id);
		}
		message.add_end();
		message.send();
		message.recv();
		//if (message.str()[0] == 0) {
		cout << "���" << endl;
			cout << "Ⱥ��ID��";
			message.putout_num(9);
			_getch();
			system("cls");
			message_lyh::recv0();
			message_lyh::send0();
			return;
		//}
		/*else {
			cout << "�����û����ڴ���" << endl;
			message.putout_num(2);
			message.recv();
			cout <<endl<< "Ⱥ�����ƣ�";
			message.putout_num(9);
			message_lyh::recv0();
			message_lyh::send0();
			_getch();
			system("cls");
			return;
		}*/
	}
	void face_lyh::group_face() {
		char input;
		if (user->way == 1) {
			while (1) {
				system("cls");
				cout << "1���鿴Ⱥ��" << endl;
				cout << "2�����Ⱥ��" << endl;
				cout << "3���˳�Ⱥ��" << endl;
				cout << "4��Ⱥ������" << endl;
				cout << "5������Ⱥ��" << endl;
				cout << "6������Ⱥ��" << endl;
				cout << "7���Ƽ����Ѽ���Ⱥ��" << endl;
				cout << "8��������Ⱥ" << endl;
				cout << "0������" << endl;
				cin >> input;
				if (input == '0') {
					return;
				}
				else if (input == '1') {
					checkgroup_face();
				}
				else if (input == '2') {
					addgroup_face();
				}
				else if (input == '3') {
					deletegroup_face();
				}
				else if (input == '4') {
					chatgroup_face();
				}
				else if (input == '5') {
					managegroup_face();
				}
				else if (input == '6') {
					creatgroup_face();
				}
				else if (input == '7') {
					pullgroup_face();
				}
				else if (input == '8') {
					songroup_face();
				}
			}
		}
		else if (user->way == 2 || user->way == 3) {
			while (1) {
				system("cls");
				cout << "1���鿴Ⱥ��" << endl;
				cout << "2���˳�Ⱥ��" << endl;
				cout << "3��Ⱥ������" << endl;
				cout << "4������Ⱥ��" << endl;
				cout << "5������Ⱥ��" << endl;
				cout << "6���Ƽ����Ѽ���Ⱥ��" << endl;
				cout << "0������" << endl;
				cin >> input;
				if (input == '0') {
					return;
				}
				else if (input == '1') {
					checkgroup_face();
				}
				else if (input == '2') {
					deletegroup_face();
				}
				else if (input == '3') {
					chatgroup_face();
				}
				else if (input == '4') {
					managegroup_face();
				}
				else if (input == '5') {
					creatgroup_face();
				}
				else if (input == '6') {
					pullgroup_face();
				}
			}
		}
	}
	/// //////////////��Ϊ����
	void face_lyh::name_dataset_face() {
		message_lyh message(socket);
		string newname;
		while (1) {
			cout << "�������ǳƣ�";
			cin >> newname;
			if (newname.size() > 20) {
				cout << "���ƹ��������20�ַ�" << endl;
			}
			else {
				message.sign("\0\0\1");
				message.clear();
				message.add_num(user->key);
				message.add_num(newname);
				message.add_end();
				message.send();
				user->name = newname;
				cout << "�޸����";
				_getch();
				system("cls");
			}
		}
	}
	void face_lyh::birth_dataset_face() {
		message_lyh message(socket);
		string newbirth;
		while (1) {
			cout << "�������ǳƣ�";
			cin >> newbirth;
			if (newbirth.size() > 20) {
				cout << "���ƹ��������20�ַ�" << endl;
			}
			else {
				message.sign("\0\0\2");
				message.clear();
				message.add_num(user->key);
				message.add_num(newbirth);
				message.add_end();
				message.send();
				user->birth = newbirth;
				cout << "�޸����";
				_getch();
				system("cls");
			}
		}
	}
	void face_lyh::place_dataset_face() {
		message_lyh message(socket);
		string newplace;
		while (1) {
			cout << "�������ǳƣ�";
			cin >> newplace;
			if (newplace.size() > 20) {
				cout << "���ƹ��������20�ַ�" << endl;
			}
			else {
				message.sign("\0\0\3");
				message.clear();
				message.add_num(user->key);
				message.add_num(newplace);
				message.add_end();
				message.send();
				user->place = newplace;
				cout << "�޸����";
				_getch();
				system("cls");
			}
		}
	}
	void face_lyh::dataset_face() {
		message_lyh::waitboth();
		message_lyh::recv1();
		message_lyh::send1();
		message_lyh message(socket);
		message.sign("\0\2\1");
		int temp;
		if (user->way == 1) {
			cout << "���QQ�˺�" << endl;
			cout << "ID��" << user->ID<<endl;
			cout << "�ǳƣ�" << user->name << endl;
			cout << "���գ�" << user->birth << endl;
			cout << "Q�䣺" << user->useage << endl;
			cout << "���ڵ�����" << user->place << endl;
			while (1) {
				cout << endl;
				cout << "1���޸��ǳ�" << endl;
				cout << "2���޸�����" << endl;
				cout << "3���޸ĵ���" << endl;
				cout << "0������" << endl;
				cin >> temp;
				if (temp == 0) {
					message_lyh::recv0();
					message_lyh::send0();
					message.sign("\0\2\1");
					return;
				}
				else if (temp == 1) {
					name_dataset_face();
				}
				else if (temp == 2) {
					birth_dataset_face();
				}
				else if (temp == 3) {
					place_dataset_face();
				}
				else {}
			}
		}
	}
	void face_lyh::bindset_face() {
		message_lyh::waitboth();
		message_lyh::recv1();
		message_lyh::send1();
		message_lyh message(socket);
		message.sign("\0\2\2");
		string str;
		message.recv();
		cout << "��İ��˻��У�" << endl;
		message.putout_num(2);
		while (1) {
			if (user->way == 1) {
				cout << "3����΢��" << endl;
			}
			if (user->way == 2) {
				cout << "3����΢��" << endl;
			}
			if (user->way == 3) {
				cout << "1����QQ/΢��" << endl;
			}
			/*
				cout << "1����QQ" << endl;
				cout << "2����΢��" << endl;
				cout << "3����΢��" << endl;
			 */
			cout << "9���˳����½�����" << endl;
			cout << "0���˳�";
			cin >> str;
			message.clear();
			if (str[0] == '1') { message.sign("\0\0\1"); }
			else if (str[0] == '2') { message.sign("\0\0\2"); }
			else if (str[0] == '3') { message.sign("\0\0\3"); }
			else if (str[0] == '0') {
				message.sign("\0\0\0");
				message_lyh::recv0();
				message_lyh::send0();
				_getch();
				system("cls");
				return;
			}
			else { 
				continue; 
			}
			message.add_num(user->ID);
			message.add_num(user->key);
			cout << "�����˺ţ�";
			cin >> str;
			message.add_num(str);
			cout << "�������룺";
			cin >> str;
			message.add_num(str);
			message.send();
			message.recv();
			str = message.str();
			if (str[0] == 1) {
				cout << "�󶨳ɹ�";
				_getch();
				system("cls");
				return;
			}
			else {
				cout << "����ʧ��";
				_getch();
				system("cls");
				return;
			}
		}
	}
	void face_lyh::delset_face() {
		string str;
		cout << "���롰ȷ������ע���˺ţ�";
		cin >> str;
		if (str == "ȷ��") {
			message_lyh message(socket);
			message_lyh::waitboth();
			message_lyh::recv1();
			message_lyh::send1();
			message.sign("\0\2\3");
			message.add_num(user->ID);
			message.add_num(user->key);
			message.recv();
			str = message.str();
			if (str[0] == 1) {
				cout << "ע���ɹ�";
				_getch();
				exit(0);
			}
			else {
				cout << "ע��ʧ��";
				_getch();
				system("cls");
				message_lyh::recv0();
				message_lyh::send0();
				return;
			}
		}
	}
	void face_lyh::set_face() {
		char input;
		while (1) {
			system("cls");
			cout << "1�����Ļ�����Ϣ" << endl;
			cout << "2�����˻�" << endl;
			cout << "3��ע���˻�" << endl;
			cout << "0������" << endl;
			cin >> input;
			if (input == '0') {
				return ;
			}
			if (input == '1') {
				dataset_face();
			}
			else if (input == '2') {
				bindset_face();
			}
			else if (input == '3') {
				delset_face();
			}
		}
	}
