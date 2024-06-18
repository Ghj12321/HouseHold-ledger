#pragma once

#include<iostream>
#include<string>
#include<vector>
#include<iomanip>
#include<algorithm>
#include <fstream>
#include <iostream>
using namespace std;
class house_account {
    int date;
    string name;
    string kind;
    double money;

public:
    house_account(int da, const string& na, const string& ki, double mon);
    int getDate() const;
    string getName() const;
    string getKind() const;
    double getMoney() const;
    void print() const;
};

void menu_print();
void input();
int remove();
void search();
void output();
void excel_title();
void loadAccounts();
bool compareByDate(const house_account& a, const house_account& b);
void sortAccounts();