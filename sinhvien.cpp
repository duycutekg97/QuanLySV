#include <iostream>
#include <iostream>
#include <fstream>
#include<string>
#include <ctime>
#include <iomanip>

using namespace std;


struct Sinhvien {
	string maSV;
	string ho;
	string ten;
	double diem1;
	double diem2;
};
typedef struct Sinhvien SINHVIEN;
// khai bao cau truc 1 node sinh vien
struct Node{
	Sinhvien data;
	Node* pre;
	Node* next;
};
// khai bao lien ket kep
struct DoubleLinkedList {
	Node* head;
	Node* tail;
};
Node* KhoiTaoDanhSachSinhVien(Sinhvien x) {
	Node* p = new Node;
	if (p == NULL) {
		cout << "\nCap Nhat That Bai";
		return NULL;
	}
	p->data = x;
	p->next = NULL;
	p->pre = NULL;
	return p;

}
//khoi tao danh sach
void initSinhvien(DoubleLinkedList &list) {
	list.head = NULL;
	list.tail = NULL;
}
void addFirst(DoubleLinkedList& list, Node* x);
void addLast(DoubleLinkedList& list, Node* x);
void readtxtSV(ifstream& filein, Sinhvien& x);// doc du lieu 1 sinh vien tu file text
void readListSV(ifstream& filein, DoubleLinkedList& list);// doc du lieu danh sach sinh vien tu file textt
void outputSV(Sinhvien x);// xuat ra 1 sinh vien
void outputListSV(DoubleLinkedList list);// xuat ra  danh sach sinh vien
void SearchSV(DoubleLinkedList& list, string ma);
Node* SearchNode(DoubleLinkedList& list, string ma); // tim kiem node de xoa
void addSV(DoubleLinkedList& list);// them 1 sinh vien vao danh sach
bool checkID(DoubleLinkedList& list, string id); // kiem tra trung id
string checkUppercase(string s);// Chuan hoa ky tu
bool checkpoint(double n);//kiem tra diem
void del(DoubleLinkedList& list); // xoa theo ten ma;
void delFirst(DoubleLinkedList& list);
void delLast(DoubleLinkedList& list);
void swapSV(Sinhvien& x, Sinhvien& y);
void SortName(DoubleLinkedList& list);/// sap xep danh sach theo ten
void SortPoint(DoubleLinkedList& list);
void swapPoint(int& x, int& y);
void checkPassExam(DoubleLinkedList& list); // Coi xem sinh vien dau va rot
void writeListSV(ofstream& filein, DoubleLinkedList& list);
void Searchpoint(DoubleLinkedList& list, int n,int m);// tim kiem theo diem trung binh

int main() {
	
	DoubleLinkedList l;
	
	
	int choose;
	ifstream filein;
	int n, m;
	
	ofstream filein2;
	

	
	string ma;
	
	do {
			cout << " 1. Doc danh sach sinh vien tu file.txt." << endl;
			cout << " 2. In danh sach sinh vien co trong file.txt." << endl;
			cout << " 3. Tim kiem thong tin sinh vien thong qua MSSV. " << endl;
			cout << " 4. Tim kiem thon tin sinh vien thong qua diem. " << endl;
			cout << " 5. Them vao danh sach mot sinh vien. " << endl;
			cout << " 6. Xoa sinh vien thong qua  MSSV." << endl;
			cout << " 7. In danh sach sinh vien theo Ten Tang dan" << endl;
			cout << " 8. In danh sach sinh vien theo diem trung binh giam dan. " << endl;
			cout << " 9. In danh sach cac sinh vien ve ket qua hoc tap." << endl;
			cout << " 0. Thoat. " << endl;
			cout << " Chon : ";
			cin >> choose;
			if (choose == 0)
				break;
			else {
				switch (choose)
				{
				case 1:
					initSinhvien(l);
					filein.open("sinhvien.txt");
					readListSV(filein, l);
					cout << " Da doc thanh cong." << endl;
					filein.close();
					break;
				case 2:
					outputListSV(l);
					break;
				case 3:
					cout << " Nhap vao  MSSV can tim : ";
					cin >> ma;
					SearchSV(l, ma);
					break;
				case 4:
					do {
						cout << "Nhap diem nho nhat can tim : ";
						cin >> n;
						if (checkpoint(n) == false)
							cout << " Nhap sai nhap lai " << endl;
					} while (checkpoint(n) == false);
					do {
						cout << "Nhap diem lon nhat can tim : ";
						cin >> m;
						if (checkpoint(m) == false)
							cout << " Nhap sai nhap lai " << endl;
					} while (checkpoint(m) == false);
					Searchpoint(l, n, m);
					break;
				case 5:
					filein2.open("sinhvien.txt");
					addSV(l);
					break;
					writeListSV(filein2, l);
					filein2.close();
				case 6:
					filein2.open("sinhvien.txt");
					del(l);
					writeListSV(filein2, l);
					break;
					filein2.close();
				case 7:
					SortName(l);
					outputListSV(l);
					break;
				case 8:
					SortPoint(l);
					outputListSV(l);
					break;
				case 9:
					checkPassExam(l);
					break;
				default:
					cout << "Nhap sai nhap lai";
					break;
				}
			}

	} while (choose != 0);
	
	
	system("pause");
	return 0;

}
void addFirst(DoubleLinkedList& list, Node* p) {


	if (list.head == NULL)  // danh sach sinh vien dang rong
	{
		list.head = list.tail = p;
	}
	else {
		p->next = list.head;
		list.head->pre = p;
		list.head = p;
	}
}
void addLast(DoubleLinkedList& list, Node* p) {
	
	if (list.tail == NULL)
	{
		list.head = list.tail = p;
	}
	else {
		p->pre = list.tail;
		list.tail->next = p;
		list.tail = p;
	}
}
void readtxtSV(ifstream& filein, Sinhvien& x) {
	getline(filein, x.maSV, '-');
	getline(filein, x.ho, '-');
	getline(filein, x.ten, '-');
	filein >> x.diem1;
	filein.seekg(1, 1);
	filein >> x.diem2;
	filein.ignore(1);



}
void outputSV(Sinhvien x) {

	cout << left <<setw(1) <<"|" << left << setw(14) << x.maSV << "\t";
	cout << left << setw(20)  << x.ho << "\t";
	cout << left << setw(10)  << x.ten << "\t";
	cout << left << setw(20)  << x.diem1 << "\t";
	cout << left << setw(20)  << x.diem2 << "\t";
	cout << left << setw(16)  << double((x.diem1 + x.diem2) / 2)<<left <<setw(1)<<"|";
}
void readListSV(ifstream& filein, DoubleLinkedList& list) {
	//doc den cuoi file thi dung
	while (!filein.eof()){
		SINHVIEN sv;
		//DocThong Tin Sinh Vien
		readtxtSV(filein, sv);
		//Khoi tao Node Sinh Vien
		Node* p = KhoiTaoDanhSachSinhVien(sv);
		// Them Sinh vien vao Node
		addLast(list, p);
	}
}
void writeListSV(ofstream& filein, DoubleLinkedList& list) {
	for (Node* p = list.head; p != NULL; p = p->next) {
		if (p->next == NULL)
			filein << p->data.maSV << "-" << p->data.ho << "-" << p->data.ten << "-" << p->data.diem1 << "-" << p->data.diem2 ;
		else
		filein<<p->data.maSV<<"-"<<p->data.ho<<"-"<<p->data.ten<<"-"<<p->data.diem1<<"-" << p->data.diem2 << endl;
	}
	

}
void outputListSV(DoubleLinkedList list) {
	cout << "=========================================================================================================================" << endl;
	
	cout << left << setw(15) << "|MSSV:" << "\t" << left << setw(20) << "Ho" << "\t" << left << setw(10) << "Ten" << "\t" << left << setw(20) << "Diem mon 1" << "\t" << left << setw(20) << "Diem mon 2" <<"\t"<< left << setw(20) << "Diem trung binh |" << endl;
	
	cout << "=========================================================================================================================" << endl;
	for (Node* p = list.head; p != NULL; p = p->next)
	{
		outputSV(p->data);
		cout << endl;
	}
	cout << "=========================================================================================================================" << endl;

}
void SearchSV(DoubleLinkedList& list, string ma) {
	cout << "=========================================================================================================================" << endl;

	for (Node* p = list.head; p != NULL; p = p->next) {
		if (ma == p->data.maSV)
			outputSV(p->data);
	}
	cout << endl;
	cout << "=========================================================================================================================" << endl;
}
void addSV(DoubleLinkedList& list) {
	Sinhvien tmp;
	do {
		
		cout << "Nhap massv: ";
		cin >> tmp.maSV;
		if (checkID(list, checkUppercase(tmp.maSV)) == false)
			cout << "Trung ma so sinh vien" << endl;
	} while (checkID(list, checkUppercase(tmp.maSV))==false);

	
	cout << "Nhap ho : ";
	cin >> tmp.ho;
	cout << " Nhap ten: ";
	cin >> tmp.ten;
	do {
		cout << "Nhap diem thi mon 1 ";
		cin >> tmp.diem1;
		if (checkpoint(tmp.diem1) == false)
		cout << " Nhap sai nhap lai " << endl;
	} while (checkpoint(tmp.diem1) == false);
	do {
		cout << "Nhap diem thi mon 2 ";
		cin >> tmp.diem2;
		if (checkpoint(tmp.diem2) == false)
			cout << " Nhap sai nhap lai " << endl;
	} while (checkpoint(tmp.diem2) == false);
	addFirst(list, KhoiTaoDanhSachSinhVien(tmp));


}
bool checkID(DoubleLinkedList& list, string id) {
	for (Node* p = list.head; p != NULL; p = p->next) {
		if (p->data.maSV == id)
			return false;
	}
	return true;
}
string checkUppercase(string s) {
	string tmp;
	for (int i = 0; i < s.length(); i++)
		s[i] = tolower(s[i]);
	tmp = s;
	return  tmp;
}
bool checkpoint(double n) {
	return (n >= 0 && n <= 10);
}
Node* SearchNode(DoubleLinkedList& list, string ma) {
	Node* p;
	p = list.head;
	while ((p != NULL) && (p->data.maSV != ma))
		p = p->next;
	return p;
}
void del(DoubleLinkedList& list) {
	string ma;
	cout << "Nhap vao ma sinh vien can xoa : ";
	cin >> ma;
	Node* p = SearchNode(list, checkUppercase(ma));

	if (p != NULL)
	{
		if (p->pre == NULL) {
			delFirst(list);
			return;
		}
		if (p->next == NULL) {
			delLast(list);
			return;
		}
		p->pre->next = p->next;
		p->next->pre = p->pre;

		p->pre = NULL;
		p->next = NULL;
		delete p;
	}

}
void delFirst(DoubleLinkedList& list) {
	Node* p = list.head;
	list.head = list.head->next;
	list.head->pre = NULL;
	if (list.head == NULL)
		list.tail = NULL;
	p->next = NULL;
	delete p;
}
void delLast(DoubleLinkedList& list) {
	Node* p = list.tail;
	list.tail = list.tail->pre;
	list.tail->next = NULL;
	if (list.tail == NULL)
		list.head = NULL;
	p->pre = NULL;
	delete p;
}void swapSV(Sinhvien& x, Sinhvien& y) {
	Sinhvien tmp = x;
	x = y;
	y = tmp;
}
void SortName(DoubleLinkedList& list) {
	for (Node* p = list.head; p != NULL; p = p->next) {
		for (Node* k = p->next; k != NULL; k = k->next) {
			if (checkUppercase(k->data.ten) < checkUppercase(p->data.ten))
				swap(k->data, p->data);
			if (checkUppercase(k->data.ten) == checkUppercase(p->data.ten))
			{
				if (k->data.ten > p->data.ten)
					swap(k->data, p->data);
			}
		}
	}
}
void SortPoint(DoubleLinkedList& list) {
	for (Node* p = list.head; p != NULL; p = p->next) {
		for (Node* k = p->next; k != NULL; k = k->next) {
			if (((k->data.diem1 + k->data.diem2) / 2) > ((p->data.diem1 + p->data.diem2) / 2))
				swap(k->data, p->data);

		}
	}
}
void swapPoint(int& x, int& y) {
		int tmp = x;
		x = y;
		y = tmp;
}
void checkPassExam(DoubleLinkedList& list) {
	cout << "=========================================================================================================================" << endl;
	cout << "====                                        Cac Sinh Vien Dau                                                        ====" << endl;
	cout << "=========================================================================================================================" << endl;
	for (Node* p = list.head; p != NULL; p = p->next) {
		if ((p->data.diem1 + p->data.diem2) / 2 >= 5) {
			outputSV(p->data); cout << endl;
		}
	}
	cout << "=========================================================================================================================" << endl;

	cout << endl;
	cout << endl;
	cout << endl;
	cout << "=========================================================================================================================" << endl;
	cout << "====                                        Cac Sinh Vien Rot                                                        ====" << endl;
	cout << "=========================================================================================================================" << endl;
	for (Node* p = list.head; p != NULL; p = p->next) {
		if ((p->data.diem1 + p->data.diem2) / 2 < 5) {
			outputSV(p->data); cout << endl;
		}
	}
	cout << "=========================================================================================================================" << endl;
	

}
void Searchpoint(DoubleLinkedList& list, int n, int m) {
	cout << "=========================================================================================================================" << endl;
	cout << left << setw(15) << "|MSSV:" << "\t" << left << setw(20) << "Ho" << "\t" << left << setw(10) << "Ten" << "\t" << left << setw(20) << "Diem mon 1" << "\t" << left << setw(20) << "Diem mon 2" << "\t" << left << setw(20) << "Diem trung binh |" << endl;
	for (Node* p = list.head; p != NULL; p = p->next) {
		if ((p->data.diem1 + p->data.diem2) / 2 >= n && (p->data.diem1 + p->data.diem2) / 2<=m) {
			outputSV(p->data); cout << endl;
		}
	}
	cout << "=========================================================================================================================" << endl;
}