#include "dialog_sql.hxx"
#include "ui_dialog_sql.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include "types.hxx"

Dialog_Sql::Dialog_Sql(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Dialog_Sql)
{
  ui->setupUi(this);

  connect(ui->buttonExit, SIGNAL(clicked(bool)), this, SLOT(close()));

  /* Column resize to content */
//  ui->tableWidget->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
  ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
  /* Do not edit contents */
  ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

  ui->tableWidget->setColumnWidth(0, 50);
  ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);

  ui->tableWidget->setColumnWidth(4, 50);
  ui->tableWidget->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Fixed);

  ui->tableWidget->setColumnWidth(7, 50);
  ui->tableWidget->horizontalHeader()->setSectionResizeMode(7, QHeaderView::Fixed);

}

Dialog_Sql::~Dialog_Sql()
{
  delete ui;
}

void Dialog_Sql::get_data_from_sql()
{
  QSqlDatabase sql_db = QSqlDatabase::addDatabase("QMYSQL");

  sql_db.setDatabaseName("Autoservice");
  sql_db.setHostName("eu-cdbr-azure-west-d.cloudapp.net");
  sql_db.setPort(3306);
  sql_db.setUserName("b0bd542b780d30");
  sql_db.setPassword("54375a31");

  if(sql_db.open())
  {
    QSqlQuery query;
    QSqlQuery query_car;
    QSqlQuery query_serv;

    // get owner from database
    query.exec("SELECT * FROM owner");
    query_car.exec("SELECT * FROM car");
    query_serv.exec("SELECT * FROM service");

    while(query.next())
    {
      // create row
      int row = ui->tableWidget->rowCount();
      ui->tableWidget->setRowCount(row + 1);

      QString own_id = query.value(0).toString();
      QTableWidgetItem *t_own_id;
      t_own_id = new QTableWidgetItem();
      t_own_id->setText(own_id);
      ui->tableWidget->setItem(row, 0, t_own_id);

      QString name = query.value(1).toString();
      QTableWidgetItem *t_name;
      t_name = new QTableWidgetItem();
      t_name->setText(name);
      ui->tableWidget->setItem(row, 1, t_name);

      QString surname = query.value(2).toString();
      QTableWidgetItem *t_surname;
      t_surname = new QTableWidgetItem();
      t_surname->setText(surname);
      ui->tableWidget->setItem(row, 2, t_surname);

      QString sec_name = query.value(3).toString();
      QTableWidgetItem *t_sec_name;
      t_sec_name = new QTableWidgetItem();
      t_sec_name->setText(surname);
      ui->tableWidget->setItem(row, 3, t_sec_name);

      while(query_car.next())
      {
        QString car_own_id = query_car.value(1).toString();

        if (car_own_id == own_id) {
          QString car_id = query_car.value(0).toString();
          QString brand = query_car.value(2).toString();
          QString model = query_car.value(3).toString();
        }

        while(query_serv.next())
        {
          QString serv_id = query_serv.value(0).toString();
          QString serv_car_id = query_serv.value(1).toString();
          QString serv_own_id = query_serv.value(2).toString();
          QString date_in = query_serv.value(3).toString();
          QString date_out = query_serv.value(4).toString();
          QString coast = query_serv.value(5).toString();
          QString descr = query_serv.value(6).toString();
        }
      }
    }

  }
  else
  {
    return;
  }

  sql_db.close();
}
