#include "notepad.h"
#include "ui_notepad.h"

#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QPrinter>
#include <QPrintDialog>

Notepad::Notepad(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Notepad)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->TextWindow);

}

Notepad::~Notepad()
{
    delete ui;
}

void Notepad::on_actionNew_triggered()
{
    currentFile.clear();
    ui->TextWindow->setText(QString());

}

void Notepad::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open the file");
    QFile file(filename);
    currentFile = filename;
    if(!file.open(QIODevice:: ReadOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Cannot open file" + file.errorString());
        return;
    }
    setWindowTitle(filename);
    QTextStream in(&file);
    //QString text = in.readAll;
    ui->TextWindow->setText(in.readAll());
    file.close();
}

void Notepad::on_actionSave_as_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save as");
    QFile file(filename);
    currentFile = filename;
    if(!file.open(QFile:: WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Cannot save file" + file.errorString());
        return;
    }
    setWindowTitle(filename);
    QTextStream out(&file);
    QString text = ui->TextWindow->toPlainText();
    out << text;
    file.close();
}

void Notepad::on_actionPrint_triggered()
{
    QPrinter printer;
    printer.setPrinterName("Printer Name");
    QPrintDialog pDialog(&printer, this);
    if(pDialog.exec() == QDialog::Rejected){
        QMessageBox::warning(this, "Warning", "Cannot Acces printer");
        return;
    }
    ui->TextWindow->print(&printer);

}

void Notepad::on_actionExit_triggered()
{
    QApplication::quit();
}

void Notepad::on_actionCopy_triggered()
{
    ui->TextWindow->copy();
}

void Notepad::on_actionPaste_triggered()
{
    ui->TextWindow->paste();
}

void Notepad::on_actionCut_triggered()
{
    ui->TextWindow->cut();
}

void Notepad::on_actionUndo_triggered()
{
    ui->TextWindow->undo();
}

void Notepad::on_actionRedo_triggered()
{
    ui->TextWindow->redo();
}
