#include <iostream>
#include <fstream>
#include <string>

// bad practice, but for this small program it's okay
using namespace std;

// Part 1

int getRollsFewerThanFour(char map[139][139], int row, int col) {
    int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
    int count = 0;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (map[i][j] != 1)
                continue;

            int sumAdjacents = 0;

            for (int d = 0; d < 8; d++)
            {
                int ni = i + dx[d];
                int nj = j + dy[d];

                // bounds check
                if (ni >= 0 && ni < row && nj >= 0 && nj < col)
                {
                    sumAdjacents += map[ni][nj];
                }
            }

            if (sumAdjacents < 4)
                count++;
        }
    }
    return count;
}

int getRollsAndRemove(char map[139][139], int row, int col)
{
    int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
    int count = 0;
    bool anyNewCount = true;
    while (anyNewCount) {
        anyNewCount = false;
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (map[i][j] != 1)
                    continue;

                int sumAdjacents = 0;

                for (int d = 0; d < 8; d++)
                {
                    int ni = i + dx[d];
                    int nj = j + dy[d];

                    // bounds check
                    if (ni >= 0 && ni < row && nj >= 0 && nj < col)
                    {
                        sumAdjacents += map[ni][nj];
                    }
                }

                if (sumAdjacents < 4)
                {
                    count++;
                    map[i][j] = 0; // remove adjacent
                    anyNewCount = true;
                }
            }
        }
    }
       
    return count;
}

int main()
{
    ifstream fin("input.txt");
    if (!fin.is_open())
    {
        cerr << "Error opening input.txt" << endl;
        return 1;
    }

    char map[139][139];
    int row = 0;
    string line;
    while (getline(fin, line))
    {
        for (size_t i = 0; i < line.length(); i++)
        {
            if (line[i] == '@')
                map[row][i] = 1;
            else
                map[row][i] = 0;
        }

        row++;
    }

    size_t col = line.length();
    int countNoRemove = getRollsFewerThanFour(map, row, col);
    int countWithRemove = getRollsAndRemove(map, row, col);
    cout << "Count: " << countNoRemove << endl;
    cout << "Count with removal: " << countWithRemove << endl;
    
    fin.close();
    return 0;
}
