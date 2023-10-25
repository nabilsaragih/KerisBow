#ifndef UTILS_ACCOUNT_HPP
#define UTILS_ACCOUNT_HPP

#include <bits/stdc++.h>
#include <string>
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

void Register(vector<Account> *accountsParam) {
    string username, password;
    cout << "Username: ";
    cin >> username; fflush(stdin);
    cout << "Password: ";
    cin >> password; fflush(stdin);

    accountsParam->push_back(Account(username, password));
}

void menuLogin(int *pilih, vector<Account> *accountsParam)
{
    string pilihanTemp;

    system("cls");
    cout << "1. Login" << endl;
    cout << "2. Register" << endl;
    cout << "Masukkan pilihan anda: ";
    cin >> pilihanTemp; fflush(stdin);

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
            Register(accountsParam);
            break;

        default:
            cout << "Pilihan tidak tersedia" << endl;
            endOfFunction(1);
            menuLogin(pilih, accountsParam);
            break;
        }
    }
    catch (invalid_argument &e)
    {
        cout << "Pilihan tidak tersedia" << endl;
        endOfFunction(1);
    }
}

#endif