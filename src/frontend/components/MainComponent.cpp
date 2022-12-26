
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
        }

        return ComponentBase::OnEvent(event);
    }
}
