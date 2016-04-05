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
#if (QT_VERSION < 0x050000) // check QT library version
  ui->tableWidget->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
  ui->tableWidget->horizontalHeader()->setResizeMode(0, QHeaderView::Fixed);
  ui->tableWidget->horizontalHeader()->setResizeMode(4, QHeaderView::Fixed);
  ui->tableWidget->horizontalHeader()->setResizeMode(7, QHeaderView::Fixed);
#else
  ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
  ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
  ui->tableWidget->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Fixed);
  ui->tableWidget->horizontalHeader()->setSectionResizeMode(7, QHeaderView::Fixed);
#endif

  /* Do not edit contents */
  ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

  ui->tableWidget->setColumnWidth(0, 50);
  ui->tableWidget->setColumnWidth(4, 50);
  ui->tableWidget->setColumnWidth(7, 50);

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
    QSqlQuery query_own;
    QSqlQuery query_car;
    QSqlQuery query_serv;

    // get owner from database
    query_own.exec("SELECT * FROM owner");
    query_car.exec("SELECT * FROM car");
    query_serv.exec("SELECT * FROM service");

    while(query_own.next())
    {
      while(query_car.next())
      {
        while(query_serv.next())
        {
          /** Owner id */
          QString own_id = query_own.value(0).toString();

          /** Car id */
          QString car_id = query_car.value(0).toString();
          QString car_own_id = query_car.value(1).toString();

          if (car_own_id == own_id) {
            /** Service id */
            QString serv_car_id = query_serv.value(1).toString();
            QString serv_own_id = query_serv.value(2).toString();

            if ((serv_car_id == car_id) && (serv_own_id == own_id))
            {
              /* create row */
              int row = ui->tableWidget->rowCount();
              ui->tableWidget->setRowCount(row + 1);

              /** Owner information */
              create_item(row, owner_id_e, own_id);

              QString name = query_own.value(1).toString();
              create_item(row, name_e, name);

              QString surname = query_own.value(2).toString();
              create_item(row, surname_e, surname);

              QString sec_name = query_own.value(3).toString();
              create_item(row, mid_name_e, sec_name);

              /** Car information */
              QString brand = query_car.value(2).toString();
              QString model = query_car.value(3).toString();

              create_item(row, car_id_e, car_id);
              create_item(row, brand_e, brand);
              create_item(row, model_e, model);

              /** Service information */
              QString serv_id = query_serv.value(0).toString();
              QString date_in = query_serv.value(3).toString();
              QString date_out = query_serv.value(4).toString();
              QString coast = query_serv.value(5).toString();
              QString descr = query_serv.value(6).toString();

              create_item(row, serv_id_e, serv_id);
              create_item(row, date_in_e, date_in);
              create_item(row, date_out_e, date_out);
              create_item(row, coast_e, coast);
              create_item(row, descr_e, descr);

            } /* if ((serv_car_id == car_id) && (serv_own_id == own_id)) */
          } /* if (car_own_id == own_id) */
        } /* while(query_serv.next()) */

        query_serv.first();
      } /* while(query_car.next()) */

      query_car.first();
    } /* while(query_own.next()) */

  }
  else
  {
    return;
  }

  sql_db.close();
}

void Dialog_Sql::create_item(const int row, const int column, QString &str)
{
    QTableWidgetItem *t_item;
    t_item = new QTableWidgetItem();
    t_item->setText(str);
    ui->tableWidget->setItem(row, column, t_item);
}
