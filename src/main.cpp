#include <iostream>
#include <unistd.h>

#include <cstdio>
#include <thread>
#include <string>

#include <codecvt>
#include <locale>

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

        while (true) {
            int c = read(fd, buffer, buffer_size);
            for (int i = 0; i < c; ++i) {
                if (buffer[i] == '\n') {
                    sender->Send(std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(line));
                    line = "";
                } else {
                    line.push_back(buffer[i]);
                }
            }

            // Refresh the screen:
            screen->PostEvent(ftxui::Event::Custom);

            if (c == 0) {
                using namespace std::chrono_literals;
                std::this_thread::sleep_for(0.5s);
            }
        }
    });
}