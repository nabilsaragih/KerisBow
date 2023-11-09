#ifndef UTILS_LOGIN_HPP
#define UTILS_LOGIN_HPP

#include <bits/stdc++.h>
#include <string>
#include "additional.hpp"
#include "admin.hpp"
#include "customer.hpp"
#include "items.hpp"
using namespace std;


struct loginCustomer
{
    string username;
    string password;
};

//login save to temporary tsv

void saveLogin(loginCustomer login)
{
    ofstream fileStream("db/login.tsv", ios::trunc);
    fileStream << "username\tpassword" << endl;
    fileStream << login.username << "\t" << login.password << endl;
    fileStream.close();
}

void readLogin(loginCustomer &login)
{
    ifstream fileStream("db/login.tsv");
    if (!fileStream.is_open())
    {
        cout << "Error opening file: db/login.tsv" << endl;
        return;
    }

    string line, username, password;

    // Skip the header line
    getline(fileStream, line);

    if (getline(fileStream, line))
    {
        stringstream lineStream(line);
        getline(lineStream, username, '\t');
        getline(lineStream, password, '\t');

        login.username = username;
        login.password = password;
    }

    fileStream.close();
}


#endif