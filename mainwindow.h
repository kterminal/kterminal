#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPushButton>


class MainWindow : public QWidget {
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
    private:
        QPushButton *m_button;
};

#endif
