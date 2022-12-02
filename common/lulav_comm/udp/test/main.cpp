// build command:   g++ test/main.cpp src/udp_client.cpp src/udp_server.cpp
// run command:     ./a.out
// expected output: 
//                  Hello from Parent!
//                  Hello from Child!
//                  Parent process: got the following message from child: Message from child!!
//                  Child process: got the following message from parent: Message from parent!!

#include <stdio.h>
#include <unistd.h>

#include "../src/udp_client_server.hpp"

using namespace lulav::comm::udp;

int main()
{
    if (fork() == 0)
    {
        printf("Hello from Child!\n");

        client child_sender("127.0.0.1", 42000);
        server child_receiver("127.0.0.1", 69000);

        std::string msg = "Message from child!!\n";
        child_sender.send(msg.c_str(), msg.length() + 1);

        char buff[64];
        child_receiver.recv(buff, 64);

        printf("Child process: got the following message from parent: %s", buff);
    }
    else
    {
        printf("Hello from Parent!\n");

        client parent_sender("127.0.0.1", 69000);
        server parent_receiver("127.0.0.1", 42000);

        char buff[64];
        int ret = parent_receiver.timed_recv(buff, 64, 500);

        if(ret != -1)
            printf("Parent process: got the following message from child: %s", buff);
        else
            printf("Parent process: error or timeout occurred while waiting for message from child.\n");

        std::string msg = "Message from parent!!\n";
        parent_sender.send(msg.c_str(), msg.length() + 1);
    }

    return 0;
}