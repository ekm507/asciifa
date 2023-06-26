#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <map>

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
    int width;
    vector<string> lines;
};

pair< font_header, vector<glyph> > read_font(ifstream& fontfile)
{

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

    for(int i = 0; i < header.number_of_glyphs; i++)
    {

        glyph current_glyph;

        getline (fontfile, fontfile_line);
        current_glyph.character = fontfile_line;

        getline (fontfile, fontfile_line, ' ');
        current_glyph.variation = stoi(fontfile_line);

        getline (fontfile, fontfile_line, ' ');
        current_glyph.direction = stoi(fontfile_line);


        
        for (int j = 0; j < header.glyph_height; j++)
        {
            getline (fontfile, fontfile_line);
            current_glyph.lines.push_back(fontfile_line);
        }
        
        current_glyph.width = current_glyph.lines[header.korsi].size();
        glyphs.push_back(current_glyph);


    }

    return make_pair(header, glyphs);
}

pair<string, int> itterate_over_string(string str, int index)
{
    unsigned char lb;
    lb = str[index];

    int code_length;
    if (( lb & 0x80 ) == 0 )          // lead bit is zero, must be a single ascii
        code_length = 1;
    else if (( lb & 0xE0 ) == 0xC0 )  // 110x xxxx
        code_length = 2;
    else if (( lb & 0xF0 ) == 0xE0 ) // 1110 xxxx
        code_length = 3;
    else if (( lb & 0xF8 ) == 0xF0 ) // 1111 0xxx
        code_length = 4;

    string symbol = str.substr(index, index + code_length);

    return make_pair(str, index + code_length);
}

int main(int argc, char** argv)
{
    string font_filename = "./fonts/aipara.aff";
    ifstream fontfile(font_filename);

    // font_header header;
    // vector<glyph> glyphs;

    auto [header, glyphs] = read_font(fontfile);

    map<pair<string, int>, int> glyph_map;

    for(int i = 0; i < glyphs.size(); i++)
    {
        pair<string, int> key = {glyphs[i].character, glyphs[i].variation};
        glyph_map[key] = i;
    }

    int screen_height = header.glyph_height;
    int screen_width = 80;

    vector<string> banner;
    string whitespace_line(" ", screen_width);
    for(int i = 0; i < screen_height; i++)
    {
        banner.push_back(whitespace_line);
    }


    pair<string, int> key = {"م", 4};

    cout << glyph_map[key] << endl;
    vector<string> lines = glyphs[glyph_map[key] ].lines;

    int pointer = screen_width;
    

    string text = "سلام";
    cout << text << endl;

    return 0;
}