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

        cout << "�޴� ������ �Ͻÿ�: ";
        cin >> i_choice;

        switch (i_choice) {
        case 1:
            input();                //����� �Է�
            break;
        case 2:
            remove();               //����� ����
            break;
        case 3:
            search();               //���� ��¥ �˻�
            break;
        case 4:
            output();               //��ü ���� ���� ���� �˻�
            break;
        case 5:
            sortAccounts();
            break;
        case 6:
            cout << " ���α׷��� �����մϴ�." << endl;
            Sleep(1000);
            exit(0);
            break;
        default:
            cout << "�ٽ� �Է� �Ͻÿ�";
            Sleep(1000);
            break;
        }
    }

    return 0;
}