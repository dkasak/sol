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

#include "Material.h"

namespace Sol {

Material::Material()
    : colour(ColourRGB(1.0, 1.0, 1.0)),
      diffuse(0.0)
    {}
    
ColourRGB
Material::get_colour() const {
    return this->colour;
}

void
Material::set_colour(ColourRGB c) {
    this->colour = c;
}

double
Material::get_diffuse() const {
    return this->diffuse;
}

void
Material::set_diffuse(const double diffuse) {
    this->diffuse = diffuse;
}

void
Material::operator=(const Material& m) {
    this->colour = m.colour;
    this->diffuse = m.diffuse;
}

} // namespace Sol

