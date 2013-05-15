#include <exception>
#include <string>
#include <vector>

#ifndef SOL_OPTIONS_H
#define SOL_OPTIONS_H

using namespace std;

// option defaults
#define DEFAULT_DEBUG_LEVEL         0
#define DEFAULT_HORIZONTAL_RES      640
#define DEFAULT_VERTICAL_RES        480
#define DEFAULT_SUPERSAMPLES        1
#define DEFAULT_PIXEL_SIZE          1.0
#define DEFAULT_OUTPUT_FILENAME     "output.bmp"

struct Options {
    int debug_level;
    unsigned int hres;
    unsigned int vres;
    unsigned int supersamples;
    double pixel_size;
    string output_filename;
};

class InvalidOptionValue : public exception {
public:
    string option_name;
    string option_value;

    InvalidOptionValue(string option_name, string option_value) :
        option_name(option_name),
        option_value(option_value)
    {}

    ~InvalidOptionValue() throw()
    {}
};

class InvalidOption : public std::exception {
public:
    string option_name;

    InvalidOption(string option_name) :
        option_name(option_name)
    {}

    ~InvalidOption() throw()
    {}
};

class MissingOptionValue : public std::exception {
public:
    string option_name;

    MissingOptionValue(string option_name) :
        option_name(option_name)
    {}

    ~MissingOptionValue() throw()
    {}
};

bool
get_option_value(const vector<string>& options,
                 size_t& i,
                 const string& short_name,
                 const string& long_name,
                 string& value);

Options
parse_options(int, char**);

#endif // SOL_OPTIONS_H
