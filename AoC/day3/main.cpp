#include <iostream>
#include <string>
#include <fstream>

using std::cout, std::string;
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int sumOfPartNumbers(const vector<string> &engine_schematic)
{
    int sum = 0;
    int digit_start_index;
    int digit_end_index;
    bool is_part = false;
    for (int i = 0; i < engine_schematic.size(); i++)
    {
        for (int j = 0; j < engine_schematic[i].size(); j++)
        {
            if (isdigit(engine_schematic[i][j]))
            {
                digit_start_index, digit_end_index = j;
                while (isdigit(engine_schematic[i][j]))
                {
                    /*
                     * check if this number is valid
                     */

                    digit_end_index = ++j;
                }
            }
        }
    }

    return sum;
}

int main()
{
    ifstream inputFile("input.txt");

    if (!inputFile.is_open())
    {
        cerr << "Error opening file!" << endl;
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

    // Output the result
    cout << "The sum of all part numbers in the engine schematic is: " << result << endl;

    return 0;
}

// int main()
// {
//     string input_file_path = "input.txt";
//     string line;
//     std::ifstream input_file(input_file_path);
//     if (input_file.is_open())
//     {
//         while (getline(input_file, line))
//         {
//             cout << line << '\n';
//         }
//         input_file.close();
//     }

//     else
//         cout << "Unable to open file";
//     return 0;
// }
