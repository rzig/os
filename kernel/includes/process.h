#pragma once
#include "utilities.h"
#include "paging.h"
#include "tar.h"

void* init_process(char* executable_fname, int argc, char** argv);
void* setup_files(void* process_addr);
void* setup_pagedir(void* process_addr); 
void* setup_page_tables(void* process_addr);
char** setup_args(char** argv, int argc);
void map_region(void* process_addr);
void pass_args(void* process_addr, int argc, char** argv); // perhaps we just store these above the stack and pass a pointer
void setup_memory(void* process_addr);

void* get_page_dir(void* process_addr);
int get_argc(void* process_addr);
char** get_argv(void* process_addr);

void* get_file(void* process_addr,int fd);
void* write_file(void* process_addr,int fd, char* info, size_t size);
char* read_file(void* process_addr,int fd, size_t size);
int open_file(void* process_addr); 
void close_file(void* process_addr,int fd);

void addProcessUserPage(void* process_addr, uint32_t virt_addr);
void mapProcessUserRegion(void* process_addr, uint32_t* page_dir, uint32_t* page_table_mapping, uint32_t desired_virt_addr, uint32_t region_size);