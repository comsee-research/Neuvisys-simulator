//
// Created by thomas on 28/06/2021.
//

#include "SimulationInterface.hpp"

int main(int argc, char **argv) {
    ros::init(argc, argv, "neuvisysSimulator");

    SimulationInterface sim;
    sim.enableSyncMode(true);
    sim.startSimulation();

    while (ros::ok()) {
        sim.triggerNextTimeStep();
        while(!sim.simStepDone()) {
            ros::spinOnce();
        }

        sim.update();
        if (!sim.getLeftEvents().empty()) {
            // Event loop
//            for (auto &event : sim.getLeftEvents()) {
//                std::cout << event.timestamp() << std::endl;
//            }

            // motor commands
            sim.motorCommand(0, "speed", -1);
            sim.motorCommand(1, "speed", 1);
        }
    }

    sim.stopSimulation();
    return 0;
}