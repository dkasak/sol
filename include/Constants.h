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

#ifndef SOL_CONSTANTS_H
#define SOL_CONSTANTS_H

#include "ColourRGB.h"

namespace Sol {

const double pi     = 3.141592653589793238462643383;
const double inv_pi = 1 / pi;

const ColourRGB black   = ColourRGB(0.0, 0.0, 0.0);
const ColourRGB white   = ColourRGB(1.0, 1.0, 1.0);
const ColourRGB red     = ColourRGB(1.0, 0.0, 0.0);
const ColourRGB green   = ColourRGB(0.0, 1.0, 0.0);
const ColourRGB blue    = ColourRGB(0.0, 0.0, 1.0);
const ColourRGB yellow  = ColourRGB(1.0, 1.0, 0.0);
const ColourRGB magenta = ColourRGB(1.0, 0.0, 1.0);
const ColourRGB cyan    = ColourRGB(0.0, 1.0, 1.0);

} // namespace Sol

#endif // SOL_CONSTANTS_H

