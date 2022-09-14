#include "DB_Connector_Instance.h"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h" 
#include "keti_util.h"

using namespace rapidjson;

DB_Connector_Instance::DB_Connector_Instance() : storageEngineInterface_(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials())), meta_data_manager_("localhost:50052")
{
    //ctor
}
DB_Connector_Instance::DB_Connector_Instance(utility::string_t url):m_listener(url), storageEngineInterface_(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials())), meta_data_manager_("localhost:50052")
{
    m_listener.support(methods::GET, std::bind(&DB_Connector_Instance::handle_get, this, std::placeholders::_1));
    m_listener.support(methods::PUT, std::bind(&DB_Connector_Instance::handle_put, this, std::placeholders::_1));
    m_listener.support(methods::POST, std::bind(&DB_Connector_Instance::handle_post, this, std::placeholders::_1));
    m_listener.support(methods::DEL, std::bind(&DB_Connector_Instance::handle_delete, this, std::placeholders::_1));
}
DB_Connector_Instance::~DB_Connector_Instance()
{
    //dtor
}

void DB_Connector_Instance::handle_error(pplx::task<void>& t)
{
    try
    {
        t.get();
    }
    catch(...)
    {
        // Ignore the error, Log it if a logger is available
    }
}


//
// Get Request 
//
void DB_Connector_Instance::handle_get(http_request message)
{
    auto body_json = message.extract_string();
    std::string json = utility::conversions::to_utf8string(body_json.get());
    
    Document document;
    document.Parse(json.c_str());
    
    Parsed_Query parsed_query(document["query"].GetString());
    
    std::cout << "------------------------------------:: STEP 1 ::------------------------------------" << std::endl;
    keti_log("DB Connector Instance","Recv Query");
    query_planner_.Parse(meta_data_manager_,parsed_query);
    plan_executer_.Execute_Query(storageEngineInterface_,parsed_query);
    
    std::string rep = U("Query Result\n");
    message.reply(status_codes::OK,rep);
    return;

};

//
// A POST request
//
void DB_Connector_Instance::handle_post(http_request message)
{
    ucout <<  message.to_string() << endl;
    message.reply(status_codes::NotFound,U("SUPPORT ONLY GET API"));
    return ;
};

//
// A DELETE request
//
void DB_Connector_Instance::handle_delete(http_request message)
{
    ucout <<  message.to_string() << endl;
    message.reply(status_codes::NotFound,U("SUPPORT ONLY GET API"));
    return;
};


//
// A PUT request 
//
void DB_Connector_Instance::handle_put(http_request message)
{
    ucout <<  message.to_string() << endl;
    message.reply(status_codes::NotFound,U("SUPPORT ONLY GET API"));
    return;
};
