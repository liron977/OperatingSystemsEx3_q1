#include "ex3_q1.h"
#include "ex3_q1_given.h"

struct all_students all_stud;
pthread_mutex_t all_stud_mtx= PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t done_threads_mtx= PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t cond_mtx;
pthread_cond_t count_done_threads;
int done_threads = 0;
int number_of_files = 0;

int main(int agrc, char* argv[]) {
    int num_stud = 0;
    FILE* output_file = NULL;
    char* input_file_name;
    pthread_t threads[10];

    number_of_files = agrc - 2;
    for (int i = 2; i < agrc; i++) {
        input_file_name = argv[i]; 
        pthread_create(&threads[i - 2], NULL, read_data_from_file, (void*)input_file_name);
    }
    wait_for_threads(threads);

    pthread_exit(NULL);
}
void wait_for_threads(pthread_t threads[10]) {

    for (int i = 0; i < number_of_files; i++) {
        pthread_join(threads[i], NULL);
    }
    /*  for (int i = 0; i < all_stud.count; i++) {
         print_student(i);
     }*/
    fprintf(stderr, "all %d threads terminated\n", done_threads);
}
void read_data_from_file(void* file_name_input) {
    char* file_name = (char*)file_name_input;
    printf("%s file_name\n", file_name);
  
    FILE* file = fopen(file_name, "r");
    char line[MAX_LINE_LENGTH];

    while (fgets(line, sizeof(line), file)) {
        get_student_average(line);
    }

    fclose(file);
    handle_done_threads();
  
}
void handle_done_threads() {

    pthread_mutex_lock(&done_threads_mtx);
    done_threads++;
    pthread_mutex_unlock(&done_threads_mtx);

    pthread_mutex_lock(&cond_mtx);
    if (done_threads == number_of_files) {
        sort_student_arr();
        //printf("%d done_threads\n", done_threads);
        pthread_cond_broadcast(&count_done_threads);
        pthread_mutex_unlock(&cond_mtx);
    }
    else {
        //printf("waiting to wake % ld\n", pthread_self());
       // printf("%d done_threads\n", done_threads);

        pthread_cond_wait(&count_done_threads, &cond_mtx);
       // printf("I`m wake\n% ld\n", pthread_self());

        pthread_mutex_unlock(&cond_mtx);
    }
}
void get_student_average(char* line) {
    int sum_of_grades = 0, counter = 0, grade = 0;
    char* token = strtok(line, " ");
    char* student_name = token;
    double avg = 0.0;
    struct student stud;

    while (token != NULL) {
        token = strtok(NULL, " ");
        if (token != NULL) {
            counter++;
            sscanf(token, "%d", &grade);
            sum_of_grades += grade;
        }
    }

    avg = (double)sum_of_grades / (counter);
    strcpy(stud.name ,student_name);
    stud.avg_grade = avg;
  pthread_mutex_lock(&all_stud_mtx);
    add_to_student_arr(&stud);
   // done_threads++;
    pthread_mutex_unlock(&all_stud_mtx);
    /*
    pthread_mutex_lock(&cond_mtx);
    if (done_threads == number_of_files) {
        printf("%d done_threads\n", done_threads);
        pthread_cond_broadcast(&count_done_threads);
        pthread_mutex_unlock(&cond_mtx);
    }
    else {
        printf("waiting to wake % ld\n", pthread_self());
        printf("%d done_threads\n", done_threads);
     
        pthread_cond_wait(&count_done_threads, &cond_mtx);
        printf("I`m wake\n% ld\n", pthread_self());

        pthread_mutex_unlock(&cond_mtx);
    }*/
  
    





   /* fprintf(stdout, "%s", student_name);
    fprintf(stdout, " %.1f\n", avg);*/
}


