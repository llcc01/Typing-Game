#ifndef __RPC_RPC__
#define __RPC_RPC__

#include <stdint.h>
#include <map>
#include "models/user.hpp"

namespace rpc
{

uint8_t Setup();

namespace server
{
class Request
{
private:
    std::string action;
    std::map<std::string, std::string> params;
    UserRole role;
    uint64_t userId;
public:
    Request(const std::string& cmd, const UserRole& role, const uint64_t& userId);
    std::string GetAction() const { return action; }
    std::string GetParam(const std::string& paramName) const { return params.at(paramName); }
    UserRole GetRole() const { return role; }
    uint64_t GetUserId() const { return userId; }
};

} // namespace server

} // namespace rpc



#endif