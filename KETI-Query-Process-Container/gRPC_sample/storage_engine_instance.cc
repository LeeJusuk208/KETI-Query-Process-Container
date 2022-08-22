#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include <grpcpp/grpcpp.h>
#include <google/protobuf/empty.pb.h>
#include "snippet_sample.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReaderWriter;
using grpc::Status;
using snippetsample::SnippetSample;
using snippetsample::Snippet;
using snippetsample::Result;
using snippetsample::Request;
using google::protobuf::Empty;

// Logic and data behind the server's behavior.
class SnippetSampleServiceImpl final : public SnippetSample::Service {
  Status SetSnippet(ServerContext* context,
                   ServerReaderWriter<Result, Snippet>* stream) override {
    Snippet snippet;
    while (stream->Read(&snippet)) {
      std::string test_json;
      google::protobuf::util::JsonPrintOptions options;
      options.always_print_primitive_fields = true;
      options.always_print_enums_as_ints = true;
      google::protobuf::util::MessageToJsonString(snippet,&test_json,options);
      std::cout << "Recv Snippet to JSON" << std::endl;
      std::cout << test_json << std::endl << std::endl;
      
      /*
      std::cout << "Recv Snippet" << std::endl;

  // QueryID
  {
    std::cout << "\"QueryID\" : " << snippet.query_id() << std::endl;
  }
  
  // WorkID
  {
    std::cout << "\"WorkID\" : " << snippet.work_id() << std::endl;
  }
  
  // table_name
  {
    std::cout << "\"table_name\" : [";
    for(int i=0;i<snippet.table_name_size();i++){
        std::cout << "\"" << snippet.table_name(i) << "\",";
    }
    std::cout << "]," << std::endl;
  }
  
  // table_col
  {
    std::cout << "\"table_col\" : [" << std::endl;
    for(int i=0;i<snippet.table_col_size();i++){
        std::cout << "\t\"" << snippet.table_col(i) << "\"," << std::endl;
    }
    std::cout << "]," << std::endl;
  }
    
  // table_filter
  {
    std::cout << "\"table_filter\" : [" << std::endl;
    for(int i=0;i<snippet.table_filter_size();i++){
        auto filter = snippet.table_filter(i);
        std::cout << "\t{";
        switch(filter.select_type()){
            case snippetsample::Snippet_Filter_OperType::Snippet_Filter_OperType_KETI_GE:
            std::cout << "\"OPERATOR\" : OperType_KETI_GE,";
            break;
            case snippetsample::Snippet_Filter_OperType::Snippet_Filter_OperType_KETI_LE:
            std::cout << "\"OPERATOR\" : OperType_KETI_LE,";
            break;
            case snippetsample::Snippet_Filter_OperType::Snippet_Filter_OperType_KETI_GT:
            std::cout << "\"OPERATOR\" : OperType_KETI_GT,";
            break;
            case snippetsample::Snippet_Filter_OperType::Snippet_Filter_OperType_KETI_LT:
            std::cout << "\"OPERATOR\" : OperType_KETI_LT,";
            break;
            case snippetsample::Snippet_Filter_OperType::Snippet_Filter_OperType_KETI_ET:
            std::cout << "\"OPERATOR\" : OperType_KETI_ET,";
            break;
            case snippetsample::Snippet_Filter_OperType::Snippet_Filter_OperType_KETI_NE:
            std::cout << "\"OPERATOR\" : OperType_KETI_NE,";
            break;
            case snippetsample::Snippet_Filter_OperType::Snippet_Filter_OperType_KETI_LIKE:
            std::cout << "\"OPERATOR\" : OperType_KETI_LIKE,";
            break;
            case snippetsample::Snippet_Filter_OperType::Snippet_Filter_OperType_KETI_BETWEEN:
            std::cout << "\"OPERATOR\" : OperType_KETI_BETWEEN,";
            break;
            case snippetsample::Snippet_Filter_OperType::Snippet_Filter_OperType_KETI_IN:
            std::cout << "\"OPERATOR\" : OperType_KETI_IN,";
            break;
            case snippetsample::Snippet_Filter_OperType::Snippet_Filter_OperType_KETI_IS:
            std::cout << "\"OPERATOR\" : OperType_KETI_IS,";
            break;
            case snippetsample::Snippet_Filter_OperType::Snippet_Filter_OperType_KETI_ISNOT:
            std::cout << "\"OPERATOR\" : OperType_KETI_LE,";
            break;
            case snippetsample::Snippet_Filter_OperType::Snippet_Filter_OperType_KETI_NOT:
            std::cout << "\"OPERATOR\" : OperType_KETI_NOT,";
            break;
            case snippetsample::Snippet_Filter_OperType::Snippet_Filter_OperType_KETI_AND:
            std::cout << "\"OPERATOR\" : OperType_KETI_AND,";
            break;
            case snippetsample::Snippet_Filter_OperType::Snippet_Filter_OperType_KETI_OR:
            std::cout << "\"OPERATOR\" : OperType_KETI_LE,";
            break;
        }
        for(int j=0;j<filter.value_size();j++){
            std::string value = filter.value(j);
            snippetsample::Snippet_ValueType value_type = filter.value_type(j);
            //const snippetsample::Snippet_SnippetAny& any = filter.keti_any(j);
            if(j==0){
                std::cout << "\"LV\" : ";
            } else if(j==1){
                std::cout << "\"RV\" : ";
            } else {
                std::cout << "\"EXTRA\" : ";
            }
            
            switch(value_type){
                case snippetsample::Snippet_ValueType::Snippet_ValueType_INT8:
                case snippetsample::Snippet_ValueType::Snippet_ValueType_INT16:
                case snippetsample::Snippet_ValueType::Snippet_ValueType_INT32:
                case snippetsample::Snippet_ValueType::Snippet_ValueType_INT64:
                case snippetsample::Snippet_ValueType::Snippet_ValueType_FLOAT32:
                case snippetsample::Snippet_ValueType::Snippet_ValueType_FLOAT64:
                    std::cout << value << ",";
                break;
                case snippetsample::Snippet_ValueType::Snippet_ValueType_NUMERIC:
                case snippetsample::Snippet_ValueType::Snippet_ValueType_DATE:
                case snippetsample::Snippet_ValueType::Snippet_ValueType_TIMESTAMP:
                case snippetsample::Snippet_ValueType::Snippet_ValueType_STRING:
                case snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN:
                case snippetsample::Snippet_ValueType::Snippet_ValueType_PLUS:
                case snippetsample::Snippet_ValueType::Snippet_ValueType_MINUS:
                case snippetsample::Snippet_ValueType::Snippet_ValueType_MULTIPLE:
                case snippetsample::Snippet_ValueType::Snippet_ValueType_DIVIDE:
                    std::cout << "\"" << value << "\",";
                break;
            }
        }
        std::cout << "}," << std::endl;
    }
    std::cout << "]," << std::endl;
  }
  
  // table_offset
  {
    std::cout << "\"table_offset\" : [";
    for(int i=0;i<snippet.table_offset_size();i++){
        std::cout << snippet.table_offset(i) << ",";
    }
    std::cout << "]," << std::endl;
  }
  
  // table_offlen
  {
    std::cout << "\"table_offlen\" : [";
    for(int i=0;i<snippet.table_offlen_size();i++){
        std::cout << snippet.table_offlen(i) << ",";;
    }
    std::cout << "]," << std::endl;
  }
  
  // table_datatype
  {
    std::cout << "\"table_datatype\" : [";
    for(int i=0;i<snippet.table_datatype_size();i++){
        std::cout << snippet.table_datatype(i) << ",";;
    }
    std::cout << "]," << std::endl;
  }
  
  // BlockList
  {
    std::cout << "\"BlockList\" : []," << std::endl;
  }
  
  // table_alias
  {
    std::cout << "\"table_alias\" : \"" << snippet.table_alias() << "\"" << std::endl;
  }
  
  // column_alias
  {
    std::cout << "\"column_alias\" : [" << std::endl;
    for(int i=0;i<snippet.column_alias_size();i++){
        std::cout << "\t\"" << snippet.column_alias(i) << "\"," << std::endl;
    }
    std::cout << "]," << std::endl;
  }
  
  // column_projection
  {
    std::cout << "\"column_projection\" : [" << std::endl;    
    for(int i=0;i<snippet.column_projection_size();i++){
        auto projection = snippet.column_projection(i);
        std::cout << "\t{";        
        switch(projection.projcetion_type()){
            case snippetsample::Snippet_Projection_SelectType::Snippet_Projection_SelectType_COLUMNNAME:
            std::cout << "0,";
            break;
            case snippetsample::Snippet_Projection_SelectType::Snippet_Projection_SelectType_SUM:
            std::cout << "1,";
            break;
            case snippetsample::Snippet_Projection_SelectType::Snippet_Projection_SelectType_AVG:            
            std::cout << "2,";
            break;
            case snippetsample::Snippet_Projection_SelectType::Snippet_Projection_SelectType_COUNT:            
            std::cout << "3,";
            break;
            case snippetsample::Snippet_Projection_SelectType::Snippet_Projection_SelectType_COUNTSTAR:
            std::cout << "4,";
            break;
            case snippetsample::Snippet_Projection_SelectType::Snippet_Projection_SelectType_TOP:
            std::cout << "5,";
            break;
            case snippetsample::Snippet_Projection_SelectType::Snippet_Projection_SelectType_MIN:
            std::cout << "6,";
            break;
            case snippetsample::Snippet_Projection_SelectType::Snippet_Projection_SelectType_MAX:
            std::cout << "7,";
            break;
            case snippetsample::Snippet_Projection_SelectType::Snippet_Projection_SelectType_CASE:
            std::cout << "8,";
            break;
            case snippetsample::Snippet_Projection_SelectType::Snippet_Projection_SelectType_WHEN:
            std::cout << "9,";
            break;
            case snippetsample::Snippet_Projection_SelectType::Snippet_Projection_SelectType_THEN:
            std::cout << "10,";
            break;
            case snippetsample::Snippet_Projection_SelectType::Snippet_Projection_SelectType_ELSE:
            std::cout << "11,";
            break;
            case snippetsample::Snippet_Projection_SelectType::Snippet_Projection_SelectType_LIKE:
            std::cout << "12,";
            break;
        }
        for(int j=0;j<projection.value_size();j++){
            std::string value = projection.value(j);
            snippetsample::Snippet_ValueType value_type = projection.value_type(j);
            switch(value_type){
                case snippetsample::Snippet_ValueType::Snippet_ValueType_INT32:
                    std::cout << value << ",";
                break;
                case snippetsample::Snippet_ValueType::Snippet_ValueType_NUMERIC:
                break;
                case snippetsample::Snippet_ValueType::Snippet_ValueType_STRING:
                    std::cout << "\"" << value << "\",";
                break;
                case snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN:
                    std::cout << "\"" << value << "\",";
                break;
                case snippetsample::Snippet_ValueType::Snippet_ValueType_PLUS:
                    std::cout << "\"" << value << "\",";
                break;
                case snippetsample::Snippet_ValueType::Snippet_ValueType_MINUS:
                    std::cout << "\"" << value << "\",";
                break;
                case snippetsample::Snippet_ValueType::Snippet_ValueType_MULTIPLE:
                    std::cout << "\"" << value << "\",";
                break;
                case snippetsample::Snippet_ValueType::Snippet_ValueType_DIVIDE:
                    std::cout << "\"" << value << "\",";
                break;
            }
        }
        std::cout << "}," << std::endl;
    }
    std::cout << "]," << std::endl;
  }
  
  // column_filtering
  {
    std::cout << "\"column_filtering\" : [" << std::endl;
    for(int i=0;i<snippet.column_filtering_size();i++){
        std::cout << "\t\"" << snippet.column_filtering(i) << "\"," << std::endl;
    }
    std::cout << "]," << std::endl;
  }
  
  // Group by
  {
    std::cout << "\"Group by\" : [" << std::endl;
    for(int i=0;i<snippet.group_by_size();i++){
        std::cout << "\t\"" << snippet.group_by(i) << "\"," << std::endl;
    }
    std::cout << "]," << std::endl;
  }
  
  // Order by
  {
    std::cout << "\"Order by\" : [" << std::endl;
    for(int i=0;i<snippet.order_by_size();i++){        
        auto odr = snippet.order_by(i);
        std::cout << "\t{";
        if(odr.direction() == snippetsample::Snippet_Order_OrderDirection::Snippet_Order_OrderDirection_DESC){
            std::cout << "1,";
        }
        std::cout << "\"" << odr.column() << "\"}," << std::endl;
    }
    std::cout << "]" << std::endl;
  }

      */

      if(snippet.table_alias() == "return"){
        Result result;
        query_result = "Under Construct";
        result.set_value(query_result);
        stream->Write(result);
      }
    }
    return Status::OK;
  }
  Status Run(ServerContext* context, const Request* request, Result* result) override {
    std::cout << "Run" << std::endl;
    std::cout << "req queryid :" << request->queryid() << std::endl << std::endl;
        
    query_result = "Under Construct";

    result->set_value(query_result);

    query_result = "";
    return Status::OK;
  }
  private:
    std::unordered_map<int, std::vector<std::string>> map;
    std::string query_result = "";
};


void RunServer() {
  std::string server_address("0.0.0.0:50051");
  SnippetSampleServiceImpl service;

  ServerBuilder builder;
  // Listen on the given address without any authentication mechanism.
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  // Register "service" as the instance through which we'll communicate with
  // clients. In this case, it corresponds to an *synchronous* service.
  builder.RegisterService(&service);
  // Finally assemble the server.
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  // Wait for the server to shutdown. Note that some other thread must be
  // responsible for shutting down the server for this call to ever return.
  server->Wait();
}

int main(int argc, char** argv) {
  RunServer();

  return 0;
}