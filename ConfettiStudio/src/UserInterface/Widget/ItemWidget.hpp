#pragma once

#include "Widget.hpp"

class ItemWidget : public Widget
{
protected:
	bool isHovered() const override;

public:
	ItemWidget(const std::string& name);
};