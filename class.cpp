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
	cout << left << setw(4) << "날짜: " << setw(12) << date
		<< setw(10) << "품목: " << setw(20) << name
		<< setw(8) << "종류: " << setw(10) << kind
		<< setw(6) << "금액: " << setw(10) << fixed << setprecision(2) << money << "원" << endl;
}


vector<house_account> accounts;

bool compareByDate(const house_account& a, const house_account& b) {
	return a.getDate() < b.getDate();
}


void sortAccounts() {
	vector<house_account> accounts1;

	// CSV 파일에서 데이터를 읽어와 벡터에 저장
	ifstream inFile("household_ledger.csv");
	string line;

	// 첫 번째와 두 번째 줄(타이틀)을 건너뛰기
	getline(inFile, line); // 첫 번째 줄 건너뛰기
	getline(inFile, line); // 두 번째 줄 건너뛰기

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

	// 벡터 내 데이터를 날짜별로 정렬
	sort(accounts1.begin(), accounts1.end(), compareByDate);

	// 정렬된 데이터를 다시 CSV 파일에 쓰기
	ofstream outFile("household_ledger.csv", ofstream::trunc); // 기존 내용 삭제하고 새로 쓰는 모드

	// 파일에 타이틀 다시 쓰기
	outFile << "날짜,이름,수입/지출,금액\n";
	outFile << "\n"; 

	for (const house_account& account : accounts1) {	//참조자를 쓰면 복사본을 사용하지 않고 원본 데이터만을 참조하기 때문에 메모리 사용량이 감소하고 효율성이 증가
		outFile << std::to_string(account.getDate()) + "," + account.getName() + "," + account.getKind() + "," + std::to_string(account.getMoney()) + "\n";
	}													//크기가 크거나 복사하는데 여러 가지 비용을 사용하는 객체들을 다룰 때 사용하면 좋다.
	outFile.close();
}


void menu_print() {
	system("cls");
	cout << "★ 가계부★" << endl;
	cout << "1. 입력" << endl;
	cout << "2. 삭제" << endl;
	cout << "3. 일일 날짜 세부 검색" << endl;
	cout << "4. 출력(전체, 연도별, 월별)" << endl;
	cout << "5. csv 파일 정렬" << endl;
	cout << "6. 종료" << endl;
}

void loadAccounts() {
	ifstream file("household_ledger.csv");
	if (!file.is_open()) {
		cerr << "파일을 열 수 없습니다." << endl;
		return;
	}

	string line;
	// 첫 번째와 두 번째 줄을 건너뜁니다.
	getline(file, line);
	getline(file, line);

	int da;
	string na, ki, temp;
	double mon;

	// 파일 내 데이터를 줄 단위로 읽습니다.
	while (getline(file, line)) 
	{
		stringstream ss(line);
		if (getline(ss, temp, ',')) 
		{
			da = stoi(temp); // 날짜
			getline(ss, na, ','); // 이름
			getline(ss, ki, ','); // 종류
			getline(ss, temp, ',');
			mon = stod(temp); // 금액
			accounts.emplace_back(da, na, ki, mon); // 읽은 데이터로 객체 생성 및 추가
		}
	}

	file.close();
}


void excel_title() {
	const char* filename = "household_ledger.csv";
	ifstream fileIn(filename);
	bool isEmpty = fileIn.peek() == ifstream::traits_type::eof(); // 파일이 비어 있는지 확인
	fileIn.close();

	if (isEmpty) {
		ofstream fileOut(filename, ios::app); // 파일을 이어쓰기 모드로 열기
		if (fileOut.is_open()) {
			fileOut << "날짜,품목,수입/지출,금액\n"; // 헤더 추가
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

	cout << "날짜 입력 (예: 20240329): ";
	cin >> date;
	cout << "품목 이름 입력: ";
	cin.ignore();					// 이전 입력에서 남은 개행 문자를 제거		에러 방지
	cin.getline(name, 30);
	cout << "종류 입력 (수입/지출): ";
	cin >> kind;
	cout << "금액 입력: ";
	cin >> money;
	if (strcmp(kind, "지출") == 0)
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
	cout << "지우고 싶은 날짜를 입력하세요 (예: 20240329): ";
	cin >> searchDate;
	cin.ignore();  // 앞에 개행문자가 있을 경우 지우기

	cout << "지우고 싶은 품목 이름을 입력하세요 (예: 외식): ";
	getline(cin, searchName); // 품목 이름 입력 받기

	bool found = false;
	for (vector<house_account>::iterator it = accounts.begin(); it != accounts.end(); ) {
		if (it->getDate() == searchDate && it->getName() == searchName) {
			it = accounts.erase(it);
			found = true;
			cout << searchName << " 항목이 삭제되었습니다." << endl;
		}
		else {
			++it;
		}
	}

	if (found) {
		// CSV 파일에서도 데이터를 삭제
		ofstream tempFile("household_ledger_temp.csv");
		ifstream file("household_ledger.csv");
		string line;

		// 첫 번째와 두 번째 줄은 헤더 또는 타이틀이므로 그대로 복사
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
			// 삭제하려는 데이터가 아닌 경우에만 임시 파일에 쓰기
			if (!(da == searchDate && tempName == searchName)) {
				tempFile << line << endl;
			}
		}

		file.close();
		tempFile.close();

		// 원본 파일 삭제 및 임시 파일 이름 변경
		remove("household_ledger.csv");
		rename("household_ledger_temp.csv", "household_ledger.csv");
		
	}
	else {
		cout << searchDate << " 또는 " << searchName << "에 해당하는 데이터가 없습니다." << endl;
		return 0;
	}

	return 1;
}

void search()
{
	int searchDate;
	double total = 0;
	cout << "출력하고 싶은 날짜를 입력하세요 (예: 20240329): ";
	cin >> searchDate;

	bool found = false;								// 날짜에 해당하는 데이터가 있는지 확인하기 위한 변수

	for (const house_account& account : accounts) {	//값을 변경하지 못하게 하고 참조자를 사용해서 다양한 데이터를 각각 가져오는 과정이 필요없기 때문에 성능 저하 문제를 해결한다,
		if (account.getDate() == searchDate) {		// account 객체의 날짜와 사용자가 입력한 날짜가 일치하는지 확인
			account.print();						// 일치하는 경우, 해당 객체의 정보를 출력
			total += account.getMoney();
			found = true;
		}
	}

	if (!found) {									// 일치하는 날짜의 데이터가 없는 경우
		cout << searchDate << "에 해당하는 데이터가 없습니다." << endl;
	}
	else {
		cout << "총 가계 금액: " << setw(12) << fixed << setprecision(2) << total << "원" << endl;
	}
	Sleep(2000);
}

void output() {
	int i_choice;
	cout << "출력하고 싶은 가계 및 총액을 선택해주세요(전체:1 연도별:2 월별:3): ";
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
		cout << "검색하고 싶은 연도를 입력해주세요 (예: 2024): ";
		cin >> searchYear;
		for (const house_account& account : accounts) {
			if (account.getDate() / 10000 == searchYear) { // YYYYMMDD 형식에서 연도만 추출
				account.print();
				total += account.getMoney();
				found = true;
			}
		}
		break;
	case 3:
		cout << "검색하고 싶은 연도와 월을 입력해주세요 (예: 202403): ";
		cin >> searchDate; // YYYYMM
		for (const house_account& account : accounts) {
			if (account.getDate() / 100 == searchDate) { // YYYYMMDD 형식에서 YYYYMM만 추출
				account.print();
				total += account.getMoney();
				found = true;
			}
		}
		break;
	}

	if (found) {
		cout << "총 가계 금액: " << setw(12) << fixed << setprecision(2) << total << "원" << endl;
	}
	else {
		cout << "해당하는 항목이 없습니다." << endl;
	}
	Sleep(2000);
}