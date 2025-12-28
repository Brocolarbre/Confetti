#pragma once

#include "UserInterface/Presenter/Presenter.hpp"

#include <glm/glm.hpp>
#include <memory>

class Widget
{
protected:
	std::string m_name;
	bool m_alwaysEndRender;
	bool m_enabled;
	std::vector<std::shared_ptr<Widget>> m_childWidgets;
	std::shared_ptr<Presenter> m_presenter;

	glm::vec2 m_position;
	glm::vec2 m_size;
	bool m_hovered;

	virtual bool isHovered() const = 0;

public:
	Widget(const std::string& name, bool alwaysEndRender);
	virtual ~Widget() = default;

	std::string getName() const;
	bool alwaysEndRender() const;
	bool isEnabled() const;

	const std::vector<std::shared_ptr<Widget>>& getChildWidgets() const;
	void addChildWidget(std::shared_ptr<Widget> widget);
	void removeChildWidget(const std::string& name);
	void setEnabled(bool enabled);

	glm::vec2 getPosition() const;
	glm::vec2 getSize() const;

	void registerPresenter(std::shared_ptr<Presenter> presenter);
	void unregisterPresenter();

	void sendEvent(const std::string& event) const;

	virtual void beginStyle() const;
	virtual bool beginRender() const = 0;
	virtual void update();
	virtual void render() = 0;
	virtual void endRender() const = 0;
	virtual void endStyle() const;
};