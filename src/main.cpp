#include <iostream>
#include <unistd.h>

#include <cstdio>
#include <thread>
#include <string>

#include <codecvt>
#include <locale>

#include <sstream>

#include "frontend/main.hpp"
#include "backend/main.hpp"

int main(int argc, char *argv[]) {
    auto frontendSerice = new frontend::FrontendService();

    int log_fd = 0;
    if (argc > 1) {
        log_fd = backend::getFileFromArgv(argv[1]);
    } else {
        std::cout << "error: (TODO) file from stdin" << std::endl;
        exit(1);
    }

    return frontendSerice->createEventLoop(log_fd, [&](int fd,
                  ftxui::Sender<std::wstring> sender,
                  ftxui::ScreenInteractive* screen) -> void {

        std::string line = "";
        int buffer_size = 1 << 10;
        char buffer[buffer_size];

        read(fd, buffer, buffer_size);

        std::string file_contents(buffer);
        std::istringstream fss(file_contents);
        for(std::string line; std::getline(fss, line);) {
            sender->Send(std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(line));
        }
    });
}