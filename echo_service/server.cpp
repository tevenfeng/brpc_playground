#include "server.h"

namespace brpc_playground_echo {

EchoServiceImpl::EchoServiceImpl()
{

}

EchoServiceImpl::~EchoServiceImpl()
{

}

void EchoServiceImpl::Echo(::google::protobuf::RpcController* rpc_controller,
            const ::examples::EchoRequest* request,
            ::examples::EchoResponse* response,
            ::google::protobuf::Closure* done)
{
    brpc::ClosureGuard done_guard(done);

    brpc::Controller* cntl =
        static_cast<brpc::Controller*>(rpc_controller);
    LOG(INFO) << "Received request[log_id=" << cntl->log_id() 
                << "] from " << cntl->remote_side() 
                << " to " << cntl->local_side()
                << ": user_name=>" << request->user_name()
                << ", user_email=>" << request->user_email()
                << " (attached=" << cntl->request_attachment() << ")";

    std::string response_message = "Hello, ";
    response_message += request->user_name();
    response_message += "; ";
    
    if (request->has_user_email())
    {
        response_message += "your email address is ";
        response_message += request->user_email();
        response_message += ".";
    }
    else
    {
        response_message += "you didn't provide any email address!";
    }

    response->set_response_message(response_message.c_str());
}

}