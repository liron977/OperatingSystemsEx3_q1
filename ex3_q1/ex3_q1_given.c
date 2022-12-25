#include "ex3_q1_given.h"

#define DEBUG 1
#define DEB DEBUG
#define DEB_MSG if (DEBUG) \
        {fprintf(stderr, "***DEBUG*** function: %s line: %d\n", __func__, __LINE__);}
#define DEB_MSG1(msg) if (DEBUG) \
        {fprintf(stderr, "***DEBUG*** function: %s line: %d %s\n", __func__, __LINE__, msg);}
#define DEB_MSG_STDOUT if (DEBUG) \
        {fprintf(stdout, "***DEBUG*** function: %s line: %d\n", __func__, __LINE__);}
#define LINE_FUNC if(DEBUG) printf("Line (%d) function: %s\n", __LINE__, __func__);
#define PVI(var) if(DEB) \
        {fprintf(stderr, "***DEBUG %s = %d\n", #var, var);}
#define PVD(var) if(DEB) \
        {fprintf(stderr, "***DEBUG %s = %f\n", #var, var);}
#define PVS(var) if(DEB) \
        {fprintf(stderr, "***DEBUG %s = %s\n", #var,  var);}
#define PVPTR(var) if(DEB) \
        {fprintf(stderr, "***DEBUG %s = %p\n", #var, var);}





//------------------------------------------------------------------------
void add_to_student_arr(struct student* a_student)
{
    // double temp = 
    random_sleep();
    all_stud.stud_arr[all_stud.count] = *a_student;
    random_sleep();
    all_stud.count++;
}

//------------------------------------------------------------------------
void sort_student_arr()
{
    struct student temp;
    int num = all_stud.count;
    for (int k = 0; k < num - 1; k++)
        for (int j = 0; j < num - 1 - k; j++)
            if (all_stud.stud_arr[j].avg_grade < all_stud.stud_arr[j + 1].avg_grade)
            {
                temp = all_stud.stud_arr[j];
                all_stud.stud_arr[j] = all_stud.stud_arr[j + 1];
                all_stud.stud_arr[j + 1] = temp;
            }
}

//------------------------------------------------------------------------
void print_student(int indx)
{
    printf("%s -> average grade: ", all_stud.stud_arr[indx].name);
    random_sleep();
    printf("%.1f\n", all_stud.stud_arr[indx].avg_grade);
}

//------------------------------------------------------------------------
void random_sleep()
{
    int d = (rand() ^ pthread_self() ^ getpid()) % 40 + 40;
    const struct timespec ts = { 0, d * 1000 * 1000 * 5 };
    nanosleep(&ts, NULL);
}

