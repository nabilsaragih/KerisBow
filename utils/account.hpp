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

void addRoles(unordered_map<string, string> *accountsParam, string role)
{
    ofstream fileStream("db/accounts_role.tsv", ios::trunc);
    fileStream << "username\trole" << endl;
    for (auto it = accountsParam->begin(); it != accountsParam->end(); it++)
    {
        fileStream << it->first << "\t" << role << endl;
    }
    fileStream.close();
}

void readFromFile(unordered_map<string, string> *accountsParam)
{
    ifstream fileStream("db/accounts.tsv");
    string line, username, password;
    getline(fileStream, line);
    while (getline(fileStream, line))
    {
        stringstream lineStream(line);
        getline(lineStream, username, '\t');
        getline(lineStream, password, '\t');
        accountsParam->insert({username, password});
    }
    fileStream.close();
}

void registerAccount(unordered_map<string, string> *accountsParam, int *pilih)
{
    string username, password, pilihanTemp;

    cout << "Register sebagai:" << endl;
    cout << "1. Customer" << endl;
    cout << "2. Seller" << endl;
    cout << "Masukkan pilihan anda: ";
    cin >> pilihanTemp;
    fflush(stdin);

    try
    {
        void registerAccount(unordered_map<string, string> * accountsParam, int *pilih)
        {
            string username, password, pilihanTemp = "";

            cout << "Register sebagai:" << endl;
            cout << "1. Customer" << endl;
            cout << "2. Seller" << endl;
            cout << "Masukkan pilihan anda: ";
            cin >> pilihanTemp;
            fflush(stdin);

            try
            {
                *pilih = stoi(pilihanTemp);
                switch (*pilih)
                {
                case 1:
                {
                    system("cls");
                    string role = "customer";
                    cout << "Register Customer" << endl;
                    cout << "Username: ";
                    cin >> username;
                    fflush(stdin);
                    cout << "Password: ";
                    cin >> password;
                    fflush(stdin);

                    if (accountsParam->find(username) != accountsParam->end())
                    {
                        cout << "Username sudah terdaftar" << endl;
                        endOfFunction(1);
                        return;
                    }

                    accountsParam->insert({username, password});
                    addToFile(accountsParam);
                    addRoles(accountsParam, role);
                    cout << "Register berhasil" << endl;
                    endOfFunction(1);
                    break;
                }

                case 2:
                    system("cls");
                    cout << "Register Seller" << endl;
                    break;

                default:
                    cout << "Pilihan tidak tersedia" << endl;
                    endOfFunction(1);
                    registerAccount(accountsParam, pilih);
                    break;
                }
            }
            catch (const invalid_argument &e)
            {
                cout << "Pilihan tidak tersedia" << endl;
                endOfFunction(1);
            }
        }
        {
        case 1:
            string role = "customer";
            system("cls");
            cout << "Register Customer" << endl;
            cout << "Username: ";
            cin >> username;
            fflush(stdin);
            cout << "Password: ";
            cin >> password;
            fflush(stdin);

            if (accountsParam->find(username) != accountsParam->end())
            {
                cout << "Username sudah terdaftar" << endl;
                endOfFunction(1);
                return;
            }

            accountsParam->insert({username, password});
            addToFile(accountsParam);
            addRoles(accountsParam, role);
            cout << "Register berhasil" << endl;
            endOfFunction(1);
            break;

        case 2:
            system("cls");
            cout << "Register Seller" << endl;
            break;

        default:
            cout << "Pilihan tidak tersedia" << endl;
            endOfFunction(1);
            registerAccount(accountsParam, pilih);
            break;
        }
    }
    catch (invalid_argument &e)
    {
        cout << "Pilihan tidak tersedia" << endl;
        endOfFunction(1);
    }
}

void login(unordered_map<string, string> *accountsParam, bool *loginStatus)
{
    string username, password;
    cout << "Username: ";
    cin >> username;
    fflush(stdin);
    cout << "Password: ";
    cin >> password;
    fflush(stdin);

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
    endOfFunction(1);
}

void menuLogin(int *pilih, unordered_map<string, string> *accountsParam, bool *loginStatus)
{
    string pilihanTemp;

    readFromFile(accountsParam);

    system("cls");
    cout << "1. Login" << endl;
    cout << "2. Register" << endl;
    cout << "Masukkan pilihan anda: ";
    cin >> pilihanTemp;
    fflush(stdin);

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
            registerAccount(accountsParam, pilih);
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