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

>   ODBC

## How To Install
-------------
# How To Build
1. Install gRPC
```bash
apt install -y cmake
apt install -y build-essential autoconf libtool pkg-config
git clone --recurse-submodules -b v1.46.3 --depth 1 --shallow-submodules https://github.com/grpc/grpc
cd grpc
mkdir -p cmake/build
cd cmake/build
cmake -DgRPC_INSTALL=ON \
      -DgRPC_BUILD_TESTS=OFF \
      -DCMAKE_INSTALL_PREFIX=$MY_INSTALL_DIR \
      ../..
make –j
make install
cd ../..
```

2. Install cpprestSDK
```bash
apt-get install libcpprest-dev
```

3. Install RapidJSON
```bash
apt-get install -y rapidjson-dev
```

4. Install ODBC
```bash
wget http://www.unixodbc.org/unixODBC-2.3.7.tar.gz
tar xvzf unixODBC-2.3.7.tar.gz
cd unixODBC-2.3.7/
./configure --prefix=/
make -j
make install
```

5. Clone KETI-Query-Process-Container
```bash
git clone https://github.com/opencsd/KETI-Query-Process-Container.git
cd KETI-Query-Process-Container/gRPC-sample/cmake/build/
```

6. Build
```bash
cmake ../..
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
message SnippetRequest {
  SnippetType type = 1;
  Snippet snippet = 2;
}
message Snippet {
  int32 query_ID = 1;
  int32 work_ID = 2;
  repeated string table_name = 3;
  repeated string table_col = 4;
  repeated Filter table_filter = 5;
  Dependency dependency = 6;
  repeated int32 table_offset = 7;
  repeated int32 table_offlen = 8;
  repeated int32 table_datatype = 9;
  string table_alias = 10;
  repeated string column_alias = 11;
  repeated Projection column_projection = 12;
  repeated string column_filtering = 13;
  repeated string group_by = 14;
  Order order_by = 15;
  int32 limit = 16;
}
```

## REST Server(DB_Connector_Instance.h DB_Connector_Instance.cpp)
-------------

## gRPC Client(Storage_Engine_Interface.h)
-------------
### OpenStream
-------------
* The start point of gRPC
* Open Stream for repeated data transmission

### SendSnippet
-------------
* Snippet sending method
* Called repeatedly to perform a query

### CloseStream
-------------
* The end point of gRPC
* Close Stream

## gRPC Server(storage_engine_instance.cc)
-------------
### SetSnippet
-------------
* Receive Snippet and convert to JSON

## Governance
-------------
This work was supported by Institute of Information & communications Technology Planning & Evaluation (IITP) grant funded by the Korea government(MSIT) (No.2021-0-00862, Development of DBMS storage engine technology to minimize massive data movement)

## Others
-------------
Due to the structure change, in the first half of the year, we worked on local repositories and private github.
> https://github.com/KETI-OpenCSD/Query-Process-Container
