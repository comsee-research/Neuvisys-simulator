//
// Created by thomas on 04/06/2021.
//

#ifndef NEUVISYS_MOTOR_H
#define NEUVISYS_MOTOR_H

#include <std_msgs/Float32.h>
#include <std_msgs/Bool.h>
#include "ros/ros.h"
#include <cstdlib>
#include "Utils.hpp"

class Motor {
    ros::Publisher m_motorSpeedPub{};
    ros::Publisher m_motorPositionPub{};
    double m_jitterSpeed = 0;
    double m_motion = 0;
    std_msgs::Float32 m_speed{};
    std_msgs::Float32 m_position{};

public:
    Motor(ros::NodeHandle &n, const std::string &topic);

    void jitter(double dt, double jitter = 0);
    [[nodiscard]] double getJitterPos() const { return m_jitterSpeed; }
    [[nodiscard]] float getSpeed() const { return m_speed.data; }
    [[nodiscard]] float getPosition() const { return m_position.data; }
    void setSpeed(float speed);
    void setPosition(float position);
};

#endif //NEUVISYS_MOTOR_H
