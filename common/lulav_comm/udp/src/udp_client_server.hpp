#ifndef UDP_CLIENT_SERVER_H
#define UDP_CLIENT_SERVER_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdexcept>

#include <string.h>
#include <unistd.h>

namespace lulav::comm::udp
{

class udp_client_server_runtime_error : public std::runtime_error
{
public:
    udp_client_server_runtime_error(const char *w) : std::runtime_error(w) {}
};


class client
{
public:
                        client(const std::string& addr, int port);
                        ~client();

    int                 get_socket() const;
    int                 get_port() const;
    std::string         get_addr() const;

    int                 send(const char *msg, size_t size);

private:
    int                 _socket;
    int                 _port;
    std::string         _addr;
    struct addrinfo *   _addrinfo;
};


class server
{
public:
                        server(const std::string& addr, int port);
                        ~server();

    int                 get_socket() const;
    int                 get_port() const;
    std::string         get_addr() const;

    int                 recv(char *msg, size_t max_size);

private:
    int                 _socket;
    int                 _port;
    std::string         _addr;
    struct addrinfo *   _addrinfo;
};

} // lulav::comm::udp
#endif