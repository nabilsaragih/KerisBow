#ifndef UTILS_ACCOUNT_HPP
#define UTILS_ACCOUNT_HPP

#include <bits/stdc++.h>
#include <string>
#include "additional.hpp"
using namespace std;

void addToFile(unordered_map<string, string> *accountsParam)
{
    ofstream fileStream("db/accounts.tsv", ios::trunc);
    fileStream << "username\tpassword" << endl;
    for (auto it = accountsParam->begin(); it != accountsParam->end(); it++)
    {
        fileStream << it->first << "\t" << it->second << endl;
    }
    fileStream.close();
}

void registerAccount(unordered_map<string, string> *accountsParam)
{
    string username, password;
    cout << "Username: ";
    cin >> username; fflush(stdin);
    cout << "Password: ";
    cin >> password; fflush(stdin);

    accountsParam->insert({username, password});
}

void login(unordered_map<string, string> *accountsParam, bool *loginStatus)
{
    string username, password;
    cout << "Username: ";
    cin >> username; fflush(stdin);
    cout << "Password: ";
    cin >> password; fflush(stdin);

    if (accountsParam->find(username) != accountsParam->end())
    {
        if (accountsParam->at(username) == password)
        {
            *loginStatus = true;
            cout << "Login berhasil" << endl;
            endOfFunction(1);
            return;
        }
    }

    cout << "Login gagal" << endl;
}

void menuLogin(int *pilih, unordered_map<string, string> *accountsParam, bool *loginStatus)
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
            login(accountsParam, loginStatus);
            break;

        case 2:
            system("cls");
            registerAccount(accountsParam);
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