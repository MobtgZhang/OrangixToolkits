#ifndef ORANGIX_STYLE_H
#define ORANGIX_STYLE_H

#include <QColor>
#include <QFont>

namespace Orangix::Style {

// Corner radii
constexpr int RadiusSmall = 8;
constexpr int RadiusMedium = 12;
constexpr int RadiusLarge = 16;
constexpr int RadiusXLarge = 20;
constexpr int RadiusFull = 999;

// Animation durations (ms)
constexpr int AnimHover = 150;
constexpr int AnimPanel = 200;
constexpr int AnimWindow = 250;
constexpr int AnimWorkspace = 350;

// Spacing (4px grid)
constexpr int SpaceXS = 4;
constexpr int SpaceSM = 8;
constexpr int SpaceMD = 12;
constexpr int SpaceLG = 16;
constexpr int SpaceXL = 24;
constexpr int SpaceXXL = 32;

// Brand colors
inline QColor brandOrange()    { return QColor(0xFF, 0x8C, 0x42); }
inline QColor brandOrangeLight() { return QColor(0xFF, 0x9A, 0x5C); }
inline QColor brandOrangeDark()  { return QColor(0xE0, 0x7A, 0x38); }

// Semantic colors
inline QColor colorDanger()    { return QColor(0xFF, 0x5F, 0x57); }
inline QColor colorWarning()   { return QColor(0xFF, 0xBD, 0x2E); }
inline QColor colorSuccess()   { return QColor(0x28, 0xCA, 0x41); }

// Glass/Aero colors
inline QColor glassWhite(int alpha = 38)  { return QColor(255, 255, 255, alpha); }
inline QColor glassBlack(int alpha = 100) { return QColor(0, 0, 0, alpha); }
inline QColor glassBorder()    { return QColor(255, 255, 255, 76); }

// Text colors
inline QColor textPrimary()    { return QColor(255, 255, 255, 230); }
inline QColor textSecondary()  { return QColor(255, 255, 255, 153); }
inline QColor textDisabled()   { return QColor(255, 255, 255, 77); }

// Shadow
constexpr int ShadowBlurActive = 32;
constexpr int ShadowBlurInactive = 16;
constexpr int ShadowOffsetY = 8;

// Blur
constexpr qreal BlurRadiusPanel = 20.0;
constexpr qreal BlurRadiusTopBar = 30.0;
constexpr qreal BlurRadiusBackground = 40.0;

// Fonts
inline QFont fontBody()  { return QFont("Sans", 13); }
inline QFont fontSmall() { return QFont("Sans", 11); }
inline QFont fontTitle() { return QFont("Sans", 16, QFont::Bold); }
inline QFont fontH1()    { return QFont("Sans", 22, QFont::Bold); }

} // namespace Orangix::Style

#endif // ORANGIX_STYLE_H
