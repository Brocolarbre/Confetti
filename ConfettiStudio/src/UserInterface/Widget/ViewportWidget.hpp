#pragma once

#include "WindowWidget.hpp"

class ViewportWidget : public WindowWidget
{
public:
	unsigned long long m_texture;

public:
	ViewportWidget();

	void render() override;
};