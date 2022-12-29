#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h> 
#ifndef ex3_q1
#define ex3_q1
#define GRADES_FILE "all_std.txt"
#define MAX_LINE_LENGTH 80
#define MAX_FILES 10

void get_student_average(char* line);
void* read_data_from_file(void* file_name_input);
void handle_done_threads();
void wait_for_threads(pthread_t threads[10]);
void destroy();
void divide_work(int agrc, pthread_t threads[MAX_FILES], char* argv[]);
void update_avg_per_student(char* student_name, double avg);
#endif