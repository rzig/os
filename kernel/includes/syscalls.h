#pragma once
#include "utilities.h"

void __attribute__((cdecl)) sysc_parser(); // the values that we want should be pushed in the appropriate registers? 

void handle_syscall(exn_info register_values);
