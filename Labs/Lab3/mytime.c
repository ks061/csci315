#include <sys/time.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char* argv[]) {
    struct timeval tv;
    gettimeofday(&tv, NULL);

    char* cur_time_str;
    time_t cur_time_tv_sec = tv.tv_sec;
    cur_time_str = ctime(&cur_time_tv_sec); 

    printf("%s",cur_time_str);
    return 0;
}
