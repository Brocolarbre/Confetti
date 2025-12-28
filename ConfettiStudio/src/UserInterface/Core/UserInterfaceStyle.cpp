#include "UserInterfaceStyle.hpp"

#include <imgui.h>

void UserInterfaceStyle::apply(ImGuiStyle& style, UserInterface::Theme theme)
{
    // Main
    style.WindowPadding = ImVec2(8.00f, 8.00f);
    style.FramePadding = ImVec2(5.00f, 3.00f);
    style.ItemSpacing = ImVec2(6.00f, 5.00f);
    style.ItemInnerSpacing = ImVec2(6.00f, 6.00f);
    style.TouchExtraPadding = ImVec2(0.00f, 0.00f);
    style.IndentSpacing = 24.00f;
    style.ScrollbarSize = 14.00f;
    style.GrabMinSize = 11.00f;

    // Borders
    style.WindowBorderSize = 1.00f;
    style.ChildBorderSize = 1.00f;
    style.PopupBorderSize = 1.00f;
    style.FrameBorderSize = 0.00f;
    style.TabBorderSize = 0.00f;
    style.TabBarBorderSize = 1.00f;
    style.TabBarOverlineSize = 1.00f;

    // Rounding
    style.WindowRounding = 3.00f;
    style.ChildRounding = 2.00f;
    style.FrameRounding = 2.00f;
    style.PopupRounding = 1.00f;
    style.ScrollbarRounding = 9.00f;
    style.GrabRounding = 2.00f;
    style.TabRounding = 2.00f;

    // Tables
    style.CellPadding = ImVec2(4.00f, 2.00f);
    style.TableAngledHeadersAngle = 35.00f;
    style.TableAngledHeadersTextAlign = ImVec2(0.50f, 0.00f);

    // Widgets
    style.WindowTitleAlign = ImVec2(0.00f, 0.50f);
    style.WindowMenuButtonPosition = ImGuiDir_None;
    style.ColorButtonPosition = ImGuiDir_Right;
    style.ButtonTextAlign = ImVec2(0.50f, 0.50f);
    style.SelectableTextAlign = ImVec2(0.00f, 0.00f);
    style.SeparatorTextBorderSize = 3.00f;
    style.SeparatorTextAlign = ImVec2(0.00f, 0.50f);
    style.SeparatorTextPadding = ImVec2(20.00f, 4.00f);
    style.LogSliderDeadzone = 4;

    // Docking
    style.DockingSeparatorSize = 2.00f;

    // Tooltips
    style.HoverFlagsForTooltipMouse = ImGuiHoveredFlags_DelayShort | ImGuiHoveredFlags_Stationary;
    style.HoverFlagsForTooltipNav = ImGuiHoveredFlags_DelayNormal | ImGuiHoveredFlags_NoSharedDelay;

    // Miscellaneous
    style.DisplayWindowPadding = ImVec2(19.00f, 19.0f);
    style.DisplaySafeAreaPadding = ImVec2(3.00f, 3.00f);

    // Color
    ImVec4 background;

    ImVec4 widget;
    ImVec4 widgetHovered;
    ImVec4 widgetActive;

    ImVec4 highlight;
    ImVec4 lowHighlight;

    ImVec4 grab;
    ImVec4 grabHovered;
    ImVec4 grabActive;

    ImVec4* colors = style.Colors;

    switch (theme)
    {
    case UserInterface::Theme::Dark:
        background = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);

        widget = ImVec4(0.16f, 0.16f, 0.16f, 0.54f);
        widgetHovered = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
        widgetActive = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);

        highlight = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        lowHighlight = ImVec4(highlight.x * 0.5f, highlight.y * 0.5f, highlight.z * 0.5f, highlight.w);

        grab = ImVec4(0.28f, 0.28f, 0.28f, 1.00f);
        grabHovered = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
        grabActive = ImVec4(0.42f, 0.42f, 0.42f, 1.00f);

        colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
        colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
        colors[ImGuiCol_WindowBg] = ImVec4(background);
        colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_PopupBg] = ImVec4(background.x * 1.2f, background.y * 1.2f, background.z * 1.2f, background.w);
        colors[ImGuiCol_Border] = ImVec4(widgetHovered.x, widgetHovered.y, widgetHovered.z, 0.30f);
        colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_FrameBg] = ImVec4(widget);
        colors[ImGuiCol_FrameBgHovered] = ImVec4(widgetHovered);
        colors[ImGuiCol_FrameBgActive] = ImVec4(widgetActive);
        colors[ImGuiCol_TitleBg] = ImVec4(background);
        colors[ImGuiCol_TitleBgActive] = ImVec4(background);
        colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
        colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
        colors[ImGuiCol_ScrollbarBg] = ImVec4(widget);
        colors[ImGuiCol_ScrollbarGrab] = ImVec4(grab);
        colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(grabHovered);
        colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(grabActive);
        colors[ImGuiCol_CheckMark] = ImVec4(highlight);
        colors[ImGuiCol_SliderGrab] = ImVec4(grab);
        colors[ImGuiCol_SliderGrabActive] = ImVec4(grabActive);
        colors[ImGuiCol_Button] = ImVec4(widgetHovered);
        colors[ImGuiCol_ButtonHovered] = ImVec4(widgetActive);
        colors[ImGuiCol_ButtonActive] = ImVec4(widget);
        colors[ImGuiCol_Header] = ImVec4(widget);
        colors[ImGuiCol_HeaderHovered] = ImVec4(widgetHovered);
        colors[ImGuiCol_HeaderActive] = ImVec4(widgetActive);
        colors[ImGuiCol_Separator] = ImVec4(grab);
        colors[ImGuiCol_SeparatorHovered] = ImVec4(lowHighlight);
        colors[ImGuiCol_SeparatorActive] = ImVec4(highlight);
        colors[ImGuiCol_ResizeGrip] = ImVec4(widget);
        colors[ImGuiCol_ResizeGripHovered] = ImVec4(widgetHovered);
        colors[ImGuiCol_ResizeGripActive] = ImVec4(widgetActive);
        colors[ImGuiCol_TabHovered] = ImVec4(widgetHovered);
        colors[ImGuiCol_Tab] = ImVec4(widget);
        colors[ImGuiCol_TabSelected] = ImVec4(widgetActive);
        colors[ImGuiCol_TabSelectedOverline] = ImVec4(highlight);
        colors[ImGuiCol_TabDimmed] = ImVec4(widget);
        colors[ImGuiCol_TabDimmedSelected] = ImVec4(widgetHovered);
        colors[ImGuiCol_TabDimmedSelectedOverline] = ImVec4(widgetActive);
        colors[ImGuiCol_DockingPreview] = ImVec4(lowHighlight.x, lowHighlight.y, lowHighlight.z, 0.70f);
        colors[ImGuiCol_DockingEmptyBg] = ImVec4(background);
        colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
        colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
        colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
        colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
        colors[ImGuiCol_TableHeaderBg] = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
        colors[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
        colors[ImGuiCol_TableBorderLight] = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
        colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
        colors[ImGuiCol_TextLink] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        colors[ImGuiCol_TextSelectedBg] = ImVec4(lowHighlight.x, lowHighlight.y, lowHighlight.z, 0.35f);
        colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
        colors[ImGuiCol_NavHighlight] = ImVec4(highlight);
        colors[ImGuiCol_NavWindowingHighlight] = ImVec4(highlight.x, highlight.y, highlight.z, 0.70f);
        colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
        colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
        break;
    case UserInterface::Theme::Light:
        background = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);

        widget = ImVec4(0.84f, 0.84f, 0.84f, 0.54f);
        widgetHovered = ImVec4(0.80f, 0.80f, 0.80f, 1.00f);
        widgetActive = ImVec4(0.76f, 0.76f, 0.76f, 1.00f);

        highlight = ImVec4(0.98f, 0.79f, 0.26f, 1.00f);
        lowHighlight = ImVec4(highlight.x * 0.5f, highlight.y * 0.5f, highlight.z * 0.5f, highlight.w);

        grab = ImVec4(0.72f, 0.72f, 0.72f, 1.00f);
        grabHovered = ImVec4(0.65f, 0.65f, 0.65f, 1.00f);
        grabActive = ImVec4(0.58f, 0.58f, 0.58f, 1.00f);

        colors[ImGuiCol_Text] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
        colors[ImGuiCol_WindowBg] = ImVec4(background);
        colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_PopupBg] = ImVec4(background.x * 1.2f, background.y * 1.2f, background.z * 1.2f, background.w);
        colors[ImGuiCol_Border] = ImVec4(widgetHovered.x, widgetHovered.y, widgetHovered.z, 0.30f);
        colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_FrameBg] = ImVec4(widget);
        colors[ImGuiCol_FrameBgHovered] = ImVec4(widgetHovered);
        colors[ImGuiCol_FrameBgActive] = ImVec4(widgetActive);
        colors[ImGuiCol_TitleBg] = ImVec4(background);
        colors[ImGuiCol_TitleBgActive] = ImVec4(background);
        colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
        colors[ImGuiCol_MenuBarBg] = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
        colors[ImGuiCol_ScrollbarBg] = ImVec4(widget);
        colors[ImGuiCol_ScrollbarGrab] = ImVec4(grab);
        colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(grabHovered);
        colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(grabActive);
        colors[ImGuiCol_CheckMark] = ImVec4(highlight);
        colors[ImGuiCol_SliderGrab] = ImVec4(grab);
        colors[ImGuiCol_SliderGrabActive] = ImVec4(grabActive);
        colors[ImGuiCol_Button] = ImVec4(widgetHovered);
        colors[ImGuiCol_ButtonHovered] = ImVec4(widgetActive);
        colors[ImGuiCol_ButtonActive] = ImVec4(widget);
        colors[ImGuiCol_Header] = ImVec4(widget);
        colors[ImGuiCol_HeaderHovered] = ImVec4(widgetHovered);
        colors[ImGuiCol_HeaderActive] = ImVec4(widgetActive);
        colors[ImGuiCol_Separator] = ImVec4(grab);
        colors[ImGuiCol_SeparatorHovered] = ImVec4(lowHighlight);
        colors[ImGuiCol_SeparatorActive] = ImVec4(highlight);
        colors[ImGuiCol_ResizeGrip] = ImVec4(widget);
        colors[ImGuiCol_ResizeGripHovered] = ImVec4(widgetHovered);
        colors[ImGuiCol_ResizeGripActive] = ImVec4(widgetActive);
        colors[ImGuiCol_TabHovered] = ImVec4(widgetHovered);
        colors[ImGuiCol_Tab] = ImVec4(widget);
        colors[ImGuiCol_TabSelected] = ImVec4(widgetActive);
        colors[ImGuiCol_TabSelectedOverline] = ImVec4(highlight);
        colors[ImGuiCol_TabDimmed] = ImVec4(widget);
        colors[ImGuiCol_TabDimmedSelected] = ImVec4(widgetHovered);
        colors[ImGuiCol_TabDimmedSelectedOverline] = ImVec4(widgetActive);
        colors[ImGuiCol_DockingPreview] = ImVec4(lowHighlight.x, lowHighlight.y, lowHighlight.z, 0.70f);
        colors[ImGuiCol_DockingEmptyBg] = ImVec4(background);
        colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
        colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
        colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
        colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
        colors[ImGuiCol_TableHeaderBg] = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
        colors[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
        colors[ImGuiCol_TableBorderLight] = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
        colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
        colors[ImGuiCol_TextLink] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        colors[ImGuiCol_TextSelectedBg] = ImVec4(lowHighlight.x, lowHighlight.y, lowHighlight.z, 0.35f);
        colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
        colors[ImGuiCol_NavHighlight] = ImVec4(highlight);
        colors[ImGuiCol_NavWindowingHighlight] = ImVec4(highlight.x, highlight.y, highlight.z, 0.70f);
        colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
        colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
        break;
    }
}