#pragma once
#include "keyboard.h"
#include "pic.h"
#include "rtc.h"
#include "utilities.h"
// eventually add syscall support

void execute_user_int(exn_info int_data);
