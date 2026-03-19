#ifndef ORANGIX_BLURBACKGROUND_H
#define ORANGIX_BLURBACKGROUND_H

#include <QWidget>
#include <QPixmap>

namespace Orangix {

/**
 * A container widget that applies real-time blur to whatever is behind it.
 * For composited environments, uses the compositor's blur protocol.
 * Fallback: captures and blurs a static snapshot.
 */
class BlurBackground : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(qreal blurRadius READ blurRadius WRITE setBlurRadius)
    Q_PROPERTY(qreal saturation READ saturation WRITE setSaturation)

public:
    explicit BlurBackground(QWidget *parent = nullptr);

    qreal blurRadius() const { return m_blurRadius; }
    void setBlurRadius(qreal radius);

    qreal saturation() const { return m_saturation; }
    void setSaturation(qreal sat);

    void captureBackground();

protected:
    void paintEvent(QPaintEvent *event) override;
    void showEvent(QShowEvent *event) override;

private:
    QPixmap blurPixmap(const QPixmap &src, qreal radius);

    qreal m_blurRadius = 20.0;
    qreal m_saturation = 1.0;
    QPixmap m_captured;
    QPixmap m_blurred;
};

} // namespace Orangix

#endif // ORANGIX_BLURBACKGROUND_H
