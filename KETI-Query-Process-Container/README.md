## Introduction of KETI-OpenCSD Query-Process-Container
-------------
![Alt text](/%EC%82%AC%EC%A7%84/pushdown.jpg)

Query-Process-Container for KETI-OpenCSD Platform

Developed by KETI

## Contents
-------------
[1. Requirement](#requirement)

[2. How To Install](#How-To-Install)

[3. Modules](#modules)

[4. Governance](#governance)

## Requirement
-------------
>   gRPC

>   cpprestSDK

>   RapidJSON

## How To Install
-------------
# How To Build
1. Clone KETI-Query-Process-Container
```bash
git clone https://github.com/opencsd/KETI-Query-Process-Container.git
cd KETI-Query-Process-Container/gRPC-sample/cmake/build/
```

2. Build
```bash
cmake -DCMAKE_PREFIX_PATH=$MY_INSTALL_DIR ../..
make -j
```

## gRPC Protobuf
-------------
### SnippetRequest
-------------
```protobuf
message SnippetRequest {
  int32 type = 1;
  Snippet snippet = 2;
}
```

### Snippet
-------------
```protobuf
message Snippet {
  int32 query_ID = 1;
  int32 work_ID = 2;
  repeated string table_name = 3;
  repeated string table_col = 4;
  repeated Filter table_filter = 5;
  repeated int32 table_offset = 6;
  repeated int32 table_offlen = 7;
  repeated int32 table_datatype = 8;
  string table_alias = 9;
  repeated string column_alias = 10;
  repeated Projection column_projection = 11;
  repeated string column_filtering = 12;
  repeated string group_by = 13;
  repeated Order order_by = 14;
}
```

## REST Server(DB_Connector_Instance.h DB_Connector_Instance.cpp)
-------------

## gRPC Client(Storage_Engine_Interface.h)
-------------
### OpenStream
-------------
The start point of gRPC
Open Stream for repeated data transmission

### SendSnippet
-------------
Snippet sending method
Called repeatedly to perform a query

### CloseStream
-------------
The end point of gRPC
Close Stream

## gRPC Server(storage_engine_instance.cc)
-------------
### SetSnippet
-------------
Receive Snippet and convert to JSON

## Governance
-------------
This work was supported by Institute of Information & communications Technology Planning & Evaluation (IITP) grant funded by the Korea government(MSIT) (No.2021-0-00862, Development of DBMS storage engine technology to minimize massive data movement)

## Others
-------------
Due to the structure change, in the first half of the year, we worked on local repositories and private github.
> https://github.com/KETI-OpenCSD/Query-Process-Container
