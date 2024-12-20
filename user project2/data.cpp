#include"data.h"
using namespace std;
using namespace std::filesystem;
/*
list：朋友id 第一个聊天记录位置 最后一个(最近)聊天记录位置
file：聊天记录 时间 上一个的位置(位置有11位)

*/
//class data_lyh {
//public:
//	static int fnew(string id) {
//		ifstream file(id+".txt");
//		if (file.good() == true) {
//			file.close();
//			return 0;
//		}
//		else {
//			fclose(fopen((id + ".txt").c_str(), "w"));
//			fclose(fopen((id + "list.txt").c_str(), "w"));
//		}
//	}
//	data_lyh(string id) {
//		ID = id;
//		file.open(ID+".txt");
//		list.open(ID + "list.txt");
//	}
//	void flash() {
//		file.flush();
//	}
//	int in(string con, time_t tm,string id) {
//		string str;
//		int  tp, tp1, tp2;
//		list.seekg(0, ios::beg);
//		list.seekp(0, ios::beg);
//		tp2 = list.tellp();
//		while (1) {
//			list >> str;
//			if (str == id) {
//				list >> str;
//				list >> str;
//				tp = stoi(str);
//				file.seekg(0, ios::end);
//				tp1 = file.tellg();
//				file << '\n';
//				file << con<<" "<<tm<<"" << '\n';
//				file.seekp(tp, ios::beg);
//				file >> str;
//				file >> str;
//				tp = file.tellp();
//				file <<' ' << tp1;
//				list.seekp(tp2, ios::beg);
//				list >> str;
//				list >> str;
//				tp2 = list.tellp();
//				list.seekg(tp2);
//				list << ' ' << tp1;
//				return 1;
//			}
//			else if(list.eof()==true){
//				list.seekg(0, ios::end);
//				list << id << ' ';
//				file.seekg(0, ios::end);
//				tp1 = file.tellg();
//				file << '\n';
//				file << con << " " << tm << "0          " << '\n';
//				list << tp1 <<"          " << tp1<<"          ";
//				return 1;
//			}
//			list >> str;
//			list >> str;
//			tp2 = list.tellp();
//		}
//	}
//	string out(string id,int tm=-1) {
//		string str = {}, tmp = {};
//		int  tp, tp1, tp2;
//		list.seekp(0, ios::beg);
//		tp2 = list.tellp();
//		while (1) {
//			list >> str;
//			if (str == id) {
//				list >> str;
//				tp = stoi(str);
//				file.seekp(tp);
//				if (tm == -1) {
//					while (1) {
//						file >> tmp;
//						str += tmp;
//						str += "\n";
//						file >> tmp;
//						str += tmp;
//						str += "\n";
//						file >> tp1;
//						if (tp1 == 0)return str;
//						else {
//							file.seekp(tp1);
//						}
//					}
//				}
//				else {
//					while (tm > 0) {
//
//					}
//				}
//				
//			}
//			else if (list.eof() == true) {
//				
//			}
//			list >> str;
//			list >> str;
//			tp2 = list.tellp();
//		}
//	}
//protected:
//	string ID;
//	fstream file;
//	fstream list;
//};
	const string allfile_lyh::id() {
		return ID;
	}
	allfile_lyh::allfile_lyh(path entry) {
		file.open(entry);
		string tmp;
		while (file.eof() != true) {
			getline(file, tmp);
			row++;
		}
		ID = entry.stem().string();
	}
	void allfile_lyh::in(string str, time_t tm) {
		file.seekg(0, ios::end);
		file << str << ' ' << tm << '\n';
		row++;
	}
	void allfile_lyh::out(string& str, int num) {
		string tmp = {};
		file.seekp(ios::beg);
		if(num==-1){
			while (1) {
				file >> tmp;
				if (file.eof() == true) { return; }
				str += tmp;
				str += "\n";
				file >> tmp;
				str += tmp;
				str += "\n";
			}
		}
		else {
			int tmpi = row - num;
			while (tmpi > 0) {
				getline(file, tmp);
				tmpi--;
			}
			while (file.eof() != true) {
				file >> tmp;
				str += tmp;
				str += "\n";
			}
		}
	}
	void allfile_lyh::flush() {
		file.flush();
	}
	void allfile_lyh::close() {
		file.close();
	}

	data_lyh::data_lyh(string id, char w) {
		ID = id;
		way = w;
		path directory = id+w;
		creatfile(id, w);
		for (const auto& entry : directory_iterator(directory)) {
			if (entry.is_regular_file() && entry.path().extension() == ".txt") {
				file.push_back(entry.path());
			}
		}
	}
	data_lyh::data_lyh() {};
	void data_lyh::start(string id,char w) {
		ID = id;
		way = w;
		path directory = id+w;
		creatfile(id, w);
		for (const auto& entry : directory_iterator(directory)) {
			if (entry.is_regular_file() && entry.path().extension() == ".txt") {
				file.push_back(entry.path());
			}
		}
	}
	void data_lyh::flush() {
		for (auto& i : file) {
			i.flush();
		}
	}
	int data_lyh::in(string str, time_t tm, string id) {
		allfile_lyh *pi = find(id);
		if (pi == NULL)return 0;
		pi->in(str, tm);
	}
	int data_lyh::out(string& str, int num,string id) {
		allfile_lyh* pi = find(id);
		if (pi == NULL)return 0;
		pi->out(str, num);
	}
	int data_lyh::remove(string id) {
		int num = 0;
		while (num<file.size()) {
			if (file[num].id() == id) {
				file[num].close();
				file.erase(file.begin() + num);
			}
		}
		remove(ID + '/' + id + ".txt");
		return 0;
	}
	int data_lyh::newone(string id) {
		string str;
		str = ID + '/' + id+".txt";
		if (find(id) != NULL) {
			return 0;
		}
		fopen(str.c_str(), "w");
		return 1;
	}
	int data_lyh::creatfile(string ID,char w) {
		if (create_directory(ID+w) == true)return 1;
		else return 0;
	}
	allfile_lyh* data_lyh::find(string id) {
		for (auto& i : file) {
			if (i.id() == id) {
				return &i;
			}
		}
		return NULL;
	}