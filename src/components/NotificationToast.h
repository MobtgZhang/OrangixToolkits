#ifndef ORANGIX_NOTIFICATIONTOAST_H
#define ORANGIX_NOTIFICATIONTOAST_H

#include <QWidget>
#include <QLabel>
#include <QPropertyAnimation>
#include <QTimer>

namespace Orangix {

class NotificationToast : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(qreal slideProgress READ slideProgress WRITE setSlideProgress)

public:
    explicit NotificationToast(QWidget *parent = nullptr);

    void show(const QString &title, const QString &message,
              const QIcon &icon = QIcon(), int durationMs = 5000);

    qreal slideProgress() const { return m_slideProgress; }
    void setSlideProgress(qreal progress);

signals:
    void clicked();
    void dismissed();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    void animateIn();
    void animateOut();

    QLabel *m_titleLabel = nullptr;
    QLabel *m_messageLabel = nullptr;
    QLabel *m_iconLabel = nullptr;

    qreal m_slideProgress = 0.0;
    QPropertyAnimation *m_slideAnim = nullptr;
    QTimer *m_autoHideTimer = nullptr;

    static constexpr int ToastWidth = 320;
    static constexpr int ToastMinHeight = 64;
    static constexpr int ScreenMarginRight = 16;
    static constexpr int ScreenMarginTop = 48;
};

} // namespace Orangix

#endif // ORANGIX_NOTIFICATIONTOAST_H
