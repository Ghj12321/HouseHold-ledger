#include "house.h"
#include <cstdlib> 
#include <windows.h> 

using namespace std;

int main(void) {
    int i_choice;
    excel_title();
    loadAccounts();
    while (true) {
        menu_print();

        cout << "메뉴 선택을 하시오: ";
        cin >> i_choice;

        switch (i_choice) {
        case 1:
            input();                //가계부 입력
            break;
        case 2:
            remove();               //가계부 삭제
            break;
        case 3:
            search();               //일일 날짜 검색
            break;
        case 4:
            output();               //전체 가계 연도 월별 검색
            break;
        case 5:
            sortAccounts();
            break;
        case 6:
            cout << " 프로그램을 종료합니다." << endl;
            Sleep(1000);
            exit(0);
            break;
        default:
            cout << "다시 입력 하시오";
            Sleep(1000);
            break;
        }
    }

    return 0;
}