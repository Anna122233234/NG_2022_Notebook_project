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
#include <QAction>

QString globalCol;
Notepad::Notepad(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Notepad)
{
    ui->setupUi(this);
    Red = new QAction("Red");
    ui->menuTextColor->addAction(Red);

    Blue = new QAction("Blue");
    ui->menuTextColor->addAction(Blue);

    Yellow = new QAction("Yellow");
    ui->menuTextColor->addAction(Yellow);

    Green = new QAction("Green");
    ui->menuTextColor->addAction(Green);

    Gray = new QAction("Gray");
    ui->menuTextColor->addAction(Gray);

    connect(Red,&QAction::triggered,this,&Notepad::setRedColor);
    connect(Blue,&QAction::triggered,this,&Notepad::setBlueColor);
    connect(Yellow,&QAction::triggered,this,&Notepad::setYellowColor);
    connect(Green,&QAction::triggered,this,&Notepad::setGreenColor);
    connect(Gray,&QAction::triggered,this,&Notepad::setGrayColor);
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

void Notepad::systemfile()
{
    QFile file("D:/NG_2022_Notebook_project/" + ui->Name->text() + ".txt");
    if(!file.open(QFile:: WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Cannot save file" + file.errorString());
        return;
    }
    QString text = ui->TextWindow->toPlainText();
    file.write(text.toUtf8());
    file.close();
    QFile sysfile("D:/NG_2022_Notebook_project/Notepad/SystemFile.txt");
    QString name = ui->Name->text();
    QString tag = ui->Tag->text();
    QString note = name + ":" + tag + ":" + globalCol.toUtf8() + "\n";
    if(!sysfile.isOpen()){
        sysfile.open(QIODevice::Append);
        sysfile.write(note.toUtf8());
        sysfile.close();
    }
}

void Notepad::search()
{
    ui->ListW->clear();
    QFile file("D:/NG_2022_Notebook_project/Notepad/SystemFile.txt");
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
        QString note = name + ":" + tag + globalCol.toUtf8() + "\n";
        qDebug() << note;
        qDebug () << "This is name: " <<name ;
        qDebug () << "This is note: " <<tag ;
        foreach(QString item, list){
            QStringList input = item.split(":");
            if((name != ""  && name == input.at(0))){
                if(tag == "" || tag == input.at(1)){
                    qDebug() << item;
                    ui->ListW->addItem(input.at(0) +  ":" + input.at(1));
                }
            }
            else if (tag != "" && tag == input.at(1)){
                qDebug() << item;
                ui->ListW->addItem(input.at(0) +  ":" + input.at(1));
            }
            else if(tag =="" && name == ""){
                ui->ListW->clear();
            }
        }
        file.close();
    }
}

void Notepad::addfiles()
{
    QFile filename("D:/NG_2022_Notebook_project/Notepad/SystemFile.txt");
    QString textColor;
    QString userText;
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
            }
            else if(name == input.at(0)){
                tag = input.at(1);
            }
            if(name == input.at(0) || tag == input.at(1)){
                textColor = input.at(2);
                qDebug() << "TEXTCOLOR ++++"<<textColor;
            }
        }
    QFile secondfile("D:/NG_2022_Notebook_project/" + name + ".txt");
        if(!secondfile.isOpen()){
            secondfile.open(QIODevice::ReadWrite);
            ui->TextWindow->setTextColor(textColor);
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

void Notepad::setRedColor()
{
    ui->TextWindow->setTextColor(Qt::red);
    QString color = ui->TextWindow->textColor().name();
    globalCol = color;
}

void Notepad::setBlueColor()
{
    ui->TextWindow->setTextColor(Qt::blue);
    QString color = ui->TextWindow->textColor().name();
    globalCol = color;
}

void Notepad::setYellowColor()
{
    ui->TextWindow->setTextColor(Qt::yellow);
    QString color = ui->TextWindow->textColor().name();
    globalCol = color;
}

void Notepad::setGreenColor()
{
    ui->TextWindow->setTextColor(Qt::green);
    QString color = ui->TextWindow->textColor().name();
    globalCol = color;
}

void Notepad::setGrayColor()
{
    ui->TextWindow->setTextColor(Qt::gray);
    QString color = ui->TextWindow->textColor().name();
    globalCol = color;
}
