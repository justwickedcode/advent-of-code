#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    ifstream fin("input.txt");
    if (!fin.is_open())
    {
        cerr << "Error opening file." << endl;
        return 1;
    }

    string line;

    // Part 1
    // int count = 0;
    // const int lineLen = 141;
    // vector<int> track;
    // for(int i = 0; i < lineLen; i++) {
    //     track.push_back(0);
    // }

    // while (getline(fin, line)) {
    //     for(int i = 0; i < lineLen; i++) {
    //         if(line[i] == '^' && track[i] == 1) {
    //             count++;
    //             track[i] = 0;
    //             track[i - 1 ] = track[i + 1] = 1;
    //         } else if(line[i] == '^' && track[i] == 0) {
    //             track[i - 1] = track[i + 1] = 1;
    //         } else if(line[i] == 'S') {
    //             track[i] = 1;
    //         }

    //     }
    // }
    // cout<<count<<endl;

    vector<string> grid;
    while (getline(fin, line))
    {
        grid.push_back(line);
    }

    int n = grid.size();
    int m = grid[0].size();
    // number of ways to reach the column
    vector<long long> ways(m, 0);

    // Find start column
    int startCol = 0;
    for (int i = 0; i < m; i++)
    {
        if (grid[0][i] == 'S')
        {
            startCol = i;
            break;
        }
    }

    ways[startCol] = 1;

    // Iterate over rows
    for (int r = 0; r < n - 1; r++)
    {
        vector<long long> next(m, 0);
        for (int c = 0; c < m; c++)
        {
            if (ways[c] == 0)
                continue; // no way to reach this column
            char cell = grid[r][c];
            if (cell == '.' || cell == 'S')
            {
                next[c] += ways[c];
            }
            else if (cell == '^')
            {
                if (c > 0)
                    next[c - 1] += ways[c]; // Move down-left
                if (c < m - 1)
                    next[c + 1] += ways[c]; // Move down-right
            }
        }
        ways = next;
    }

    // Sum all ways in the last row
    long long total = 0;
    for (long long w : ways)
        total += w;

    cout << "Split count: " << total << endl;

    fin.close();
    return 0;
}
