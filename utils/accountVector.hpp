#ifndef UTILS_ACCOUNT_HPP
#define UTILS_ACCOUNT_HPP

#include <bits/stdc++.h>
#include <string>
#include "additional.hpp"
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

void AddToFile(vector<Account> *accountsParam)
{
    ofstream fileStream("db/accounts.tsv", ios::trunc);
    fileStream << "username\tpassword" << endl;
    for (int i = 0; i < accountsParam->size(); i++)
    {
        fileStream << accountsParam->at(i).getUsername() << "\t" << accountsParam->at(i).getPassword() << endl;
    }
    fileStream.close();
}

void Register(vector<Account> *accountsParam) {
    string username, password;
    cout << "Username: ";
    cin >> username; fflush(stdin);
    cout << "Password: ";
    cin >> password; fflush(stdin);

    accountsParam->push_back(Account(username, password));
    AddToFile(accountsParam);
}

void Login(vector<Account> *accountsParam, bool *loginStatus) {
    string username, password;
    cout << "Username: ";
    cin >> username; fflush(stdin);
    cout << "Password: ";
    cin >> password; fflush(stdin);

    for (int i = 0; i < accountsParam->size(); i++) {
        if (accountsParam->at(i).getUsername() == username && accountsParam->at(i).getPassword() == password) {
            *loginStatus = true;
            cout << "Login berhasil" << endl;
            endOfFunction(1);
            return;
        }
    }

    cout << "Login gagal" << endl;
}

void menuLogin(int *pilih, vector<Account> *accountsParam, bool *loginStatus)
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
            Login(accountsParam, loginStatus);
            break;

        case 2:
            system("cls");
            Register(accountsParam);
            break;

        default:
            cout << "Pilihan tidak tersedia" << endl;
            endOfFunction(1);
            menuLogin(pilih, accountsParam, loginStatus);
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