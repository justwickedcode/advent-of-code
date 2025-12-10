#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        perror("Could not open your file");
        return 1;
    }

    int position = 50;
    int zero_count = 0;
    string line;
    while (getline(inputFile, line)) {
        char dir = line[0];
        int dist = stoi(line.substr(1));

        // Part 1
        // int full = dist / 100;
        // int partial = dist % 100;
        // int delta = (dir == 'L') ? -partial : partial;
        // int next_position = position + delta;
        // if (next_position % 100 == 0)
        //     zero_count++;

        // Part 2
        int full = dist / 100;
        int partial = dist % 100;

        zero_count += full; // full 100-step cycles

        int delta = (dir == 'L') ? -partial : partial;
        int next_position = position + delta;

        // check if zero is crossed in the partial movement
        // from position to a value over 100, or one under 0
        if (position != 0) {
            if (dir == 'L' && next_position <= 0) zero_count++;
            else if (dir == 'R' && next_position >= 100) zero_count++;
        }

        position = (next_position % 100 + 100) % 100;
    }

    cout << zero_count << endl;
}
