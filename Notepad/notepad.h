#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Notepad; }
QT_END_NAMESPACE

class Notepad : public QMainWindow
{
    Q_OBJECT

public:
    Notepad(QWidget *parent = nullptr);
    ~Notepad();

private slots:
    void on_actionNew_triggered();
    void on_actionExit_triggered();
    void on_actionCopy_triggered();
    void on_actionPaste_triggered();
    void on_actionCut_triggered();
    void on_actionUndo_triggered();
    void on_actionRedo_triggered();
    void systemfile();
    void search();
    void addfiles();
    void deleteitem();
    void setRedColor();
    void setBlueColor();
    void setYellowColor();
    void setGreenColor();
    void setGrayColor();

private:
    Ui::Notepad *ui;
    QString currentFile = "";
    QAction *Red;
    QAction *Blue;
    QAction *Yellow;
    QAction *Green;
    QAction *Gray;
};
#endif // NOTEPAD_H
