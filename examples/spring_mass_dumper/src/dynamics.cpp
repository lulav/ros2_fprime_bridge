#include "../include/dynamics.hpp"

Dynamics::Dynamics()
{
    set_parameters();

    _dt = TIME_STEP;
    
    _r = _params.r0;
    _v = _params.v0;
}

void Dynamics::set_parameters(float m, float k, float c, float r0, float v0)
{
    _params.m = m;
    _params.k = k;
    _params.c = c;
    _params.r0 = r0;
    _params.v0 = v0;
}

void Dynamics::set_inputs(const control_signal &control_signal)
{
    _u = control_signal.u;
}

void Dynamics::step()
{
    _spring_force = _params.k * _r;
    _dumper_force = _params.c * _v;

    _a = (_u - _spring_force - _dumper_force) / _params.m;
    _v += _a * _dt;
    _r += _v * _dt;
}

void Dynamics::get_outputs(state &state)
{
    state.r = _r; 
    state.v = _v; 
}