#include "BlurBackground.h"

#include <QPainter>
#include <QScreen>
#include <QApplication>
#include <QtMath>

namespace Orangix {

BlurBackground::BlurBackground(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_TranslucentBackground);
}

void BlurBackground::setBlurRadius(qreal radius)
{
    if (qFuzzyCompare(m_blurRadius, radius))
        return;
    m_blurRadius = radius;
    if (!m_captured.isNull())
        m_blurred = blurPixmap(m_captured, m_blurRadius);
    update();
}

void BlurBackground::setSaturation(qreal sat)
{
    m_saturation = sat;
    update();
}

void BlurBackground::captureBackground()
{
    QScreen *screen = QApplication::primaryScreen();
    if (!screen)
        return;

    QPoint globalPos = mapToGlobal(QPoint(0, 0));
    m_captured = screen->grabWindow(0, globalPos.x(), globalPos.y(),
                                     width(), height());
    m_blurred = blurPixmap(m_captured, m_blurRadius);
    update();
}

void BlurBackground::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    if (!m_blurred.isNull()) {
        painter.drawPixmap(rect(), m_blurred);
    } else {
        painter.fillRect(rect(), QColor(0, 0, 0, 180));
    }
}

void BlurBackground::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    captureBackground();
}

QPixmap BlurBackground::blurPixmap(const QPixmap &src, qreal radius)
{
    if (src.isNull() || radius < 1.0)
        return src;

    // Downscale -> blur -> upscale for performance
    qreal scale = 0.25;
    QImage small = src.toImage()
                       .scaled(src.width() * scale, src.height() * scale,
                               Qt::IgnoreAspectRatio, Qt::SmoothTransformation)
                       .convertToFormat(QImage::Format_ARGB32_Premultiplied);

    int w = small.width();
    int h = small.height();
    int r = qCeil(radius * scale);

    // Box blur approximation (3 passes for Gaussian)
    for (int pass = 0; pass < 3; ++pass) {
        // Horizontal
        QImage hBlur(w, h, QImage::Format_ARGB32_Premultiplied);
        for (int y = 0; y < h; ++y) {
            for (int x = 0; x < w; ++x) {
                int rs = 0, gs = 0, bs = 0, as = 0, cnt = 0;
                for (int kx = -r; kx <= r; ++kx) {
                    int sx = qBound(0, x + kx, w - 1);
                    QRgb p = small.pixel(sx, y);
                    rs += qRed(p); gs += qGreen(p); bs += qBlue(p); as += qAlpha(p);
                    ++cnt;
                }
                hBlur.setPixel(x, y, qRgba(rs/cnt, gs/cnt, bs/cnt, as/cnt));
            }
        }
        // Vertical
        for (int y = 0; y < h; ++y) {
            for (int x = 0; x < w; ++x) {
                int rs = 0, gs = 0, bs = 0, as = 0, cnt = 0;
                for (int ky = -r; ky <= r; ++ky) {
                    int sy = qBound(0, y + ky, h - 1);
                    QRgb p = hBlur.pixel(x, sy);
                    rs += qRed(p); gs += qGreen(p); bs += qBlue(p); as += qAlpha(p);
                    ++cnt;
                }
                small.setPixel(x, y, qRgba(rs/cnt, gs/cnt, bs/cnt, as/cnt));
            }
        }
    }

    QImage result = small.scaled(src.size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    return QPixmap::fromImage(result);
}

} // namespace Orangix
