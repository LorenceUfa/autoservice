#ifndef MAINWINDOW_HXX
#define MAINWINDOW_HXX

#include <QMainWindow>
#include "database.hxx"

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  DataBase db;

protected:
  void changeEvent(QEvent *e);

private slots:
  void button_add_car();
  void button_add_owner();
  void button_add_service();
  void button_edit();
  void button_delete();
  void button_return_auto();
  void button_exit();

private:
  Ui::MainWindow *ui;
};

#endif // MAINWINDOW_HXX
