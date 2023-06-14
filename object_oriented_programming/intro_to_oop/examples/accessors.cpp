#include <iostream>
#include <string>
#include <cassert>

class BankAccount
{
  private:
      // TODO: declare member variables
    int account_num;
    std::string account_name;
    int available_funds; // defaults to zero

  public:
      // TODO: declare setters
    void AccountNum(int num);
    void Name(std::string name);
    void AvailableFunds(int funds);
      // TODO: declare getters
    int AccountNum() const;
    std::string Name() const;
    int AvailableFunds() const;
};

// TODO: implement setters
void BankAccount::AccountNum(int num){
    account_num = num;
}
void BankAccount::Name(std::string name){
    account_name = name;
}
void BankAccount::AvailableFunds(int funds){
    available_funds = funds;
}
// TODO: implement getters
int BankAccount::AccountNum() const {
    return account_num;
}
std::string BankAccount::Name() const {
    return account_name;
}
int BankAccount::AvailableFunds() const {
    return available_funds;
}

int main(){
    // TODO: instantiate and output a bank account
    BankAccount ba = BankAccount();
    ba.AccountNum(123);
    ba.Name("Bob");
    ba.AvailableFunds(100);
    assert(ba.AccountNum() == 123);
    assert(ba.Name() == "Bob");
    assert(ba.AvailableFunds() == 100);
}