#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>
#include <google/protobuf/empty.pb.h>
#include "snippet_sample.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using snippetsample::SnippetSample;
using snippetsample::Snippet;
using snippetsample::Result;
using snippetsample::Request;
using google::protobuf::Empty;

class StorageEngineInterface {
	public:
		StorageEngineInterface(std::shared_ptr<Channel> channel) : stub_(SnippetSample::NewStub(channel)) {}

		void OpenStream(){
			stream = stub_->SetSnippet(&streamcontext);
		}
		void SendSnippet(const Snippet &snippet) {			
			Empty empty;
      		stream->Write(snippet);
			stream->Read(&empty);
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
		std::unique_ptr<grpc::ClientReaderWriter<snippetsample::Snippet, google::protobuf::Empty>> stream;
		ClientContext streamcontext;
};

int main(int argc, char** argv) {
	Snippet val1, val2, val3;
	val1.set_queryid(1);
	val1.set_workid(1);
	val1.set_snippet("snippet01");
	
	val2.set_queryid(1);
	val2.set_workid(2);
	val2.set_snippet("snippet02");
	
	val3.set_queryid(1);
	val3.set_workid(3);
	val3.set_snippet("snippet03");

	StorageEngineInterface tester(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));

	tester.OpenStream();
	tester.SendSnippet(val1);
	tester.SendSnippet(val2);
	tester.SendSnippet(val3);
	tester.CloseStream();
	
	tester.Run(1);

	return 0;
}

