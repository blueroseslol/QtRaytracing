#include "Constants.h"
#include <ctime>
#include <random>

std::default_random_engine reng(time(nullptr));
std::uniform_real_distribution<double> uni_dist(0.0f, 1.0f);

double rand_float()
{
  return uni_dist(reng);
}

double rand_float(const double min,const double max)
{
    std::uniform_real_distribution<double> float_uni_dist(min,max);
    return float_uni_dist(reng);
}

int rand_int(const int min,const int max)
{
    std::uniform_int_distribution<int> int_uni_dist(min,max);
    return int_uni_dist(reng);
}
