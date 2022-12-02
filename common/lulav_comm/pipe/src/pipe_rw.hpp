#ifndef LULAV_PIPE_RW
#define LULAV_PIPE_RW

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string>

#define FIFO_MODE 0666
#define PIPE_FROM_ALICE "/tmp/from_alice"
#define PIPE_TO_ALICE "/tmp/to_alice"


namespace lulav::comm::pipe
{

inline bool fifo_exist(const char* name)
{
    struct stat buffer;   
    return (stat(name, &buffer) == 0); 
}

enum endpoint
{
    EP_ALICE = 0,
    EP_BOB = 1
};

class reader
{
public:
    reader(endpoint ep);
    bool init_fifo();
    inline int pread(const char *buff, size_t size)
    {
        return read(_rd, (void*)buff, size);
    }
      
private:
    int _rd;
    std::string _read_from;
};


class writer
{
public:
    writer(endpoint ep);
    bool init_fifo();
    inline int pwrite(const char *buff, size_t size)
    {
        return write(_wd, (const void*)buff, size);
    }

private:
    int _wd;
    std::string _write_to;
};

} // namespace lulav::comm::pipe

#endif