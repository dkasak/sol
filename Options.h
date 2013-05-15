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

enum SamplerType { REGULAR, STOCHASTIC };

struct Options {
    int debug_level;
    unsigned int hres;
    unsigned int vres;
    unsigned int supersamples;
    double pixel_size;
    string output_filename;
    SamplerType sampler;
};

class InvalidOptionValue : public exception {
public:
    string name;
    string value;

    InvalidOptionValue(string name, string value) :
        name(name),
        value(value)
    {}

    ~InvalidOptionValue() throw()
    {}
};

class InvalidOption : public std::exception {
public:
    string name;

    InvalidOption(string name) :
        name(name)
    {}

    ~InvalidOption() throw()
    {}
};

class MissingOptionValue : public std::exception {
public:
    string name;

    MissingOptionValue(string name) :
        name(name)
    {}

    ~MissingOptionValue() throw()
    {}
};

bool
get_option_value(const vector<string>& options,
                 size_t& i,
                 const string& short_name,
                 const string& long_name,
                 string& option,
                 string& value);

Options
parse_options(size_t, char**);

#endif // SOL_OPTIONS_H
