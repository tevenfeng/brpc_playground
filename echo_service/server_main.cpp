#include <iostream>
#include <string>

#include "server.h"

#define FLAGS_port 18381
#define FLAGS_idle_timeout_sec -1

int main()
{
    brpc::Server server;
    brpc_playground_echo::EchoServiceImpl echo_service_impl;

    if (server.AddService(&echo_service_impl,
                        brpc::SERVER_DOESNT_OWN_SERVICE) != 0)
    {
        LOG(ERROR) << "Fail to add service";
        return -1;
    }

    brpc::ServerOptions server_options;
    server_options.idle_timeout_sec = FLAGS_idle_timeout_sec;
    if (server.Start(FLAGS_port, &server_options) != 0) {
        LOG(ERROR) << "Fail to start EchoServer";
        return -1;
    }

    server.RunUntilAskedToQuit();
    return 0;
}