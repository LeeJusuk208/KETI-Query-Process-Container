#include "Plan_Executer.h"
#include <iostream>
#include <fstream>

#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <sql.h>
#include <sqlext.h>
#include "kodbc.h"

void load_snippet(std::list<SnippetRequest> &list,std::string snippet_name);

void Plan_Executer::Execute_Query(Storage_Engine_Interface &storageEngineInterface,Parsed_Query &parsed_query){
  std::cout << parsed_query.Get_Ori_Query() << std::endl;
  std::cout << parsed_query.Get_Parsed_Query() << std::endl;

    if(parsed_query.isGenericQuery()){

    char *szDSN = (char*)"myodbc5w";
    char *szUID;
    char *szPWD;
    char *szSQL;
    SQLHENV hEnv = SQL_NULL_HENV;
    SQLHDBC hDbc = SQL_NULL_HDBC;
    // SQLRETURN retcode;

    //Open database
    if(!OpenDatabase(&hEnv, &hDbc, szDSN, szUID, szPWD)){
        return;
    }

    //Execute SQL
    szSQL = strcpy(new char[parsed_query.Get_Parsed_Query().length() + 1], parsed_query.Get_Parsed_Query().c_str());
    //szSQL = (char*)"SELECT SUM(l_extendedprice) / 7.0 AS avg_yearly FROM lineitem, part WHERE p_partkey = l_partkey AND p_brand = 'Brand#44' AND p_container = 'WRAP PKG' AND l_quantity < (SELECT 0.2 * AVG(l_quantity) FROM lineitem WHERE l_partkey = p_partkey);";
    ExecuteSQL( hDbc, szSQL);
    delete[] szSQL;

    //Database Close
    CloseDatabase(hEnv, hDbc);

    } else {
        int query_id = Set_Query_ID();
        auto snippet_list = Gen_Snippet(parsed_query);
        std::list<SnippetRequest>::iterator iter = snippet_list->begin();
        
        storageEngineInterface.OpenStream();
        for(;iter != snippet_list->end();iter++){
            storageEngineInterface.SendSnippet(*iter);
        }
        //storageEngineInterface.GetReturn();
        storageEngineInterface.CloseStream();

        //storageEngineInterface.Run(query_id);
    }
}

int Plan_Executer::Set_Query_ID(){ // test code
    return 5;
}

std::unique_ptr<std::list<SnippetRequest>> Plan_Executer::Gen_Snippet(Parsed_Query &parsed_query){ // test code
    std::unique_ptr<std::list<SnippetRequest>> ret(new std::list<SnippetRequest>());
    std::string query_str = parsed_query.Get_Ori_Query();

    if (query_str == "TPC-H_01"){ //TPC-H Query 1
        load_snippet(*ret,"tpch01-0");
        load_snippet(*ret,"tpch01-1");
    } else if(query_str == "TPC-H_05"){ //TPC-H Query 5
        load_snippet(*ret,"tpch05-0");
        load_snippet(*ret,"tpch05-1");
        load_snippet(*ret,"tpch05-2");
        load_snippet(*ret,"tpch05-3");
        load_snippet(*ret,"tpch05-4");
        load_snippet(*ret,"tpch05-5");
        load_snippet(*ret,"tpch05-6");
    }
	
    return ret;
}

void read_json(std::string& request,std::string snippet_name){
  request = "";
	std::ifstream openFile("../../../snippets/" + snippet_name + ".json");
	if(openFile.is_open() ){
		std::string line;
		while(getline(openFile, line)){
			request += line;
      //std::cout << line << std::endl;
		}
		openFile.close();
	}
}

void load_snippet(std::list<SnippetRequest> &list,std::string snippet_name){
  SnippetRequest request;

  std::string json_str;
  read_json(json_str,snippet_name);
  google::protobuf::util::JsonParseOptions options;
  options.ignore_unknown_fields = true;
  google::protobuf::util::JsonStringToMessage(json_str,&request,options);

  list.push_back(request);
}