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
>   MySQL 5.6(Storage Engine : MyROCSK by KETI-Version)

>   RapidJSON

## How To Install
-------------
# How To Build
1. Clone Myrocks
```bash
git clone https://github.com/facebook/mysql-5.6.git
cd myrocks
```
2. Query-Process-Container
```bash
git clone 'Query-Process-Container address'
```

3. Replace Source Code

4. Build
```bash
./build.sh
```

## Handler APIs
-------------
### rnd_init
-------------
Initializes a handler for table scanning.

Request a Scan operation to the Storage Engine Node and initialize the buffer

### rnd_next
-------------
Reads the next row from buffer and returns it to the server.

### parse_cond
-------------
Parsing Where clauses and performing arithmetic operations

### req_scanned_block
-------------
Request Scanned Data Blocks to Storage Engine Nodes

## Governance
-------------
This work was supported by Institute of Information & communications Technology Planning & Evaluation (IITP) grant funded by the Korea government(MSIT) (No.2021-0-00862, Development of DBMS storage engine technology to minimize massive data movement)

## Others
-------------
Due to the structure change, in the first half of the year, we worked on local repositories and private github.
> https://github.com/KETI-OpenCSD/Query-Process-Container
