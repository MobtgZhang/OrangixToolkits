#include "GlassPanel.h"
#include "OrangixStyle.h"

#include <QPainter>
#include <QPainterPath>

namespace Orangix {

GlassPanel::GlassPanel(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_TranslucentBackground);
}

void GlassPanel::setBlurRadius(qreal radius)
{
    m_blurRadius = radius;
    update();
}

void GlassPanel::setTintColor(const QColor &color)
{
    m_tintColor = color;
    update();
}

void GlassPanel::setBorderColor(const QColor &color)
{
    m_borderColor = color;
    update();
}

void GlassPanel::setCornerRadius(int radius)
{
    m_cornerRadius = radius;
    update();
}

void GlassPanel::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QRectF panelRect = QRectF(rect()).adjusted(1, 1, -1, -1);
    QPainterPath path;
    path.addRoundedRect(panelRect, m_cornerRadius, m_cornerRadius);

    // Shadow layer
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(0, 0, 0, 50));
    QPainterPath shadowPath;
    shadowPath.addRoundedRect(panelRect.translated(0, 3), m_cornerRadius, m_cornerRadius);
    painter.drawPath(shadowPath);

    // Glass fill with gradient (Aero characteristic)
    QLinearGradient gradient(panelRect.topLeft(), panelRect.bottomLeft());
    gradient.setColorAt(0.0, QColor(m_tintColor.red(), m_tintColor.green(),
                                     m_tintColor.blue(), m_tintColor.alpha() + 15));
    gradient.setColorAt(0.4, m_tintColor);
    gradient.setColorAt(1.0, QColor(m_tintColor.red(), m_tintColor.green(),
                                     m_tintColor.blue(), m_tintColor.alpha() - 10));

    painter.setBrush(gradient);
    painter.drawPath(path);

    // Border
    painter.setPen(QPen(m_borderColor, 1.0));
    painter.setBrush(Qt::NoBrush);
    painter.drawPath(path);

    // Top highlight line (Aero signature effect)
    painter.setPen(QPen(QColor(255, 255, 255, 90), 0.5));
    qreal hlLeft = panelRect.left() + m_cornerRadius;
    qreal hlRight = panelRect.right() - m_cornerRadius;
    painter.drawLine(QPointF(hlLeft, panelRect.top() + 1.5),
                     QPointF(hlRight, panelRect.top() + 1.5));
}

} // namespace Orangix
