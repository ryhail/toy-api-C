#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char* getCommand(char* req, int len) {
    char* command = calloc(len, 1);
    int index = 0;
    while(req[index] != ' ')
        index++;
    index++;
    for(int i = 0; req[index] != ' '; i++, index++)
        command[i] = req[index];
    return command;
}

char* commandHandler(char* command) {
    char* response;
    char** users = calloc(3, sizeof(char*));
        users[0] = "bebra";
        users[1] = "asyow";
        users[2] = "anton";
    int index = 1;
    int value = 0;
    char* value_str;
    while(command[index] != '\0') {
        if(command[index] == '/') {
            command[index] = '\0';
            index++;
            while(command[index] != '\0') {
                value *= 10;
                value += command[index] - '0';
                command[index] = '\0';
                index++;
            }
            itoa(value, value_str, 10);
        }
        index++;
    }

    if(strcmp(command, "/") == 0) {
        response = "HTTP/1.1 200 OK\r\n\r\n";
    }
    else if(strcmp(command, "/hello") == 0) {
        response = "HTTP/1.1 200 OK\r\n\r\nHello world!!!";
    }
    else if(strcmp(command, "/user") == 0) {
        response = calloc(100, 1);
        strcat(response,"HTTP/1.1 200 OK\r\n\r\n{\n\tid: ");
        strcat(response, value_str);
        strcat(response, "\n\tuser: ");
        strcat(response,users[value]);
        strcat(response,"\n}");
    }
    else {
        response = "HTTP/1.1 404 Not found\r\n\r\nNot found";
    }
    return response;
}


int main() {
    FILE* f = fopen("E:\\papkis\\server\\reqFile.txt", "r");
    size_t req_size = 20;
    char* request = calloc(req_size, 1);
    int len = 0;
    char buf;
    while((buf = getc(f)) != '\n') {
       if(len > req_size) {
           req_size *= 2;
           request = realloc(request, req_size);
       }
       request[len] = buf;
       len++;
    }
    char* command = getCommand(request, len);
    fclose(f);
    FILE* out = fopen("E:\\papkis\\server\\respFile.bin", "w+");
    char* response;
    response = commandHandler(command);
    fwrite(response, strlen(response), 1, out);
    fwrite(response, strlen(response), 1, stdout);
    printf("%c", '\n');
    fclose(out);
    return 0;
}
