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

