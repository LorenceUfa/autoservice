#ifndef DIALOG_SQL_HXX
#define DIALOG_SQL_HXX

#include <QDialog>

namespace Ui {
  class Dialog_Sql;
}

class Dialog_Sql : public QDialog
{
  Q_OBJECT

public:
  explicit Dialog_Sql(QWidget *parent = 0);
  ~Dialog_Sql();

  void get_data_from_sql();

//private slots:
//  void button_exit();

private:
  Ui::Dialog_Sql *ui;
};

#endif // DIALOG_SQL_HXX
