#include "pipe_rw.hpp"

namespace lulav::comm::pipe
{

writer::writer(endpoint ep)
{
    if(ep == EP_ALICE)
    {
        _write_to = PIPE_FROM_ALICE;
    }
    else // EP_BOB
    {
        _write_to = PIPE_TO_ALICE;
    }
}

bool writer::init_fifo()
{
    const char* pipe_name = _write_to.c_str();

    if (!fifo_exist(pipe_name))
        mkfifo(pipe_name, FIFO_MODE);
      
    _wd = open(pipe_name, O_WRONLY);
    return (_wd != -1);
}

}