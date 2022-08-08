#pragma once
#include "Storage_Engine_Interface.h"
#include <list>

class Plan_Executer {
public:
	Plan_Executer( ){ }
    void Execute_Query(Storage_Engine_Interface &storageEngineInterface);
private:
    int Set_Query_ID();
    std::unique_ptr<std::list<Snippet>> Gen_Snippet(int query_id);
};