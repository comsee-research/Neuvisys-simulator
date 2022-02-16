#include "Utils.hpp"

std::mt19937 generator(static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count()));
std::normal_distribution<double> normalDistr(0.0, 1.0);
std::uniform_real_distribution<double> uniformRealDistr(0.0, 1.0);

namespace Util {

    bool fileExist(std::string &path) {
        if (FILE *file = fopen(path.c_str(), "r")) {
            fclose(file);
            return true;
        } else {
            return false;
        }
    }

    double ornsteinUhlenbeckProcess(double &pos, double dt, double theta, double mu, double sigma) {
        double noise = normalDistr(generator) * std::sqrt(dt);
        pos = theta * (mu - pos) * dt + sigma * noise;
    }
}
