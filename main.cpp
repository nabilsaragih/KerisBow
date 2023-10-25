#include <bits/stdc++.h>
#include <conio.h>
#include "utils/account.hpp"
#include "utils/additional.hpp"
#include "utils/admin.hpp"
#include "utils/customer.hpp"
#include "utils/items.hpp"
using namespace std;

void menu(int *pilih, unordered_map<string, string> *accountParam, unordered_map<string, string> *accountRolesParam)
{
    string pilihanTemp;

    system("cls");
    cout << "Selamat datang di KerisBow" << endl;
    cout << "1. Login" << endl;
    cout << "2. Lihat Barang" << endl;
    cout << "3. Keluar" << endl;
    cout << "Masukkan pilihan anda: ";
    cin >> pilihanTemp;

    try
    {
        *pilih = stoi(pilihanTemp);
        switch (*pilih)
        {
        case 1:
            menuLogin(pilih, accountParam, accountRolesParam);
            break;

        case 2:
            cout << "Lihat Barang" << endl;
            break;

        case 3:
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
        cout << "Pilihan tidak tersedia" << endl;
        endOfFunction(1);
    }
}

int main()
{
    int pilihan = 0;
    unordered_map<string, string> accounts;
    unordered_map<string, string> accountRoles;

    directoryChecker("db");
    fileChecker("accounts.tsv", "db");
    fileChecker("accounts_role.tsv", "db");
    fileChecker("items.tsv", "db");

    while (true)
    {
        menu(&pilihan, &accounts, &accountRoles);
    }

    return 0;
}
