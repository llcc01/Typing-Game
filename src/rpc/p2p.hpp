#ifndef __RPC_HPP__
#define __RPC_HPP__

#include <stdint.h>
#include <atomic>
#include <winsock2.h>
#include <memory>

#include "rpc/rpc.hpp"

namespace rpc
{

class P2P
{
private:
    WSADATA wsa_;
    SOCKET udpSocket_ = INVALID_SOCKET;
    std::atomic<bool> rxFlag_ = false;
    bool running_ = false;
    uint16_t port_ = 0;
    std::shared_ptr<Request> req_ = nullptr;

    void loop();
public:
    P2P(uint16_t port) : port_(port) {}
    ~P2P() {}
    int64_t Setup();
    void Start();
    void Stop();
    void SetRxFlag(bool flag) { rxFlag_ = flag; }
    bool GetRxFlag() const { return rxFlag_; }
    bool IsRunning() const { return running_; }
    std::shared_ptr<Request> GetRequest() const { return std::make_shared<Request>(*req_); }
    int Send(const std::string& ipAddr, const uint16_t& port, const std::string& cmd, const UserRole& role, const uint64_t& userId);
};

} // namespace rpc





#endif