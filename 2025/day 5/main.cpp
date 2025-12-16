#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

struct Range
{
    long long min;
    long long max;
};

int main()
{
    std::ifstream fin("input.txt");
    if (!fin.is_open())
    {
        std::cerr << "Error opening input.txt" << std::endl;
        return 1;
    }

    std::vector<Range> ranges;
    std::string line;

    while (std::getline(fin, line) && !line.empty())
    {
        size_t dash_pos = line.find('-');
        long long a = std::stoll(line.substr(0, dash_pos));
        long long b = std::stoll(line.substr(dash_pos + 1));
        ranges.push_back({a, b});
    }

    std::vector<Range> rangesForPart1 = ranges;
    std::vector<long long> availableIDs;
    while (std::getline(fin, line))
    {
        if (!line.empty())
            availableIDs.push_back(std::stoll(line));
    }

    fin.close();

    // Part 1
    long long countFreshIngredients = 0;
    for (long long id : availableIDs)
    {
        for (const auto &r : rangesForPart1)
        {
            if (id >= r.min && id <= r.max)
            {
                countFreshIngredients++;
                break; // stop at first matching range
            }
        }
    }

    // Part 2 
    // sort, then merge ranges & count union
    std::sort(ranges.begin(), ranges.end(),
              [](const Range &a, const Range &b)
              {
                  return a.min < b.min;
              });

    // merge overlapping/contained ranges
    std::vector<Range> merged;
    for (const auto &r : ranges)
    {
        if (merged.empty() || r.min > merged.back().max + 1)
            merged.push_back(r);
        else
            merged.back().max = std::max(merged.back().max, r.max);
    }

    // count total unique fresh IDs
    long long totalFreshIDs = 0;
    for (const auto &r : merged)
        totalFreshIDs += (r.max - r.min + 1);

    std::cout << "Fresh available ingredients: " << countFreshIngredients << std::endl;
    std::cout << "Total fresh ingredient IDs: " << totalFreshIDs << std::endl;

    return 0;
}
