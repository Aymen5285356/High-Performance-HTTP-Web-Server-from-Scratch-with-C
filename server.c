#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include "server.h"

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    
    // قراءة الطلب القادم من المتصفح
    read(client_socket, buffer, BUFFER_SIZE);
    printf("--- طلب قادم من المتصفح ---\n%s\n", buffer);

    // فتح ملف الـ HTML الذي نريد عرضه
    FILE *html_file = fopen("index.html", "r");
    if (html_file == NULL) {
        char *error_response = "HTTP/1.1 404 Not Found\r\nContent-Length: 9\r\n\r\nNot Found";
        write(client_socket, error_response, strlen(error_response));
        close(client_socket);
        return;
    }

    // قراءة محتوى ملف HTML
    char html_content[1024] = {0};
    fread(html_content, 1, sizeof(html_content), html_file);
    fclose(html_file);

    // صياغة رد HTTP القياسي (HTTP Header + Body)
    char http_response[BUFFER_SIZE];
    sprintf(http_response,
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html; charset=UTF-8\r\n"
            "Content-Length: %zu\r\n"
            "Connection: close\r\n"
            "\r\n"
            "%s",
            strlen(html_content), html_content);

    // إرسال الرد إلى المتصفح
    write(client_socket, http_response, strlen(http_response));
    
    // إغلاق الاتصال مع العميل لتنتهي العملية بنجاح
    close(client_socket);
}