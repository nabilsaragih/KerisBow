#ifndef UTILS_ADDITIONAL_HPP
#define UTILS_ADDITIONAL_HPP

#include <bits/stdc++.h>
using namespace std;
void endOfFunction(int delayInSeconds)
{
    this_thread::sleep_for(chrono::milliseconds(delayInSeconds * 1000));
    system("cls");
}

void directoryChecker(string directory)
{
    if (!filesystem::exists(directory))
    {
        filesystem::create_directory(directory);
    }
}

void fileChecker(string file, string directory)
{
    if (!filesystem::exists(directory + "/" + file))
    {
        if (file == "accounts.tsv")
        {
            ofstream fileStream(directory + "/" + file);
            fileStream << "username\tpassword" << endl;
            fileStream.close();
        }
        else if (file == "items.tsv")
        {
            ofstream fileStream(directory + "/" + file);
            fileStream << "nama\tharga\tfitur\tdeskripsi" << endl;
            fileStream.close();
        }
        else if (file == "transactions.tsv")
        {
            ofstream fileStream(directory + "/" + file);
            fileStream << "username\titem_names\tamount" << endl;
            fileStream.close();
        }
        else if (file == "accounts_role.tsv")
        {
            ofstream fileStream(directory + "/" + file);
            fileStream << "username\trole" << endl;
            fileStream.close();
        }
    }
}

#endif