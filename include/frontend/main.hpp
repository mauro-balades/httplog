
#include <functional>

#include "ftxui/component/screen_interactive.hpp"

#ifndef __FRONTEND_MAIN_H_
#define __FRONTEND_MAIN_H_

namespace frontend {

    class FrontendService {
        public:
            FrontendService();
            ~FrontendService() = default;

            int createEventLoop(int log_fd, std::function<void(int,
                  ftxui::Sender<std::wstring>,
                  ftxui::ScreenInteractive*)> callback);

        private:

    };
}

#endif // __FRONTEND_MAIN_H_