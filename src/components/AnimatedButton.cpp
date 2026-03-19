#include "AnimatedButton.h"
#include "OrangixStyle.h"

#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>

namespace Orangix {

AnimatedButton::AnimatedButton(const QString &text, QWidget *parent)
    : QPushButton(text, parent)
{
    setCursor(Qt::PointingHandCursor);
    setFixedHeight(36);
    setupAnimations();
}

void AnimatedButton::setButtonStyle(ButtonStyle style)
{
    m_style = style;
    update();
}

void AnimatedButton::setHoverProgress(qreal progress)
{
    m_hoverProgress = progress;
    update();
}

void AnimatedButton::setPressScale(qreal scale)
{
    m_pressScale = scale;
    update();
}

void AnimatedButton::setupAnimations()
{
    m_hoverAnim = new QPropertyAnimation(this, "hoverProgress", this);
    m_hoverAnim->setDuration(Style::AnimHover);
    m_hoverAnim->setEasingCurve(QEasingCurve::OutCubic);

    m_pressAnim = new QPropertyAnimation(this, "pressScale", this);
    m_pressAnim->setDuration(80);
    m_pressAnim->setEasingCurve(QEasingCurve::InOutCubic);
}

void AnimatedButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QRectF btnRect = QRectF(rect());

    // Apply press scale transform
    if (m_pressScale != 1.0) {
        painter.translate(btnRect.center());
        painter.scale(m_pressScale, m_pressScale);
        painter.translate(-btnRect.center());
    }

    int radius = Style::RadiusMedium;
    QPainterPath path;
    path.addRoundedRect(btnRect.adjusted(1, 1, -1, -1), radius, radius);

    switch (m_style) {
    case Primary: {
        QColor bg = Style::brandOrange();
        QColor bgHover = Style::brandOrangeLight();
        QColor mixed(
            bg.red() + (bgHover.red() - bg.red()) * m_hoverProgress,
            bg.green() + (bgHover.green() - bg.green()) * m_hoverProgress,
            bg.blue() + (bgHover.blue() - bg.blue()) * m_hoverProgress
        );
        painter.setPen(Qt::NoPen);
        painter.setBrush(isEnabled() ? mixed : QColor(128, 128, 128, 60));
        painter.drawPath(path);

        // Hover glow
        if (m_hoverProgress > 0.01) {
            painter.setOpacity(m_hoverProgress * 0.3);
            QPainterPath glowPath;
            glowPath.addRoundedRect(btnRect.adjusted(-2, -2, 2, 2), radius + 2, radius + 2);
            painter.setBrush(QColor(0xFF, 0x8C, 0x42, 60));
            painter.drawPath(glowPath);
            painter.setOpacity(1.0);
        }
        break;
    }
    case Secondary: {
        QColor fill(255, 255, 255, static_cast<int>(m_hoverProgress * 20));
        painter.setPen(QPen(Style::glassBorder(), 1));
        painter.setBrush(fill);
        painter.drawPath(path);
        break;
    }
    case Ghost: {
        if (m_hoverProgress > 0.01) {
            QColor fill(255, 255, 255, static_cast<int>(m_hoverProgress * 15));
            painter.setPen(Qt::NoPen);
            painter.setBrush(fill);
            painter.drawPath(path);
        }
        break;
    }
    }

    // Text
    QColor textColor = isEnabled() ? Style::textPrimary() : Style::textDisabled();
    painter.setPen(textColor);
    painter.setFont(Style::fontBody());
    painter.drawText(btnRect, Qt::AlignCenter, text());
}

void AnimatedButton::enterEvent(QEnterEvent *)
{
    m_hoverAnim->stop();
    m_hoverAnim->setStartValue(m_hoverProgress);
    m_hoverAnim->setEndValue(1.0);
    m_hoverAnim->start();
}

void AnimatedButton::leaveEvent(QEvent *)
{
    m_hoverAnim->stop();
    m_hoverAnim->setStartValue(m_hoverProgress);
    m_hoverAnim->setEndValue(0.0);
    m_hoverAnim->start();
}

void AnimatedButton::mousePressEvent(QMouseEvent *event)
{
    QPushButton::mousePressEvent(event);
    m_pressAnim->stop();
    m_pressAnim->setStartValue(m_pressScale);
    m_pressAnim->setEndValue(0.96);
    m_pressAnim->start();
}

void AnimatedButton::mouseReleaseEvent(QMouseEvent *event)
{
    QPushButton::mouseReleaseEvent(event);
    m_pressAnim->stop();
    m_pressAnim->setStartValue(m_pressScale);
    m_pressAnim->setEndValue(1.0);
    m_pressAnim->start();
}

} // namespace Orangix
