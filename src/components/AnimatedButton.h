#ifndef ORANGIX_ANIMATEDBUTTON_H
#define ORANGIX_ANIMATEDBUTTON_H

#include <QPushButton>
#include <QPropertyAnimation>
#include <QColor>

namespace Orangix {

/**
 * Button with hover glow, press scale, and smooth transitions.
 * Follows Citrus Design Language animation specs.
 */
class AnimatedButton : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(qreal hoverProgress READ hoverProgress WRITE setHoverProgress)
    Q_PROPERTY(qreal pressScale READ pressScale WRITE setPressScale)

public:
    enum ButtonStyle {
        Primary,   // Orangix orange background
        Secondary, // Transparent with border
        Ghost      // Transparent, text only
    };

    explicit AnimatedButton(const QString &text = QString(), QWidget *parent = nullptr);

    void setButtonStyle(ButtonStyle style);
    ButtonStyle buttonStyle() const { return m_style; }

    qreal hoverProgress() const { return m_hoverProgress; }
    void setHoverProgress(qreal progress);

    qreal pressScale() const { return m_pressScale; }
    void setPressScale(qreal scale);

protected:
    void paintEvent(QPaintEvent *event) override;
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    void setupAnimations();

    ButtonStyle m_style = Primary;
    qreal m_hoverProgress = 0.0;
    qreal m_pressScale = 1.0;

    QPropertyAnimation *m_hoverAnim = nullptr;
    QPropertyAnimation *m_pressAnim = nullptr;
};

} // namespace Orangix

#endif // ORANGIX_ANIMATEDBUTTON_H
