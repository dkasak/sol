#include "Options.h"
#include <cstring>
#include <cstdlib>

char *get_option_value(char *option, const char *short_name, const char *long_name) {
    // options are of the format -o=val or --opt=val so we need to skip
    // over the equal sign as well
    if (strncmp(option, long_name, strlen(long_name)) == 0) {
        // if there is no equals sign, the option is badly formatted
        if (!strchr(option, '=')) {
            return NULL;
        }
        return option+strlen(long_name)+1;
    } else if (strncmp(option, short_name, strlen(short_name)) == 0) {
        // if there is no equals sign, the option is badly formatted
        if (!strchr(option, '=')) {
            return NULL;
        }
        return option+strlen(short_name)+1;
    } else {
        return NULL;
    }
}

Options parse_options(int argc, char **argv) {
    Options opt;

    // initialize defaults
    opt.debug_level = DEFAULT_DEBUG_LEVEL;
    opt.hres = DEFAULT_HORIZONTAL_RES;
    opt.vres = DEFAULT_VERTICAL_RES;
    opt.output_filename = DEFAULT_OUTPUT_FILENAME;

    for (int i = 1; i < argc; ++i) {
        char *value;
        if ((value = get_option_value(argv[i], "-d", "--debug"))) {
            char *tmp;
            opt.debug_level = strtol(value, &tmp, 10);
            if (*tmp != '\0') {
                *(value-1) = '\0';
                throw InvalidOptionValue(argv[i], value);
            }
        } else if ((value = get_option_value(argv[i], "-h", "--hres"))) {
            char *tmp;
            opt.hres = strtol(value, &tmp, 10);
            if (*tmp != '\0') {
                *(value-1) = '\0';
                throw InvalidOptionValue(argv[i], value);
            }
        } else if ((value = get_option_value(argv[i], "-v", "--vres"))) {
            char *tmp;
            opt.vres = strtol(value, &tmp, 10);
            if (*tmp != '\0') {
                *(value-1) = '\0';
                throw InvalidOptionValue(argv[i], value);
            }
        } else if ((value = get_option_value(argv[i], "-f", "--filename"))) {
            opt.output_filename = value;
        } else {
            throw InvalidOption(argv[i]);
        }
    }

    return opt;
}
