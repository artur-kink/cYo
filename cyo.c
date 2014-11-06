#include "cyo.h"

#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>

size_t curl_response(void* ptr, size_t size, size_t nmemb, void* userptr){
    char** response = (char**)(userptr);
    *response = malloc(sizeof(char)*size*nmemb+1);
    strncpy(*response, ptr, size*nmemb);
    return nmemb*size;
}

int response_to_code(const char* response){
    if(strncmp(response, "{\"result\": \"OK\"}", 16) == 0){
        return yo_ok;
    }
    return yo_fail;
}

int yo(const char* username, const char* token){
    CURL* curl;
    curl = curl_easy_init();
    if(curl){
        curl_easy_setopt(curl, CURLOPT_POST, 1);
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.justyo.co/yo/");
        
        int post_len = 8 + 9 + 2 + 1 + strlen(username) + strlen(token);
        char post_fields[post_len+1];
        strcpy(post_fields, "username=");
        strcat(post_fields, username);
        strcat(post_fields, "&api_token=");
        strcat(post_fields, token);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_fields);

        char* response_ptr = 0;
        char** response = &response_ptr;
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_response);

        CURLcode res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        if(res != CURLE_OK){
            return connection_fail;    
        }else if(*response){
            int response_code = response_to_code(*response);
            free(*response);
            return response_code;
        }
    }
    return connection_fail;
}

int yo_link(const char* username, const char* token, const char* link){
    CURL* curl;
    curl = curl_easy_init();
    if(curl){
        curl_easy_setopt(curl, CURLOPT_POST, 1);
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.justyo.co/yo/");
        
        int post_len = 8 + 9 + 4 + 3 + 2 + strlen(username) + strlen(token) + strlen(link);
        char post_fields[post_len+1];
        strcpy(post_fields, "username=");
        strcat(post_fields, username);
        strcat(post_fields, "&api_token=");
        strcat(post_fields, token);
        strcat(post_fields, "&link=");
        strcat(post_fields, link);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_fields);

        char* response_ptr = 0;
        char** response = &response_ptr;
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_response);

        CURLcode res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        if(res != CURLE_OK){
            return connection_fail;    
        }else if(*response){
            int response_code = response_to_code(*response);
            free(*response);
            return response_code;
        }
    }
    return connection_fail;
}

int yo_location(const char* username, const char* token, const char* location){
    CURL* curl;
    curl = curl_easy_init();
    if(curl){
        curl_easy_setopt(curl, CURLOPT_POST, 1);
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.justyo.co/yo/");
        
        int post_len = 8 + 9 + 8 + 3 + 2 + strlen(username) + strlen(token) + strlen(location);
        char post_fields[post_len+1];
        strcpy(post_fields, "username=");
        strcat(post_fields, username);
        strcat(post_fields, "&api_token=");
        strcat(post_fields, token);
        strcat(post_fields, "&location=");
        strcat(post_fields, location);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_fields);

        char* response_ptr = 0;
        char** response = &response_ptr;
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_response);

        CURLcode res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        if(res != CURLE_OK){
            return connection_fail;    
        }else if(*response){
            int response_code = response_to_code(*response);
            free(*response);
            return response_code;
        }
    }
    return connection_fail;
}
