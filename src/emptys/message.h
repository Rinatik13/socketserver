
#include <string>

enum command{
    nocommand = 0,
    writemessage = 1,
    readmessage = 2,
    newuser = 3,
    autorization = 4
};

class message {
    message() = default;
    message(int id):id_(id),cmd_(nocommand){};

public:
    int id_;
    command cmd_;
    std::string body_;
};
