#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>

using std::cout, std::string, std::vector, std::endl, std::unordered_set;

struct RowAndCol
{
    int row;
    int col;
    RowAndCol(int x, int y) : row(x), col{y}
    {
    }
    bool operator==(const RowAndCol &other) const
    {
        return row == other.row && col == other.col;
    };
};

// Define hash function for RowAndCol struct
namespace std
{
    template <>
    struct hash<RowAndCol>
    {
        size_t operator()(const RowAndCol &key) const
        {
            return hash<int>()(key.row) ^ hash<int>()(key.col);
        }
    };
}

int sumOfPartNumbers(const vector<string> &engine_schematic, const std::unordered_set<RowAndCol> &valid_indices)
{
    int sum = 0;

    for (int i = 0; i < engine_schematic.size(); i++)
    {
        int current_number = 0;
        bool is_valid_digit = false;
        for (int j = 0; j < engine_schematic[i].size(); j++)
        {
            char current_char = engine_schematic[i][j];
            if (isdigit(current_char))
            {
                if (current_number == 0)
                {
                    current_number += current_char - '0';
                }
                else
                {
                    current_number = current_number * 10 + (current_char - '0');
                }

                if (valid_indices.find(RowAndCol(i, j)) != valid_indices.end())
                {
                    is_valid_digit = true;
                }
            }
            // Done with number that was being evaluated, add to sum and clean up for next digit
            else
            {
                if (is_valid_digit)
                {
                    sum += current_number;
                    is_valid_digit = false;
                }
                current_number = 0;
            }
            cout << "Current Number: " << current_number << endl;
            cout << "Is Valid Digit: " << is_valid_digit << endl;
            cout << "Current Sum: " << sum << endl;
        }
        // Accounts for valid numbers at the end of the current line
        if (is_valid_digit)
        {
            sum += current_number;
        }
    }
    return sum;
}

// Find symbols and store all indices that can contain a valid digit
std::unordered_set<RowAndCol> store_valid_indices(const vector<string> &engine_schematic)
{
    std::unordered_set<RowAndCol> valid_indices;

    // Define relative positions of adjacent indices
    std::vector<std::pair<int, int>> adjacent_positions = {
        {-1, 0}, {-1, 1}, {-1, -1}, {0, -1}, {0, 1}, {1, 0}, {1, 1}, {1, -1}};

    for (int i = 0; i < engine_schematic.size(); i++)
    {
        for (int j = 0; j < engine_schematic[i].size(); j++)
        {
            char character = engine_schematic[i][j];
            if (character != '.' && !isdigit(character))
            {
                // Add all adjacent indices
                for (const auto &position : adjacent_positions)
                {
                    int newRow = i + position.first;
                    int newCol = j + position.second;

                    // Check if the new indices are within bounds
                    if (newRow >= 0 && newRow < engine_schematic.size() &&
                        newCol >= 0 && newCol < engine_schematic[i].size())
                    {
                        valid_indices.emplace(newRow, newCol);
                    }
                }
            }
        }
    }

    return valid_indices;
}

int main()
{
    std::ifstream inputFile("input.txt");

    if (!inputFile.is_open())
    {
        std::cerr << "Error opening file!" << endl;
        return 1;
    }

    vector<string> engine_schematic;
    string line;

    // Read the engine schematic from the file
    while (getline(inputFile, line))
    {
        engine_schematic.push_back(line);
    }
    inputFile.close();

    unordered_set<RowAndCol> valid_indices = store_valid_indices(engine_schematic);
    int result = sumOfPartNumbers(engine_schematic, valid_indices);
    cout << "The sum of all part numbers in the engine schematic is: " << result << endl;

    return 0;
}
