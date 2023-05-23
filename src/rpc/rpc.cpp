#include "rpc/rpc.hpp"
#include <winsock2.h>

uint8_t rpc::Setup()
{
    WORD sockVersion = MAKEWORD(2, 2);
    WSADATA data;
    if (WSAStartup(sockVersion, &data) != 0)
    {
        return 1;
    }
    return 0;
}