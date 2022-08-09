#pragma once
#include "Meta_Data_Manager.h"
#include "Parsed_Query.h"

class Query_Planner {
public:
	Query_Planner() {}
    void Parse(Meta_Data_Manager &mata_data_manager,Parsed_Query &parsed_query){
        parsed_query.Set_Query_Type_As_PushdownQuery();
    }

private:
};