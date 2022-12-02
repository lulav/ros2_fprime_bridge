// build command:   g++ test/main.cpp src/pipe_reader.cpp src/pipe_writer.cpp
// run command:     ./a.out
// expected output: 
//                  Hello from BOB the Parent!
//                  Hello from ALICE the Child!
//                  Parent process: got the following message from child: Message from child!!
//                  Child process: got the following message from parent: Message from parent!!

#include <stdio.h>
#include <unistd.h>
#include <string>

#include "../src/pipe_rw.hpp"

using namespace lulav::comm::pipe;

int main()
{
    if (fork() == 0)
    {
        printf("Hello from ALICE the Child!\n");

        reader child_reader(EP_ALICE);
        writer child_writer(EP_ALICE);

        child_reader.init_fifo();
        child_writer.init_fifo();

        std::string msg = "Message from child!!\n";
        child_writer.pwrite(msg.c_str(), msg.length() + 1);

        char buff[64];
        child_reader.pread(buff, 64);

        printf("Child process: got the following message from parent: %s", buff);
    }
    else
    {
        printf("Hello from BOB the Parent!\n");

        reader parent_reader(EP_BOB);
        writer parent_writer(EP_BOB);

        // Notice the order!
        // Must be in the opposite order from ALICE to avoid deadlock.
        parent_writer.init_fifo();
        parent_reader.init_fifo();

        char buff[64];
        int ret = parent_reader.pread(buff, 64);

        if(ret > 0)
            printf("Parent process: got the following message from child: %s", buff);
        else
            printf("Parent process: failed to read.\n");

        std::string msg = "Message from parent!!\n";
        parent_writer.pwrite(msg.c_str(), msg.length() + 1);
    }

    return 0;
}