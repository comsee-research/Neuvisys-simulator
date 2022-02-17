//
// Created by thomas on 04/06/2021.
//

#include "Motor.hpp"

Motor::Motor(ros::NodeHandle &n, const std::string &topic) {
    m_motorSpeedPub = n.advertise<std_msgs::Float32>(topic + "Speed", 1000);
    m_motorPositionPub = n.advertise<std_msgs::Float32>(topic + "Position", 1000);
}

void Motor::setSpeed(float speed) {
    m_speed.data = speed;
    m_motorSpeedPub.publish(m_speed);
}

void Motor::setPosition(float position) {
    m_position.data = position;
    m_motorPositionPub.publish(m_position);
}

void Motor::jitter(double dt, double jitter) {
    if (jitter == 0) {
        Util::ornsteinUhlenbeckProcess(m_jitterSpeed, dt, 25, 0., 0.05);
    } else {
        m_jitterSpeed = jitter;
    }
    m_speed.data = static_cast<float>(m_motion + m_jitterSpeed);
    m_motorSpeedPub.publish(m_speed);
}