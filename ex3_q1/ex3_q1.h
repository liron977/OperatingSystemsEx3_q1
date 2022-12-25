#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h> 
#ifndef ex3_q1
#define ex3_q1
#define GRADES_FILE "all_std.txt"
#define MAX_LINE_LENGTH 80

void get_student_average(char* line);
void report_data_summary(int num_stud);
FILE* open_output_file(char* open_mode);
void read_data_from_file(void* file_name_input);

#endif