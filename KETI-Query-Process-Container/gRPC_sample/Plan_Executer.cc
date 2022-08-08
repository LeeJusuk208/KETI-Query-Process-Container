#include "Plan_Executer.h"

void Plan_Executer::Execute_Query(Storage_Engine_Interface &storageEngineInterface){    
    int query_id = Set_Query_ID();
    auto snippet_list = Gen_Snippet(query_id);
    std::list<Snippet>::iterator iter = snippet_list->begin();
        
    storageEngineInterface.OpenStream();
    for(;iter != snippet_list->end();iter++){
        storageEngineInterface.SendSnippet(*iter);
    }
    storageEngineInterface.CloseStream();

    storageEngineInterface.Run(query_id);    
}

int Plan_Executer::Set_Query_ID(){ // test code
    return 1;
}

std::unique_ptr<std::list<Snippet>> Plan_Executer::Gen_Snippet(int query_id){ // test code
    int work_id = 1;
    std::unique_ptr<std::list<Snippet>> ret(new std::list<Snippet>());

	Snippet val1, val2, val3;
	val1.set_queryid(query_id);
	val1.set_workid(work_id++);
	val1.set_snippet("snippet01");
	val2.set_queryid(query_id);
	val2.set_workid(work_id++);
	val2.set_snippet("snippet02");	
	val3.set_queryid(query_id);
	val3.set_workid(work_id++);
	val3.set_snippet("snippet03");

    ret->push_back(Snippet(val1));
    ret->push_back(Snippet(val2));
    ret->push_back(Snippet(val3));
	
    return ret;
}