#include "ex3_q1.h"
#include "ex3_q1_given.h"

struct all_students all_stud;
pthread_mutex_t all_stud_mtx= PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t done_threads_mtx= PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t index_to_print_mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t cond_mtx= PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t count_done_threads;
int done_threads,number_of_files,next_index_to_print,turn;

int main(int agrc, char* argv[]) {
    pthread_t threads[MAX_FILES];

    init();
    divide_work(agrc,threads,argv);
    wait_for_threads(threads);

    pthread_exit(NULL);
}

void init() {
     pthread_cond_init(&count_done_threads, NULL);
     done_threads = 0;
     number_of_files = 0;
     next_index_to_print = 0;
     turn = 0;
}

void divide_work(int agrc, pthread_t threads[MAX_FILES],char* argv[]) {
    number_of_files = agrc - 1;
    char* input_file_name;

    for (int i = 1; i < agrc; i++) {
        input_file_name = argv[i];
        pthread_create(&threads[i - 1], NULL, read_data_from_file, (void*)input_file_name);
    }
}

void wait_for_threads(pthread_t threads[MAX_FILES]) {
    for (int i = 0; i < number_of_files; i++) {
        pthread_join(threads[i], NULL);
    }
    
    fprintf(stderr, "all %d threads terminated\n", done_threads);
    destroy();
}
void destroy() {
    pthread_mutex_destroy(&all_stud_mtx);
    pthread_mutex_destroy(&done_threads_mtx);
    pthread_mutex_destroy(&cond_mtx);
    pthread_mutex_destroy(&index_to_print_mtx);
    pthread_cond_destroy(&count_done_threads);
}
void *read_data_from_file(void *file_name_input) {
    char* file_name = (char*)file_name_input;
    FILE* file = fopen(file_name, "r");
    char line[MAX_LINE_LENGTH];

    while (fgets(line, sizeof(line), file)) {
        get_student_average(line);
    }

    fclose(file);
    handle_done_threads();
    pthread_exit(NULL);
  
}
void handle_done_threads() {
    increase_done_threads();

    pthread_mutex_lock(&cond_mtx);
    if (done_threads == number_of_files) {
        sort_student_arr();
        pthread_cond_broadcast(&count_done_threads);
        pthread_mutex_unlock(&cond_mtx);
    }
   else {
        pthread_cond_wait(&count_done_threads, &cond_mtx);
        pthread_mutex_unlock(&cond_mtx);
    }
   
    threads_print_array();
  
}
void increase_done_threads() {
    pthread_mutex_lock(&done_threads_mtx);
    done_threads++;
    pthread_mutex_unlock(&done_threads_mtx);
}
void threads_print_array() {
    int index_to_print_per_thread;

    while (next_index_to_print < all_stud.count) {
        pthread_mutex_lock(&index_to_print_mtx);
        if (next_index_to_print < all_stud.count) {
            index_to_print_per_thread = next_index_to_print;
            next_index_to_print++;
            print_student(index_to_print_per_thread);
        }
        pthread_mutex_unlock(&index_to_print_mtx);
    }
}
void get_student_average(char* line) {
    char* save_ptr;
    int sum_of_grades = 0, counter = 0, grade = 0;
    char* token = strtok_r(line, " ",&save_ptr);
    char* student_name = token;
    double avg = 0.0;
   
    while (token != NULL) {
        token = strtok_r(NULL, " ",&save_ptr);
        if (token != NULL) {
            counter++;
            sscanf(token, "%d", &grade);
            sum_of_grades += grade;
        }
    }

    avg = (double)sum_of_grades / (counter);
    update_avg_per_student(student_name,avg);
}
void update_avg_per_student(char* student_name, double avg) {
    struct student stud;
    strcpy(stud.name, student_name);
    stud.avg_grade = avg;
    pthread_mutex_lock(&all_stud_mtx);
    add_to_student_arr(&stud);
    pthread_mutex_unlock(&all_stud_mtx);
}


