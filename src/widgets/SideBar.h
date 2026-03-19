#ifndef ORANGIX_SIDEBAR_H
#define ORANGIX_SIDEBAR_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QList>

namespace Orangix {

class SideBar : public QWidget
{
    Q_OBJECT

public:
    explicit SideBar(QWidget *parent = nullptr);

    void addItem(const QIcon &icon, const QString &text, const QString &id);
    void addSeparator();
    void setActiveItem(const QString &id);

signals:
    void itemClicked(const QString &id);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    struct SideBarItem {
        QPushButton *button = nullptr;
        QString id;
    };

    QVBoxLayout *m_layout = nullptr;
    QList<SideBarItem> m_items;
    QString m_activeId;

    static constexpr int SideBarWidth = 220;
};

} // namespace Orangix

#endif // ORANGIX_SIDEBAR_H
