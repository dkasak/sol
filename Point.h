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

#ifndef SOL_POINT_H
#define SOL_POINT_H

namespace Sol {

struct Point {
    double x, y, z;

    Point() {
        this->x = 0.0;
        this->y = 0.0;
        this->z = 0.0;
    }

    Point(double x, double y, double z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    double distance(const Point& other) {
        return sqrt(sqr(other.x - this->x) +
                    sqr(other.y - this->y) +
                    sqr(other.z - this->z))
    }
};

} // namespace Sol

#endif // SOL_POINT_H

