#include "Options.h"
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <boost/algorithm/string.hpp>

void
print_help() {
    string help_string =
        "Usage: ./sol <OPTION> [<OPTION> ...]\n"                               \
        "    -d, --debug         Display debug information\n"                  \
        "    -H, --hres          Horizontal resolution of the image\n"         \
        "    -V, --vres          Vertical resolution of the image\n"           \
        "    -s, --supersamples  Number of supersamples\n"                     \
        "    -S, --sampler       Sampler to use (regular, stochastic)\n"       \
        "    -p, --pixelsize     Size of screen pixels inside the world\n"     \
        "    -f, --filename      Filename to output the resulting image\n"     \
        "    -h, --help          Display this help information\n";

    cout << help_string << endl;
}

bool
get_option_value(const vector<string>& options, 
                 size_t& i,
                 const string& short_name,
                 const string& long_name,
                 string& option,
                 string& value) {

    string s = options[i];

    /* There are three possible cases:
     *   1. option is exactly equal to the short or long name. In this case,
     *      we assume the arguments to the option are passed as separate shell
     *      arguments.
     *   2. option contains an equals character. In this case, the option
     *      argument should immediately follow the equals character.
     *   3. Finally, option could be longer than both the short and long name,
     *      and *not* contain the equals character. In this case, the option
     *      argument should again immediately follow the option name.
     */ 

    size_t p;

    if (s == short_name || s == long_name) {
        if (i + 1 >= options.size()) {
            throw MissingOptionValue(s);
        } else {
            option = options[i];    // extract option name
            value = options[++i];   // extract the option value
            return true;
        }
    } else if ((p = s.find('=')) != string::npos) {
       if (s.substr(0, p) == short_name ||
           s.substr(0, p) == long_name) {
           option = s.substr(0, p);
           value = s.substr(p+1);
           if (value.empty()) {
               throw MissingOptionValue(s.substr(0, p));
           }
           return true;
       } else {
           return false;
       }
    } else {
       if (s.find(short_name) == 0) {
           option = short_name;
           value = s.substr(short_name.length());
           return true;
       } else if (s.find(long_name) == 0) {
           option = long_name;
           value = s.substr(long_name.length());
           return true;
       } else {
           return false;
       }
    }
}

template <typename T>
bool parse_number(string value, T& ret) {
    stringstream ss(value);

    ss >> ret;

    // If everything was parsed, the operation succeeded
    if (ss.eof()) {
        return true;
    } else {
        return false;
    }
}

Options
parse_options(size_t argc, char** argv) {
    // Convert argv to a deque of strings
    vector<string> options;
    for (size_t i = 1; i < argc; ++i) {
        options.push_back(argv[i]);
    }

    // Initialize defaults.
    Options opt;
    opt.debug_level     = DEFAULT_DEBUG_LEVEL;
    opt.hres            = DEFAULT_HORIZONTAL_RES;
    opt.vres            = DEFAULT_VERTICAL_RES;
    opt.output_filename = DEFAULT_OUTPUT_FILENAME;
    opt.pixel_size      = DEFAULT_PIXEL_SIZE;
    opt.supersamples    = DEFAULT_SUPERSAMPLES;
    opt.sampler         = REGULAR;

    for (size_t i = 0; i < options.size(); ++i) {
        string value, option;
        if (get_option_value(options, i, "-d", "--debug", option, value)) {
            if (!parse_number(value, opt.debug_level)) {
                throw InvalidOptionValue(option, value);
            }
        } else if (get_option_value(options, i, "-H", "--hres", option, value)) {
            if (!parse_number(value, opt.hres)) {
                throw InvalidOptionValue(option, value);
            }
        } else if (get_option_value(options, i, "-V", "--vres", option, value)) {
            if (!parse_number(value, opt.vres)) {
                throw InvalidOptionValue(option, value);
            }
        } else if (get_option_value(options, i, "-f", "--filename", option, value)) {
            opt.output_filename = value;
        } else if (get_option_value(options, i, "-S", "--sampler", option, value)) {
            string lowercase = value;
            boost::algorithm::to_lower(lowercase);
            if (lowercase == "stochastic") {
                opt.sampler = STOCHASTIC;
            } else if (lowercase == "regular") {
                opt.sampler = REGULAR;
            } else {
                throw InvalidOptionValue(option, value);
            }
        } else if (options[i] == "-h" || options[i] == "--help") {
            print_help();
            exit(EXIT_SUCCESS);
        } else if (get_option_value(options, i, "-s", "--supersamples", option, value)) {
            if (!parse_number(value, opt.supersamples)) {
                throw InvalidOptionValue(option, value);
            }
        } else if (get_option_value(options, i, "-p", "--pixelsize", option, value)) {
            if (!parse_number(value, opt.pixel_size)) {
                throw InvalidOptionValue(option, value);
            }
        } else {
            throw InvalidOption(option);
        }
    }

    return opt;
}
