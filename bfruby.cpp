#include "bfruby.h"
#include "ui_bfruby.h"
#include <QtGui>
#include <QtSql>
#include <iostream>

using namespace std;

BFRuby::BFRuby(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BFRuby)
{
    db = QSqlDatabase::addDatabase("QMYSQL","BFConnection");
    ui->setupUi(this);
    setupConnections();
    dbConnect();
    model = new QSqlTableModel ;
    setupMembersTable(model);
    setupGroupCompoBox();


}

BFRuby::~BFRuby()
{
    delete ui;
}



void BFRuby::setupConnections()
{
    connect(ui->groupComboBox,SIGNAL(editTextChanged(QString)),this,SLOT(getGroup(QString)));
    connect(ui->aboutAction,SIGNAL(triggered()),this,SLOT(about()));
    connect(ui->quitAction,SIGNAL(triggered()),qApp,SLOT(quit()));
}

void BFRuby::setupMembersTable(QSqlTableModel *model,const QString groupFilter)
{
    model->setEditStrategy(QSqlTableModel::OnRowChange);
    model->setTable("RubyCourse");

    if(!groupFilter.isEmpty())
        model->setFilter(QString("group = %1 ; ").arg(groupFilter));

//    cout << "group = " << groupFilter.toStdString() << ";"<< endl;
//    model->setFilter("group = 5");
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Group ID"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Name"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Day 1"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Day 2"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Day 3"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Day 4"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Day 5"));

    model->select();

    ui->membersTable->setModel(model);
    ui->membersTable->setColumnWidth(0,30);
    ui->membersTable->setColumnWidth(1,80);
    ui->membersTable->setColumnWidth(2,300);
    ui->membersTable->setColumnWidth(3,50);
    ui->membersTable->setColumnWidth(4,50);
    ui->membersTable->setColumnWidth(5,50);
    ui->membersTable->setColumnWidth(6,50);
    ui->membersTable->setColumnWidth(7,50);



}

void BFRuby::setupGroupCompoBox()
{
    QRegExp exp("[1-9]{0,2}");
    ui->groupComboBox->setValidator(new QRegExpValidator(exp));
}

bool BFRuby::dbConnect()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("BF");
    db.setUserName("root");
    db.setPassword("root");
    if(!db.open()){
        QMessageBox::critical(this,tr("ERROR"),
                              tr("Database can NOT be opened : %1.").arg(db.lastError().text()));
        return false;
    }

    return true;
}

void BFRuby::setupContextMenu()
{
}

void BFRuby::about()
{
    QMessageBox::about(this,
                       tr("Bokra Fekra Course APP"),
                       tr("<b><u>Bokra Fekra Course APP :</u></b> is a small program created by <b><font color=\"red\">Ahmed Magdy</font></b>"
                          " to help <b>Bokra Fekra</b> organisers to organise their FREE courses."));

}



void BFRuby::getGroup(const QString &groupId)
{
    setupMembersTable(model,groupId);
}
