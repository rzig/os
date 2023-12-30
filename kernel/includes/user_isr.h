#pragma once
#include "keyboard.h"
#include "rtc.h"
#include "utilities.h"
#include "pic.h"
//eventually add syscall support

void execute_user_int(exn_info int_data);