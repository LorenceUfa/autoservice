#ifndef SERVICE
#define SERVICE

#include <types.hxx>

class Service
{
public:
  Service();

  Service(uint id,
          uint owner_id,
          uint car_id,
          std::string description,
          double coast,
          QDate date_in,
          QDate date_out);

  void set_id(uint id);
  void set_owner_id(uint owner_id);
  void set_car_id(uint car_id);

  void set_description(std::string description);

  void set_coast(double coast);

  void set_date_in(QDate date_in);
  void set_date_out(QDate date_out);


  uint get_id() const;
  uint get_owner_id() const;
  uint get_car_id() const;

  std::string get_description() const;

  double get_coast() const;

  QDate get_date_in() const;
  QDate get_date_out() const;

  friend std::istream& operator>>(std::istream &is, Service& service_e);
  friend std::ostream& operator<<(std::ostream &os, const Service& service_e);

private:
  uint _id;
  uint _owner_id;
  uint _car_id;
  std::string _description;
  double      _coast;
  QDate _date_in;
  QDate _date_out ; // transmit date

};

#endif // SERVICE

