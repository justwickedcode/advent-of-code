#include <iostream>
#include <fstream>
#include <string>
#include <queue>

// bad practice, but for this small program it's okay
using namespace std;

// Indexes of adjacent cells (8 directions)
const int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

// Part 1
int countCells(char grid[139][139], int row, int col) {
    int count = 0;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (grid[i][j] != 1)
                continue;

            int sumAdjacents = 0;

            for (int d = 0; d < 8; d++)
            {
                int ni = i + dx[d];
                int nj = j + dy[d];

                // bounds check
                if (ni >= 0 && ni < row && nj >= 0 && nj < col)
                {
                    sumAdjacents += grid[ni][nj];
                }
            }

            if (sumAdjacents < 4)
                count++;
        }
    }
    return count;
}

// Part 2 - dumb, but works
int removeAndCountCells(char grid[139][139], int row, int col)
{
    int count = 0;
    bool anyNewCount = true;
    while (anyNewCount) {
        anyNewCount = false;
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (grid[i][j] != 1)
                    continue;

                int sumAdjacents = 0;

                for (int d = 0; d < 8; d++)
                {
                    int ni = i + dx[d];
                    int nj = j + dy[d];

                    // bounds check
                    if (ni >= 0 && ni < row && nj >= 0 && nj < col)
                    {
                        sumAdjacents += grid[ni][nj];
                    }
                }

                if (sumAdjacents < 4)
                {
                    count++;
                    // remove adjacent
                    grid[i][j] = 0; 
                    anyNewCount = true; // repeat until a clean pass through the matrix
                }
            }
        }
    }
       
    return count;
}

// Part 2 - optimized
int removeAndCountCellsOptimized(char grid[139][139], int row, int col)
{
    int removedCount = 0;
    int neighborCount[139][139] = {0};
    std::queue<std::pair<int, int>> q;

    // Step 1: compute initial neighbor counts
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (grid[i][j] != 1)
                continue;

            for (int d = 0; d < 8; d++)
            {
                int ni = i + dx[d];
                int nj = j + dy[d];
                if (ni >= 0 && ni < row && nj >= 0 && nj < col)
                    neighborCount[i][j] += grid[ni][nj];
            }

            if (neighborCount[i][j] < 4)
                q.push({i, j});
        }
    }

    // Step 2: prune iteratively
    while (!q.empty())
    {
        // get cells that can be removed
        auto [i, j] = q.front();
        q.pop();

        if (grid[i][j] == 0)
            continue;

        // remove the cell
        grid[i][j] = 0;
        removedCount++;

        // for each neighbor, update its neighbor count
        // and add the possible candidates to the queue (the ones with 3 neighbors now)
        for (int d = 0; d < 8; d++)
        {
            int ni = i + dx[d];
            int nj = j + dy[d];

            if (ni >= 0 && ni < row && nj >= 0 && nj < col &&
                grid[ni][nj] == 1)
            {
                neighborCount[ni][nj]--;
                if (neighborCount[ni][nj] == 3)
                    q.push({ni, nj});
            }
        }
    }

    return removedCount;
}

int main()
{
    ifstream fin("input.txt");
    if (!fin.is_open())
    {
        cerr << "Error opening input.txt" << endl;
        return 1;
    }
    const size_t row = 139, col = 139;
    char grid[row][col];
    int currentRow = 0;
    string line;

    while (getline(fin, line))
    {
        for (size_t i = 0; i < col; i++)
        {
            if (line[i] == '@')
                grid[currentRow][i] = 1;
            else
                grid[currentRow][i] = 0;
        }
        currentRow++;
    }

    int countWithoutRemoval = countCells(grid, row, col);
    int countWithRemove = removeAndCountCellsOptimized(grid, row, col);
    cout << "Count without removal: " << countWithoutRemoval << endl;
    cout << "Count with removal: " << countWithRemove << endl;
    
    fin.close();
    return 0;
}
