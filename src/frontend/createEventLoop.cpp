
#include <functional>
#include <iostream>

#include <memory>
#include <string>
#include <thread>

#include "frontend/components/MainComponent.hpp"
#include "frontend/main.hpp"

#include "ftxui/component/component.hpp"
// #include <ftxui/component/loop.hpp>
#include "ftxui/component/screen_interactive.hpp"
#include <ftxui/component/event.hpp>
#include <ftxui/component/receiver.hpp>

namespace frontend {
int FrontendService::createEventLoop(
    int log_fd, std::function<void(int, ftxui::Sender<std::wstring>,
                                   ftxui::ScreenInteractive *)>
                    callback) {
  using namespace ftxui;

  auto line_receiver = MakeReceiver<std::wstring>();
  auto line_sender = line_receiver->MakeSender();

  auto screen = ScreenInteractive::Fullscreen();
  auto component = std::make_shared<MainComponent>(std::move(line_receiver));

  // Read from the log file.
  std::thread line_producer_thread(callback, log_fd, std::move(line_sender),
                                   &screen);

  screen.Loop(component);
  return EXIT_SUCCESS;
}
} // namespace frontend
