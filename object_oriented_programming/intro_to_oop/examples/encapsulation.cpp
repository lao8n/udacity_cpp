#include <cassert>

class Date {
public:
  Date(int day, int month, int year);
  int Day() const { return day_; }
  void Day(int day);
  int Month() const { return month_; }
  void Month(int month);
  int Year() const { return year_; }
  void Year(int year);
  int DaysInMonth();

private:
  int day_;
  int month_;
  int year_;
};

Date::Date(int day, int month, int year) {
  Year(year);
  Month(month);
  Day(day);
}

int Date::DaysInMonth(){
    // september, april june, november
    int days;
    if(month_ == 4 || month_ == 6 || month_ == 9 || month_ == 11){
        days = 30;
    // february alone
    } else if(month_ == 2){
        // leap year
        if(year_ % 4 == 0){
            days = 29;
        } else {
            days = 28;
        }
    // all the rest
    } else {
        days = 31;
    }
    return days;
}


void Date::Day(int day) {
  if (day >= 1 && day <= DaysInMonth())
    day_ = day;
}

void Date::Month(int month) {
  if (month >= 1 && month <= 12)
    month_ = month;
}

void Date::Year(int year) { year_ = year; }

// Test
int main() {
  Date date(29, 8, 1981);
  assert(date.Day() == 29);
  assert(date.Month() == 8);
  assert(date.Year() == 1981);
  Date date2(29, 2, 2020);
  assert(date2.Day() == 29);
  assert(date2.Month() == 2);
  assert(date2.Year() == 2020);
}