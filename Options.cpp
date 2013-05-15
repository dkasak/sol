#include "Options.h"
#include <cstring>
#include <cstdlib>
#include <iostream>

void
print_help() {
    string help_string =
        "Usage: ./sol <OPTION> [<OPTION> ...]\n"                               \
        "    -d, --debug         Display debug information\n"                  \
        "    -H, --hres          Horizontal resolution of the image\n"         \
        "    -V, --vres          Vertical resolution of the image\n"           \
        "    -s, --supersamples  Number of supersamples\n"                     \
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
                 string& value) {

    string option = options[i];

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

    if (option == short_name || option == long_name) {
        if (i + 1 >= options.size()) {
            throw MissingOptionValue(option);
        } else {
            value = options[++i];   // extract the option value
            return true;
        }
    } else if ((p = option.find('=')) != string::npos) {
       if (option.substr(0, p) == short_name ||
           option.substr(0, p) == long_name) {
           value = option.substr(p+1);
           if (value.empty()) {
               throw MissingOptionValue(option.substr(0, p));
           }
           return true;
       } else {
           return false;
       }
    } else {
       if (option.find(short_name) == 0) {
           value = option.substr(short_name.length());
           return true;
       } else if (option.find(long_name) == 0) {
           value = option.substr(long_name.length());
           return true;
       } else {
           return false;
       }
    }
}

Options
parse_options(int argc, char** argv) {
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

    for (size_t i = 0; i < options.size(); ++i) {
        string value;
        string option = options[i];
        if (get_option_value(options, i, "-d", "--debug", value)) {
            char *tmp;
            opt.debug_level = strtol(value.c_str(), &tmp, 10);
            if (*tmp != '\0') {
                throw InvalidOptionValue(option, value);
            }
        } else if (get_option_value(options, i, "-H", "--hres", value)) {
            char *tmp;
            opt.hres = strtol(value.c_str(), &tmp, 10);
            if (*tmp != '\0') {
                throw InvalidOptionValue(option, value);
            }
        } else if (get_option_value(options, i, "-V", "--vres", value)) {
            char *tmp;
            opt.vres = strtol(value.c_str(), &tmp, 10);
            if (*tmp != '\0') {
                throw InvalidOptionValue(option, value);
            }
        } else if (get_option_value(options, i, "-f", "--filename", value)) {
            opt.output_filename = value;
        } else if (option == "-h" || option == "--help") {
            print_help();
        } else if (get_option_value(options, i, "-s", "--supersamples", value)) {
            char *tmp;
            opt.supersamples = strtol(value.c_str(), &tmp, 10);
            if (*tmp != '\0') {
                throw InvalidOptionValue(option, value);
            }
        } else if (get_option_value(options, i, "-p", "--pixelsize", value)) {
            char *tmp;
            opt.pixel_size = strtod(value.c_str(), &tmp);
            if (*tmp != '\0') {
                throw InvalidOptionValue(option, value);
            }
        } else {
            throw InvalidOption(option);
        }
    }

    return opt;
}
