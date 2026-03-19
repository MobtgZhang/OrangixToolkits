#include "SearchBar.h"
#include "../components/OrangixStyle.h"

#include <QFocusEvent>

namespace Orangix {

SearchBar::SearchBar(QWidget *parent)
    : QLineEdit(parent)
{
    setupStyle();

    m_expandAnim = new QPropertyAnimation(this, "expandedWidth", this);
    m_expandAnim->setDuration(Style::AnimHover);
    m_expandAnim->setEasingCurve(QEasingCurve::OutCubic);
}

void SearchBar::setCollapsedWidth(int width)
{
    m_collapsedWidth = width;
    if (!hasFocus())
        setFixedWidth(width);
}

void SearchBar::setExpandedWidth(int width)
{
    m_expandedWidth = width;
    setFixedWidth(width);
}

void SearchBar::setupStyle()
{
    setFixedHeight(36);
    setFixedWidth(m_collapsedWidth);
    setPlaceholderText("  Search...");

    setStyleSheet(
        "QLineEdit {"
        "  background: rgba(255,255,255,0.08);"
        "  border: 1px solid rgba(255,255,255,0.1);"
        "  border-radius: 18px;"
        "  color: rgba(255,255,255,0.9);"
        "  padding: 0 16px;"
        "  font-size: 13px;"
        "  selection-background-color: rgba(255,140,66,0.4);"
        "}"
        "QLineEdit:focus {"
        "  border: 1px solid rgba(255,140,66,0.6);"
        "  background: rgba(255,255,255,0.12);"
        "}"
    );
}

void SearchBar::focusInEvent(QFocusEvent *event)
{
    QLineEdit::focusInEvent(event);
    m_expandAnim->stop();
    m_expandAnim->setStartValue(width());
    m_expandAnim->setEndValue(m_maxExpandedWidth);
    m_expandAnim->start();
}

void SearchBar::focusOutEvent(QFocusEvent *event)
{
    QLineEdit::focusOutEvent(event);
    if (text().isEmpty()) {
        m_expandAnim->stop();
        m_expandAnim->setStartValue(width());
        m_expandAnim->setEndValue(m_collapsedWidth);
        m_expandAnim->start();
    }
}

} // namespace Orangix
