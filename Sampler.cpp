
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

#include "Sampler.h"

namespace Sol {

RegularSampler::RegularSampler(unsigned int supersamples) {
    this->n_samples = supersamples * supersamples;
    this->samples.reserve(this->n_samples);

    for (unsigned int i = 0; i < supersamples; ++i) {
        for (unsigned int j = 0; j < supersamples; ++j) {
            this->samples.push_back(Point2D((i + 0.5) / supersamples, 
                                            (j + 0.5) / supersamples));
        }
    }
} 

std::vector<Point2D>::iterator
RegularSampler::begin() {
    return this->samples.begin();
}

std::vector<Point2D>::iterator
RegularSampler::end() {
    return this->samples.end();
}

unsigned int
RegularSampler::num_samples() {
    return this->n_samples;
}

} // namespace Sol