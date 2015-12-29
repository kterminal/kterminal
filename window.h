#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QPushButton>

class QPushButton;
class Window : public QWidget {
    Q_OBJECT
    public:
        explicit Window(QWidget *parent = 0);
    private:
        QPushButton *m_button;
};

#endif // WINDOW_H
