#include "rpc/p2p.hpp"
#include <winsock2.h>
#include <atomic>
#include <thread>
#include <iostream>

#include "rpc/rpc.hpp"

namespace rpc
{



int64_t P2P::Setup()
{
    if (WSAStartup(MAKEWORD(2, 2), &wsa_) != 0)
    {
        return -1;
    }

    // UDP
    udpSocket_ = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (udpSocket_ == INVALID_SOCKET)
    {
        return -2;
    }

    sockaddr_in sock_in;
    sock_in.sin_family = AF_INET;
    sock_in.sin_port = htons(port_);
    sock_in.sin_addr.S_un.S_addr = INADDR_ANY;
    if (bind(udpSocket_, (sockaddr*)&sock_in, sizeof(sock_in)) == SOCKET_ERROR)
    {
        return -3;
    }

    sockaddr_in connAddr;
    int len = sizeof(connAddr);
    getsockname(udpSocket_, (sockaddr*)&connAddr, &len);

    return ntohs(connAddr.sin_port);
}


void P2P::loop()
{
    char buf[1024];
    sockaddr_in clientAddr;
    while (running_)
    {
        if (GetRxFlag())
        {
            continue;
        }
        int len = sizeof(clientAddr);
        int n = recvfrom(udpSocket_, buf, sizeof(buf), 0, (sockaddr*)&clientAddr, &len);

        std::string reqStr(buf, n);

        // std::cout << "reqStr: " << reqStr << std::endl;
        size_t pos1 = reqStr.find("\n");
        std::string cmd = reqStr.substr(0, pos1);
        std::string action = reqStr.substr(0, cmd.find("?"));

        uint64_t id = 0;
        UserRole role = UserRole::None;

        size_t pos2 = reqStr.find("\n", pos1 + 1);
        uint64_t destId = 0;

        if (pos2 != std::string::npos)
        {
            std::string auth = reqStr.substr(pos1 + 1, pos2 - pos1 - 1);
            size_t pos3 = auth.find(":");

            if (pos3 != std::string::npos)
            {
                role = static_cast<UserRole>(std::stoi(auth.substr(0, pos3)));
                id = std::stoull(auth.substr(pos3 + 1));
                if (role == UserRole::Player)
                {
                    req_ = std::make_shared<Request>(Request(cmd, role, id));
                    SetRxFlag(true);
                }
            }
        }
    }
    closesocket(udpSocket_);
    WSACleanup();
}

int P2P::Send(const std::string& ipAddr, const uint16_t& port, const std::string& cmd, const UserRole& role, const uint64_t& userId)
{
    std::string reqStr = cmd + "\n" + std::to_string(uint16_t(role)) + ":" + std::to_string(userId) + "\n";
    sockaddr_in sock_in;
    sock_in.sin_family = AF_INET;
    sock_in.sin_port = htons(port);
    sock_in.sin_addr.S_un.S_addr = inet_addr(ipAddr.c_str());
    return sendto(udpSocket_, reqStr.c_str(), reqStr.size() + 1, 0, (sockaddr*)&sock_in, sizeof(sock_in));
}

void P2P::Start()
{
    running_ = true;
    std::thread(loop, this).detach();
}

void P2P::Stop()
{
    running_ = false;
}

}