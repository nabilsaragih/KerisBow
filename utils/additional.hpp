#ifndef UTILS_ADDITIONAL_HPP
#define UTILS_ADDITIONAL_HPP

#include <bits/stdc++.h>
void endOfFunction(int delayInSeconds)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(delayInSeconds * 1000));
    system("cls");
}

void directoryChecker(std::string directory)
{
    if (!std::filesystem::exists(directory))
    {
        std::filesystem::create_directory(directory);
    }
}

void fileChecker(std::string file, std::string directory)
{
    if (!std::filesystem::exists(directory + "/" + file))
    {
        if (file == "accounts.tsv")
        {
            std::ofstream fileStream(directory + "/" + file);
            fileStream << "username\tpassword" << std::endl;
            fileStream.close();
        }
        else if (file == "items.tsv")
        {
            std::ofstream fileStream(directory + "/" + file);
            fileStream << "id\tname\tprice\tamount" << std::endl;
            fileStream.close();
        }
        else if (file == "transactions.tsv")
        {
            std::ofstream fileStream(directory + "/" + file);
            fileStream << "username\titem_id\tamount" << std::endl;
            fileStream.close();
        }
    }
}

#endif