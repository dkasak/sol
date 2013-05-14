#include "Options.h"
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <string>

void
print_help() {
    std::string help_string =
        "Usage: ./sol <OPTION> [<OPTION> ...]\n"                               \
        "    -d, --debug         Display debug information\n"                  \
        "    -H, --hres          Horizontal resolution of the image\n"         \
        "    -V, --vres          Vertical resolution of the image\n"           \
        "    -s, --supersamples  Number of supersamples\n"                     \
        "    -p, --pixelsize     Size of screen pixels inside the world\n"     \
        "    -f, --filename      Filename to output the resulting image\n"     \
        "    -h, --help          Display this help information\n";

    std::cout << help_string << std::endl;
}

char*
get_option_value(char* option, const char* short_name, const char* long_name) {
    /* We should only get options with arguments in here, so the length of the
     * string we're parsing shouldn't be shorter than (nor equal to) both names
     * of the option.
     */
    if (strlen(option) <= strlen(short_name) &&
        strlen(option) <= strlen(long_name)) {
        return NULL;
    }


    /* Options are of the format -o=val or --opt=val so we need to skip over
     * the equal sign as well. Also, users can pass NULL as either the
     * short_name or the long_name to specify that a short or long version of
     * the option is absent, so we need to check for that.
     */
    if (long_name &&
        strncmp(option, long_name, strlen(long_name)) == 0) {

        // If there is no equals sign, the option is badly formatted.
        if (*(option + strlen(long_name)) != '=') {
            return NULL;
        }

        // Skip over the equal sign.
        return option + strlen(long_name) + 1;
    }

    if (short_name &&
        strncmp(option, short_name, strlen(short_name)) == 0) {

        // If there is no equals sign, the option is badly formatted.
        if (*(option + strlen(short_name)) != '=') {
            return NULL;
        }

        // Skip over the equal sign.
        return option + strlen(short_name) + 1;
    }

    // No such option.
    return NULL;
}

Options
parse_options(int argc, char** argv) {
    Options opt;

    // Initialize defaults.
    opt.debug_level     = DEFAULT_DEBUG_LEVEL;
    opt.hres            = DEFAULT_HORIZONTAL_RES;
    opt.vres            = DEFAULT_VERTICAL_RES;
    opt.output_filename = DEFAULT_OUTPUT_FILENAME;
    opt.pixel_size      = DEFAULT_PIXEL_SIZE;
    opt.supersamples    = DEFAULT_SUPERSAMPLES;

    for (int i = 1; i < argc; ++i) {
        char *value;
        if ((value = get_option_value(argv[i], "-d", "--debug"))) {
            char *tmp;
            opt.debug_level = strtol(value, &tmp, 10);
            if (*tmp != '\0') {
                *(value-1) = '\0';
                throw InvalidOptionValue(argv[i], value);
            }
        } else if ((value = get_option_value(argv[i], "-H", "--hres"))) {
            char *tmp;
            opt.hres = strtol(value, &tmp, 10);
            if (*tmp != '\0') {
                *(value-1) = '\0';
                throw InvalidOptionValue(argv[i], value);
            }
        } else if ((value = get_option_value(argv[i], "-V", "--vres"))) {
            char *tmp;
            opt.vres = strtol(value, &tmp, 10);
            if (*tmp != '\0') {
                *(value-1) = '\0';
                throw InvalidOptionValue(argv[i], value);
            }
        } else if ((value = get_option_value(argv[i], "-f", "--filename"))) {
            opt.output_filename = value;
        } else if (argv[i] == std::string("-h") || 
                   argv[i] == std::string("--help")) {
            print_help();
        } else if ((value = get_option_value(argv[i], "-s", "--supersamples"))) {
            char *tmp;
            opt.supersamples = strtol(value, &tmp, 10);
            if (*tmp != '\0') {
                *(value-1) = '\0';
                throw InvalidOptionValue(argv[i], value);
            }
        } else if ((value = get_option_value(argv[i], "-p", "--pixelsize"))) {
            char *tmp;
            opt.pixel_size = strtod(value, &tmp);
            if (*tmp != '\0') {
                *(value-1) = '\0';
                throw InvalidOptionValue(argv[i], value);
            }
        } else {
            throw InvalidOption(argv[i]);
        }
    }

    return opt;
}
