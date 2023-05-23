#include "rpc/rpc.hpp"
#include "rpc/server.hpp"
#include "db.hpp"
#include <iostream>

int main(void)
{
    if(rpc::Setup())
    {
        std::cout << "rpc::Setup() failed" << std::endl;
        return 1;
    }
    auto res = rpc::server::ServeForever("0.0.0.0", 12345);
    std::cout << "Server exited with code: " << int(res) << std::endl;

    Database::DestroyInstance();
    return 0;
}