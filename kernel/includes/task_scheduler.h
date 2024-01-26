#pragma once
#include "utilities.h"
#include "tar.h"
#include "paging.h"
#include "initrd.h"
#include "process.h"


/***
 * Should create some sort of linked list of currently active processes. 
 * Also should setup some kernel variables for maintaining the current process. 
*/
int setup_task_space(); 

int create_process(char* executable_fname, int argc, char** argv);

int swap_process_in(int process_id);

void __attribute__((cdecl)) call_user();

void* get_current_process(); 

void mapUserRegionProcess(uint32_t* page_dir, uint32_t* page_table_mapping);