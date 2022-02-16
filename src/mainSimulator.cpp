//
// Created by thomas on 28/06/2021.
//

#include "SimulationInterface.hpp"

int main(int argc, char **argv) {
    ros::init(argc, argv, "neuvisysSimulator");

    SimulationInterface sim;
    sim.enableSyncMode(true);
    sim.startSimulation();

    int action;
    std::string msg;
    while (ros::ok() && sim.getSimulationTime() < 300) {
        sim.triggerNextTimeStep();
        while(!sim.simStepDone()) {
            ros::spinOnce();
        }

        sim.update();
        if (!sim.getLeftEvents().empty()) {
            for (auto event : sim.getLeftEvents()) {

            }
            if (sim.getLeftEvents().size() % 2 == 0) {
                action = 0; // left
            } else {
                action = 2; // right
            }

            sim.activateMotors(0);
        }
    }

    sim.stopSimulation();
    return 0;
}