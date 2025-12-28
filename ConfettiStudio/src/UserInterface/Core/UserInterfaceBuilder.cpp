#include "UserInterfaceBuilder.hpp"
#include "UserInterface/Widget/DockspaceWidget.hpp"

void UserInterfaceBuilder::build(UserInterface& userInterface, dove::Window& window)
{
    CommandHistory& commandHistory = userInterface.getCommandHistory();

    std::shared_ptr<DockspaceWidget> dockspaceWidget = std::make_shared<DockspaceWidget>();

    userInterface.loadSettings("res/settings/user_interface.ini");
    userInterface.setFont("res/fonts/Inter-Regular.ttf", 16);
    userInterface.setStyle(UserInterface::Theme::Dark);
    userInterface.setRootWidget(dockspaceWidget);
}