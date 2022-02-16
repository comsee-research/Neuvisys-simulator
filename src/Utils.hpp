#ifndef NEUVISYS_DV_UTILS_HPP
#define NEUVISYS_DV_UTILS_HPP

#include <random>
#include <chrono>

#define SIMPLEDIM 5
#define COMPLEXDIM 3
#define NBPOLARITY 2

namespace Util {
    bool fileExist(std::string &path);
    double ornsteinUhlenbeckProcess(double &pos, double dt, double theta, double mu, double sigma);
}

#endif //NEUVISYS_DV_UTILS_HPP
