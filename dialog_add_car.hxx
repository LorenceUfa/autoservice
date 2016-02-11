#ifndef DIALOG_ADD_CAR_HXX
#define DIALOG_ADD_CAR_HXX

#include <QDialog>
#include "types.hxx"

namespace Ui {
  class Dialog_add_car;
}

class Dialog_Add_Car : public QDialog
{
  Q_OBJECT

public:
  explicit Dialog_Add_Car(QWidget *parent = 0);
  ~Dialog_Add_Car();

  std::string get_surname() const;
  std::string get_name() const;
  std::string get_mid_name() const;

  std::string get_brand() const;
  std::string get_model() const;

  QDate get_date_in() const;
  double get_coast() const;
  std::string get_descr() const;

  void setID(const QString& id);
  void setSurname(const QString& surname);
  void setName(const QString& name);
  void setMidName(const QString& mid_name);

  uint get_owner_id() const;

protected:
  void changeEvent(QEvent *e);

private slots:
  void enableButtonOk();
private:
  Ui::Dialog_add_car *ui;
  uint owner_id;
};

#endif // DIALOG_ADD_CAR_HXX
