#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

// Read operations from a specific line in the file
vector<char> readOperations(ifstream &fin, int lineNumber)
{
    fin.clear();
    fin.seekg(0); // rewind file
    string line;
    int currentLine = 0;
    vector<char> operations;

    while (getline(fin, line))
    {
        currentLine++;
        if (currentLine == lineNumber)
        {
            for (char c : line)
                if (c != ' ')
                    operations.push_back(c);
            break;
        }
    }
    return operations;
}

// Process numbers from the first few lines and apply operations
vector<unsigned long long> processNumbers(ifstream &fin, int linesToRead, const vector<char> &operations)
{
    fin.clear();
    fin.seekg(0); // rewind file
    string line;
    vector<unsigned long long> results;
    int currentLine = 0;
    size_t opIndex = 0;

    while (getline(fin, line))
    {
        currentLine++;
        opIndex = 0;
        if (currentLine > linesToRead)
            break;

        istringstream iss(line);
        unsigned long long number;

        while (iss >> number)
        {
            // Apply operation if possible
            if (!results.empty() && opIndex < operations.size() && opIndex < results.size())
            {
                if (operations[opIndex] == '+')
                    number += results[opIndex];
                else if (operations[opIndex] == '*')
                    number *= results[opIndex];

                results[opIndex] = number;
            }
            else
            {
                // First line or new position not yet in results
                if (opIndex >= results.size())
                    results.push_back(number);
                else
                    results[opIndex] = number;
            }

            opIndex++;
        }
    }

    return results;
}

vector<unsigned long long> processCephalopodNumbers(ifstream &fin)
{
    fin.clear();
    fin.seekg(0); // rewind file
    string line;

    const int rows = 5;    // 4 rows of numbers + 1 row of operations
    const int cols = 3722; // adjust to your input width
    vector<vector<char>> numbers(rows, vector<char>(cols, ' '));
    vector<unsigned long long> results;

    // Read the first 5 lines into numbers
    int currentLine = 0;
    while (getline(fin, line) && currentLine < rows)
    {
        for (size_t i = 0; i < line.size() && i < cols; i++)
            numbers[currentLine][i] = line[i];
        currentLine++;
    }

    // Apply operations column-wise
    for (size_t i = 0; i < cols; i++)
    {
        unsigned long long number = 0;
        char currentOp = ' ';

        // First 4 rows are digits
        bool hasDigit = false;
        for (size_t j = 0; j < 4; j++)
        {
            if (numbers[j][i] != ' ')
            {
                number = number * 10 + (numbers[j][i] - '0');
                hasDigit = true;
            }
        }

        // Skip this column if no number
        if (!hasDigit)
            continue;

        // 5th row is operation
        if (numbers[4][i] != ' ')
            currentOp = numbers[4][i];

        // Apply operation if possible
        if (i < results.size() && currentOp != ' ')
        {
            if (currentOp == '+')
                number += results[i];
            else if (currentOp == '*')
                number *= results[i];

            results[i] = number;
        }
        else
        {
            if (i >= results.size())
                results.push_back(number);
            else
                results[i] = number;
        }
    }

    return results;
}

// Compute sum of a vector
unsigned long long sumResults(const vector<unsigned long long> &results)
{
    unsigned long long sum = 0;
    for (unsigned long long n : results)
        sum += n;
    return sum;
}

int main()
{
    ifstream fin("input.txt");
    if (!fin.is_open())
    {
        cerr << "Error opening file." << endl;
        return 1;
    }

    // opeartions on line 5, numbes on lines 1 - 4
    vector<char> operations = readOperations(fin, 5);
    vector<unsigned long long> results = processCephalopodNumbers(fin);
    unsigned long long sum = sumResults(results);

    cout << "Sum: " << sum << endl;

    fin.close();
    return 0;
}
