#pragma once

class Parsed_Query {
public:
    Parsed_Query(std::string query){
        ori_query_ = query;
        query_type_ = Parsed_Query_Type::GenericQuery;

        if(ori_query_ == "TPC-H_01") {
            parsed_query_ = "SELECT l_returnflag,\n\
       l_linestatus,\n\
       SUM(l_quantity)                                           AS sum_qty,\n\
       SUM(l_extendedprice)                                      AS\n\
       sum_base_price,\n\
       SUM(l_extendedprice * ( 1 - l_discount ))                 AS\n\
       sum_disc_price,\n\
       SUM(l_extendedprice * ( 1 - l_discount ) * ( 1 + l_tax )) AS sum_charge,\n\
       Avg(l_quantity)                                           AS avg_qty,\n\
       Avg(l_extendedprice)                                      AS avg_price,\n\
       Avg(l_discount)                                           AS avg_disc,\n\
       Count(*)                                                  AS count_order\n\
FROM   lineitem\n\
WHERE  l_shipdate <= DATE ('1998-12-01') - interval '108' day\n\
GROUP  BY l_returnflag,\n\
          l_linestatus\n\
ORDER  BY l_returnflag,\n\
          l_linestatus;";
        } else if(ori_query_ == "TPC-H_05"){ //TPC-H Query 5
            parsed_query_ = "select \n\
    n_name, \n\
    sum(l_extendedprice * (1 - l_discount)) as revenue \n\
from \n\
    customer, \n\
    orders, \n\
    lineitem, \n\
    supplier, \n\
    nation, \n\
    region \n\
where \n\
    c_custkey = o_custkey and \n\
    l_orderkey = o_orderkey and \n\
    l_suppkey = s_suppkey and \n\
    c_nationkey = s_nationkey and \n\
    s_nationkey = n_nationkey and \n\
    n_regionkey = r_regionkey and \n\
    r_name = 'middle east' and \n\
    o_orderdate >= date '1994-01-01' and \n\
    o_orderdate < date '1994-01-01' + interval '1' year\n\
group by \n\
    n_name \n\
order by \n\
    revenue desc;";
        }
    }
    
    bool isGenericQuery(){
        return (query_type_ == Parsed_Query_Type::GenericQuery) ? true : false;
    }

    void Set_Query_Type_As_PushdownQuery(){
        query_type_ = Parsed_Query_Type::PushdownQuery;
    }

    enum Parsed_Query_Type{
        GenericQuery, // Default
        PushdownQuery
    };

    std::string Get_Parsed_Query(){
        return parsed_query_;
    }
    std::string Get_Ori_Query(){
        return ori_query_;
    }

private:
    std::string ori_query_;
    std::string parsed_query_;
    Parsed_Query_Type query_type_;
};