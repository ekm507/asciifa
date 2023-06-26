#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char** argv)
{
    string font_filename = "./fonts/aipara.aff";
    ifstream fontfile(font_filename);
    string fontfile_line;
    while (getline (fontfile, fontfile_line)) {
    // Output the text from the file
    cout << fontfile_line << endl;
    }

    return 0;
}