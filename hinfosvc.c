// Verevkin Aleksandr VUT/FIT
// IPK 2022/2023
// Project #1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/times.h>
#include <unistd.h>

void get_name(char *command, char *str) {
    FILE *name = popen(command, "r");
    if (name == NULL) {
        fprintf(stderr, "Popen error.");
        exit(EXIT_FAILURE);
    }
    char arr[512];
    size_t n;
    while ((n = fread(arr, 1, sizeof(arr)-1, name)) > 0) {
        arr[n] = '\0';
    }
    if (pclose(name) < 0) {
        perror("Pclose error.");
    }
    strcpy(str, arr);
}

void get_cpu_details(char *details_s, int *arr) {
    char details[10][10];
    int index_ctr = 0, num_index = 0, total_nums = 0;

    for (index_ctr = 0; index_ctr <= strlen(details_s); index_ctr++) {
        if (details_s[index_ctr] == ' ' || details_s[index_ctr] == '\n') {
            details[total_nums][num_index] = '\0';
            total_nums++;
            num_index = 0;
        } else {
            details[total_nums][num_index] = details_s[index_ctr];
            num_index++;
        }
    }
    for (int i = 0; i < 10; i++) {
        arr[i] = atoi(details[i]);
    }
}

double get_cpu_percentage() {
    char prev_cpu_info[512], post_cpu_info[512];
    int prev_details[10], post_details[10];
    char *cpu_stat_command = "cat /proc/stat | head -n 1 | awk '{ for(i=2; i<NF; i++) {printf(\"%s \", $i)} print $NF}'";
    get_name(cpu_stat_command, prev_cpu_info);
    sleep(1);
    get_name(cpu_stat_command, post_cpu_info);

    get_cpu_details(prev_cpu_info, prev_details);
    get_cpu_details(post_cpu_info, post_details);

    int prev_idle = prev_details[3] + prev_details[4];
    int post_idle = post_details[3] + post_details[4];

    int prev_non_idle = prev_details[0] + prev_details[1] + prev_details[2] + prev_details[5] + prev_details[6] + prev_details[7];
    int post_non_idle = post_details[0] + post_details[1] + post_details[2] + post_details[5] + post_details[6] + post_details[7];

    int prev_sum = prev_idle + prev_non_idle;
    int post_sum = post_idle + post_non_idle;

    int sum_diff = post_sum - prev_sum;
    int idle_diff = post_idle - prev_idle;

    double cpu_percentage = (double) (sum_diff - idle_diff) / (double) sum_diff;
    
    return cpu_percentage;
}


int main(int argc, char *argv[]) {
    char cpu_name[128], hostname[128];
    char *cpu_name_command = "lscpu | sed -nr '/Model name/ s/.*:\\s*(.*) @ .*/\\1/p'";
    get_name(cpu_name_command, cpu_name);

    char *host_name_command = "cat /proc/sys/kernel/hostname";
    get_name(host_name_command, hostname);

    double cpuUsage = get_cpu_percentage();

    // create a socket
    int net_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    int opt = 1;
    setsockopt(net_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
    
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[1]));
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(net_socket, (struct sockaddr*) &addr, sizeof(addr));
    listen(net_socket, 5);

    char msg[6] = "Hello!";
    int client_sock;
    client_sock = accept(net_socket, NULL, NULL);

    send(client_sock, msg, sizeof(msg), 0);
    
    return 0;
}
