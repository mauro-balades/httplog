
#include <ftxui/component/component.hpp>
#include <ftxui/component/container.hpp>
#include <ftxui/component/receiver.hpp>
#include <ftxui/component/component.hpp>

#include <string>

namespace frontend {
    class MainComponent : public ftxui::ComponentBase {
        public:
            MainComponent(ftxui::Receiver<std::wstring> receiver);
            ftxui::Element Render() override;
            bool OnEvent(ftxui::Event) override;
    };
}
