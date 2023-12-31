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
    vector<vector<string> > lines;
};


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

    string symbol = str.substr(index, code_length);

    return make_pair(symbol, code_length);
}

vector<string> string_into_vector(string text)
{
    int i = 0;
    int index = 0;
    vector<string> chars;
    // for(i = 0; i < ; i++)
    while(index < text.size())
    {
        pair<string, int> str_parts = itterate_over_string(text, index);
        string symbol = str_parts.first;
        index += str_parts.second;
        chars.push_back(symbol);
    }
    return chars;
}


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

        getline (fontfile, fontfile_line);
        current_glyph.direction = stoi(fontfile_line);


        
        for (int j = 0; j < header.glyph_height; j++)
        {
            getline (fontfile, fontfile_line);
            current_glyph.lines.push_back(string_into_vector(fontfile_line));
        }
        
        current_glyph.width = current_glyph.lines[header.korsi].size();
        glyphs.push_back(current_glyph);


    }

    return make_pair(header, glyphs);
}


int get_variation(string before, string character, string after)
{

    // define persian joining and non-joining symbols

    // characters which need character to be separated if it is after them
    string after_n = "()«»رذزدژآاءٔوؤ!؟?\n. ‌،:؛";
    //  characters which need character to be separated if it is before them
    string before_n = "()«» ‌،؛:ٔ.؟!?\n";
    // list of characters in persian alphabet
    string fa = "ضصثقفغعهخحجچشسیبلاتنمکگظطزآرذدپوؤءژ‍";

    int variation = 0;

    if (fa.find(character) != string::npos)
        if (before_n.find(after) == string::npos and after_n.find(character) == string::npos)
            if (after_n.find(before) == string::npos)
                variation = 2;
            else
                variation = 1;
        else if (after_n.find(before) == string::npos)
            variation = 3;
        else
            variation = 4;

    return variation;
}

void copy_line(vector<string> &boardline, vector<string> glyphline, int index, int glyph_width)
{
    if(glyphline.size() > index)
    {
        throw "Error while rendering. glyph size too big";
    }

    for(int i = 0; i < glyphline.size(); i++)
    {
        boardline[index - glyph_width + i] = glyphline[i];
    }
}

void copy_board(vector<vector<string> > &board, vector<vector<string> > glyph, int index, int glyph_width)
{
    for(int i = 0; i < board.size(); i++)
    {
        auto line = glyph[i];
        copy_line(board[i], line, index, glyph_width);
        // cout << line << endl;
    }
}

void print_board(vector<vector<string> > board)
{
    for (auto &line: board)
    {
        for (auto &symbol:line)
        {
            cout << symbol;
        }
        cout << endl;
    }
}

vector<vector<string> > make_empty_board(int screen_width, int screen_height)
{

    vector<vector<string> > board;
    string whitespace = " ";
    vector<string> whitespace_line;
    for(int i = 0; i < screen_width; i++)
    {
        whitespace_line.push_back(whitespace);
    }

    for(int i = 0; i < screen_height; i++)
    {
        board.push_back(whitespace_line);
    }

    return board;
}

map<pair<string, int>, int> make_glyph_map(vector<glyph> glyphs)
{
    map<pair<string, int>, int> glyph_map;

    for(int i = 0; i < glyphs.size(); i++)
    {
        pair<string, int> key = {glyphs[i].character, glyphs[i].variation};
        glyph_map[key] = i;
    }

    return glyph_map;

}

vector<vector<string> > render(string text, vector<glyph> glyphs, font_header header, int screen_width)
{


    // get string and convert it into vector
    text = " " + text + " ";
    vector<string> chars = string_into_vector(text);
    
    // make screen board

    int screen_height = header.glyph_height;
    auto board = make_empty_board(screen_width, screen_height);

    // generate glyph map
    auto glyph_map = make_glyph_map(glyphs);

    // start rendering

    int index = screen_width - 1;

    for(int i = 1; i < chars.size() - 1; i++)
    {
        string before = chars[i-1];
        string character = chars[i];
        string after = chars[i+1];
        int variation = get_variation(before, character, after);
        // cout << chars[i] << " " << variation << endl;
        // TODO: get a default value when a glyph does not exist. it can be either empty, question mark or spaces.
        glyph current_glyph = glyphs[glyph_map[make_pair(character, variation)]];
        
        copy_board(board, current_glyph.lines, index, current_glyph.width);
        index -= current_glyph.width;
    }

    return board;

}

int main(int argc, char** argv)
{

    // read font
    string font_filename = "./fonts/aipara.aff";
    ifstream fontfile(font_filename);


    // get string and convert it into vector

    string text;

    if(argc > 1)
        text = argv[1];
    else
        text = "سلام";

    int screen_width = 80;

    auto [header, glyphs] = read_font(fontfile);

    auto board = render(text, glyphs, header, screen_width);
    print_board(board);

    return 0;
}
