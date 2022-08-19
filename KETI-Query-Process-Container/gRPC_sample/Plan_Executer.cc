#include "Plan_Executer.h"

void snippet0_0(Snippet& request);
void snippet0_1(Snippet& request);

void Plan_Executer::Execute_Query(Storage_Engine_Interface &storageEngineInterface,Parsed_Query &parsed_query){
    if(parsed_query.isGenericQuery()){

    } else {
        int query_id = Set_Query_ID();
        auto snippet_list = Gen_Snippet(query_id);
        std::list<Snippet>::iterator iter = snippet_list->begin();
        
        storageEngineInterface.OpenStream();
        for(;iter != snippet_list->end();iter++){
            storageEngineInterface.SendSnippet(*iter);
        }
        storageEngineInterface.GetReturn();
        storageEngineInterface.CloseStream();

        //storageEngineInterface.Run(query_id);
    }
}

int Plan_Executer::Set_Query_ID(){ // test code
    return 0;
}

std::unique_ptr<std::list<Snippet>> Plan_Executer::Gen_Snippet(int query_id){ // test code
    std::unique_ptr<std::list<Snippet>> ret(new std::list<Snippet>());

    switch (query_id)
    {
    case 0:{ //TPC-H Query 1
	    Snippet val1, val2;
        snippet0_0(val1);
        snippet0_1(val2);

        ret->push_back(Snippet(val1));
        ret->push_back(Snippet(val2));
    }
    break;
    
    default:
        break;
    }
	
    return ret;
}


void snippet0_0(Snippet& request){  
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
    int dt;

    auto filter = request.add_table_filter();
    filter->set_operator_(snippetsample::Snippet_Filter_OperType::Snippet_Filter_OperType_KETI_LE);
    auto sany = filter->add_sany();
    sany->set_snippettype(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN_NAME);
    sany->set_value("l_shipdate",10);
    
    sany = filter->add_sany();
    sany->set_snippettype(snippetsample::Snippet_ValueType::Snippet_ValueType_DATE);
    dt = 1023253;
    sany->set_value(&dt,sizeof(dt));
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
    projection->set_projcetiontype(snippetsample::Snippet_Projection_ProjectionType::Snippet_Projection_ProjectionType_DEFAULT);
    auto sany = projection->add_sany();
    sany->set_snippettype(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN_NAME);
    sany->set_value("l_returnflag",12);

    projection = request.add_column_projection();
    projection->set_projcetiontype(snippetsample::Snippet_Projection_ProjectionType::Snippet_Projection_ProjectionType_DEFAULT);
    sany = projection->add_sany();
    sany->set_snippettype(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN_NAME);
    sany->set_value("l_linestatus",12);

    projection = request.add_column_projection();
    projection->set_projcetiontype(snippetsample::Snippet_Projection_ProjectionType::Snippet_Projection_ProjectionType_SUM);
    sany = projection->add_sany();
    sany->set_snippettype(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN_NAME);
    sany->set_value("l_quantity",10);

    projection = request.add_column_projection();
    projection->set_projcetiontype(snippetsample::Snippet_Projection_ProjectionType::Snippet_Projection_ProjectionType_SUM);
    sany = projection->add_sany();
    sany->set_snippettype(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN_NAME);
    sany->set_value("l_extendedprice",15);

    projection = request.add_column_projection();
    projection->set_projcetiontype(snippetsample::Snippet_Projection_ProjectionType::Snippet_Projection_ProjectionType_SUM);
    sany = projection->add_sany();
    sany->set_snippettype(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN_NAME);
    sany->set_value("l_extendedprice",15);
    
    sany = projection->add_sany();
    sany->set_snippettype(snippetsample::Snippet_ValueType::Snippet_ValueType_INT32);
    i32 = 1;
    sany->set_value(&i32,sizeof(i32));

    sany = projection->add_sany();
    sany->set_snippettype(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN_NAME);
    sany->set_value("l_discount",10);

    sany = projection->add_sany();
    sany->set_snippettype(snippetsample::Snippet_ValueType::Snippet_ValueType_OPERATOR);
    sany->set_value("-",1); 

    sany = projection->add_sany();
    sany->set_snippettype(snippetsample::Snippet_ValueType::Snippet_ValueType_OPERATOR);
    sany->set_value("*",1);

    projection = request.add_column_projection();
    projection->set_projcetiontype(snippetsample::Snippet_Projection_ProjectionType::Snippet_Projection_ProjectionType_SUM);
    sany = projection->add_sany();
    sany->set_snippettype(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN_NAME);
    sany->set_value("l_extendedprice",15);
    
    sany = projection->add_sany();
    sany->set_snippettype(snippetsample::Snippet_ValueType::Snippet_ValueType_INT32);
    i32 = 1;
    sany->set_value(&i32,sizeof(i32));

    sany = projection->add_sany();
    sany->set_snippettype(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN_NAME);
    sany->set_value("l_discount",10);

    sany = projection->add_sany();
    sany->set_snippettype(snippetsample::Snippet_ValueType::Snippet_ValueType_OPERATOR);
    sany->set_value("-",1); 

    sany = projection->add_sany();
    sany->set_snippettype(snippetsample::Snippet_ValueType::Snippet_ValueType_OPERATOR);
    sany->set_value("*",1);
    
    sany = projection->add_sany();
    sany->set_snippettype(snippetsample::Snippet_ValueType::Snippet_ValueType_INT32);
    i32 = 1;
    sany->set_value(&i32,sizeof(i32));

    sany = projection->add_sany();
    sany->set_snippettype(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN_NAME);
    sany->set_value("l_tax",5);

    sany = projection->add_sany();
    sany->set_snippettype(snippetsample::Snippet_ValueType::Snippet_ValueType_OPERATOR);
    sany->set_value("+",1); 

    sany = projection->add_sany();
    sany->set_snippettype(snippetsample::Snippet_ValueType::Snippet_ValueType_OPERATOR);
    sany->set_value("*",1);

    projection = request.add_column_projection();
    projection->set_projcetiontype(snippetsample::Snippet_Projection_ProjectionType::Snippet_Projection_ProjectionType_AVG);
    sany = projection->add_sany();
    sany->set_snippettype(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN_NAME);
    sany->set_value("l_quantity",10);

    projection = request.add_column_projection();
    projection->set_projcetiontype(snippetsample::Snippet_Projection_ProjectionType::Snippet_Projection_ProjectionType_AVG);
    sany = projection->add_sany();
    sany->set_snippettype(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN_NAME);
    sany->set_value("l_extendedprice",15);

    projection = request.add_column_projection();
    projection->set_projcetiontype(snippetsample::Snippet_Projection_ProjectionType::Snippet_Projection_ProjectionType_AVG);
    sany = projection->add_sany();
    sany->set_snippettype(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN_NAME);
    sany->set_value("l_discount",10);

    projection = request.add_column_projection();
    projection->set_projcetiontype(snippetsample::Snippet_Projection_ProjectionType::Snippet_Projection_ProjectionType_COUNT);
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
}

void snippet0_1(Snippet& request){ 
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
    projection->set_projcetiontype(snippetsample::Snippet_Projection_ProjectionType::Snippet_Projection_ProjectionType_DEFAULT);
    auto sany = projection->add_sany();
    sany->set_snippettype(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN_NAME);
    sany->set_value("l_returnflag",12);

    projection = request.add_column_projection();
    projection->set_projcetiontype(snippetsample::Snippet_Projection_ProjectionType::Snippet_Projection_ProjectionType_DEFAULT);
    sany = projection->add_sany();
    sany->set_snippettype(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN_NAME);
    sany->set_value("l_linestatus",12);

    projection = request.add_column_projection();
    projection->set_projcetiontype(snippetsample::Snippet_Projection_ProjectionType::Snippet_Projection_ProjectionType_DEFAULT);
    sany = projection->add_sany();
    sany->set_snippettype(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN_NAME);
    sany->set_value("sum_qty",7);

    projection = request.add_column_projection();
    projection->set_projcetiontype(snippetsample::Snippet_Projection_ProjectionType::Snippet_Projection_ProjectionType_DEFAULT);
    sany = projection->add_sany();
    sany->set_snippettype(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN_NAME);
    sany->set_value("sum_base_price",15);

    projection = request.add_column_projection();
    projection->set_projcetiontype(snippetsample::Snippet_Projection_ProjectionType::Snippet_Projection_ProjectionType_DEFAULT);
    sany = projection->add_sany();
    sany->set_snippettype(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN_NAME);
    sany->set_value("sum_disc_price",15);

    projection = request.add_column_projection();
    projection->set_projcetiontype(snippetsample::Snippet_Projection_ProjectionType::Snippet_Projection_ProjectionType_DEFAULT);
    sany = projection->add_sany();
    sany->set_snippettype(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN_NAME);
    sany->set_value("sum_charge",10);

    projection = request.add_column_projection();
    projection->set_projcetiontype(snippetsample::Snippet_Projection_ProjectionType::Snippet_Projection_ProjectionType_DEFAULT);
    sany = projection->add_sany();
    sany->set_snippettype(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN_NAME);
    sany->set_value("sum_qty",7);
    
    sany = projection->add_sany();
    sany->set_snippettype(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN_NAME);
    sany->set_value("count_order",11);
    
    sany = projection->add_sany();
    sany->set_snippettype(snippetsample::Snippet_ValueType::Snippet_ValueType_OPERATOR);
    sany->set_value("/",1);

    projection = request.add_column_projection();
    projection->set_projcetiontype(snippetsample::Snippet_Projection_ProjectionType::Snippet_Projection_ProjectionType_DEFAULT);
    sany = projection->add_sany();
    sany->set_snippettype(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN_NAME);
    sany->set_value("sum_base_price",14);
    
    sany = projection->add_sany();
    sany->set_snippettype(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN_NAME);
    sany->set_value("count_order",11);
    
    sany = projection->add_sany();
    sany->set_snippettype(snippetsample::Snippet_ValueType::Snippet_ValueType_OPERATOR);
    sany->set_value("/",1);

    projection = request.add_column_projection();
    projection->set_projcetiontype(snippetsample::Snippet_Projection_ProjectionType::Snippet_Projection_ProjectionType_DEFAULT);
    sany = projection->add_sany();
    sany->set_snippettype(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN_NAME);
    sany->set_value("sum_for_avg_disc",16);
    
    sany = projection->add_sany();
    sany->set_snippettype(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN_NAME);
    sany->set_value("count_order",11);
    
    sany = projection->add_sany();
    sany->set_snippettype(snippetsample::Snippet_ValueType::Snippet_ValueType_OPERATOR);
    sany->set_value("/",1);

    projection = request.add_column_projection();
    projection->set_projcetiontype(snippetsample::Snippet_Projection_ProjectionType::Snippet_Projection_ProjectionType_DEFAULT);
    sany = projection->add_sany();
    sany->set_snippettype(snippetsample::Snippet_ValueType::Snippet_ValueType_COLUMN_NAME);
    sany->set_value("count_order",11);
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
}

