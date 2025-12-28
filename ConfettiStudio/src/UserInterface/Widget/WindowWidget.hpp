#pragma once

#include "Widget.hpp"

class WindowWidget : public Widget
{
protected:
	bool m_child;

	bool isHovered() const override;

public:
	WindowWidget(const std::string& name, bool child);

	bool beginRender() const override;
	void endRender() const override;
};