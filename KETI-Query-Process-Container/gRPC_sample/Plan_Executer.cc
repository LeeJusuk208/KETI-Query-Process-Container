#include "Plan_Executer.h"
#include <iostream>
#include <fstream>

//tcp-h query 1
void snippet0_0(SnippetRequest& request);
void snippet0_1(SnippetRequest& request);

//tcp-h query 5
void snippet4_0(SnippetRequest& request);
void snippet4_1(SnippetRequest& request);
void snippet4_2(SnippetRequest& request);
void snippet4_3(SnippetRequest& request);
void snippet4_4(SnippetRequest& request);
void snippet4_5(SnippetRequest& request);
void snippet4_6(SnippetRequest& request);

void Plan_Executer::Execute_Query(Storage_Engine_Interface &storageEngineInterface,Parsed_Query &parsed_query){
  std::cout << parsed_query.Get_Ori_Query() << std::endl;
  std::cout << parsed_query.Get_Parsed_Query() << std::endl;

    if(parsed_query.isGenericQuery()){

    } else {
        int query_id = Set_Query_ID();
        auto snippet_list = Gen_Snippet(parsed_query.Get_Ori_Query());
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

std::unique_ptr<std::list<SnippetRequest>> Plan_Executer::Gen_Snippet(std::string query_str){ // test code
    std::unique_ptr<std::list<SnippetRequest>> ret(new std::list<SnippetRequest>());

    if (query_str == "TPC-H_01"){ //TPC-H Query 1
	    SnippetRequest val1, val2;
        snippet0_0(val1);
        snippet0_1(val2);

        ret->push_back(SnippetRequest(val1));
        ret->push_back(SnippetRequest(val2));
    } else if(query_str == "TPC-H_05"){ //TPC-H Query 5
	    SnippetRequest val0, val1, val2, val3, val4, val5, val6;
        snippet4_0(val0);
        snippet4_1(val1);
        snippet4_2(val2);
        snippet4_3(val3);
        snippet4_4(val4);
        snippet4_5(val5);
        snippet4_6(val6);

        ret->push_back(SnippetRequest(val0));
        ret->push_back(SnippetRequest(val1));
        ret->push_back(SnippetRequest(val2));
        ret->push_back(SnippetRequest(val3));
        ret->push_back(SnippetRequest(val4));
        ret->push_back(SnippetRequest(val5));
        ret->push_back(SnippetRequest(val6));
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

void snippet0_0(SnippetRequest& request){
  std::string json_str;
  read_json(json_str,"tpch01-0");
  google::protobuf::util::JsonParseOptions options;
  options.ignore_unknown_fields = true;
  google::protobuf::util::JsonStringToMessage(json_str,&request,options);
  /*
  // set snippet type
  {
    request.set_snippet_type(1);
  }

  // set query id
  {
    request.set_query_id(0);
  }

  // set work id
  {
    request.set_work_id(0); 
  }

  // set table name
  {
    request.add_table_name("lineitem");
  }

  // set table coumns
  {
    request.add_table_col("l_orderkey");
    request.add_table_col("l_partkey");
    request.add_table_col("l_suppkey");
    request.add_table_col("l_linenumber");
    request.add_table_col("l_quantity");
    request.add_table_col("l_extendedprice");
    request.add_table_col("l_discount");
    request.add_table_col("l_tax");
    request.add_table_col("l_returnflag");
    request.add_table_col("l_linestatus");
    request.add_table_col("l_shipdate");
    request.add_table_col("l_commitdate");
    request.add_table_col("l_receiptdate");
    request.add_table_col("l_shipinstruct");
    request.add_table_col("l_shipmode");
    request.add_table_col("l_comment");
  }

  // set table filter
  {
    auto filter = request.add_table_filter();
    auto lv = new snippetsample::Snippet_Filter_FilterValue();
    auto rv = new snippetsample::Snippet_Filter_FilterValue();
    
    lv->add_value("l_shipdate",10);
    lv->add_type(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN);
    rv->add_value("1023253",7);
    rv->add_type(snippetsample::Snippet_ValueType::Snippet_ValueType_DATE);
    filter->set_allocated_lv(lv);
    filter->set_operator_(snippetsample::Snippet_Filter_OperType::Snippet_Filter_OperType_KETI_LE);
    filter->set_allocated_rv(rv);
  }

  // set table offset
  {
    request.add_table_offset(0);
    request.add_table_offset(4);
    request.add_table_offset(8);
    request.add_table_offset(12);
    request.add_table_offset(16);
    request.add_table_offset(23);
    request.add_table_offset(30);
    request.add_table_offset(37);
    request.add_table_offset(44);
    request.add_table_offset(45);
    request.add_table_offset(46);
    request.add_table_offset(49);
    request.add_table_offset(52);
    request.add_table_offset(55);
    request.add_table_offset(80);
    request.add_table_offset(90);
  }
    
  // set table offset length
  {
    request.add_table_offlen(4);
    request.add_table_offlen(4);
    request.add_table_offlen(4);
    request.add_table_offlen(4);
    request.add_table_offlen(7);
    request.add_table_offlen(7);
    request.add_table_offlen(7);
    request.add_table_offlen(7);
    request.add_table_offlen(1);
    request.add_table_offlen(1);
    request.add_table_offlen(3);
    request.add_table_offlen(3);
    request.add_table_offlen(3);
    request.add_table_offlen(25);
    request.add_table_offlen(10);
    request.add_table_offlen(44);
  }
    
  // set table datatype(each columns)
  {
    request.add_table_datatype(3);
    request.add_table_datatype(3);
    request.add_table_datatype(3);
    request.add_table_datatype(3);
    request.add_table_datatype(246);
    request.add_table_datatype(246);
    request.add_table_datatype(246);
    request.add_table_datatype(246);
    request.add_table_datatype(254);
    request.add_table_datatype(254);
    request.add_table_datatype(14);
    request.add_table_datatype(14);
    request.add_table_datatype(14);
    request.add_table_datatype(254);
    request.add_table_datatype(254);
    request.add_table_datatype(254);
  }

  // set table alias
  {
    request.set_table_alias("snippet0-0");
  }
    
  // set column alias
  {
    request.add_column_alias("l_returnflag");
    request.add_column_alias("l_linestatus");
    request.add_column_alias("sum_qty");
    request.add_column_alias("sum_base_price");
    request.add_column_alias("sum_disc_price");
    request.add_column_alias("sum_charge");
    request.add_column_alias("sum_for_avg_disc");
    request.add_column_alias("count_order");
  }
    
  // set column projection
  {
    int i32;

    auto projection = request.add_column_projection();
    projection->set_select_type(snippetsample::Snippet_Projection_SelectType::Snippet_Projection_SelectType_COLUMNNAME);
    projection->add_value_type(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN);
    projection->add_value("l_returnflag",12);

    projection = request.add_column_projection();
    projection->set_select_type(snippetsample::Snippet_Projection_SelectType::Snippet_Projection_SelectType_COLUMNNAME);
    projection->add_value_type(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN);
    projection->add_value("l_linestatus",12);

    projection = request.add_column_projection();
    projection->set_select_type(snippetsample::Snippet_Projection_SelectType::Snippet_Projection_SelectType_SUM);
    projection->add_value_type(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN);
    projection->add_value("l_quantity",10);

    projection = request.add_column_projection();
    projection->set_select_type(snippetsample::Snippet_Projection_SelectType::Snippet_Projection_SelectType_SUM);
    projection->add_value_type(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN);
    projection->add_value("l_extendedprice",15);

    projection = request.add_column_projection();
    projection->set_select_type(snippetsample::Snippet_Projection_SelectType::Snippet_Projection_SelectType_SUM);
    projection->add_value_type(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN);
    projection->add_value("l_extendedprice",15);
    projection->add_value_type(snippetsample::Snippet_ValueType::Snippet_ValueType_INT32);
    projection->add_value("1",1);
    projection->add_value_type(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN);
    projection->add_value("l_discount",10);
    projection->add_value_type(snippetsample::Snippet_ValueType::Snippet_ValueType_MINUS);
    projection->add_value("-",1);
    projection->add_value_type(snippetsample::Snippet_ValueType::Snippet_ValueType_MULTIPLE);
    projection->add_value("*",1);

    projection = request.add_column_projection();
    projection->set_select_type(snippetsample::Snippet_Projection_SelectType::Snippet_Projection_SelectType_SUM);
    projection->add_value_type(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN);
    projection->add_value("l_extendedprice",15);
    projection->add_value_type(snippetsample::Snippet_ValueType::Snippet_ValueType_INT32);
    projection->add_value("1",1);
    projection->add_value_type(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN);
    projection->add_value("l_discount",10);
    projection->add_value_type(snippetsample::Snippet_ValueType::Snippet_ValueType_MINUS);
    projection->add_value("-",1);
    projection->add_value_type(snippetsample::Snippet_ValueType::Snippet_ValueType_MULTIPLE);
    projection->add_value("*",1);
    projection->add_value_type(snippetsample::Snippet_ValueType::Snippet_ValueType_INT32);
    projection->add_value("1",1);
    projection->add_value_type(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN);
    projection->add_value("l_tax",5);
    projection->add_value_type(snippetsample::Snippet_ValueType::Snippet_ValueType_PLUS);
    projection->add_value("+",1);
    projection->add_value_type(snippetsample::Snippet_ValueType::Snippet_ValueType_MULTIPLE);
    projection->add_value("*",1);

    projection = request.add_column_projection();
    projection->set_select_type(snippetsample::Snippet_Projection_SelectType::Snippet_Projection_SelectType_AVG);
    projection->add_value_type(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN);
    projection->add_value("l_quantity",10);

    projection = request.add_column_projection();
    projection->set_select_type(snippetsample::Snippet_Projection_SelectType::Snippet_Projection_SelectType_AVG);
    projection->add_value_type(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN);
    projection->add_value("l_extendedprice",15);

    projection = request.add_column_projection();
    projection->set_select_type(snippetsample::Snippet_Projection_SelectType::Snippet_Projection_SelectType_AVG);
    projection->add_value_type(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN);
    projection->add_value("l_discount",10);

    projection = request.add_column_projection();
    projection->set_select_type(snippetsample::Snippet_Projection_SelectType::Snippet_Projection_SelectType_COUNTSTAR);
  }

  // set column filtering
  {
    request.add_column_filtering("l_returnflag");
    request.add_column_filtering("l_linestatus");
    request.add_column_filtering("l_quantity");
    request.add_column_filtering("l_extendedprice");
    request.add_column_filtering("l_discount");
    request.add_column_filtering("l_tax");
  }

  // set group by
  {
    request.add_group_by("l_returnflag");
    request.add_group_by("l_linestatus");
  }

  // set order by
  {
    auto odr = request.add_order_by();
    odr->set_column("l_returnflag");

    odr = request.add_order_by();
    odr->set_column("l_linestatus");
  }
  */
}

void snippet0_1(SnippetRequest& request){
  std::string json_str;
  read_json(json_str,"tpch01-1");
  google::protobuf::util::JsonParseOptions options;
  options.ignore_unknown_fields = true;
  google::protobuf::util::JsonStringToMessage(json_str,&request,options);
  /*
  // set snippet type
  {
    request.set_snippet_type(2);
  }
 
  // set query id
  {
    request.set_query_id(0);
  }

  // set work id
  {
    request.set_work_id(1); 
  }

  // set table name
  {
    request.add_table_name("snippet0-0");
  }

  // set table coumns
  {
    request.add_table_col("l_returnflag");
    request.add_table_col("l_linestatus");
    request.add_table_col("sum_qty");
    request.add_table_col("sum_base_price");
    request.add_table_col("sum_disc_price");
    request.add_table_col("sum_charge");
    request.add_table_col("sum_for_avg_disc");
    request.add_table_col("count_order");
  }

  // set table filter

  // set table offset
    
  // set table offset length
    
  // set table datatype(each columns)

  // set table alias
  {
    request.set_table_alias("snippet0-1");
  }
    
  // set column alias
  {
    request.add_column_alias("l_returnflag");
    request.add_column_alias("l_linestatus");
    request.add_column_alias("sum_qty");
    request.add_column_alias("sum_base_price");
    request.add_column_alias("sum_disc_price");
    request.add_column_alias("sum_charge");
    request.add_column_alias("avg_qty");
    request.add_column_alias("avg_price");
    request.add_column_alias("avg_disc");
    request.add_column_alias("count_order");
  }
    
  // set column projection
  {
    auto projection = request.add_column_projection();
    projection->set_select_type(snippetsample::Snippet_Projection_SelectType::Snippet_Projection_SelectType_COLUMNNAME);
    projection->add_value_type(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN);
    projection->add_value("l_returnflag",12);

    projection = request.add_column_projection();
    projection->set_select_type(snippetsample::Snippet_Projection_SelectType::Snippet_Projection_SelectType_COLUMNNAME);
    projection->add_value_type(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN);
    projection->add_value("l_linestatus",12);

    projection = request.add_column_projection();
    projection->set_select_type(snippetsample::Snippet_Projection_SelectType::Snippet_Projection_SelectType_COLUMNNAME);
    projection->add_value_type(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN);
    projection->add_value("sum_qty",7);

    projection = request.add_column_projection();
    projection->set_select_type(snippetsample::Snippet_Projection_SelectType::Snippet_Projection_SelectType_COLUMNNAME);
    projection->add_value_type(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN);
    projection->add_value("sum_base_price",14);

    projection = request.add_column_projection();
    projection->set_select_type(snippetsample::Snippet_Projection_SelectType::Snippet_Projection_SelectType_COLUMNNAME);
    projection->add_value_type(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN);
    projection->add_value("sum_disc_price",14);

    projection = request.add_column_projection();
    projection->set_select_type(snippetsample::Snippet_Projection_SelectType::Snippet_Projection_SelectType_COLUMNNAME);
    projection->add_value_type(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN);
    projection->add_value("sum_charge",10);

    projection = request.add_column_projection();
    projection->set_select_type(snippetsample::Snippet_Projection_SelectType::Snippet_Projection_SelectType_COLUMNNAME);
    projection->add_value_type(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN);
    projection->add_value("sum_qty",7);
    projection->add_value_type(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN);
    projection->add_value("count_order",11);
    projection->add_value_type(snippetsample::Snippet_ValueType::Snippet_ValueType_DIVIDE);
    projection->add_value("/",1);

    projection = request.add_column_projection();
    projection->set_select_type(snippetsample::Snippet_Projection_SelectType::Snippet_Projection_SelectType_COLUMNNAME);
    projection->add_value_type(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN);
    projection->add_value("sum_base_price",14);
    projection->add_value_type(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN);
    projection->add_value("count_order",11);
    projection->add_value_type(snippetsample::Snippet_ValueType::Snippet_ValueType_DIVIDE);

    projection = request.add_column_projection();
    projection->set_select_type(snippetsample::Snippet_Projection_SelectType::Snippet_Projection_SelectType_COLUMNNAME);
    projection->add_value_type(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN);
    projection->add_value("sum_for_avg_disc",16);
    projection->add_value_type(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN);
    projection->add_value("count_order",11);
    projection->add_value_type(snippetsample::Snippet_ValueType::Snippet_ValueType_DIVIDE);

    projection = request.add_column_projection();
    projection->set_select_type(snippetsample::Snippet_Projection_SelectType::Snippet_Projection_SelectType_COLUMNNAME);
    projection->add_value_type(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN);
    projection->add_value("count_order",11);
  }

  // set column filtering

  // set group by
  {
    request.add_group_by("l_returnflag");
    request.add_group_by("l_linestatus");
  }

  // set order by
  {
    auto odr = request.add_order_by();
    odr->set_column("l_returnflag");

    odr = request.add_order_by();
    odr->set_column("l_linestatus");
  }
  */
}


void snippet4_0(SnippetRequest& request){
  std::string json_str;
  read_json(json_str,"tpch05-0");
  google::protobuf::util::JsonParseOptions options;
  options.ignore_unknown_fields = true;
  google::protobuf::util::JsonStringToMessage(json_str,&request,options);
  /*
  // set snippet type
  {
    request.set_snippet_type(0);
  }
  
  // set query id
  {
    request.set_query_id(4);
  }

  // set work id
  {
    request.set_work_id(0);
  }

  // set table name
  {
    request.add_table_name("customer");
  }

  // set table coumns
  {
    request.add_table_col("c_custkey");
    request.add_table_col("c_name");
    request.add_table_col("c_address");
    request.add_table_col("c_nationkey");
    request.add_table_col("c_phone");
    request.add_table_col("c_acctbal");
    request.add_table_col("c_mktsegment");
    request.add_table_col("c_comment");
  }

  // set table filter

  // set table offset
  {
    request.add_table_offset(0);
    request.add_table_offset(4);
    request.add_table_offset(29);
    request.add_table_offset(69);
    request.add_table_offset(73);
    request.add_table_offset(88);
    request.add_table_offset(98);
    request.add_table_offset(105);
  }
    
  // set table offset length
  {
    request.add_table_offlen(4);
    request.add_table_offlen(25);
    request.add_table_offlen(40);
    request.add_table_offlen(4);
    request.add_table_offlen(15);
    request.add_table_offlen(7);
    request.add_table_offlen(10);
    request.add_table_offlen(117);
  }
    
  // set table datatype(each columns)
  {
    request.add_table_datatype(3);
    request.add_table_datatype(254);
    request.add_table_datatype(254);
    request.add_table_datatype(3);
    request.add_table_datatype(254);
    request.add_table_datatype(246);
    request.add_table_datatype(254);
    request.add_table_datatype(254);
  }

  // set table alias
  {
    request.set_table_alias("snippet4-0");
  }
    
  // set column alias
  {
    request.add_column_alias("c_custkey");
    request.add_column_alias("c_nationkey");
  }
    
  // set column projection
  {
    auto projection = request.add_column_projection();
    projection->set_select_type(snippetsample::Snippet_Projection_SelectType::Snippet_Projection_SelectType_COLUMNNAME);
    projection->add_value_type(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN);
    projection->add_value("c_custkey",9);

    projection = request.add_column_projection();
    projection->set_select_type(snippetsample::Snippet_Projection_SelectType::Snippet_Projection_SelectType_COLUMNNAME);
    projection->add_value_type(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN);
    projection->add_value("c_nationkey",11);
  }

  // set column filtering
  {
    request.add_column_filtering("c_custkey");
    request.add_column_filtering("c_nationkey");
  }
  */
}

void snippet4_1(SnippetRequest& request){
  std::string json_str;
  read_json(json_str,"tpch05-1");
  google::protobuf::util::JsonParseOptions options;
  options.ignore_unknown_fields = true;
  google::protobuf::util::JsonStringToMessage(json_str,&request,options);
  /*
  // set snippet type
  {
    request.set_snippet_type(0);
  }
  
  // set query id
  {
    request.set_query_id(4);
  }

  // set work id
  {
    request.set_work_id(1);
  }

  // set table name
  {
    request.add_table_name("orders");
  }

  // set table coumns
  {
    request.add_table_col("o_orderkey");
    request.add_table_col("o_custkey");
    request.add_table_col("o_orderstatus");
    request.add_table_col("o_totalprice");
    request.add_table_col("o_orderDATE");
    request.add_table_col("o_orderpriority");
    request.add_table_col("o_clerk");
    request.add_table_col("o_shippriority");
    request.add_table_col("o_comment");
  }

  // set table filter
  {
    int dt;

    auto filter = request.add_table_filter();
    auto lv = new snippetsample::Snippet_Filter_FilterValue();
    auto rv = new snippetsample::Snippet_Filter_FilterValue();
    
    lv->add_value("o_orderdate",11);
    lv->add_type(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN);
    rv->add_value("1020961",7);
    rv->add_type(snippetsample::Snippet_ValueType::Snippet_ValueType_DATE);
    filter->set_allocated_lv(lv);
    filter->set_operator_(snippetsample::Snippet_Filter_OperType::Snippet_Filter_OperType_KETI_GE);
    filter->set_allocated_rv(rv);
    
    filter = request.add_table_filter();
    filter->set_operator_(snippetsample::Snippet_Filter_OperType::Snippet_Filter_OperType_KETI_AND);

    filter = request.add_table_filter();
    lv = new snippetsample::Snippet_Filter_FilterValue();
    rv = new snippetsample::Snippet_Filter_FilterValue();
    
    lv->add_value("o_orderdate",11);
    lv->add_type(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN);
    rv->add_value("1021473",7);
    rv->add_type(snippetsample::Snippet_ValueType::Snippet_ValueType_DATE);
    filter->set_allocated_lv(lv);
    filter->set_operator_(snippetsample::Snippet_Filter_OperType::Snippet_Filter_OperType_KETI_LT);
    filter->set_allocated_rv(rv);
  }

  // set table offset
  {
    request.add_table_offset(0);
    request.add_table_offset(4);
    request.add_table_offset(8);
    request.add_table_offset(9);
    request.add_table_offset(17);
    request.add_table_offset(20);
    request.add_table_offset(35);
    request.add_table_offset(50);
    request.add_table_offset(54);
  }
    
  // set table offset length
  {
    request.add_table_offlen(4);
    request.add_table_offlen(4);
    request.add_table_offlen(1);
    request.add_table_offlen(8);
    request.add_table_offlen(3);
    request.add_table_offlen(15);
    request.add_table_offlen(15);
    request.add_table_offlen(4);
    request.add_table_offlen(79);
  }
    
  // set table datatype(each columns)
  {
    request.add_table_datatype(3);
    request.add_table_datatype(3);
    request.add_table_datatype(254);
    request.add_table_datatype(246);
    request.add_table_datatype(14);
    request.add_table_datatype(254);
    request.add_table_datatype(254);
    request.add_table_datatype(3);
    request.add_table_datatype(254);
  }

  // set table alias
  {
    request.set_table_alias("snippet4-1");
  }
    
  // set column alias
  {
    request.add_column_alias("o_orderkey");
    request.add_column_alias("o_custkey");
  }
    
  // set column projection
  {
    auto projection = request.add_column_projection();
    projection->set_select_type(snippetsample::Snippet_Projection_SelectType::Snippet_Projection_SelectType_COLUMNNAME);
    projection->add_value_type(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN);
    projection->add_value("l_orderkey",10);

    projection = request.add_column_projection();
    projection->set_select_type(snippetsample::Snippet_Projection_SelectType::Snippet_Projection_SelectType_COLUMNNAME);
    projection->add_value_type(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN);
    projection->add_value("o_custkey",9);
  }
  
  // set column filtering
  {
    request.add_column_filtering("o_orderkey");
    request.add_column_filtering("o_custkey");
  }
  */
}

void snippet4_2(SnippetRequest& request){
  std::string json_str;
  read_json(json_str,"tpch05-2");
  google::protobuf::util::JsonParseOptions options;
  options.ignore_unknown_fields = true;
  google::protobuf::util::JsonStringToMessage(json_str,&request,options);
  /*
  // set snippet type
  {
    request.set_snippet_type(1);
  }
  
  // set query id
  {
    request.set_query_id(4);
  }

  // set work id
  {
    request.set_work_id(2);
  }

  // set table name
  {
    request.add_table_name("lineitem");
  }

  // set table coumns
  {
    request.add_table_col("l_orderkey");
    request.add_table_col("l_partkey");
    request.add_table_col("l_suppkey");
    request.add_table_col("l_linenumber");
    request.add_table_col("l_quantity");
    request.add_table_col("l_extendedprice");
    request.add_table_col("l_discount");
    request.add_table_col("l_tax");
    request.add_table_col("l_returnflag");
    request.add_table_col("l_linestatus");
    request.add_table_col("l_shipdate");
    request.add_table_col("l_commitdate");
    request.add_table_col("l_receiptdate");
    request.add_table_col("l_shipinstruct");
    request.add_table_col("l_shipmode");
    request.add_table_col("l_comment");
  }

  // set table filter

  // set table offset
  {
    request.add_table_offset(0);
    request.add_table_offset(4);
    request.add_table_offset(8);
    request.add_table_offset(12);
    request.add_table_offset(16);
    request.add_table_offset(23);
    request.add_table_offset(30);
    request.add_table_offset(37);
    request.add_table_offset(44);
    request.add_table_offset(45);
    request.add_table_offset(46);
    request.add_table_offset(49);
    request.add_table_offset(52);
    request.add_table_offset(55);
    request.add_table_offset(80);
    request.add_table_offset(90);
  }
    
  // set table offset length
  {
    request.add_table_offlen(4);
    request.add_table_offlen(4);
    request.add_table_offlen(4);
    request.add_table_offlen(4);
    request.add_table_offlen(7);
    request.add_table_offlen(7);
    request.add_table_offlen(7);
    request.add_table_offlen(7);
    request.add_table_offlen(1);
    request.add_table_offlen(1);
    request.add_table_offlen(3);
    request.add_table_offlen(3);
    request.add_table_offlen(3);
    request.add_table_offlen(25);
    request.add_table_offlen(10);
    request.add_table_offlen(44);
  }
    
  // set table datatype(each columns)
  {
    request.add_table_datatype(3);
    request.add_table_datatype(3);
    request.add_table_datatype(3);
    request.add_table_datatype(3);
    request.add_table_datatype(246);
    request.add_table_datatype(246);
    request.add_table_datatype(246);
    request.add_table_datatype(246);
    request.add_table_datatype(254);
    request.add_table_datatype(254);
    request.add_table_datatype(14);
    request.add_table_datatype(14);
    request.add_table_datatype(14);
    request.add_table_datatype(254);
    request.add_table_datatype(254);
    request.add_table_datatype(254);
  }

  // set table alias
  {
    request.set_table_alias("snippet4-2");
  }
    
  // set column alias
  {
    request.add_column_alias("l_orderkey");
    request.add_column_alias("l_suppkey");
    request.add_column_alias("revenue");
  }
    
  // set column projection
  {
    int i32;

    auto projection = request.add_column_projection();
    projection->set_select_type(snippetsample::Snippet_Projection_SelectType::Snippet_Projection_SelectType_COLUMNNAME);
    projection->add_value_type(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN);
    projection->add_value("l_orderkey",10);

    projection = request.add_column_projection();
    projection->set_select_type(snippetsample::Snippet_Projection_SelectType::Snippet_Projection_SelectType_COLUMNNAME);
    projection->add_value_type(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN);
    projection->add_value("l_suppkey",9);

    projection = request.add_column_projection();
    projection->set_select_type(snippetsample::Snippet_Projection_SelectType::Snippet_Projection_SelectType_SUM);
    projection->add_value_type(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN);
    projection->add_value("l_extendedprice",15);
    projection->add_value_type(snippetsample::Snippet_ValueType::Snippet_ValueType_INT32);
    projection->add_value("1",1);
    projection->add_value_type(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN);
    projection->add_value("l_discount",10);
    projection->add_value_type(snippetsample::Snippet_ValueType::Snippet_ValueType_MINUS);
    projection->add_value("-",1);
    projection->add_value_type(snippetsample::Snippet_ValueType::Snippet_ValueType_MULTIPLE);
    projection->add_value("*",1);
  }

  // set column filtering
  {
    request.add_column_filtering("l_orderkey");
    request.add_column_filtering("l_suppkey");
    request.add_column_filtering("l_extendedprice");
    request.add_column_filtering("l_discount");
  }

  // set group by

  // set order by
  */
}

void snippet4_3(SnippetRequest& request){
  std::string json_str;
  read_json(json_str,"tpch05-3");
  google::protobuf::util::JsonParseOptions options;
  options.ignore_unknown_fields = true;
  google::protobuf::util::JsonStringToMessage(json_str,&request,options);
  /*
  // set snippet type
  {
    request.set_snippet_type(0);
  }
  
  // set query id
  {
    request.set_query_id(4);
  }

  // set work id
  {
    request.set_work_id(3);
  }

  // set table name
  {
    request.add_table_name("supplier");
  }

  // set table coumns
  {
    request.add_table_col("s_suppkey");
    request.add_table_col("s_name");
    request.add_table_col("s_address");
    request.add_table_col("s_nationkey");
    request.add_table_col("s_phone");
    request.add_table_col("s_acctbal");
    request.add_table_col("s_comment");
  }

  // set table filter

  // set table offset
  {
    request.add_table_offset(0);
    request.add_table_offset(4);
    request.add_table_offset(29);
    request.add_table_offset(69);
    request.add_table_offset(73);
    request.add_table_offset(88);
    request.add_table_offset(95);
  }
    
  // set table offset length
  {
    request.add_table_offlen(4);
    request.add_table_offlen(25);
    request.add_table_offlen(40);
    request.add_table_offlen(4);
    request.add_table_offlen(15);
    request.add_table_offlen(7);
    request.add_table_offlen(101);
  }
    
  // set table datatype(each columns)
  {
    request.add_table_datatype(3);
    request.add_table_datatype(254);
    request.add_table_datatype(254);
    request.add_table_datatype(3);
    request.add_table_datatype(254);
    request.add_table_datatype(246);
    request.add_table_datatype(254);
  }

  // set table alias
  {
    request.set_table_alias("snippet4-3");
  }
    
  // set column alias
  {
    request.add_column_alias("s_suppkey");
    request.add_column_alias("s_nationkey");
  }
    
  // set column projection
  {
    auto projection = request.add_column_projection();
    projection->set_select_type(snippetsample::Snippet_Projection_SelectType::Snippet_Projection_SelectType_COLUMNNAME);
    projection->add_value_type(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN);
    projection->add_value("s_suppkey",9);

    projection = request.add_column_projection();
    projection->set_select_type(snippetsample::Snippet_Projection_SelectType::Snippet_Projection_SelectType_COLUMNNAME);
    projection->add_value_type(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN);
    projection->add_value("s_nationkey",11);
  }

  // set column filtering
  {
    request.add_column_filtering("s_suppkey");
    request.add_column_filtering("s_nationkey");
  }
  */
}

void snippet4_4(SnippetRequest& request){
  std::string json_str;
  read_json(json_str,"tpch05-4");
  google::protobuf::util::JsonParseOptions options;
  options.ignore_unknown_fields = true;
  google::protobuf::util::JsonStringToMessage(json_str,&request,options);
  /*
  // set snippet type
  {
    request.set_snippet_type(0);
  }
  
  // set query id
  {
    request.set_query_id(4);
  }

  // set work id
  {
    request.set_work_id(4); 
  }

  // set table name
  {
    request.add_table_name("nation");
  }

  // set table coumns
  {
    request.add_table_col("n_nationkey");
    request.add_table_col("n_name");
    request.add_table_col("n_regionkey");
    request.add_table_col("n_comment");
  }

  // set table filter

  // set table offset
  {
    request.add_table_offset(0);
    request.add_table_offset(4);
    request.add_table_offset(29);
    request.add_table_offset(32);
  }
    
  // set table offset length
  {
    request.add_table_offlen(4);
    request.add_table_offlen(25);
    request.add_table_offlen(4);
    request.add_table_offlen(152);
  }
    
  // set table datatype(each columns)
  {
    request.add_table_datatype(3);
    request.add_table_datatype(254);
    request.add_table_datatype(3);
    request.add_table_datatype(254);
  }

  // set table alias
  {
    request.set_table_alias("snippet4-4");
  }
    
  // set column alias
  {
    request.add_column_alias("n_nationkey");
    request.add_column_alias("n_name");
    request.add_column_alias("n_regionkey");
  }
    
  // set column projection
  {
    auto projection = request.add_column_projection();
    projection->set_select_type(snippetsample::Snippet_Projection_SelectType::Snippet_Projection_SelectType_COLUMNNAME);
    projection->add_value_type(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN);
    projection->add_value("n_nationkey",11);

    projection = request.add_column_projection();
    projection->set_select_type(snippetsample::Snippet_Projection_SelectType::Snippet_Projection_SelectType_COLUMNNAME);
    projection->add_value_type(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN);
    projection->add_value("n_name",6);

    projection = request.add_column_projection();
    projection->set_select_type(snippetsample::Snippet_Projection_SelectType::Snippet_Projection_SelectType_COLUMNNAME);
    projection->add_value_type(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN);
    projection->add_value("n_regionkey",11);
  }

  // set column filtering
  {
    request.add_column_filtering("n_nationkey");
    request.add_column_filtering("n_name");
    request.add_column_filtering("n_regionkey");
  }  

  // set group by

  // set order by
  */
}

void snippet4_5(SnippetRequest& request){
  std::string json_str;
  read_json(json_str,"tpch05-5");
  google::protobuf::util::JsonParseOptions options;
  options.ignore_unknown_fields = true;
  google::protobuf::util::JsonStringToMessage(json_str,&request,options);
  /*
  // set snippet type
  {
    request.set_snippet_type(0);
  }
  
  // set query id
  {
    request.set_query_id(4);
  }

  // set work id
  {
    request.set_work_id(5); 
  }

  // set table name
  {
    request.add_table_name("region");
  }

  // set table coumns
  {
    request.add_table_col("r_regionkey");
    request.add_table_col("r_name");
    request.add_table_col("r_comment");
  }

  // set table filter
  {
    auto filter = request.add_table_filter();
    auto lv = new snippetsample::Snippet_Filter_FilterValue();
    auto rv = new snippetsample::Snippet_Filter_FilterValue();
    
    lv->add_value("r_name",6);
    lv->add_type(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN);
    rv->add_value("middle east",11);
    rv->add_type(snippetsample::Snippet_ValueType::Snippet_ValueType_STRING);
    filter->set_allocated_lv(lv);
    filter->set_operator_(snippetsample::Snippet_Filter_OperType::Snippet_Filter_OperType_KETI_ET);
    filter->set_allocated_rv(rv);
  }

  // set table offset
  {
    request.add_table_offset(0);
    request.add_table_offset(4);
    request.add_table_offset(29);
  }
    
  // set table offset length
  {
    request.add_table_offlen(4);
    request.add_table_offlen(25);
    request.add_table_offlen(152);
  }

  // set table datatype(each columns)
  {
    request.add_table_datatype(3);
    request.add_table_datatype(254);
    request.add_table_datatype(254);
  }

  // set table alias
  {
    request.set_table_alias("snippet4-5");
  }
   
  // set column alias
  {
    request.add_column_alias("r_regionkey");
  }
  // set column projection
  {
    auto projection = request.add_column_projection();
    projection->set_select_type(snippetsample::Snippet_Projection_SelectType::Snippet_Projection_SelectType_COLUMNNAME);
    projection->add_value_type(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN);
    projection->add_value("r_regionkey",11);
  }

  // set column filtering
  {
    request.add_column_filtering("r_regionkey");
  }
  */
}

void snippet4_6(SnippetRequest& request){
  std::string json_str;
  read_json(json_str,"tpch05-6");
  google::protobuf::util::JsonParseOptions options;
  options.ignore_unknown_fields = true;
  google::protobuf::util::JsonStringToMessage(json_str,&request,options);
}