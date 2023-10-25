#include <bits/stdc++.h>
#include <string>
// #include "utils/account.hpp"
#include "utils/additional.hpp"
using namespace std;

class Account
{
private:
    string username;
    string password;

public:
    Account(string username, string password)
    {
        this->username = username;
        this->password = password;
    }

    string getUsername()
    {
        return this->username;
    }

    string getPassword()
    {
        return this->password;
    }
};

void menuLogin(int *pilih)
{
    string pilihanTemp;

    system("cls");
    cout << "1. Login" << endl;
    cout << "2. Register" << endl;
    cout << "Masukkan pilihan anda: ";
    cin >> pilihanTemp;

    try
    {
        *pilih = stoi(pilihanTemp);
        switch (*pilih)
        {
        case 1:
            system("cls");
            cout << "Login" << endl;
            break;

        case 2:
            system("cls");
            cout << "Register" << endl;
            break;

        default:
            cout << "Pilihan tidak tersedia" << endl;
            endOfFunction(1);
            menuLogin(pilih);
            break;
        }
    }
    catch (invalid_argument &e)
    {
        cout << "Pilihan tidak tersedia" << endl;
        endOfFunction(1);
    }
}

void menu(int *pilih)
{
    string pilihanTemp;

    system("cls");
    cout << "Selamat datang di KerisBow" << endl;
    cout << "1. Login" << endl;
    cout << "2. Lihat Barang" << endl;
    cout << "Masukkan pilihan anda: ";
    cin >> pilihanTemp;

    try
    {
        *pilih = stoi(pilihanTemp);
        switch (*pilih)
        {
        case 1:
            menuLogin(pilih);
            break;

        case 2:
            cout << "Lihat Barang" << endl;
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

    while (true)
    {
        menu(&pilihan);
    }

    return 0;
}