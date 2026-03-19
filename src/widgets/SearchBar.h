#ifndef ORANGIX_SEARCHBAR_H
#define ORANGIX_SEARCHBAR_H

#include <QLineEdit>
#include <QPropertyAnimation>

namespace Orangix {

class SearchBar : public QLineEdit
{
    Q_OBJECT
    Q_PROPERTY(int expandedWidth READ expandedWidth WRITE setExpandedWidth)

public:
    explicit SearchBar(QWidget *parent = nullptr);

    int collapsedWidth() const { return m_collapsedWidth; }
    void setCollapsedWidth(int width);

    int expandedWidth() const { return m_expandedWidth; }
    void setExpandedWidth(int width);

protected:
    void focusInEvent(QFocusEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;

private:
    void setupStyle();

    int m_collapsedWidth = 200;
    int m_expandedWidth = 200;
    int m_maxExpandedWidth = 360;
    QPropertyAnimation *m_expandAnim = nullptr;
};

} // namespace Orangix

#endif // ORANGIX_SEARCHBAR_H
