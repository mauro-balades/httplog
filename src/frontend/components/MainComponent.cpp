
#include <ftxui/component/component.hpp>
#include <ftxui/component/receiver.hpp>
#include <ftxui/component/component.hpp>
#include <string>

#include "frontend/components/MainComponent.hpp"

#include "backend/parser/LogsParser.hpp"

using namespace ftxui;

namespace frontend {
    MainComponent::MainComponent(Receiver<std::wstring> receiver)
        : _receiver(std::move(receiver)) {
        _parser = new backend::parser::LogsParser("hey %s");
    }

    bool MainComponent::OnEvent(Event event) {
        while (_receiver->HasPending()) {
            std::wstring line;
            _receiver->Receive(&line);

            auto parsed = _parser->parse_line(line);

            this->parsed_logs.push_back(line);
        }

        return ComponentBase::OnEvent(event);
    }

    Element MainComponent::Render() {

        auto full_logs = Elements {};

        for (auto log : this->parsed_logs) {
            full_logs.push_back(text(log));
        }

        return vbox({
            vbox({
                text("STATS RESULT")
            }) | border | flex,
            hbox({
                text("CONFIGURATION OR SOME SHIT") | border | flex,
                vbox(full_logs) | border | flex,
            }) | flex
        }) | flex;
    }
}
