#include "NotificationToast.h"
#include "OrangixStyle.h"

#include <QPainter>
#include <QPainterPath>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScreen>
#include <QApplication>
#include <QMouseEvent>

namespace Orangix {

NotificationToast::NotificationToast(QWidget *parent)
    : QWidget(parent, Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool)
{
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_ShowWithoutActivating);
    setFixedWidth(ToastWidth);

    auto *mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(16, 12, 16, 12);
    mainLayout->setSpacing(12);

    m_iconLabel = new QLabel(this);
    m_iconLabel->setFixedSize(24, 24);
    m_iconLabel->hide();
    mainLayout->addWidget(m_iconLabel, 0, Qt::AlignTop);

    auto *textLayout = new QVBoxLayout();
    textLayout->setSpacing(4);

    m_titleLabel = new QLabel(this);
    m_titleLabel->setStyleSheet("color: rgba(255,255,255,0.95); font-weight: bold; font-size: 13px;");
    m_titleLabel->setWordWrap(true);
    textLayout->addWidget(m_titleLabel);

    m_messageLabel = new QLabel(this);
    m_messageLabel->setStyleSheet("color: rgba(255,255,255,0.7); font-size: 12px;");
    m_messageLabel->setWordWrap(true);
    textLayout->addWidget(m_messageLabel);

    mainLayout->addLayout(textLayout, 1);

    m_slideAnim = new QPropertyAnimation(this, "slideProgress", this);
    m_slideAnim->setEasingCurve(QEasingCurve::OutCubic);

    m_autoHideTimer = new QTimer(this);
    m_autoHideTimer->setSingleShot(true);
    connect(m_autoHideTimer, &QTimer::timeout, this, &NotificationToast::animateOut);
}

void NotificationToast::show(const QString &title, const QString &message,
                              const QIcon &icon, int durationMs)
{
    m_titleLabel->setText(title);
    m_messageLabel->setText(message);

    if (!icon.isNull()) {
        m_iconLabel->setPixmap(icon.pixmap(24, 24));
        m_iconLabel->show();
    } else {
        m_iconLabel->hide();
    }

    adjustSize();
    animateIn();

    if (durationMs > 0) {
        m_autoHideTimer->start(durationMs);
    }
}

void NotificationToast::setSlideProgress(qreal progress)
{
    m_slideProgress = progress;

    QScreen *screen = QApplication::primaryScreen();
    if (!screen) return;

    QRect screenRect = screen->geometry();
    int targetX = screenRect.right() - ToastWidth - ScreenMarginRight;
    int offscreenX = screenRect.right() + 10;
    int y = ScreenMarginTop;

    int x = offscreenX + (targetX - offscreenX) * progress;
    move(x, y);
    setWindowOpacity(progress);
}

void NotificationToast::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPainterPath path;
    path.addRoundedRect(QRectF(rect()).adjusted(2, 2, -2, -2),
                        Style::RadiusMedium, Style::RadiusMedium);

    // Shadow
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(0, 0, 0, 50));
    painter.drawPath(path.translated(0, 3));

    // Glass background
    QLinearGradient gradient(rect().topLeft(), rect().bottomLeft());
    gradient.setColorAt(0.0, QColor(40, 40, 50, 230));
    gradient.setColorAt(1.0, QColor(30, 30, 40, 230));
    painter.setBrush(gradient);
    painter.drawPath(path);

    // Border
    painter.setPen(QPen(QColor(255, 255, 255, 40), 0.5));
    painter.setBrush(Qt::NoBrush);
    painter.drawPath(path);
}

void NotificationToast::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked();
        animateOut();
    }
}

void NotificationToast::animateIn()
{
    QWidget::show();
    m_slideAnim->stop();
    m_slideAnim->setDuration(300);
    m_slideAnim->setStartValue(0.0);
    m_slideAnim->setEndValue(1.0);
    m_slideAnim->setEasingCurve(QEasingCurve::OutCubic);
    m_slideAnim->start();
}

void NotificationToast::animateOut()
{
    m_slideAnim->stop();
    m_slideAnim->setDuration(200);
    m_slideAnim->setStartValue(m_slideProgress);
    m_slideAnim->setEndValue(0.0);
    m_slideAnim->setEasingCurve(QEasingCurve::InCubic);
    connect(m_slideAnim, &QPropertyAnimation::finished, this, [this]() {
        QWidget::hide();
        emit dismissed();
    });
    m_slideAnim->start();
}

} // namespace Orangix
