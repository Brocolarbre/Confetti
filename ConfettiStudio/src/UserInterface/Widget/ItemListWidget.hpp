#pragma once

#include "ItemWidget.hpp"

#include <optional>

struct Item
{
	unsigned int id;
	std::string name;
};

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
	std::vector<Item> m_items;
	std::optional<unsigned int> m_selectedItem;
	std::optional<RenameBuffer> m_renameBuffer;
	std::string m_name;

	ItemListCallbacks m_callbacks;

public:
	ItemListWidget(const std::string& name, const ItemListCallbacks& callbacks);

	const std::vector<Item>& getItems() const;
	std::vector<Item>& getItems();
	const std::string& getName() const;

	const std::optional<unsigned int>& getSelectedItem() const;
	void setSelectedItem(const std::optional<unsigned int>& item);
	void cancelRenaming();

	void addItem(const Item& item);
	void removeItem(unsigned int id);
	void renameItem(unsigned int id, const std::string& name);
	void selectItem(unsigned int id);

	bool beginRender() const override;
	void render() override;
	void endRender() const override;
};