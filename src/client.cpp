// собираем активный сокет(клиент)
#include "client.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <cstring>
#include <thread>

#define IP "127.0.0.1"
#define PORT 8889

void clientRun(){
    int fd,cfd;
    struct sockaddr_in address;
    address.sin_family = AF_INET; // тип работы в интернете
    address.sin_port = PORT; // порт сервера
    inet_pton(AF_INET, IP, &address.sin_addr); //IPv4 - адрес

    socklen_t len = sizeof(sockaddr_in);


    // socket -
    fd = socket(AF_INET,SOCK_STREAM,0);

    if(fd < 0){
        std::cerr << "Error create socket";
        exit(1);
    }
    // connect -
    cfd = connect(fd,(struct sockaddr*) & address,len);

    if(cfd < 0){
        std::cerr << "Error create connect";
        exit(1);
    }

    // Подготовка данных для отправки
    char buffer[1024] = "TESTING SEND TO SERVER!!!";
    size_t messageLength = strlen(buffer);

    while(true){
        std::this_thread::sleep_for(std::chrono::seconds(2));
        // write -
        // read -

        // Отправка данных
        int sentBytes = send(fd, buffer, messageLength, MSG_MORE);
        if (sentBytes == -1) {
            std::cerr << "Error send";
            exit(1);
        }
        std::cout << "Данные отправлены: " << buffer << std::endl;
    }
    // close -
    shutdown(fd,SHUT_RDWR);
}