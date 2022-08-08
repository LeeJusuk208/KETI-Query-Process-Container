#include <iostream>
#include <memory>
#include <string>

#include "Storage_Engine_Interface.h"

class DB_Connector_Instance {
public:
	DB_Connector_Instance(std::string channel_ = "localhost") : storageEngineInterface_(grpc::CreateChannel(channel_ + ":50051", grpc::InsecureChannelCredentials())){
		//init(channel_);
	}
	void run() {
		//while(1){
			//std::string input_query = "";

			// get input_query with tcp/ip

			//if(input_query == "exit" || input_query == "quit"){
			//	break;
			//}

			//ParsedQuery parsed_query(input_query);

			//query_planner_.Parse(parsed_query);
			//plan_executer_.Execute_Query(parsed_query);
		//}
		
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
	
		storageEngineInterface_.OpenStream();
		storageEngineInterface_.SendSnippet(val1);
		storageEngineInterface_.SendSnippet(val2);
		storageEngineInterface_.SendSnippet(val3);
		storageEngineInterface_.CloseStream();
	
		storageEngineInterface_.Run(1);
	}

private:
	//Query_Planner query_planner_;
	//Plan_Executer plan_executer_;
	//Meta_Data_Manager mata_data_manager_;
	Storage_Engine_Interface storageEngineInterface_;

	void init(std::string channel_){
		//query_planner_ = Query_Planner();
		//plan_executer_ = Plan_Executer();

		//mata_data_manager_ = Meta_Data_Manager(channel_ + ":50052");
		//storageEngineInterface_ = Storage_Engine_Interface(grpc::CreateChannel(channel_ + ":50051", grpc::InsecureChannelCredentials()));

		//query_planner_.Set_Meta_Data_Manager(mata_data_manager_);
		//plan_executer_.Set_Storage_Engine_Interface(storageEngineInterface_);
	}
};

int main(int argc, char** argv) {
	DB_Connector_Instance instance("localhost");

	instance.run();

	return 0;
}

