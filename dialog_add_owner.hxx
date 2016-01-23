#ifndef DIALOG_ADD_OWNER_HXX
#define DIALOG_ADD_OWNER_HXX

#include <QDialog>

namespace Ui {
  class Dialog_Add_Owner;
}

class Dialog_Add_Owner : public QDialog
{
  Q_OBJECT

public:
  explicit Dialog_Add_Owner(QWidget *parent = 0);
  ~Dialog_Add_Owner();

protected:
  void changeEvent(QEvent *e);

private:
  Ui::Dialog_Add_Owner *ui;
};

#endif // DIALOG_ADD_OWNER_HXX
