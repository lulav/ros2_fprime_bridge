#include "udp_client_server.hpp"

namespace lulav::comm::udp
{

client::client(const std::string& addr, int port)
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
        throw udp_client_server_runtime_error(("invalid address or port: \"" + addr + ":" + decimal_port + "\"").c_str());
    }

    _socket = socket(_addrinfo->ai_family, SOCK_DGRAM | SOCK_CLOEXEC, IPPROTO_UDP);
    if(_socket == -1)
    {
        freeaddrinfo(_addrinfo);
        throw udp_client_server_runtime_error(("could not create socket for: \"" + addr + ":" + decimal_port + "\"").c_str());
    }
}

client::~client()
{
    freeaddrinfo(_addrinfo);
    close(_socket);
}

int client::get_socket() const
{
    return _socket;
}

int client::get_port() const
{
    return _port;
}

std::string client::get_addr() const
{
    return _addr;
}

int client::send(const char *msg, size_t size)
{
    return sendto(_socket, msg, size, 0, _addrinfo->ai_addr, _addrinfo->ai_addrlen);
}

}