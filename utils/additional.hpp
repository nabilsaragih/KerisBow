#ifndef UTILS_ADDITIONAL_HPP
#define UTILS_ADDITIONAL_HPP

#include <bits/stdc++.h>
void endOfFunction(int delayInSeconds)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(delayInSeconds * 1000));
    system("cls");
}

#endif