#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
using namespace std;

// Part 1: Nasty O(n^2)
int getLargest2DigitsJoltageBrutForce(const string &str)
{
    int maxJoltage = -1;

    for (int i = 0; i < str.length(); i++)
    {
        int first = str[i] - '0';

        for (int j = i + 1; j < str.length(); j++)
        {
            int second = str[j] - '0';
            int joltage = first * 10 + second;

            if (joltage > maxJoltage)
            {
                maxJoltage = joltage;
            }
        }
    }

    return maxJoltage;
}

// Part 1: O(n)
int getLargest2DigitsJoltage(const string &str)
{
    int maxRight = -1;
    int maxJoltage = -1;
    // we go from the end to the start
    // we keep track of the max digit and calculate the joltage with all digits on the left
    // and we save the highest value
    for (int i = str.length() - 1; i >= 0; --i)
    {
        int digit = str[i] - '0';

        if (maxRight != -1)
        {
            int joltage = digit * 10 + maxRight;
            if (joltage > maxJoltage)
            {
                maxJoltage = joltage;
            }
        }

        if (digit > maxRight)
        {
            maxRight = digit;
        }
    }

    return maxJoltage;
}

// Part 2
long long getLargest12DigitsJoltage(const string &str)
{
    const int K = 12;
    int n = str.length();
    int toRemove = n - K;

    string stack;

    for (char c : str)
    {
        while (!stack.empty() &&
               toRemove > 0 &&
               stack.back() < c)
        {
            stack.pop_back();
            --toRemove;
        }
        stack.push_back(c);
    }

    stack.resize(K);

    long long joltage = 0;
    for (char c : stack)
        joltage = joltage * 10 + (c - '0');

    return joltage;
}

int main() {
    ifstream fin("input.txt");
    if (!fin.is_open()) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    string line;
    long long sum = 0;
    while (getline(fin, line))
        sum += getLargest12DigitsJoltage(line);

    fin.close();
    cout<<sum<<endl;
    return 0;
}