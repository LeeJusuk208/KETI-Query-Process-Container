#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include <grpcpp/grpcpp.h>
#include <google/protobuf/empty.pb.h>
#include "snippet_sample.grpc.pb.h"
#include "WalManager.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReaderWriter;
using grpc::Status;
using snippetsample::SnippetSample;
using snippetsample::Snippet;
using snippetsample::SnippetRequest;
using snippetsample::Result;
using snippetsample::Request;
using google::protobuf::Empty;

// Logic and data behind the server's behavior.
class SnippetSampleServiceImpl final : public SnippetSample::Service {
  Status SetSnippet(ServerContext* context,
                   ServerReaderWriter<Result, SnippetRequest>* stream) override {
    SnippetRequest snippetrequest;
    while (stream->Read(&snippetrequest)) {
      //Snippet snippet = snippetrequest.snippet();
      std::string test_json;
      google::protobuf::util::JsonPrintOptions options;
      options.always_print_primitive_fields = true;
      options.always_print_enums_as_ints = true;
      google::protobuf::util::MessageToJsonString(snippetrequest,&test_json,options);
      std::cout << "Recv Snippet to JSON" << std::endl;
      //std::cout << "Snippet Type : " << snippetrequest.type() << std::endl;
      std::cout << test_json << std::endl << std::endl;
      
      if(snippetrequest.type() == 0) {
        WalManager test(snippetrequest.snippet());
        test.run();
      }
    }
    
    return Status::OK;
  }
  Status Run(ServerContext* context, const Request* request, Result* result) override {
    std::cout << "Run" << std::endl;
    std::cout << "req queryid :" << request->queryid() << std::endl << std::endl;
        
    query_result = "Under Construct";

    result->set_value(query_result);

    query_result = "";
    return Status::OK;
  }
  private:
    std::unordered_map<int, std::vector<std::string>> map;
    std::string query_result = "";
};


void RunServer() {
  std::string server_address("0.0.0.0:50051");
  SnippetSampleServiceImpl service;

  ServerBuilder builder;
  // Listen on the given address without any authentication mechanism.
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  // Register "service" as the instance through which we'll communicate with
  // clients. In this case, it corresponds to an *synchronous* service.
  builder.RegisterService(&service);
  // Finally assemble the server.
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  // Wait for the server to shutdown. Note that some other thread must be
  // responsible for shutting down the server for this call to ever return.
  server->Wait();
}

int main(int argc, char** argv) {
  RunServer();

  return 0;
}