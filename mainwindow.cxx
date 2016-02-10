#include "mainwindow.hxx"
#include "ui_mainwindow.h"
#include "dialog_add_owner.hxx"
#include "dialog_add_car.hxx"


MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  connect(ui->button_add_car, SIGNAL(clicked(bool)), this, SLOT(button_add_car()));
  connect(ui->button_add_owner, SIGNAL(clicked(bool)), this, SLOT(button_add_owner()));
  connect(ui->button_add_service, SIGNAL(clicked(bool)), this, SLOT(button_add_service()));
  connect(ui->button_delete, SIGNAL(clicked(bool)), this, SLOT(button_delete()));
  connect(ui->button_edit, SIGNAL(clicked(bool)), this, SLOT(button_edit()));
  connect(ui->button_exit, SIGNAL(clicked(bool)), this, SLOT(button_exit()));
  connect(ui->button_return_auto, SIGNAL(clicked(bool)), this, SLOT(button_return_auto()));

  ui->tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Fixed);
  ui->tableWidget->setColumnWidth(0, 30);
  ui->tableWidget->setColumnWidth(4, 30);
  ui->tableWidget->setColumnWidth(7, 30);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
  QMainWindow::changeEvent(e);
  switch (e->type()) {
    case QEvent::LanguageChange:
      ui->retranslateUi(this);
      break;
    default:
      break;
  }
}

void MainWindow::button_add_owner()
{
  Owner own;
  Car car;
  Service serv;

  Dialog_Add_Owner dialog;
  if(dialog.exec() == QDialog::Accepted)
  {
    uint own_id, car_id;

    own.set_surname(dialog.get_surname());
    own.set_name(dialog.get_name());
    own.set_sec_name(dialog.get_mid_name());
    own_id = db.add_data(own);

    car.set_owner_id(own_id);
    car.set_brand(dialog.get_brand());
    car.set_model(dialog.get_model());
    car_id = db.add_data(car);

    serv.set_owner_id(own_id);
    serv.set_car_id(car_id);
    serv.set_date_in(dialog.get_date_in());
    serv.set_date_out(dialog.get_date_out());
    serv.set_coast(dialog.get_coast());
    serv.set_description(dialog.get_descr());
    db.add_data(serv);
    add_column(&own, &car, &serv);
  }
}

void MainWindow::button_add_car()
{
  Dialog_Add_Car dialog;
  Owner own;
  Car car;
  Service serv;
  int row = ui->tableWidget->currentRow();
  if (row < 0)
    return;

  /* set owner information from selected row in table widget */
  dialog.setID(ui->tableWidget->item(row, owner_id_e)->text());
  dialog.setSurname(ui->tableWidget->item(row, surname_e)->text());
  dialog.setName(ui->tableWidget->item(row, name_e)->text());
  dialog.setMidName(ui->tableWidget->item(row, mid_name_e)->text());

  if(dialog.exec() == QDialog::Accepted)
  {
    uint own_id, car_id;

    own_id = dialog.get_owner_id();
    own.set_surname(dialog.get_surname());
    own.set_name(dialog.get_name());
    own.set_sec_name(dialog.get_mid_name());
    own.set_id(own_id);

    car.set_brand(dialog.get_brand());
    car.set_model(dialog.get_model());
    car.set_owner_id(own_id);
    car_id = db.add_data(car);

    serv.set_date_in(dialog.get_date_in());
    serv.set_date_out(dialog.get_date_out());
    serv.set_coast(dialog.get_coast());
    serv.set_description(dialog.get_descr());
    serv.set_owner_id(own_id);
    serv.set_car_id(car_id);
    db.add_data(serv);

    add_column(&own, &car, &serv);
  }

}

void MainWindow::button_add_service()
{

}

void MainWindow::button_delete()
{

}

void MainWindow::button_edit()
{

}


void MainWindow::button_return_auto()
{

}

void MainWindow::button_exit()
{
  exit(0);
}
void MainWindow::add_column(const Owner *own, const Car *car, const Service *service)
{
  int row = ui->tableWidget->rowCount();
  ui->tableWidget->setRowCount(row + 1);

  for(int column=0; column!=ui->tableWidget->columnCount(); ++column) {

    switch(column)
    {
      case 0:
        {
          QTableWidgetItem *newItem;
          newItem = new QTableWidgetItem(tr("%1").arg(own->get_id()));
          ui->tableWidget->setItem(row, column, newItem);
        }
        break;
      case 1:
        {
          QTableWidgetItem *newItem = new QTableWidgetItem();
          newItem->setText(QString::fromStdString(own->get_surname()));
          ui->tableWidget->setItem(row, column, newItem);
        }
        break;
      case 2:
        {
          QTableWidgetItem *newItem = new QTableWidgetItem();
          newItem->setText(QString::fromStdString(own->get_name()));
          ui->tableWidget->setItem(row, column, newItem);
        }
        break;
      case 3:
        {
          QTableWidgetItem *newItem = new QTableWidgetItem();
          newItem->setText(QString::fromStdString(own->get_sec_name()));
          ui->tableWidget->setItem(row, column, newItem);
        }
        break;
      case 4:
        {
          QTableWidgetItem *newItem;
          newItem = new QTableWidgetItem(tr("%1").arg(car->get_id()));
          ui->tableWidget->setItem(row, column, newItem);
        }
        break;
      case 5:
        {
          QTableWidgetItem *newItem = new QTableWidgetItem();
          newItem->setText(QString::fromStdString(car->get_brand()));
          ui->tableWidget->setItem(row, column, newItem);
        }
        break;
      case 6:
        {
          QTableWidgetItem *newItem = new QTableWidgetItem();
          newItem->setText(QString::fromStdString(car->get_model()));
          ui->tableWidget->setItem(row, column, newItem);
        }
        break;
      case 7:
        {
          QTableWidgetItem *newItem;
          newItem = new QTableWidgetItem(tr("%1").arg(service->get_id()));
          ui->tableWidget->setItem(row, column, newItem);
        }
        break;
      case 8:
        {
          QTableWidgetItem *newItem = new QTableWidgetItem();
          newItem->setText(service->get_date_in().toString("dd/MM/yyyy"));
          ui->tableWidget->setItem(row, column, newItem);
        }
        break;
      case 9:
        {
          QTableWidgetItem *newItem = new QTableWidgetItem();
          newItem->setText(service->get_date_out().toString("dd/MM/yyyy"));
          ui->tableWidget->setItem(row, column, newItem);
        }
        break;
      case 10:
        {
          QTableWidgetItem *newItem;
          newItem = new QTableWidgetItem(tr("%1").arg(service->get_coast()));
          ui->tableWidget->setItem(row, column, newItem);
        }
        break;
      case 11:
        {
          QTableWidgetItem *newItem = new QTableWidgetItem();
          newItem->setText(QString::fromStdString(service->get_description()));
          ui->tableWidget->setItem(row, column, newItem);
        }
        break;
      default: break;
    }
  }
}
