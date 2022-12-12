#include "udp_client_server.hpp"

namespace lulav::comm::udp
{

server::server(const std::string& addr, int port)
    : _port(port)
    , _addr(addr)
{
    char decimal_port[16];
    snprintf(decimal_port, sizeof(decimal_port), "%d", _port);
    decimal_port[sizeof(decimal_port) / sizeof(decimal_port[0]) - 1] = '\0';

    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC; // support for both IPv4 and IPv6 
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_protocol = IPPROTO_UDP;

    int r(getaddrinfo(addr.c_str(), decimal_port, &hints, &_addrinfo));
    if(r != 0 || _addrinfo == NULL)
    {
        throw udp_client_server_runtime_error(("invalid address or port for UDP socket: \"" + addr + ":" + decimal_port + "\"").c_str());
    }

    _socket = socket(_addrinfo->ai_family, SOCK_DGRAM | SOCK_CLOEXEC, IPPROTO_UDP);
    if(_socket == -1)
    {
        freeaddrinfo(_addrinfo);
        throw udp_client_server_runtime_error(("could not create UDP socket for: \"" + addr + ":" + decimal_port + "\"").c_str());
    }

    r = bind(_socket, _addrinfo->ai_addr, _addrinfo->ai_addrlen);
    if(r != 0)
    {
        freeaddrinfo(_addrinfo);
        close(_socket);
        throw udp_client_server_runtime_error(("could not bind UDP socket with: \"" + addr + ":" + decimal_port + "\"").c_str());
    }
}

server::~server()
{
    freeaddrinfo(_addrinfo);
    close(_socket);
}

int server::get_socket() const
{
    return _socket;
}

int server::get_port() const
{
    return _port;
}

std::string server::get_addr() const
{
    return _addr;
}

int server::recv(char *msg, size_t max_size)
{
    return ::recv(_socket, msg, max_size, 0);
}

} // namespace lulav::comm::udp