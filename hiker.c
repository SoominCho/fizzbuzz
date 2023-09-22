#include "hiker.h"

int answer()
{
    return 6 * 7;
}

int sum(int i, int j)
{
    return i + j;
}

int calcFizzBuzz(int inputNumber)
{
    int result = 0;
    
    if ((inputNumber % 15) == 0)
    {
        result = 1500;
    }
    else if ((inputNumber % 3) == 0)
    {
        result = 300;
    }
    else if ((inputNumber % 5) == 0)
    {
        result = 500;
    }
    else
    {
        result = inputNumber;
    }
    return result;
}