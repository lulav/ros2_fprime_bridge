#ifndef _CONTROLLER_HPP
#define _CONTROLLER_HPP

#include "io_structs.hpp"

#define TIME_STEP 0.01

class Controller 
{
public:

    typedef struct parameters
    {
        float kp;
        float ki;
        float kd;
        float r_req;
    } parameters;

    Controller();

    void set_parameters(float kp = 1.0, float ki = 0.5,
                        float kd = 2.0, float r_req = 0.0);

    void get_outputs(control_signal &control_signal);
    void set_inputs(const state &state);
    void step();

private:

    parameters _params;
    
    float _u;
    float _r;
    float _v;

    float _dt;
    float _error;
    float _i_error;
    float _d_error;
    float _last_error;
    float _last_r_feedback;

    float _p_element;
    float _i_element;
    float _d_element;
};
#endif