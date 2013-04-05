#ifndef BFRUBY_H
#define BFRUBY_H

#include <QMainWindow>
#include <QSqlDatabase>

class QSqlTableModel;
class QTableView;

namespace Ui {
class BFRuby;
}

class BFRuby : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit BFRuby(QWidget *parent = 0);
    ~BFRuby();
    
private:
    Ui::BFRuby *ui;
    QSqlDatabase db;
    QSqlTableModel *model;

    void setupConnections();
    void setupMembersTable(QSqlTableModel *model, const QString groupFilter = "");
    void setupGroupCompoBox();
    bool dbConnect();
    void setupContextMenu();


private slots:
    void about();
    void getGroup(const QString &groupId="0");
};

#endif // BFRUBY_H
