#include <stdio.h>
#include <unistd.h>
#include "cyo.h"

/**
 * Print program usage.
 */
void printf_usage(){
    printf("Usage: yo <api_token>\n");
    printf("Optional:\n");
    printf("-t <username> to send yo to, without this all subscribers will be Yo'd\n");
    printf("-u <url>, can be sent to all or specific user\n");
    printf("-l <location>, can only be sent to specific user\n");
}

int main(int argc, char** argv){

    //Min arguments check
    if(argc < 2){
        printf_usage();
        return 1;
    }

    char* token = argv[1];
    int flag;
    char* username = 0;
    char* url = 0;
    char* location = 0;

    //Parse arg flags
    while((flag = getopt(argc, argv, "t:u:l:")) != -1){
        switch(flag){
            case 't':
                username = optarg;
                break;
            case 'u':
                url = optarg;
                break;
            case 'l':
                location = optarg;
                break;
            default:
                printf_usage();
                return 1;
                break;
        }
    }

    //Perform Yo
    int resp = 0;
    if(username == 0){
        if(url == 0)
            resp = yo_all(token);
        else
            resp = yo_all_link(token, url);
    }else if(username){
        if(url)
            resp = yo_link(username, token, url);
        else if(location)
            resp = yo_location(username, token, location);
        else
            resp = yo(username, token);
    }

    //Print result
    if(resp == yo_ok){
        printf("Yo sent\n");
    }else{
        printf("Failed to send Yo\n");
    }

    return 0;
}
