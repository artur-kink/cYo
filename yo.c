#include <stdio.h>
#include "cyo.h"

void printf_usage(){
    printf("Usage: yo <username> <api_token>\n");
    printf("Optional: Only 1 of the following\n");
    printf("-u url\n");
    printf("-l location\n");
}

int main(int argc, char** argv){

    if(argc < 3){
        printf_usage();
        return 1;
    }

    int resp = 0;
    if(argc == 3){
        resp = yo(argv[1], argv[2]);
    }else if(argc == 5){
        if(strcmp(argv[3], "-u") == 0){
            resp = yo_link(argv[1], argv[2], argv[4]);
        }else if(strcmp(argv[3], "-l") == 0){
            resp = yo_location(argv[1], argv[2], argv[4]);
        }else{
            printf_usage();
            return 1;
        }
    }else{
        printf_usage();
        return 1;
    }

    if(resp == yo_ok){
        printf("Yo sent\n");
    }else{
        printf("Failed to send Yo\n");
    }

    return 0;
}
