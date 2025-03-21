#pragma once
#include <iostream>

#define PANIC(msg) do_panic( msg, __LINE__, __FILE__, __func__ );

void do_panic(const std::string& panic_msg, size_t line_no, const char* file_name, const char* function);

// sets up error handler for both C++ and other errors
void init_error_manager();

