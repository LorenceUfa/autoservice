#ifndef DIALOG_ADD_SERVICE_HXX
#define DIALOG_ADD_SERVICE_HXX

#include <QDialog>
#include "types.hxx"

namespace Ui {
  class Dialog_Add_Service;
}

class Dialog_Add_Service : public QDialog
{
  Q_OBJECT

public:
  explicit Dialog_Add_Service(QWidget *parent = 0);
  ~Dialog_Add_Service();

  std::string get_surname() const;
  std::string get_name() const;
  std::string get_mid_name() const;

  std::string get_brand() const;
  std::string get_model() const;

  QDate get_date_in() const;
  double get_coast() const;
  std::string get_descr() const;

  void setOwnerID(const QString& id);
  void setSurname(const QString& surname);
  void setName(const QString& name);
  void setMidName(const QString& mid_name);

  void setCarID(const QString& id);
  void setBrand(const QString& brand);
  void setModel(const QString& model);

  uint get_owner_id() const;
  uint get_car_id() const;

protected:
  void changeEvent(QEvent *e);

private slots:
  void enableButtonOk();

private:
  Ui::Dialog_Add_Service *ui;

  uint owner_id;
  uint car_id;
};

#endif // DIALOG_ADD_SERVICE_HXX
