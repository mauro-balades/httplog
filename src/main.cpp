#include <iostream>
#include <unistd.h>

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

        std::cout << "hey" << std::endl;
    });
}