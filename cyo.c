#include "cyo.h"

#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>

/**
 * Curl response storing buffer.
 */
struct response_memory{
    char* response;
    size_t size;
};

/**
 * Store curl response in given userptr.
 */
size_t curl_response(void* ptr, size_t size, size_t nmemb, void* userptr){
    size_t realsize = size*nmemb;
    struct response_memory* mem = (struct response_memory*)userptr;
    
    if(mem->size == 0){
        mem->response = malloc(realsize + 1);
    }else{
        mem->response = realloc(mem->response, mem->size + realsize + 1);
    }
    memcpy(&(mem->response[mem->size]), ptr, realsize);
    mem->size += realsize;
    mem->response[mem->size] = 0;
    
    return realsize;
}

/**
 * Convert response string from POST to enum code.
 */
int response_to_code(const char* response){
    //printf("Response: %s\n", response);
    if(strncmp(response, "{\"result\": \"OK\"}", 16) == 0){
        return yo_ok;
    }else if(strncmp(response, "{}", 2) == 0){
        return yo_ok;
    }
    return yo_fail;
}

/**
 * Send yo to specific user.
 */
int yo(const char* username, const char* token){
    CURL* curl;
    curl = curl_easy_init();
    if(curl){
        curl_easy_setopt(curl, CURLOPT_POST, 1);
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.justyo.co/yo/");
        
        //Create post arguments
        int post_len = 20 + strlen(username) + strlen(token);
        char post_fields[post_len+1];
        strcpy(post_fields, "username=");
        strcat(post_fields, username);
        strcat(post_fields, "&api_token=");
        strcat(post_fields, token);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_fields);

        //Response callback
        struct response_memory response;
        response.size = 0;
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_response);

        CURLcode res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        //Check result
        if(res != CURLE_OK){
            if(response.size){
                free(response.response);
            }
            return connection_fail;    
        }else if(response.size != 0){
            int response_code = response_to_code(response.response);
            free(response.response);
            return response_code;
        }
    }
    return connection_fail;
}

/**
 * Send link Yo to specific user.
 */
int yo_link(const char* username, const char* token, const char* link){
    CURL* curl;
    curl = curl_easy_init();
    if(curl){
        curl_easy_setopt(curl, CURLOPT_POST, 1);
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.justyo.co/yo/");
        
        //Create post arguments
        int post_len = 26 + strlen(username) + strlen(token) + strlen(link);
        char post_fields[post_len+1];
        strcpy(post_fields, "username=");
        strcat(post_fields, username);
        strcat(post_fields, "&api_token=");
        strcat(post_fields, token);
        strcat(post_fields, "&link=");
        strcat(post_fields, link);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_fields);

        //Response callback
        struct response_memory response;
        response.size = 0;
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_response);

        CURLcode res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        //Check result
        if(res != CURLE_OK){
            if(response.size){
                free(response.response);
            }
            return connection_fail;    
        }else if(response.size != 0){
            int response_code = response_to_code(response.response);
            free(response.response);
            return response_code;
        }
    }
    return connection_fail;
}

/**
 * Send location Yo to specific user.
 */
int yo_location(const char* username, const char* token, const char* location){
    CURL* curl;
    curl = curl_easy_init();
    if(curl){
        curl_easy_setopt(curl, CURLOPT_POST, 1);
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.justyo.co/yo/");
        
        //Create post arguments
        int post_len = 30 + strlen(username) + strlen(token) + strlen(location);
        char post_fields[post_len+1];
        strcpy(post_fields, "username=");
        strcat(post_fields, username);
        strcat(post_fields, "&api_token=");
        strcat(post_fields, token);
        strcat(post_fields, "&location=");
        strcat(post_fields, location);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_fields);

        //Response callback
        struct response_memory response;
        response.size = 0;
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_response);

        CURLcode res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        //Check result
        if(res != CURLE_OK){
            if(response.size){
                free(response.response);
            }
            return connection_fail;    
        }else if(response.size != 0){
            int response_code = response_to_code(response.response);
            free(response.response);
            return response_code;
        }
    }
    return connection_fail;
}

/**
 * Send Yo to all subscribers.
 */
int yo_all(const char* token){
    CURL* curl;
    curl = curl_easy_init();
    if(curl){
        curl_easy_setopt(curl, CURLOPT_POST, 1);
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.justyo.co/yoall/");
        
        //Create post arguments
        int post_len = 10 + strlen(token);
        char post_fields[post_len+1];
        strcpy(post_fields, "api_token=");
        strcat(post_fields, token);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_fields);

        //Response callback
        struct response_memory response;
        response.size = 0;
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_response);

        CURLcode res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        //Check result
        if(res != CURLE_OK){
            if(response.size){
                free(response.response);
            }
            return connection_fail;    
        }else if(response.size != 0){
            int response_code = response_to_code(response.response);
            free(response.response);
            return response_code;
        }
    }
    return connection_fail;
}

/**
 * Send link Yo to all subscribers.
 */
int yo_all_link(const char* token, const char* link){
    CURL* curl;
    curl = curl_easy_init();
    if(curl){
        curl_easy_setopt(curl, CURLOPT_POST, 1);
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.justyo.co/yoall/");
        
        //Create post arguments
        int post_len = 16 + strlen(token) + strlen(link);
        char post_fields[post_len+1];
        strcpy(post_fields, "api_token=");
        strcat(post_fields, token);
        strcat(post_fields, "&link=");
        strcat(post_fields, link);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_fields);

        //Response callback
        struct response_memory response;
        response.size = 0;
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_response);

        CURLcode res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        //Check result
        if(res != CURLE_OK){
            if(response.size){
                free(response.response);
            }
            return connection_fail;    
        }else if(response.size != 0){
            int response_code = response_to_code(response.response);
            free(response.response);
            return response_code;
        }
    }
    return connection_fail;
}
