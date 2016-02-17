#ifndef TYPES
#define TYPES

#include <iostream>
#include <string>
#include <iomanip>
#include <QDate>

#include <QDebug>

enum
{
  owner_e = 1,
  car_e,
  service_e,
  main_e
};

enum
{
  owner_id_e,
  surname_e,
  name_e,
  mid_name_e,
  car_id_e,
  brand_e,
  model_e,
  date_id_e,
  date_in_e,
  date_out_e,
  coast_e,
  descr_e
};

typedef unsigned int uint;

#endif // TYPES

