
#include <ftxui/component/component.hpp>
#include <ftxui/component/receiver.hpp>

#include <string>
#include <vector>

#include "backend/parser/LogsParser.hpp"

#ifndef __FRONTEND_MAIN_COMPONENT_H_
#define __FRONTEND_MAIN_COMPONENT_H_

namespace frontend {
class MainComponent : public ftxui::ComponentBase {
public:
  MainComponent(ftxui::Receiver<std::wstring> receiver);
  ftxui::Element Render() override;
  bool OnEvent(ftxui::Event) override;

private:
  ftxui::Receiver<std::wstring> _receiver;

  std::vector<std::wstring> parsed_logs;
  backend::parser::LogsParser *_parser;
};
} // namespace frontend

#endif // __FRONTEND_MAIN_COMPONENT_H_
