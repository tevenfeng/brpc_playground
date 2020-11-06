#include "client.h"

#define FLAGS_protocol "baidu_std"
#define FLAGS_connection_type ""
#define FLAGS_timeout_ms 2000
#define FLAGS_max_retry 5

#define FLAGS_server "0.0.0.0:18381"
#define FLAGS_load_balancer ""

int main()
{
    brpc::Channel channel;

    brpc::ChannelOptions channel_options;
    channel_options.protocol = FLAGS_protocol;
    channel_options.connection_type = FLAGS_connection_type;
    channel_options.timeout_ms = FLAGS_timeout_ms;      /*milliseconds*/
    channel_options.max_retry = FLAGS_max_retry;

    if (channel.Init(FLAGS_server, FLAGS_load_balancer, &channel_options) != 0)
    {
        LOG(ERROR) << "Fail to initialize channel";
        return -1;
    }

    examples::EchoService_Stub echo_service_stub(&channel);

    int log_id = 0;
    while (!brpc::IsAskedToQuit())
    {
        examples::EchoRequest request;
        examples::EchoResponse response;
        brpc::Controller rpc_controller;

        std::string user_name = "";
        std::string user_email = "";

        while (user_name == "")
        {
            std::cout << "Please input your name(Required): ";
            std::cin >> user_name;
        }
        request.set_user_name(user_name.c_str());

        std::cout << "Please input email(optional): ";
        std::cin >> user_email;
        if (user_email != "")
        {
            request.set_user_email(user_email.c_str());
        }

        rpc_controller.set_log_id(log_id++);
        echo_service_stub.Echo(&rpc_controller, &request, &response, NULL);
        if (!rpc_controller.Failed()) {
            LOG(INFO) << "Received response from " << rpc_controller.remote_side()
                << " to " << rpc_controller.local_side()
                << ": " << response.response_message() << " (attached="
                << rpc_controller.response_attachment() << ")"
                << " latency=" << rpc_controller.latency_us() << "us";
        } else {
            LOG(WARNING) << rpc_controller.ErrorText();
        }
    }

}