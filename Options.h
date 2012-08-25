#include <exception>
#include <string>

#ifndef SOL_OPTIONS_H
#define SOL_OPTIONS_H

using namespace std;

// option defaults
#define DEFAULT_DEBUG_LEVEL         0
#define DEFAULT_HORIZONTAL_RES      640
#define DEFAULT_VERTICAL_RES        480

struct Options {
    int debug_level;
    unsigned int hres;
    unsigned int vres;
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

char *get_option_value(char *, const char *, const char *);
Options parse_options(int, char **);

#endif // SOL_OPTIONS_H
