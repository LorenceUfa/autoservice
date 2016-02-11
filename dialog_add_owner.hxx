#ifndef DIALOG_ADD_OWNER_HXX
#define DIALOG_ADD_OWNER_HXX

#include <QDialog>
#include "types.hxx"

namespace Ui {
  class Dialog_Add_Owner;
}

class Dialog_Add_Owner : public QDialog
{
  Q_OBJECT

public:
  explicit Dialog_Add_Owner(QWidget *parent = 0);
  ~Dialog_Add_Owner();

  std::string get_surname() const;
  std::string get_name() const;
  std::string get_mid_name() const;

  std::string get_brand() const;
  std::string get_model() const;

  QDate get_date_in() const;
  double get_coast() const;
  std::string get_descr() const;

protected:
  void changeEvent(QEvent *e);

private slots:
  void enableButtonOk();
private:
  Ui::Dialog_Add_Owner *ui;
};

#endif // DIALOG_ADD_OWNER_HXX
