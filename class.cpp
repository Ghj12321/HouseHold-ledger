#include "house.h"
#include <iostream>
#include <cstring>
#include <windows.h> 
#include <fstream>
#include <iostream>
#include<sstream>

using namespace std;


house_account::house_account(int da, const string& na, const string& ki, double mon)
	: date(da), name(na), kind(ki), money(mon) {}

int house_account::getDate() const {
	return date;
}

string house_account::getName() const {
	return name;
}

string house_account::getKind() const {
	return kind;
}

double house_account::getMoney() const {
	return money;
}

void house_account::print() const {
	cout << left << setw(4) << "��¥: " << setw(12) << date
		<< setw(10) << "ǰ��: " << setw(20) << name
		<< setw(8) << "����: " << setw(10) << kind
		<< setw(6) << "�ݾ�: " << setw(10) << fixed << setprecision(2) << money << "��" << endl;
}


vector<house_account> accounts;

bool compareByDate(const house_account& a, const house_account& b) {
	return a.getDate() < b.getDate();
}


void sortAccounts() {
	vector<house_account> accounts1;

	// CSV ���Ͽ��� �����͸� �о�� ���Ϳ� ����
	ifstream inFile("household_ledger.csv");
	string line;

	// ù ��°�� �� ��° ��(Ÿ��Ʋ)�� �ǳʶٱ�
	getline(inFile, line); // ù ��° �� �ǳʶٱ�
	getline(inFile, line); // �� ��° �� �ǳʶٱ�

	while (getline(inFile, line)) {
		stringstream ss(line);
		string tempDate, tempName, tempKind, tempMoney;

		getline(ss, tempDate, ',');
		getline(ss, tempName, ',');
		getline(ss, tempKind, ',');
		getline(ss, tempMoney, ',');

		accounts1.emplace_back(stoi(tempDate), tempName, tempKind, stod(tempMoney));
	}
	inFile.close();

	// ���� �� �����͸� ��¥���� ����
	sort(accounts1.begin(), accounts1.end(), compareByDate);

	// ���ĵ� �����͸� �ٽ� CSV ���Ͽ� ����
	ofstream outFile("household_ledger.csv", ofstream::trunc); // ���� ���� �����ϰ� ���� ���� ���

	// ���Ͽ� Ÿ��Ʋ �ٽ� ����
	outFile << "��¥,�̸�,����/����,�ݾ�\n";
	outFile << "\n"; 

	for (const house_account& account : accounts1) {	//�����ڸ� ���� ���纻�� ������� �ʰ� ���� �����͸��� �����ϱ� ������ �޸� ��뷮�� �����ϰ� ȿ������ ����
		outFile << std::to_string(account.getDate()) + "," + account.getName() + "," + account.getKind() + "," + std::to_string(account.getMoney()) + "\n";
	}													//ũ�Ⱑ ũ�ų� �����ϴµ� ���� ���� ����� ����ϴ� ��ü���� �ٷ� �� ����ϸ� ����.
	outFile.close();
}


void menu_print() {
	system("cls");
	cout << "�� ����Ρ�" << endl;
	cout << "1. �Է�" << endl;
	cout << "2. ����" << endl;
	cout << "3. ���� ��¥ ���� �˻�" << endl;
	cout << "4. ���(��ü, ������, ����)" << endl;
	cout << "5. csv ���� ����" << endl;
	cout << "6. ����" << endl;
}

void loadAccounts() {
	ifstream file("household_ledger.csv");
	if (!file.is_open()) {
		cerr << "������ �� �� �����ϴ�." << endl;
		return;
	}

	string line;
	// ù ��°�� �� ��° ���� �ǳʶݴϴ�.
	getline(file, line);
	getline(file, line);

	int da;
	string na, ki, temp;
	double mon;

	// ���� �� �����͸� �� ������ �н��ϴ�.
	while (getline(file, line)) 
	{
		stringstream ss(line);
		if (getline(ss, temp, ',')) 
		{
			da = stoi(temp); // ��¥
			getline(ss, na, ','); // �̸�
			getline(ss, ki, ','); // ����
			getline(ss, temp, ',');
			mon = stod(temp); // �ݾ�
			accounts.emplace_back(da, na, ki, mon); // ���� �����ͷ� ��ü ���� �� �߰�
		}
	}

	file.close();
}


void excel_title() {
	const char* filename = "household_ledger.csv";
	ifstream fileIn(filename);
	bool isEmpty = fileIn.peek() == ifstream::traits_type::eof(); // ������ ��� �ִ��� Ȯ��
	fileIn.close();

	if (isEmpty) {
		ofstream fileOut(filename, ios::app); // ������ �̾�� ���� ����
		if (fileOut.is_open()) {
			fileOut << "��¥,ǰ��,����/����,�ݾ�\n"; // ��� �߰�
			fileOut << "\n";
			fileOut.close();
		}
		else {
			cout << "Unable to open file";
		}
	}
}
void input() {
	int date;
	char name[30];
	char kind[10];
	double money;
	ofstream file("household_ledger.csv", ios::app);

	cout << "��¥ �Է� (��: 20240329): ";
	cin >> date;
	cout << "ǰ�� �̸� �Է�: ";
	cin.ignore();					// ���� �Է¿��� ���� ���� ���ڸ� ����		���� ����
	cin.getline(name, 30);
	cout << "���� �Է� (����/����): ";
	cin >> kind;
	cout << "�ݾ� �Է�: ";
	cin >> money;
	if (strcmp(kind, "����") == 0)
	{
		money = -1 * money;
	}
	if (file.is_open()) {
		file << to_string(date) + "," + name + "," + kind + "," + to_string(money) + "\n";
		file.close();
	}
	else {
		std::cout << "Unable to open file";
	}
	accounts.emplace_back(date, name, kind, money);

}


int remove() {
	int searchDate;
	string searchName;
	cout << "����� ���� ��¥�� �Է��ϼ��� (��: 20240329): ";
	cin >> searchDate;
	cin.ignore();  // �տ� ���๮�ڰ� ���� ��� �����

	cout << "����� ���� ǰ�� �̸��� �Է��ϼ��� (��: �ܽ�): ";
	getline(cin, searchName); // ǰ�� �̸� �Է� �ޱ�

	bool found = false;
	for (vector<house_account>::iterator it = accounts.begin(); it != accounts.end(); ) {
		if (it->getDate() == searchDate && it->getName() == searchName) {
			it = accounts.erase(it);
			found = true;
			cout << searchName << " �׸��� �����Ǿ����ϴ�." << endl;
		}
		else {
			++it;
		}
	}

	if (found) {
		// CSV ���Ͽ����� �����͸� ����
		ofstream tempFile("household_ledger_temp.csv");
		ifstream file("household_ledger.csv");
		string line;

		// ù ��°�� �� ��° ���� ��� �Ǵ� Ÿ��Ʋ�̹Ƿ� �״�� ����
		if (getline(file, line)) tempFile << line << endl;
		if (getline(file, line)) tempFile << line << endl;

		while (getline(file, line)) {
			stringstream ss(line);
			string tempDate, tempName, ki, tempMon;
			getline(ss, tempDate, ',');
			getline(ss, tempName, ',');
			getline(ss, ki, ',');
			getline(ss, tempMon, ',');

			int da = stoi(tempDate);
			// �����Ϸ��� �����Ͱ� �ƴ� ��쿡�� �ӽ� ���Ͽ� ����
			if (!(da == searchDate && tempName == searchName)) {
				tempFile << line << endl;
			}
		}

		file.close();
		tempFile.close();

		// ���� ���� ���� �� �ӽ� ���� �̸� ����
		remove("household_ledger.csv");
		rename("household_ledger_temp.csv", "household_ledger.csv");
		
	}
	else {
		cout << searchDate << " �Ǵ� " << searchName << "�� �ش��ϴ� �����Ͱ� �����ϴ�." << endl;
		return 0;
	}

	return 1;
}

void search()
{
	int searchDate;
	double total = 0;
	cout << "����ϰ� ���� ��¥�� �Է��ϼ��� (��: 20240329): ";
	cin >> searchDate;

	bool found = false;								// ��¥�� �ش��ϴ� �����Ͱ� �ִ��� Ȯ���ϱ� ���� ����

	for (const house_account& account : accounts) {	//���� �������� ���ϰ� �ϰ� �����ڸ� ����ؼ� �پ��� �����͸� ���� �������� ������ �ʿ���� ������ ���� ���� ������ �ذ��Ѵ�,
		if (account.getDate() == searchDate) {		// account ��ü�� ��¥�� ����ڰ� �Է��� ��¥�� ��ġ�ϴ��� Ȯ��
			account.print();						// ��ġ�ϴ� ���, �ش� ��ü�� ������ ���
			total += account.getMoney();
			found = true;
		}
	}

	if (!found) {									// ��ġ�ϴ� ��¥�� �����Ͱ� ���� ���
		cout << searchDate << "�� �ش��ϴ� �����Ͱ� �����ϴ�." << endl;
	}
	else {
		cout << "�� ���� �ݾ�: " << setw(12) << fixed << setprecision(2) << total << "��" << endl;
	}
	Sleep(2000);
}

void output() {
	int i_choice;
	cout << "����ϰ� ���� ���� �� �Ѿ��� �������ּ���(��ü:1 ������:2 ����:3): ";
	cin >> i_choice;

	int searchDate, searchYear, searchMonth;
	double total = 0;
	bool found = false;

	switch (i_choice) {
	case 1:
		for (const house_account& account : accounts) {
			account.print();
			total += account.getMoney();
			found = true;
		}
		break;
	case 2:
		cout << "�˻��ϰ� ���� ������ �Է����ּ��� (��: 2024): ";
		cin >> searchYear;
		for (const house_account& account : accounts) {
			if (account.getDate() / 10000 == searchYear) { // YYYYMMDD ���Ŀ��� ������ ����
				account.print();
				total += account.getMoney();
				found = true;
			}
		}
		break;
	case 3:
		cout << "�˻��ϰ� ���� ������ ���� �Է����ּ��� (��: 202403): ";
		cin >> searchDate; // YYYYMM
		for (const house_account& account : accounts) {
			if (account.getDate() / 100 == searchDate) { // YYYYMMDD ���Ŀ��� YYYYMM�� ����
				account.print();
				total += account.getMoney();
				found = true;
			}
		}
		break;
	}

	if (found) {
		cout << "�� ���� �ݾ�: " << setw(12) << fixed << setprecision(2) << total << "��" << endl;
	}
	else {
		cout << "�ش��ϴ� �׸��� �����ϴ�." << endl;
	}
	Sleep(2000);
}