#pragma once

#include "UserInterface/Presenter/Presenter.hpp"

#include <unordered_set>

class Model
{
private:
	std::unordered_set<std::shared_ptr<Presenter>> m_presenters;
	bool m_enabled;

public:
	Model();

	void registerPresenter(std::shared_ptr<Presenter> presenter);
	void unregisterPresenter(std::shared_ptr<Presenter> presenter);

	void sendEvent(const std::string& event) const;

	bool isEnabled() const;
	void setEnabled(bool enabled);
};