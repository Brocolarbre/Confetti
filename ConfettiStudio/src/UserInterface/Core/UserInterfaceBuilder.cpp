#include "UserInterfaceBuilder.hpp"

#include "UserInterface/Presenter/ViewportPresenter.hpp"
#include "UserInterface/Widget/DockspaceWidget.hpp"

void UserInterfaceBuilder::build(UserInterface& userInterface, dove::Window& window, ConfettiInstance& confettiInstance)
{
    CommandHistory& commandHistory = userInterface.getCommandHistory();

    std::shared_ptr<DockspaceWidget> dockspaceWidget = std::make_shared<DockspaceWidget>();
    std::shared_ptr<ViewportWidget> viewportWidget = std::make_shared<ViewportWidget>();

    std::shared_ptr<ViewportPresenter> viewportPresenter = std::make_shared<ViewportPresenter>(commandHistory, *viewportWidget, confettiInstance);

    viewportWidget->registerPresenter(viewportPresenter);

    dockspaceWidget->addChildWidget(viewportWidget);

    userInterface.loadSettings("res/settings/user_interface.ini");
    userInterface.setFont("res/fonts/Inter-Regular.ttf", 16);
    userInterface.setStyle(UserInterface::Theme::Dark);
    userInterface.setRootWidget(dockspaceWidget);
}