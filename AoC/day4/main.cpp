#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>
#include <sstream>
#include <cmath>

using std::cout, std::string, std::vector, std::endl, std::unordered_set, std::stringstream;

unordered_set<int> extract_nums(string str)
{
    stringstream ss;
    string temp;
    unordered_set<int> nums;
    int found;

    ss << str;
    while (!ss.eof())
    {
        ss >> temp;

        if (stringstream(temp) >> found)
        {
            nums.insert(found);
        }
        temp = "";
    }
    return nums;
}

int calculate_score(const unordered_set<int> &winning_nums, const unordered_set<int> &nums)
{
    int score = 0;
    int count = 0;
    for (auto num : nums)
    {
        if (winning_nums.find(num) != winning_nums.end())
        {
            score = std::pow(2, count++);
        }
    }
    return score;
}

unordered_set<int> find_nums(const string &line, int start_index, int end_index)
{
    size_t colonPos = line.find(':');
    string nums = line.substr(start_index, end_index);
    unordered_set<int> winning_nums = extract_nums(nums);

    return winning_nums;
}

int main()
{

    std::ifstream inputFile("input.txt");

    if (!inputFile.is_open())
    {
        std::cerr << "Error opening file!" << endl;
        return 1;
    }

    vector<string> scratch_cards;
    string line;
    int score = 0;

    while (getline(inputFile, line))
    {
        unordered_set<int> winning_nums;
        unordered_set<int> nums;

        size_t colon_pos = line.find(':');
        size_t bar_pos = line.find('|');

        winning_nums = find_nums(line, colon_pos + 1, bar_pos - colon_pos - 1);
        nums = find_nums(line, bar_pos + 1, line.length() - bar_pos - 1);
        score += calculate_score(winning_nums, nums);

        cout << score << endl;
        nums.clear();
        winning_nums.clear();
    }
    cout << score;
    inputFile.close();
    return 0;
}
