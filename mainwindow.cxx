#include "mainwindow.hxx"
#include "ui_mainwindow.h"
#include <Qt>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
  ui->tableWidget->setColumnWidth(0, 30);
  ui->tableWidget->setColumnWidth(4, 30);
  ui->tableWidget->setColumnWidth(7, 30);

  for(int row=0; row!=ui->tableWidget->rowCount(); ++row){
      for(int column=0; column!=ui->tableWidget->columnCount(); ++column) {
          QTableWidgetItem *newItem = new QTableWidgetItem(tr("%1").arg((row+1)*(column+1)));
          ui->tableWidget->setItem(row, column, newItem);
      }
  }

  int row_count = ui->tableWidget->rowCount();

  ui->tableWidget->setRowCount(row_count + 1);
  QTableWidgetItem *table_item = new QTableWidgetItem(tr("%1").arg(rand()%100));
  table_item->setTextAlignment(Qt::AlignLeft);
  ui->tableWidget->setItem(row_count, 1, table_item);
}

MainWindow::~MainWindow()
{
  delete ui;
}
