#include <bits/stdc++.h>
#include <conio.h>
#include "utils/account.hpp"
#include "utils/additional.hpp"
#include "utils/admin.hpp"
#include "utils/customer.hpp"
#include "utils/items.hpp"
#include "utils/anonymousRead.hpp"
#include "utils/menu.hpp"
using namespace std;

enum Pilihan {
    LOGIN = 1,
    LIHAT_BARANG = 2,
    KELUAR = 0
};

void menu(int *pilih, unordered_map<string, string> *accountParam, unordered_map<string, string> *accountRolesParam, Node *headParam, NodeTransaksi *headTransaksi)
{
    string pilihanTemp;

    system("cls");

    frameAwal();
    gotoXY(72,11);std::cout << "Selamat datang di KerisBow" << std::endl;
	gotoXY(54,18);std::cout << "1. Login" << std::endl;
	gotoXY(78,18);std::cout << "2. Lihat Barang" << std::endl;
	gotoXY(108,18);std::cout << "0. Keluar" << std::endl;
    pilihanTemp = getch();

    try
    {
        *pilih = stoi(pilihanTemp);
        switch (*pilih)
        {
        case LOGIN:
            menuLogin(pilih, accountParam, accountRolesParam, headParam, headTransaksi);
            break;

        case LIHAT_BARANG:
            display(headParam);
            system("pause");
            break;

        case KELUAR:
            cout << "Terima kasih telah menggunakan KerisBow" << endl;
            endOfFunction(1);
            exit(0);
            break;

        default:
            cout << "Pilihan tidak tersedia" << endl;
            endOfFunction(1);
            break;
        }
    }
    catch (invalid_argument &e)
    {
        cout << "Mohon isi dengan pilihan yang ada!" << endl;
        endOfFunction(1);
    }
}

int main()
{
    Node *head = nullptr;
    NodeTransaksi *headTransaksi = nullptr;
    // loginCustomer *login = nullptr;
    int pilihan = 0;
    unordered_map<string, string> accounts;
    unordered_map<string, string> accountRoles;

    readFromFile(&accounts);
    readRoles(&accountRoles);
    importFromFile(headTransaksi);
    importFromFile(head);


    directoryChecker("db");
    fileChecker("accounts.tsv", "db");
    fileChecker("accounts_role.tsv", "db");
    fileChecker("items.tsv", "db");
    fileChecker("transactions.tsv", "db");
    fileChecker("checkout.tsv", "db");
    fileChecker("login.tsv", "db");

    while (true)
    {
        menu(&pilihan, &accounts, &accountRoles, head, headTransaksi);
    }

    return 0;
}
