#include "rpc/rpc.hpp"
#include <winsock2.h>

namespace rpc
{

uint8_t Setup()
{
    WORD sockVersion = MAKEWORD(2, 2);
    WSADATA data;
    if (WSAStartup(sockVersion, &data) != 0)
    {
        return 1;
    }
    return 0;
}

namespace server
{
Request::Request(const std::string& cmd, const UserRole& role, const uint64_t& userId) : role(role), userId(userId)
{
    std::string::size_type pos = cmd.find("?");
    if (pos != std::string::npos)
    {
        action = cmd.substr(0, pos);
        std::string paramsStr = cmd.substr(pos + 1);
        std::string::size_type pos2 = paramsStr.find("&");
        while (pos2 != std::string::npos)
        {
            std::string param = paramsStr.substr(0, pos2);
            std::string::size_type pos3 = param.find("=");
            if (pos3 != std::string::npos)
            {
                std::string paramName = param.substr(0, pos3);
                std::string paramValue = param.substr(pos3 + 1);
                params[paramName] = paramValue;
            }
            paramsStr = paramsStr.substr(pos2 + 1);
            pos2 = paramsStr.find("&");
        }
        std::string::size_type pos3 = paramsStr.find("=");
        if (pos3 != std::string::npos)
        {
            std::string paramName = paramsStr.substr(0, pos3);
            std::string paramValue = paramsStr.substr(pos3 + 1);
            params[paramName] = paramValue;
        }
    }
    else
    {
        action = cmd;
    }
}
} // namespace server


} // namespace rpc


