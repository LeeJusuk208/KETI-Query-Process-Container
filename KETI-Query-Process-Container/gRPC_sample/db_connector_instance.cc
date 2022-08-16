#include <iostream>
#include <memory>
#include <string>

#include "Query_Planner.h"
#include "Meta_Data_Manager.h"
#include "Plan_Executer.h"
#include "Storage_Engine_Interface.h"
#include "Parsed_Query.h"

class DB_Connector_Instance {
public:
	DB_Connector_Instance(std::string channel_ = "localhost") : storageEngineInterface_(grpc::CreateChannel(channel_ + ":50051", grpc::InsecureChannelCredentials())), meta_data_manager_(channel_ + ":50052"){
		//init(channel_);
	}
	void run() {
		while (1)
		{
			std::string input_query = "";
			std::cout << "input: ";
			std::getline(std::cin,input_query);
			if(input_query == "exit" || input_query == "quit"){
				std::cout << "bye~" << std::endl;
				break;
			}
			Parsed_Query parsed_query(input_query);
			query_planner_.Parse(meta_data_manager_,parsed_query);
			std::cout << "parse ok " << std::endl;
			plan_executer_.Execute_Query(storageEngineInterface_,parsed_query);
		}
	}

private:
	Query_Planner query_planner_;
	Meta_Data_Manager meta_data_manager_;
	Plan_Executer plan_executer_;
	Storage_Engine_Interface storageEngineInterface_;
};

int main(int argc, char** argv) {
	DB_Connector_Instance instance("localhost");

	instance.run();

	return 0;
}

