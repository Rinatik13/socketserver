#include <iostream>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>

#define PORT 8888

int main() {
    // Определение IP-адреса и порта назначения
    const char* serverAddr = "127.0.0.1"; // Замените на нужный IP-адрес

    // Создание сокета
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("Ошибка при создании сокета");
        return 1;
    }

    // Преобразование IP-адреса и порта в структуру sockaddr_in
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = PORT;
    inet_pton(AF_INET, serverAddr, &serverAddress.sin_addr);
    socklen_t len = sizeof(sockaddr_in);
    // Установка соединения с сервером
    if (connect(sockfd, (struct sockaddr *)&serverAddress, len) == -1) {
        perror("Ошибка при установлении соединения");
        return 1;
    }

    // Подготовка данных для отправки
    char buffer[1024] = "TEST TEXT";
    size_t messageLength = strlen(buffer);

    while(true){
        std::this_thread::sleep_for(std::chrono::seconds(5));
        // Отправка данных
        int sentBytes = send(sockfd, buffer, messageLength, 0);
        if (sentBytes == -1) {
            perror("Ошибка при отправке данных");
            return 1;
        }
        std::cout << "Данные отправлены: " << buffer << std::endl;
    }

    // Закрытие соединения
    shutdown(sockfd,SHUT_RDWR);

    return 0;
}