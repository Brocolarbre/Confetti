#include "ItemListWidget.hpp"

#include <imgui.h>
#include <format>

ItemListWidget::ItemListWidget(const std::string& name, const ItemListCallbacks& callbacks) :
    ItemWidget(name),
    m_items(),
    m_selectedItem(),
    m_renameBuffer(),
    m_name(name),
    m_callbacks(callbacks)
{

}

const std::vector<Item>& ItemListWidget::getItems() const
{
    return m_items;
}

std::vector<Item>& ItemListWidget::getItems()
{
    return m_items;
}

const std::string& ItemListWidget::getName() const
{
    return m_name;
}

const std::optional<unsigned int>& ItemListWidget::getSelectedItem() const
{
    return m_selectedItem;
}

void ItemListWidget::setSelectedItem(const std::optional<unsigned int>& item)
{
    m_selectedItem = item;
}

void ItemListWidget::cancelRenaming()
{
    if(m_renameBuffer.has_value())
        m_renameBuffer = std::nullopt;
}

void ItemListWidget::addItem(const Item& item)
{
    m_items.push_back(item);
}

void ItemListWidget::removeItem(unsigned int id)
{
    for (unsigned int i = 0; i < m_items.size(); ++i)
    {
        if (m_items[i].id == id)
        {
            m_items.erase(m_items.begin() + i);
            break;
        }
    }
}

void ItemListWidget::renameItem(unsigned int id, const std::string& name)
{
    for (unsigned int i = 0; i < m_items.size(); ++i)
    {
        if (m_items[i].id == id)
        {
            m_items[i].name = name;
            break;
        }
    }
}

void ItemListWidget::selectItem(unsigned int id)
{
    for (unsigned int i = 0; i < m_items.size(); ++i)
    {
        if (m_items[i].id == id)
        {
            m_selectedItem = std::make_optional(i);
            break;
        }
    }
}

bool ItemListWidget::beginRender() const
{
    return true;
}

void ItemListWidget::render()
{
    for (unsigned int i = 0; i < m_items.size(); ++i)
    {
        Item& item = m_items[i];
        bool selected = m_selectedItem.has_value() && i == m_selectedItem.value();

        if (selected && m_renameBuffer.has_value())
        {
            if (m_renameBuffer.value().firstFrame)
            {
                ImGui::SetKeyboardFocusHere();
                m_renameBuffer.value().firstFrame = false;
            }

            RenameBuffer& renameBuffer = m_renameBuffer.value();
            ImGui::InputText(std::format("##{}RenameInputText", m_name).c_str(), renameBuffer.buffer.data(), renameBuffer.buffer.size(), ImGuiInputTextFlags_AutoSelectAll);
        }
        else if (ImGui::Selectable(std::format("{}##{}", item.name, item.id).c_str(), selected))
        {
            m_selectedItem = std::make_optional(i);
            m_callbacks.selectCallback();
        }

        if (ImGui::IsKeyPressed(ImGuiKey_Delete) && m_selectedItem.has_value())
        {
            m_callbacks.destroyCallback();
            m_items.erase(m_items.begin() + m_selectedItem.value());
            m_selectedItem = std::nullopt;
            m_callbacks.selectCallback();
            break;
        }

        if (ImGui::IsKeyPressed(ImGuiKey_Escape) && m_renameBuffer.has_value())
        {
            m_renameBuffer = std::nullopt;
        }

        if (ImGui::IsKeyPressed(ImGuiKey_F2) && m_selectedItem.has_value() && !m_renameBuffer.has_value())
        {
            std::string buffer = std::string(256, '\0').replace(0, item.name.size(), item.name);
            m_renameBuffer = std::make_optional(RenameBuffer{ buffer, true });
        }

        if ((ImGui::IsKeyPressed(ImGuiKey_Enter) || ImGui::IsKeyPressed(ImGuiKey_KeypadEnter)) && m_renameBuffer.has_value())
        {
            const std::string& renameBuffer = m_renameBuffer.value().buffer;
            std::string newName = renameBuffer.substr(0, renameBuffer.find('\n', 0));
            if (!newName.empty())
            {
                m_items[m_selectedItem.value()].name = newName;
                m_renameBuffer = std::nullopt;
                m_callbacks.renameCallback();
            }
        }
    }

    if (ImGui::Button("Add"))
    {
        m_callbacks.createCallback();
    }
}

void ItemListWidget::endRender() const
{

}