
#include <ftxui/component/component.hpp>
#include <ftxui/component/receiver.hpp>
#include <ftxui/component/component.hpp>

#include "frontend/components/MainComponent.hpp"

using namespace ftxui;

namespace frontend {
    MainComponent::MainComponent(Receiver<std::wstring> receiver)
        : receiver_(std::move(receiver)) {

    }

    bool MainComponent::OnEvent(Event event) {
        while (receiver_->HasPending()) {
            std::wstring line;
            receiver_->Receive(&line);

            printf("heyllo\n");

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
