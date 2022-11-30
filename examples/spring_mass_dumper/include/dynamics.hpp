#ifndef _DYNAMICS_HPP
#define _DYNAMICS_HPP

#include "../io_structs.hpp"
#define TIME_STEP 0.01

class Dynamics 
{
public:

    struct parameters
    {
        float m;
        float k;
        float c;
        float r0;
        float v0;
    };

    Dynamics();

    void set_parameters(float m = 1.0, float k = 2.5,
                        float c = 0.3, float r0 = -1.0, float v0 = 0.0);
                        
    void set_inputs(const control_signal &control_signal);
    void get_outputs(state &state);
    void step();

private:

        parameters _params;

        float _u;
        float _r;
        float _v;
        
        float _dt;
        float _a;
        float _spring_force;
        float _dumper_force;
};
#endif