#include "ex3_q1.h"
#include "ex3_q1_given.h"

struct all_students all_stud;
pthread_mutex_t filleMutex= PTHREAD_MUTEX_INITIALIZER;

int main(int agrc, char* argv[]) {
    int num_stud = 0;
    FILE* output_file = NULL;
    char* input_file_name;
    pthread_t threads[10];

  
    for (int i = 2; i < agrc; i++) {
        input_file_name = argv[i];
     
        pthread_create(&threads[i - 2], NULL, read_data_from_file, (void*)input_file_name);
 
    }

  
    //report_data_summary(num_stud);
    pthread_exit(NULL);
}
FILE* open_output_file(char* open_mode) {
    FILE* output_file = NULL;

    if (strcmp(open_mode, "-t") == 0) {
        output_file = fopen(GRADES_FILE, "w");
        fseek(output_file, 0, SEEK_SET);
    }
    else if (strcmp(open_mode, "-a") == 0) {
        output_file = fopen(GRADES_FILE, "a");
    }

    return output_file;
}

void read_data_from_file(void* file_name_input) {
    char* file_name = (char*)file_name_input;
    printf("%s file_name\n", file_name);
    long threadId = pthread_self();
    printf("%ld threadId \n", threadId);
    FILE* file = fopen(file_name, "r");
    char line[MAX_LINE_LENGTH];

    while (fgets(line, sizeof(line), file)) {
        get_student_average(line);
    }

    fclose(file);
}
void get_student_average(char* line) {
    int sum_of_grades = 0, counter = 0, grade = 0;
    char* token = strtok(line, " ");
    char* student_name = token;
    double avg = 0.0;

    while (token != NULL) {
        token = strtok(NULL, " ");
        if (token != NULL) {
            counter++;
            sscanf(token, "%d", &grade);
            sum_of_grades += grade;
        }
    }

    avg = (double)sum_of_grades / (counter);
    fprintf(stdout, "%s", student_name);
    fprintf(stdout, " %.1f\n", avg);
}
void report_data_summary(int num_stud) {
    //fprintf(stderr, "grade calculation for %d students is done\n", num_stud);
}


