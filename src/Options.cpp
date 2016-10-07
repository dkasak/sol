/**
 * Copyright 2011-2015 Denis Kasak <dkasak[at]termina.org.uk>
 *
 * This file is part of Sol.
 *
 * Sol is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Sol is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Sol. If not, see <http://www.gnu.org/licenses/>.
 */

#include "Options.h"
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <algorithm>

void
print_help() {
    string help_string =
        "Usage: ./sol <OPTION> [<OPTION> ...]\n"                                   \
        "    -d, --debug         Display debug information\n"                      \
        "    -H, --hres          Horizontal resolution of the image\n"             \
        "    -V, --vres          Vertical resolution of the image\n"               \
        "    -s, --supersamples  Number of supersamples\n"                         \
        "    -S, --sampler       Sampler to use (regular, jittered, stochastic)\n" \
        "    -p, --pixelsize     Size of screen pixels inside the world\n"         \
        "    -f, --filename      Filename to output the resulting image\n"         \
        "    -h, --help          Display this help information\n";

    std::cout << help_string << std::endl;
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
    std::stringstream ss(value);

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
            string lowercase;
            lowercase.resize(value.length());
            std::transform(value.begin(), value.end(), lowercase.begin(), ::tolower);
            if (lowercase == "stochastic") {
                opt.sampler = STOCHASTIC;
            } else if (lowercase == "regular") {
                opt.sampler = REGULAR;
            } else if (lowercase == "jittered") {
                opt.sampler = JITTERED;
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

    // If only a single resolution was provided, adjust the other so the
    // default aspect ratio is preserved
    if (opt.hres != DEFAULT_HORIZONTAL_RES && opt.vres == DEFAULT_VERTICAL_RES) {
        double ratio = opt.hres / double(DEFAULT_HORIZONTAL_RES);
        opt.vres *= ratio;
    } else if (opt.vres != DEFAULT_VERTICAL_RES && opt.hres == DEFAULT_HORIZONTAL_RES) {
        double ratio = opt.vres / double(DEFAULT_VERTICAL_RES);
        opt.hres *= ratio;
    }

    // If the user has supplied a non-default horizontal or vertical
    // resolution, but hasn't changed the pixel size, adapt the pixel size so
    // the same scene is shown
    if (opt.pixel_size == DEFAULT_PIXEL_SIZE) {
        if (opt.hres != DEFAULT_HORIZONTAL_RES) {
            double ratio = opt.hres / double(DEFAULT_HORIZONTAL_RES);
            opt.pixel_size /= ratio;
        } else if (opt.vres != DEFAULT_VERTICAL_RES) {
            double ratio = opt.vres / double(DEFAULT_VERTICAL_RES);
            opt.pixel_size /= ratio;
        }
    }

    return opt;
}
