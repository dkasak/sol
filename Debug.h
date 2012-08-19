/**
 * Copyright 2011, 2012 Denis Kasak <denis.kasak@gmail.com>
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
using std::cout;
using std::endl;

template <typename T>
void DEBUG(int n, T out) {
    if (DEBUG_LEVEL >= n) {
        cout << out << endl;
    }
}

template <typename T, typename U>
void DEBUG(int n, T out1, U out2) {
    if (DEBUG_LEVEL >= n) {
        cout << out1 << " " << out2 << endl;
    }
}

template <typename T, typename U, typename V>
void DEBUG(int n, T out1, U out2, V out3) {
    if (DEBUG_LEVEL >= n) {
        cout << out1 << " " << out2 << " " << out3 << endl;
    }
}

#endif // SOL_DEBUG_H

