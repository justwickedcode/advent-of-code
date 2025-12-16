#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using std::ifstream;
using std::string;
using std::vector;
using ull = unsigned long long;

void rewindFile(ifstream &fin)
{
    fin.clear();
    fin.seekg(0);
}

ull sumResults(const vector<ull> &values)
{
    ull sum = 0;
    for (ull v : values)
        sum += v;
    return sum;
}

// Part 1
vector<char> readOperations(ifstream &fin, int lineNumber)
{
    rewindFile(fin);

    string line;
    for (int current = 1; std::getline(fin, line); ++current)
    {
        if (current == lineNumber)
        {
            vector<char> ops;
            for (char c : line)
                if (c != ' ')
                    ops.push_back(c);
            return ops;
        }
    }

    return {};
}


// Part 1
vector<ull> processNumbers(ifstream &fin, int linesToRead, const vector<char> &ops)
{
    rewindFile(fin);

    vector<ull> results;
    string line;

    // add numbers to results on index on first row, then apply the operations on the added values at each index

    // eg: retults[0] = 4  for line 1
    // results[0] = 4 * 3 for line 2
    // results[0] = 4 * 3 * 12 for line 3 etc.

    for (int row = 1; row <= linesToRead && std::getline(fin, line); ++row)
    {
        std::istringstream iss(line);
        ull value;
        size_t index = 0;

        while (iss >> value)
        {
            if (index < results.size() && index < ops.size())
            {
                if (ops[index] == '+')
                    value += results[index];
                if (ops[index] == '*')
                    value *= results[index];
                results[index] = value;
            }
            else
            {
                results.push_back(value);
            }
            ++index;
        }
    }

    return results;
}

// Part 2 - Work hard, not smart
vector<ull> processCephalopodNumbers(ifstream &fin)
{
    rewindFile(fin);

    constexpr int DIGIT_ROWS = 4;
    constexpr int OP_ROW = 4;
    constexpr int TOTAL_ROWS = 5;


    // Store the entire input in a grid
    vector<vector<char>> grid(TOTAL_ROWS);
    string line;

    for (int i = 0; i < TOTAL_ROWS && std::getline(fin, line); ++i)
        grid[i] = {line.begin(), line.end()};

    size_t maxCols = 0;
    for (const auto &row : grid)
        maxCols = std::max(maxCols, row.size());

    vector<ull> results;
    char currentOp = ' ';
    int currentIndex = -1;

    // keep track of the current operation and construct the numbers
    // then add the numbers with the opearion applied into results
    // on next line apply the operation on the next number formed
    // when a new operation is found, change it and increase the index of the result added, we're done applying the operation on the previous result

    for (size_t col = 0; col < maxCols; ++col)
    {
        ull number = 0;
        bool hasDigit = false;

        for (int r = 0; r < DIGIT_ROWS; ++r)
        {
            if (col < grid[r].size() && grid[r][col] != ' ')
            {
                number = number * 10 + (grid[r][col] - '0');
                hasDigit = true;
            }
        }

        if (!hasDigit)
            continue;

        if (col < grid[OP_ROW].size() && grid[OP_ROW][col] != ' ')
        {
            currentOp = grid[OP_ROW][col];
            ++currentIndex;
        }

        if (currentIndex == static_cast<int>(results.size()))
        {
            results.push_back(number);
        }
        else
        {
            if (currentOp == '+')
                results[currentIndex] += number;
            if (currentOp == '*')
                results[currentIndex] *= number;
        }
    }

    return results;
}

int main()
{
    ifstream fin("input.txt");
    if (!fin)
    {
        std::cerr << "Error opening file\n";
        return 1;
    }

    // Part 1
    vector<char> operations = readOperations(fin, 5);
    vector<ull> part1Results = processNumbers(fin, 4, operations);

    std::cout << "Part 1 Sum: " << sumResults(part1Results) << std::endl;

    // Part 2
    vector<ull> part2Results = processCephalopodNumbers(fin);    
    std::cout << "Part 2 Sum: " << sumResults(part2Results) <<std::endl;

    return 0;
}
