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

#include "backend/parser/LogsParser.hpp"

int main(int argc, char *argv[]) {

    backend::parser::LogsParser* parser = new backend::parser::LogsParser("127.0.0.1 - - [30/Dec/2022 13:18:15] \"%m %p HTTP/1.1\"");
    parser->parse_line(std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes("127.0.0.1 - - [30/Dec/2022 13:18:15] \"GET /favicon.ico HTTP/1.1\""));
    return 0;

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