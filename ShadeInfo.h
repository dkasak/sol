
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

#ifndef SOL_SHADEINFO_H
#define SOL_SHADEINFO_H

#include "Vector.h"
#include "Point.h"
#include "Material.h"

namespace Sol {

class ShadeInfo {
public:
    Vector3D normal;
    Point hitpoint;
    const Material *material;

    ShadeInfo();
    ShadeInfo(const Vector3D normal, const Point hitpoint, 
              const Material *material);
};

} // namespace Sol

#endif // SOL_SHADEINFO_H

