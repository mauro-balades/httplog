
#include <iostream>
#include <unistd.h>

#include "backend/main.hpp"

namespace backend {
    int getFileFromArgv(std::string filename) {
        int log_fd = 0;

        FILE* file = fopen(filename.c_str(), "r");
        log_fd = dup(fileno(file));
        fclose(file);

        return log_fd;
    }
}
