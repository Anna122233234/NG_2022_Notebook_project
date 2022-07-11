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
    void on_actionOpen_triggered();
    void on_actionSave_as_triggered();
    void on_actionExit_triggered();
    void on_actionCopy_triggered();
    void on_actionPaste_triggered();
    void on_actionCut_triggered();
    void on_actionUndo_triggered();
    void on_actionRedo_triggered();
    void on_actionRed_triggered();
    void on_actionGreen_triggered();
    void on_actionGray_triggered();
    void on_actionWhite_triggered();
    void on_actionSave_triggered();
    void systemfile();
    void search();
    void addfiles();
    void deleteitem();

private:
    Ui::Notepad *ui;
    QString currentFile = "";
};
#endif // NOTEPAD_H
