#include <iostream>
#include <string>
#include <fstream>

using std::cout, std::string;
int main()
{
    string input_file_path = "input.txt";
    string line;
    std::ifstream input_file(input_file_path);
    if (input_file.is_open())
    {
        while (getline(input_file, line))
        {
            cout << line << '\n';
        }
        input_file.close();
    }

    else
        cout << "Unable to open file";
    return 0;
}
