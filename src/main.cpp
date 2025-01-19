#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <thread>
#include "client.h"
#include "emptys/message.h"

#define SERVERPORT 8888
#define OTHERSERVERPORT 7777
#define IP "127.0.0.1"
// запускаем режим работы сокетов в режиме сервера
void runServerSocket() {

    int fd, bfd, lfd, afd;

    // адрес интернет сокета
    sockaddr_in address;
    address.sin_family = AF_INET; //семейство адресов (AF_INET)
    address.sin_port = SERVERPORT; //номер порта
    inet_pton(AF_INET, IP, &address.sin_addr); //IPv4 - адрес

    socklen_t len = sizeof(sockaddr_in);
// 1) socket - создаём новый сокет
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        std::cerr << "Error create socket";
        exit(1);
    }
    std::cout << "Create socket" << std::endl;;
// 2) bind - привязываем сокет к адресу
    bfd = bind(fd, (struct sockaddr *) &address, len);
    if (bfd < 0) {
        std::cerr << "Error create bind";
        exit(1);
    }
    std::cout << "Create bind" << std::endl;;
// 3) listen - принимаем входящие соединения от других сокетов
// делаем потоковый сокет, этот сокет используется для приема соединений от других активных сокетов
// нельзя применить для подключённых сокетов для которых уже успешно выполнена операция connect
    lfd = listen(fd,SOMAXCONN);

    if(lfd < 0 ){
        std::cerr << "Error create listen";
        exit(1);
    }
    std::cout << "Create listen" << std::endl;;


// 4) accept - принимаем соединение от удаленных приложений в слушающий потоковый сокет
// и опционально возвращаем адрес удаленного сокета
// если вызов не обнаруживает ожидающих соединений, то блокируется и ждёт пока не поступит запрос
// он создаёт новый сокет который затем подключается к удаленному сокету, выполнившему вызов connect
// если нам не нужны данные с удалённого сокета то по дефолту ставим NULL (структура адреса) и 0 (размер структуры)
    afd = accept(fd, NULL, 0);

    if(afd < 0){
        std::cerr << "Error create accept";
        exit(1);
    }
    char buffer[1024];
    ssize_t sizeRecvBuffer = 0;
// 4.1) connect - устанавливаем соединение с другим сокетом

    std::thread newThread(clientRun);
    while(true){
    // 5) write - запись в сообщение
    // 6) read - чтение сообщения

        // recv возвращает количество пришедших байт, при ошибке -1, если конец файла то 0
        sizeRecvBuffer = recv(afd,buffer,1024,MSG_MORE);
        //std::cout << "Count: " << sizeRecvBuffer << std::endl;
        if(sizeRecvBuffer < 0){
            std::cerr << "Error recv";
            exit(1);
        }
        if(sizeRecvBuffer > 0) {
            // создаём буфер для чтения, туда записываем полученные данные.
            char readBuffer[sizeRecvBuffer];
            std::cout << "Read " << sizeRecvBuffer << " count: ";
            for (ssize_t step = 0; step < sizeRecvBuffer; ++step) {
                readBuffer[step] = buffer[step];
                std::cout << buffer[step];
            }
            std::cout << std::endl;
        }

    }
// 7) close - закрытие соединения
    shutdown(fd,SHUT_RDWR);
}

int main() {
    std::cout << "START!" << std::endl;
    runServerSocket();
    return 0;
}
