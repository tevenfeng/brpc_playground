#include <brpc/server.h>
#include <iostream>
#include <string>

#include "message.pb.h"

namespace brpc_playground_echo {

class EchoServiceImpl : public examples::EchoService {
public:
    EchoServiceImpl();
    ~EchoServiceImpl();
    void Echo(::google::protobuf::RpcController* rpc_controller,
                const ::examples::EchoRequest* request,
                ::examples::EchoResponse* response,
                ::google::protobuf::Closure* done);
};

}