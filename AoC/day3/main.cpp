#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>

using std::cout, std::string, std::vector, std::endl;

struct RowAndCol
{
    int row;
    int col;
    RowAndCol(int x, int y) : row(x), col{y}
    {
    }
    bool operator==(const RowAndCol &other) const { return row == other.row && col == other.col; };
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

int sumOfPartNumbers(const vector<string> &engine_schematic)
{
    int sum = 0;
    int digit_start_index;
    int digit_end_index;
    for (int i = 0; i < engine_schematic.size(); i++)
    {
        for (int j = 0; j < engine_schematic[i].size(); j++)
        {
            bool is_valid_digit = false;
            if (isdigit(engine_schematic[i][j]))
            {
            }
        }
    }

    return sum;
}

std::unordered_set<RowAndCol> storeAllSymbols(const vector<string> &engine_schematic)
{
    std::unordered_set<RowAndCol> symbol_indices;
    for (int i = 0; i < engine_schematic.size(); i++)
    {
        for (int j = 0; j < engine_schematic[i].size(); j++)
        {
            char character = engine_schematic[i][j];
            if (character != '.' && !isdigit(character))
            {
                symbol_indices.emplace(i, j);
            }
        }
    }

    return symbol_indices;
}

// return true if the given index adjacent has a symbol (other than '.') adjacent to it
bool isValidDigit(const vector<string> &engine_schematic, int row, int col)
{
    for (int x = -1; x <= 1; ++x)
    {
        for (int y = -1; y <= 1; ++y)
        {
            int newRow = row + x;
            int newCol = col + y;

            if (newRow >= 0 && newRow < engine_schematic.size() &&
                newCol >= 0 && newCol < engine_schematic[row].size() &&
                (x != 0 || y != 0) && isdigit(engine_schematic[newRow][newCol]))
            {
                // Accumulate the digits to form the multi-digit number
            }
        }
    }
    return false;
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

    int result = sumOfPartNumbers(engine_schematic);
    cout << "The sum of all part numbers in the engine schematic is: " << result << endl;

    // auto test = storeAllSymbols(engine_schematic);
    // for (auto &i : test)
    // {
    //     std::cout << "Row: " << i.row << " Col: " << i.col << endl;
    // }

    return 0;
}
