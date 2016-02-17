#ifndef DATABASE_HXX
#define DATABASE_HXX

#include <owner.hxx>
#include <car.hxx>
#include <service.hxx>
#include <list>
#include <types.hxx>

class DataBase
{
public:
  DataBase();

  void add_data();
  void remove_data();
  void show_data();
  void edit_data();

  void add_out_date();
  void add_out_date(const QDate &date_out, const uint &serv_id);

  void add_owner();
  void add_car(uint owner_id);
  void add_service(uint owner_id, uint car_id);

  uint add_data(Car& car);
  uint add_data(Owner& owner);
  void add_data(Service& service);

private:
  std::list<Car> _car;
  std::list<Owner> _owner;
  std::list<Service> _service;

  uint _car_id;
  uint _owner_id;
  uint _service_id;

  void edit_owner();
  void edit_car();
  void edit_service();
  void edit_all();

  void remove_owner(uint id);
  void remove_car(uint owner_id);
  void remove_service(uint owner_id, uint car_id);

  uint find_owner() const;
  uint find_car(const uint owner_id) const;
  uint find_service(const uint car_id) const;

  bool list_is_empty(uint type) const;

};

bool print_head(uint type);
void print_border(uint count);

#endif // DATABASE_HXX
