#include "../include/controller.hpp"

Controller::Controller()
{
    set_parameters();

    _dt = TIME_STEP;
    
    _last_error = 0.0;
    _last_r_feedback = 0.0;
}

void Controller::set_parameters(float kp, float ki, float kd, float r_req)
{
    _params.kp = kp;
    _params.ki = ki;
    _params.kd = kd;
    _params.r_req = r_req;
}

void Controller::set_inputs(const state &state)
{
    _r = state.r;
    _v = state.v;
}

void Controller::step()
{
    _error  = _params.r_req - _r;
    _i_error = _last_error + _params.ki * _error * _dt;
    _d_error = -_v;

    _p_element = _params.kp * _error;
    _i_element = _params.ki * _i_error;
    _d_element = _params.kd * _d_error;

    _u = _p_element + _i_element + _d_element;

    _last_error = _error;
    _last_r_feedback = _r;
}

void Controller::get_outputs(control_signal &control_signal)
{
    control_signal.u = _u;
}