#pragma once

#include "Widget.hpp"

class DockspaceWidget : public Widget
{
private:
	bool isHovered() const override;

public:
	DockspaceWidget();

	bool beginRender() const override;
	void render() override;
	void endRender() const override;
};