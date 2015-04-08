/**
 * Copyright 2011, 2012 Denis Kasak <dkasak[at]termina.org.uk>
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

#ifndef SOL_DEBUG_H
#define SOL_DEBUG_H

#include <iostream>
#include <chrono>

using std::cout;
using std::endl;
using namespace std::chrono;

extern int debug_level;

void print_progress(steady_clock::time_point start, size_t complete,
                    size_t current, size_t chunks);

// TODO: Use variadic templates
//
template <typename T>
void
DEBUG(int n, T out) {
    if (debug_level >= n) {
        cout << out << endl;
    }
}

template <typename T, typename U>
void
DEBUG(int n, T out1, U out2) {
    if (debug_level >= n) {
        cout << out1 << " " << out2 << endl;
    }
}

template <typename T, typename U, typename V>
void
DEBUG(int n, T out1, U out2, V out3) {
    if (debug_level >= n) {
        cout << out1 << " " << out2 << " " << out3 << endl;
    }
}

template <typename T, typename U, typename V, typename W>
void
DEBUG(int n, T out1, U out2, V out3, W out4) {
    if (debug_level >= n) {
        cout << out1 << " " << out2 << " " << out3 << " " << out4 << endl;
    }
}

template <typename T, typename U, typename V, typename W, typename X>
void
DEBUG(int n, T out1, U out2, V out3, W out4, X out5) {
    if (debug_level >= n) {
        cout << out1 << " " << out2 << " " << out3 << " " << out4 << " " << out5 << endl;
    }
}

template <typename T, typename U, typename V, typename W, typename X, typename Y>
void
DEBUG(int n, T out1, U out2, V out3, W out4, X out5, Y out6) {
    if (debug_level >= n) {
        cout << out1 << " " << out2 << " " << out3 << " " << out4 << " " << out5 << " " << out6 << endl;
    }
}

template <typename T, typename U, typename V, typename W, typename X, typename Y, typename Z>
void
DEBUG(int n, T out1, U out2, V out3, W out4, X out5, Y out6, Z out7) {
    if (debug_level >= n) {
        cout << out1 << " " << out2 << " " << out3 << " " << out4 << " " << out5 << " " << out6 << " " << out7 << endl;
    }
}

#endif // SOL_DEBUG_H

