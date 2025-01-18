#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8888
#define IP "127.0.0.1"
// запускаем режим работы сокетов в режиме сервера
void runServerSocket(){
    int fd, bfd;

    // адрес интернет сокета
    struct sockaddr_in address;
    address.sin_family = AF_INET; //семейство адресов (AF_INET)
    address.sin_port = PORT; //номер порта
    inet_pton(AF_INET,IP,&address.sin_addr); //IPv4 - адрес

    socklen_t len = sizeof(sockaddr_in);
// 1) socket - создаём новый сокет
    fd = socket(AF_INET,SOCK_STREAM,0);
    if(fd < 0){
        std::cerr << "Error create socket";
        exit(1);
    }
// 2) bind - привязываем сокет к адресу
    bfd = bind(fd,(struct sockaddr*)&address, len);
    if(bfd < 0){
        std::cerr << "Error create bind";
        exit(1);
    }

// 3) listen - принимаем входящие соединения от других сокетов
// 4) accept - принимаем соединение от удаленных приложений в слушающий потоковый сокет
// и опционально возвращаем адрес удаленного сокета

// 4.1) connect - устанавливаем соединение с другим сокетом

// 5) write - запись в сообщение
// 6) read - чтение сообщения

// 7) close - закрытие соединения
}

int main() {
    std::cout << "Hello, World!" << std::endl;

    return 0;
}
