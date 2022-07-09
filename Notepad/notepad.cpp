#include "notepad.h"
#include "ui_notepad.h"

#include <fstream>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QPrinter>
#include <QPrintDialog>
#include <QColorDialog>

QString globalCol;
Notepad::Notepad(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Notepad)
{
    ui->setupUi(this);
    //this->setCentralWidget(ui->TextWindow);
    connect(ui->Edit,&QPushButton::clicked,this,&Notepad::on_Edit_clicked);

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
        QMessageBox::warning(this, "Warning", " Cannot open file" + file.errorString());
        return;
    }
    setWindowTitle(filename);
    QTextStream in(&file);
    ui->TextWindow->setTextColor(globalCol);
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
    ui->TextWindow->setTextColor(globalCol);
    QString text = ui->TextWindow->toPlainText();
    out << text;
    file.close();
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

void Notepad::on_actionRed_triggered()
{

//   bool colorSelected;
//  QString color = QColorDialog::getColor(&colorSelected, this);
//  if (colorSelected)
//          ui->TextWindow->setTextColor(color);


    ui->TextWindow->setTextColor(Qt::red);
    QString color = ui->TextWindow->textColor().name();
    globalCol = color;
}

void Notepad::on_actionGreen_triggered()
{
    ui->TextWindow->setTextColor(Qt::green);
    QString color = ui->TextWindow->textColor().name();
    globalCol = color;
}

void Notepad::on_actionGray_triggered()
{
    ui->TextWindow->setTextColor(Qt::gray);
    QString color = ui->TextWindow->textColor().name();
    globalCol = color;
}

void Notepad::on_actionWhite_triggered()
{
    ui->TextWindow->setTextColor(Qt::white);
    ui->TextWindow->setTextBackgroundColor(Qt::black);
    QString color = ui->TextWindow->textColor().name();
    globalCol = color;
}

void Notepad::on_actionSave_triggered()
{
    QFile file("D:/Notebook/NG_2022_Notebook_project/" + ui->Name->text());
    if(!file.open(QFile:: WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Cannot save file" + file.errorString());
        return;
    }
}

void Notepad::on_Edit_clicked()
{
    QFile file("D:/Notebook/NG_2022_Notebook_project/Notepad/SystemFile.txt");
    if(!file.open(QFile:: WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Cannot save file" + file.errorString());
        return;
    }
        QString name = ui->Name->text();
        QString tag = ui->Tag->text();
        QTextStream stream(&file);
        stream << name << Qt::endl << tag;
    file.close();
}


void Notepad::on_Search_clicked()
{

}

