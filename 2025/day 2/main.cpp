#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        perror("Could not open your file");
        return 1;
    }

    std::string range;
    while (std::getline(inputFile, range, ',')) {
        std::cout << range << " ";
    }

    return 0;
}
