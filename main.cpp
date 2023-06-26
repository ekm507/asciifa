#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct font_header
{
    string filetype;
    int glyph_height;
    int korsi;
    int number_of_comment_lines;
    int glyph_max_width;
    int number_of_glyphs;
    int default_direction;
};

struct glyph
{
    string character;
    int direction;
    int variation;
    vector<string> lines;
};

int main(int argc, char** argv)
{
    string font_filename = "./fonts/aipara.aff";
    ifstream fontfile(font_filename);
    string fontfile_line;
    string font_header_line;
    font_header header;
    string header_part;

    getline (fontfile, header_part, ' ');
    header.filetype = header_part;

    getline (fontfile, header_part, ' ');
    header.glyph_height = stoi(header_part);

    getline (fontfile, header_part, ' ');
    header.korsi = stoi(header_part);

    getline (fontfile, header_part, ' ');
    header.number_of_comment_lines = stoi(header_part);

    getline (fontfile, header_part, ' ');
    header.glyph_max_width = stoi(header_part);

    getline (fontfile, header_part, ' ');
    header.number_of_glyphs = stoi(header_part);

    getline (fontfile, header_part, ' ');
    header.default_direction = stoi(header_part);

    for(int i = 0; i < header.number_of_comment_lines; i++)
        getline (fontfile, fontfile_line);

    vector <glyph> glyphs;

    cout << header.number_of_glyphs << endl;

    for(int i = 0; i < header.number_of_glyphs; i++)
    {
        cout << i << endl;

        glyph current_glyph;
        getline (fontfile, fontfile_line);
        current_glyph.character = fontfile_line;
        getline (fontfile, fontfile_line, ' ');
        current_glyph.variation = stoi(fontfile_line);
        getline (fontfile, fontfile_line, ' ');
        current_glyph.direction = stoi(fontfile_line);

        cout << current_glyph.character << current_glyph.variation << current_glyph.direction << endl;
        
        for (int j = 0; j < header.glyph_height; j++)
        {
            getline (fontfile, fontfile_line);
            current_glyph.lines.push_back(fontfile_line);
        }
        
        for (int j = 0; j < header.glyph_height; j++)
        {
            cout << current_glyph.lines[j] << endl;
        }

    }

    // getline (fontfile, fontfile_line);
    // cout << fontfile_line << endl;


    // cout << header.filetype << endl;
    // cout << header.glyph_height << endl;
    // cout << header.korsi << endl;
    // cout << header.glyph_max_width << endl;
    // cout << header.number_of_glyphs << endl;
    // cout << header.default_direction << endl;

    // while (getline (fontfile, fontfile_line)) {
    // // Output the text from the file
    // cout << fontfile_line << endl;
    // }

    return 0;
}