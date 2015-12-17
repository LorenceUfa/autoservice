#ifndef CAR
#define CAR

#include <types.hxx>

class Car
{
public:
  Car();

  Car(uint id,
      uint owner_id,
      std::string brand,
      std::string model);

  void set_id(uint id);
  void set_owner_id(uint owner_id);
  void set_brand(std::string brand);
  void set_model(std::string model);

  uint        get_id() const;
  uint        get_owner_id() const;
  std::string get_brand() const;
  std::string get_model() const;

  friend std::istream& operator>>(std::istream &is, Car& car);

private:
  uint _id;
  uint _owner_id;
  std::string _brand;
  std::string _model;
};

#endif // CAR

