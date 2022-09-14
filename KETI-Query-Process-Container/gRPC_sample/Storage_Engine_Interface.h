#pragma once
#include <grpcpp/grpcpp.h>
#include <google/protobuf/empty.pb.h>
#include "snippet_sample.grpc.pb.h"
#include "keti_util.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using snippetsample::SnippetSample;
using snippetsample::Snippet;
using snippetsample::SnippetRequest;
using snippetsample::Result;
using snippetsample::Request;
using google::protobuf::Empty;

class Storage_Engine_Interface {
	public:
		Storage_Engine_Interface(std::shared_ptr<Channel> channel) : stub_(SnippetSample::NewStub(channel)) {}

		void OpenStream(){
			streamcontext.reset(new ClientContext());
			stream = stub_->SetSnippet(streamcontext.get());
		}
		void SendSnippet(const SnippetRequest &snippet) {
      		stream->Write(snippet);
			keti_log("Storage Engine Interface","Send Snippet (WorkID : " + std::to_string(snippet.snippet().work_id()) + ") to Storage Engine Instance");
		}
		void GetReturn(){		
			Result result;		
			stream->Read(&result);
			std::cout << result.value() << std::endl;
		}
		void CloseStream(){
			stream->WritesDone();
			Status status = stream->Finish();
			
			if (!status.ok()) {
				std::cout << status.error_code() << ": " << status.error_message() << std::endl;
				std::cout << "RPC failed";
			}
		}

		void Run(int queryid) {
			Request request;
			request.set_queryid(queryid);
    		ClientContext context;
			Result result;
			
			Status status = stub_->Run(&context, request, &result);

			std::cout << std::endl << "result : " << result.value() << "\n";
			
	  		if (!status.ok()) {
				std::cout << status.error_code() << ": " << status.error_message() << std::endl;
				std::cout << "RPC failed";
			}
		}

	private:
		std::unique_ptr<SnippetSample::Stub> stub_;
		std::unique_ptr<grpc::ClientReaderWriter<snippetsample::SnippetRequest, snippetsample::Result>> stream;
		std::unique_ptr<ClientContext> streamcontext;
};
