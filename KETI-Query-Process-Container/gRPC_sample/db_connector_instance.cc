#include <iostream>
#include <memory>
#include <string>

#include "Query_Planner.h"
#include "Meta_Data_Manager.h"
#include "Plan_Executer.h"
#include "Storage_Engine_Interface.h"

class DB_Connector_Instance {
public:
	DB_Connector_Instance(std::string channel_ = "localhost") : storageEngineInterface_(grpc::CreateChannel(channel_ + ":50051", grpc::InsecureChannelCredentials())), meta_data_manager_(channel_ + ":50052"){
		//init(channel_);
	}
	void run() {
		plan_executer_.Execute_Query(storageEngineInterface_);
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

