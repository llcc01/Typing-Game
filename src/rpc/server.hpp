#ifndef __RPC_SERVER__
#define __RPC_SERVER__

#include <stdint.h>
#include <string>

namespace rpc::server
{
uint8_t ServeForever(const std::string& ipAdrr, uint16_t port);

} // namespace rpc::server


#endif