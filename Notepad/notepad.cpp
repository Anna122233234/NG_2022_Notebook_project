#include "notepad.h"
#include "ui_notepad.h"

#include <QDebug>
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
    connect(ui->Add,&QPushButton::clicked,this,&Notepad::systemfile);
    connect(ui->Search,&QPushButton::clicked,this,&Notepad::search);
    connect(ui->ListW,&QListWidget::clicked,this,&Notepad::addfiles);
    connect(ui->Delete,&QPushButton::clicked,this,&Notepad::deleteitem);
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
    QFile file("D:/Notebook/NG_2022_Notebook_project/" + ui->Name->text() + ".txt");
    if(!file.open(QFile:: WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Cannot save file" + file.errorString());
        return;
    }
    QString text = ui->TextWindow->toPlainText();
    file.write(text.toUtf8());
    file.close();
}

void Notepad::systemfile()
{
    QFile sysfile("D:/Notebook/NG_2022_Notebook_project/Notepad/SystemFile.txt");
    QString name = ui->Name->text();
    QString tag = ui->Tag->text();
    QString note = name + ":" + tag + "\n";
    if(!sysfile.isOpen()){
        sysfile.open(QIODevice::Append);
        sysfile.write(note.toUtf8());
        sysfile.close();
    }
}

void Notepad::search()
{
    QFile file("D:/Notebook/NG_2022_Notebook_project/Notepad/SystemFile.txt");
    if(!file.isOpen()){
        file.open(QIODevice::ReadOnly);
        QString ntfile = file.readAll();
        ntfile = ntfile.remove(ntfile.length()-1,1);
        QStringList list = ntfile.split("\n");
        qDebug() << "List = " << list;
        foreach(QString item, list)
            qDebug() << "List item = " << item;
        QString name = ui->Name->text();
        QString tag = ui->Tag->text();
        QString note = name + ":" + tag + "\n";
        qDebug() << note;
        qDebug () << "This is name: " <<name ;
        qDebug () << "This is note: " <<tag ;
        foreach(QString item, list){
            QStringList input = item.split(":");
            if((name != ""  && name == input.at(0))){
                if(tag == "" || tag == input.at(1)){
                    qDebug() << item;
                    ui->ListW->addItem(item);
                }
            }
            else if (tag != "" && tag == input.at(1)){
                qDebug() << item;
                ui->ListW->addItem(item);
            }
        }
        file.close();
    }
}

void Notepad::addfiles()
{
    QFile filename("D:/Notebook/NG_2022_Notebook_project/Notepad/SystemFile.txt");
    if(!filename.isOpen()){
        filename.open(QIODevice::ReadOnly);
        QString ntfile = filename.readAll();
        ntfile = ntfile.remove(ntfile.length()-1,1);
        QStringList list = ntfile.split("\n");
        qDebug() << "LIST++" << list;
        QString name = ui->Name->text();
        QString tag = ui->Tag->text();
        QString note = name + ":" + tag + "\n";
        foreach(QString item, list){
            QStringList input = item.split(":");
            if(tag == input.at(1)){
                name = input.at(0);
                qDebug() << "name___" << name;
            }
        }
        QFile secondfile("D:/Notebook/NG_2022_Notebook_project/" + name + ".txt");
        if(!secondfile.isOpen()){
            secondfile.open(QIODevice::ReadWrite);
            ui->TextWindow->setText(secondfile.readAll());
            secondfile.close();
        }
    }
    filename.close();
}

void Notepad::deleteitem()
{
    QListWidgetItem *it = ui->ListW->takeItem(ui->ListW->currentRow());
        delete it;
}
