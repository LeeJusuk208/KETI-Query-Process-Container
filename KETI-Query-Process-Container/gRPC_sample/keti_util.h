#ifndef KETI_UTIL_H_INCLUDED
#define KETI_UTIL_H_INCLUDED

#pragma once

#include <iostream>

inline void keti_log(std::string id, std::string msg){
    std::cout << "[" << id << "] " << msg << std::endl;
}

#endif // KETI_UTIL_H_INCLUDED