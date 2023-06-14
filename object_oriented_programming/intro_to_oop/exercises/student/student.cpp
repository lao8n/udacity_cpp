#include <cassert>
#include <stdexcept>
#include <string>
#include <cmath>
using std::string;

// TODO: Define "Student" class
class Student {
 public:
  // constructor
    Student(string name, int grade, float gpa): name_(name), grade_(grade), gpa_(gpa){
        Validate();
    }
  // accessors
    string Name(){ return name_; };
    int Grade(){ return grade_; };
    float Gpa(){ return gpa_; };
  // mutators
    void Name(string name){ name_ = name; };
    void Grade(int grade){ 
        grade_ = grade;
        Validate(); 
    };
    void Gpa(float gpa){ gpa_ = gpa; 
        Validate(); 
    };

 private:
  // name
    string name_;
  // grade
    int grade_;
  // GPA
    float gpa_;
    void Validate(){
        if(grade_ < 0 || grade_ > 12 || gpa_ < 0.0 || gpa_ > 4.0) {
            throw std::invalid_argument("invalid grade or gpa");
        }
    }
};

// TODO: Test
int main() {
    Student student1 = Student("Tim", 5, 3.2);
    assert(student1.Name() == "Tim");
    assert(student1.Grade() == 5);
    // assert(student1.Gpa() == 3.2) fails because of floating point precision
    assert(std::abs(student1.Gpa() - 3.2) < 0.0001f);
    
    bool catchStudent2 = false;
    try {
        Student student2 = Student("Bob", 13, 3.2);
    } catch (...){
        catchStudent2 = true;
    }
    assert(catchStudent2 == true);
    
    bool catchStudent3 = false;
    try {
        Student student3 = Student("Bob", 5, -1.2);
    } catch (...){
        catchStudent3 = true;
    }
    assert(catchStudent3 == true);
}