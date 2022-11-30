#include "include/controller.hpp"
#include "include/dynamics.hpp"
#include <stdio.h>

int main()
{
    Dynamics dynamics;
    state dynamics_output;
    control_signal dynamics_input;
    Dynamics::parameters dynamics_parameters;

    Controller controller;
    control_signal controller_output;
    state controller_input;
    Controller::parameters controller_parameters;

    // Initial step
    dynamics_input.u = 0.0;

    dynamics.set_inputs(dynamics_input);
    dynamics.step();
    dynamics.get_outputs(dynamics_output);

    for (int i = 0; i < 500; i++)
    {
        controller_input.r = dynamics_output.r;
        controller_input.v = dynamics_output.v;

        controller.set_inputs(controller_input);
        controller.step();
        controller.get_outputs(controller_output);

        dynamics_input.u = controller_output.u;

        dynamics.set_inputs(dynamics_input);
        dynamics.step();
        dynamics.get_outputs(dynamics_output);

        printf("Position = %f\n", dynamics_output.r);
    }

}