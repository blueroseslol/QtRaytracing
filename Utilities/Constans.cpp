#include "Constants.h"
#include <ctime>
#include <random>

std::default_random_engine reng(time(nullptr));
std::uniform_real_distribution<double> uni_dist(0.0f, 1.0f);
double float_rand()
{
  return uni_dist(reng);
}
