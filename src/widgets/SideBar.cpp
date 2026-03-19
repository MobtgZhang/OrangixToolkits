#include "SideBar.h"
#include "../components/OrangixStyle.h"

#include <QPainter>
#include <QPainterPath>

namespace Orangix {

SideBar::SideBar(QWidget *parent)
    : QWidget(parent)
{
    setFixedWidth(SideBarWidth);

    m_layout = new QVBoxLayout(this);
    m_layout->setContentsMargins(8, 8, 8, 8);
    m_layout->setSpacing(2);
    m_layout->setAlignment(Qt::AlignTop);
}

void SideBar::addItem(const QIcon &icon, const QString &text, const QString &id)
{
    auto *btn = new QPushButton(icon, text, this);
    btn->setFixedHeight(32);
    btn->setCursor(Qt::PointingHandCursor);
    btn->setStyleSheet(
        "QPushButton {"
        "  background: transparent;"
        "  border: none;"
        "  border-radius: 8px;"
        "  color: rgba(255,255,255,0.8);"
        "  text-align: left;"
        "  padding: 0 12px;"
        "  font-size: 13px;"
        "}"
        "QPushButton:hover {"
        "  background: rgba(255,255,255,0.08);"
        "}"
        "QPushButton:checked, QPushButton[active=\"true\"] {"
        "  background: rgba(255,140,66,0.2);"
        "  color: #FF8C42;"
        "}"
    );

    connect(btn, &QPushButton::clicked, this, [this, id]() {
        setActiveItem(id);
        emit itemClicked(id);
    });

    SideBarItem item{btn, id};
    m_items.append(item);
    m_layout->addWidget(btn);
}

void SideBar::addSeparator()
{
    auto *separator = new QWidget(this);
    separator->setFixedHeight(1);
    separator->setStyleSheet("background: rgba(255,255,255,0.08);");
    m_layout->addSpacing(4);
    m_layout->addWidget(separator);
    m_layout->addSpacing(4);
}

void SideBar::setActiveItem(const QString &id)
{
    m_activeId = id;
    for (auto &item : m_items) {
        bool active = (item.id == id);
        item.button->setProperty("active", active);
        item.button->style()->unpolish(item.button);
        item.button->style()->polish(item.button);
    }
}

void SideBar::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Aero glass sidebar background
    QLinearGradient gradient(0, 0, width(), 0);
    gradient.setColorAt(0.0, QColor(255, 255, 255, 12));
    gradient.setColorAt(1.0, QColor(255, 255, 255, 5));

    painter.fillRect(rect(), gradient);

    // Right border
    painter.setPen(QPen(QColor(255, 255, 255, 20), 0.5));
    painter.drawLine(width() - 1, 0, width() - 1, height());
}

} // namespace Orangix
