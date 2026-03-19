#ifndef ORANGIX_GLASSPANEL_H
#define ORANGIX_GLASSPANEL_H

#include <QWidget>
#include <QColor>

namespace Orangix {

/**
 * Win7 Aero-style glass panel with blur effect and highlight border.
 * Use as a container for menus, popups, dock backgrounds, etc.
 */
class GlassPanel : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(qreal blurRadius READ blurRadius WRITE setBlurRadius)
    Q_PROPERTY(QColor tintColor READ tintColor WRITE setTintColor)
    Q_PROPERTY(int cornerRadius READ cornerRadius WRITE setCornerRadius)

public:
    explicit GlassPanel(QWidget *parent = nullptr);

    qreal blurRadius() const { return m_blurRadius; }
    void setBlurRadius(qreal radius);

    QColor tintColor() const { return m_tintColor; }
    void setTintColor(const QColor &color);

    QColor borderColor() const { return m_borderColor; }
    void setBorderColor(const QColor &color);

    int cornerRadius() const { return m_cornerRadius; }
    void setCornerRadius(int radius);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    qreal m_blurRadius = 20.0;
    QColor m_tintColor = QColor(255, 255, 255, 38);
    QColor m_borderColor = QColor(255, 255, 255, 76);
    int m_cornerRadius = 12;
};

} // namespace Orangix

#endif // ORANGIX_GLASSPANEL_H
