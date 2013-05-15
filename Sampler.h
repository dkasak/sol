
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

#ifndef SOL_SAMPLER_H
#define SOL_SAMPLER_H

#include <cmath>
#include <vector>
#include <functional>

#include "Point.h"

namespace Sol {

class Sampler {
protected:
    std::vector<Point2D> samples;
    unsigned int n_samples;

public:
    std::vector<Point2D>::iterator
    begin();

    std::vector<Point2D>::iterator
    end();

    unsigned int
    num_samples() const;

    const std::vector<Point2D>&
    get_samples() const;

    virtual void
    resample() {};
};

class RegularSampler : public Sampler {
public:
    RegularSampler(unsigned int supersamples);

    void
    resample();
};

class StochasticSampler : public Sampler {
private:
    std::function<double()> distribution;
    
public:
    StochasticSampler(unsigned int supersamples, 
                      std::function<double()> distribution);

    void
    resample();
};

} // namespace Sol

#endif // SOL__H

