#include "pipe_rw.hpp"

namespace lulav::comm::pipe
{

reader::reader(endpoint ep)
{
    if(ep == EP_ALICE)
    {
        _read_from = PIPE_TO_ALICE;
    }
    else //EP_BOB
    {
        _read_from = PIPE_FROM_ALICE;
    }
}

bool reader::init_fifo()
{
    const char* pipe_name = _read_from.c_str();

    if (!fifo_exist(pipe_name))
        mkfifo(pipe_name, FIFO_MODE);  
      
    _rd = open(pipe_name, O_RDONLY); // blocking
    return (_rd != -1);
}

}