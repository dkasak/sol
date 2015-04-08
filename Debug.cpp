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

#include "Debug.h"
#include <sstream>

using namespace std;
using std::chrono::steady_clock;
using std::chrono::system_clock;

int debug_level;

void
print_progress(steady_clock::time_point start, size_t complete, 
                    size_t current, size_t chunks) {
    auto end = steady_clock::now();
    auto elapsed = duration_cast<seconds>(end-start).count();
    auto elapsed_minutes = elapsed / 60;
    auto elapsed_seconds = elapsed % 60;
    double percent = double(current) / complete;
    auto estimate = int(elapsed * 1/percent - elapsed);
    std::time_t eta = system_clock::to_time_t(system_clock::now()) + estimate;
    auto minutes_left = estimate / 60;
    auto seconds_left = estimate % 60;
    stringstream ss;
    ss << percent*100 << "% done, "
       << "elapsed: " << elapsed_minutes << "m " << elapsed_seconds << "s, "
       << "time left: " << minutes_left << "m " << seconds_left << "s, "
       << "ETA: " << std::ctime(&eta); 
    string s = ss.str();
    s.pop_back();
    DEBUG(1, s);
}

