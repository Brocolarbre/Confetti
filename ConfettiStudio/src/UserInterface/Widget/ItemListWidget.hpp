#pragma once

#include "ItemWidget.hpp"

#include <optional>

struct RenameBuffer
{
	std::string buffer;
	bool firstFrame;
};

struct ItemListCallbacks
{
	std::function<void()> createCallback;
	std::function<void()> destroyCallback;
	std::function<void()> renameCallback;
	std::function<void()> selectCallback;
};

class ItemListWidget : public ItemWidget
{
private:
	std::vector<std::string> m_items;
	std::optional<unsigned int> m_selectedItem;
	std::optional<RenameBuffer> m_renameBuffer;
	std::string m_previousItemName;
	std::string m_name;

	ItemListCallbacks m_callbacks;

public:
	ItemListWidget(const std::string& name, const ItemListCallbacks& callbacks);

	const std::vector<std::string>& getItems() const;
	std::vector<std::string>& getItems();
	const std::string& getPreviousItemName() const;
	const std::string& getName() const;

	const std::optional<unsigned int>& getSelectedItem() const;
	void setSelectedItem(const std::optional<unsigned int>& item);
	void cancelRenaming();

	void addItem(const std::string& item);
	void removeItem(const std::string& item);
	void renameItem(const std::string& item, const std::string& name);
	void selectItem(const std::string& name);

	bool beginRender() const override;
	void render() override;
	void endRender() const override;
};