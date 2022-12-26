
#include <functional>

#include "ftxui/component/screen_interactive.hpp"

#ifndef __FRONTEND_MAIN_H_
#define __FRONTEND_MAIN_H_

namespace frontend {

    class FrontendService {
        public:
            FrontendService();
            ~FrontendService() = default;

            int createEventLoop(std::function<void()> callback);

        private:

    };
}

#endif // __FRONTEND_MAIN_H_