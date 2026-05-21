#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "server.h"

int main() {
    int server_fd, client_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // 1. إنشاء الـ Socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("فشل إنشاء الـ Socket");
        exit(EXIT_FAILURE);
    }

    // 2. ربط الـ Socket بالمنفذ والخادم المحلي
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt فشل");
        exit(EXIT_FAILURE);
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // الاستماع لجميع العناوين
    address.sin_port = htons(PORT);       // تحديد البورت 8080

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("فشل عملية الـ Bind");
        exit(EXIT_FAILURE);
    }

    // 3. وضع السيرفر في حالة استماع (Listening)
    if (listen(server_fd, 10) < 0) {
        perror("فشل الـ Listen");
        exit(EXIT_FAILURE);
    }

    printf("🚀 السيرفر يعمل بنجاح على الرابط: http://localhost:%dn", PORT);

    // 4. حلقة لا متناهية لاستقبال الطلبات باستمرار
    while (1) {
        if ((client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("فشل استقبال الاتصال");
            exit(EXIT_FAILURE);
        }
        
        // معالجة العميل
        handle_client(client_socket);
    }

    close(server_fd);
    return 0;
}