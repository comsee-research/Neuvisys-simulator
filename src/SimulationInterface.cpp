//
// Created by alphat on 14/04/2021.
//

#include "SimulationInterface.hpp"

SimulationInterface::SimulationInterface() {
    m_rewardSub = nh.subscribe<std_msgs::Float32>("reward", 1000, [this](auto && PH1) { rewardSignalCallBack(std::forward<decltype(PH1)>(PH1)); });
    m_leftSensorSub = nh.subscribe<sensor_msgs::Image>("leftimage", 1000,
                                                      [this](auto && PH1) { visionCallBack(std::forward<decltype(PH1)>(PH1), "left"); });
    m_rightSensorSub = nh.subscribe<sensor_msgs::Image>("rightimage", 1000,
                                                       [this](auto && PH1) { visionCallBack(std::forward<decltype(PH1)>(PH1), "right"); });
    m_timeSub = nh.subscribe<std_msgs::Float32>("simulationTime", 1000, [this](auto && PH1) { timeCallBack(std::forward<decltype(PH1)>(PH1)); });
    m_simTimeStepSub = nh.subscribe<std_msgs::Float32>("simulationTimeStep", 1000, [this](auto && PH1) { timeStepCallBack(std::forward<decltype(PH1)>(PH1)); });
    m_simStepDoneSub = nh.subscribe<std_msgs::Bool>("simulationStepDone", 1000, [this](auto && PH1) { simulationStepDoneCallBack(std::forward<decltype(PH1)>(PH1)); });

    m_startSimulation = nh.advertise<std_msgs::Bool>("startSimulation", 1000);
    m_stopSimulation = nh.advertise<std_msgs::Bool>("stopSimulation", 1000);
    m_enableSyncMode = nh.advertise<std_msgs::Bool>("enableSyncMode", 1000);
    m_triggerNextStep = nh.advertise<std_msgs::Bool>("triggerNextStep", 1000);

    while (m_startSimulation.getNumSubscribers() < 1 && m_stopSimulation.getNumSubscribers() < 1 && m_enableSyncMode.getNumSubscribers() < 1 && m_triggerNextStep.getNumSubscribers() < 1) {
        ros::WallDuration sleep_t(0.5);
        sleep_t.sleep();
    }
}

void SimulationInterface::visionCallBack(const ros::MessageEvent<sensor_msgs::Image const> &frame, const std::string &topic) {
    if (topic == "left") {
        leftEvents.clear();
        frameConverter.frameConversion(topic, frame, leftReference, leftThresholdmap, leftEim, leftEvents, 0, firstLeftImage);
        if (firstLeftImage) {
            firstLeftImage = false;
        }
    } else if (topic == "right") {
        rightEvents.clear();
        frameConverter.frameConversion(topic, frame, rightReference, rightThresholdmap, rightEim, rightEvents, 1, firstRightImage);
        if (firstRightImage) {
            firstRightImage = false;
        }
    } else {
        std::cout << "wrong camera topic" << std::endl;
        return;
    }
    m_imageTime = frame.getMessage()->header.stamp;
}

void SimulationInterface::rewardSignalCallBack(const ros::MessageEvent<std_msgs::Float32> &reward) {
    m_rewardStored = reward.getMessage()->data;
}

void SimulationInterface::timeCallBack(const ros::MessageEvent<std_msgs::Float32> &time) {
    m_time = time.getMessage()->data;
}

void SimulationInterface::timeStepCallBack(const ros::MessageEvent<std_msgs::Float32> &timeStep) {
    m_timeStep = timeStep.getMessage()->data;
}

void SimulationInterface::simulationStepDoneCallBack(const ros::MessageEvent<std_msgs::Bool> &simStepDone) {
    m_simStepDone = simStepDone.getMessage()->data;
}

void SimulationInterface::update() {
    m_simStepDone = false;
    m_lastImageTime = m_imageTime;

//    auto dt = (m_imageTime - m_lastImageTime).toSec();
//    motorsJitter(dt);
}

void SimulationInterface::motorsJitter(double dt) {
    m_leftMotor1Pub.jitter(dt);
    m_leftMotor2Pub.jitter(dt, m_leftMotor1Pub.getJitterPos());

    m_rightMotor1Pub.jitter(dt);
    m_rightMotor2Pub.jitter(dt, m_leftMotor2Pub.getJitterPos());
}

void SimulationInterface::startSimulation() {
    std_msgs::Bool msg{};
    msg.data = true;
    m_startSimulation.publish(msg);
}

void SimulationInterface::stopSimulation() {
    std_msgs::Bool msg{};
    msg.data = true;
    m_stopSimulation.publish(msg);
}

void SimulationInterface::enableSyncMode(bool enable) {
    std_msgs::Bool msg{};
    msg.data = enable;
    m_enableSyncMode.publish(msg);
}

void SimulationInterface::triggerNextTimeStep() {
    std_msgs::Bool msg{};
    msg.data = true;
    m_triggerNextStep.publish(msg);
}

/*
 * Motor ids:
 * 0 = left z axis (horizontal)
 * 1 = left y axis (vertical)
 * 0 = right z axis (horizontal)
 * 1 = right y axis (vertical)
 */
void SimulationInterface::motorCommand(uint64_t motorId, const std::string& action, float value) {
    Motor *motor;
    switch (motorId) {
        case 0:
            motor = &m_leftMotor1Pub;
            break;
        case 1:
            motor = &m_leftMotor2Pub;
            break;
        case 2:
            motor = &m_rightMotor1Pub;
            break;
        case 3:
            motor = &m_rightMotor2Pub;
            break;
        default:
            motor = &m_leftMotor1Pub;
    }

    if (action == "speed") {
        motor->setSpeed(value);
    } else if (action == "position") {
        motor->setPosition(value);
    }
}
