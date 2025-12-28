#include "Model.hpp"

Model::Model() :
	m_presenters(),
	m_enabled(true)
{

}

void Model::registerPresenter(std::shared_ptr<Presenter> presenter)
{
	m_presenters.insert(presenter);
}

void Model::unregisterPresenter(std::shared_ptr<Presenter> presenter)
{
	m_presenters.erase(presenter);
}

void Model::sendEvent(const std::string& event) const
{
	if (m_enabled)
	{
		for (const std::shared_ptr<Presenter>& presenter : m_presenters)
			presenter->onModelEvent(event);
	}
}

bool Model::isEnabled() const
{
	return m_enabled;
}

void Model::setEnabled(bool enabled)
{
	m_enabled = enabled;
}