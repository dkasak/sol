
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

#include "Sampler.h"

namespace Sol {
std::vector<Point2D>::iterator
Sampler::begin() {
    return this->samples.begin();
}

std::vector<Point2D>::iterator
Sampler::end() {
    return this->samples.end();
}

const std::vector<Point2D>&
Sampler::get_samples() const {
    return this->samples;
}

unsigned int
Sampler::num_samples() const {
    return this->n_samples;
}

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

void
RegularSampler::resample() {
    // This is a no-op because there's only one way to sample
    // a unit square regularly.
}

StochasticSampler::StochasticSampler(unsigned int supersamples, 
                                     std::function<double()> distribution) {
    this->n_samples = supersamples;
    this->samples.reserve(this->n_samples);
    this->distribution = distribution;

    resample();
} 

void
StochasticSampler::resample() {
    this->samples.clear();

    for (unsigned int i = 0; i < this->n_samples; ++i) {
        this->samples.push_back(Point2D(this->distribution(),
                                        this->distribution()));
    }
}

JitteredSampler::JitteredSampler(unsigned int supersamples, 
                                 std::function<double()> distribution) {
    this->n_supersamples = supersamples;
    this->n_samples = supersamples * supersamples;
    this->samples.reserve(this->n_samples);
    this->distribution = distribution;

    resample();
} 

void
JitteredSampler::resample() {
    this->samples.clear();

    double stratum_size = 1.0 / this->n_supersamples;

    for (unsigned int j = 0; j < this->n_supersamples; ++j) {
        for (unsigned int i = 0; i < this->n_supersamples; ++i) {
            double x = this->distribution() * stratum_size;
            double y = this->distribution() * stratum_size;
            this->samples.push_back(Point2D(i * stratum_size + x,
                                            j * stratum_size + y));
        }
    }
}

} // namespace Sol
