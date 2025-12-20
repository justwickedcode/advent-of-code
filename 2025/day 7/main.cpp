#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main()
{   
    ifstream fin("input.txt");
    if (!fin.is_open()) {
        cerr << "Error opening file." << endl;
        return 1;
    }
    string line;
    int count = 0;
    const int lineLen = 141;
    vector<int> track;
    for(int i = 0; i < lineLen; i++) {
        track.push_back(0);
    }

    while (getline(fin, line)) {
        for(int i = 0; i < lineLen; i++) {
            if(line[i] == '^' && track[i] == 1) {
                count++;
                track[i] = 0;
                track[i - 1 ] = track[i + 1] = 1;
            } else if(line[i] == '^' && track[i] == 0) {
                track[i - 1] = track[i + 1] = 1;
            } else if(line[i] == 'S') {
                track[i] = 1;
            }
                
        }
    }
    cout<< "Split count: " << count << endl;
    fin.close();
    return 0;
}