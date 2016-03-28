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
  void button_return_car();
  void button_sql();
  void button_exit();

private:
  Ui::MainWindow *ui;
  void add_column(const Owner *own, const Car *car, const Service *service);

  template <typename T>
  void dialog_func(const T& dialog, Owner& own, Car& car, Service& serv);
};

#endif // MAINWINDOW_HXX
