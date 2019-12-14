#include <iostream>
#include <string>
#include<vector>
#include <cstdlib>
using namespace std;

class AccountInfo{

  public:
  int NumDep;
  int NumWith;
  double AnnIntRate;
  double MonthlyServiceCharges;

  double balance;
  double AmountDep;
  double AmountWith;
  double MonthlyIntRate;
  double MonthlyInt;

 int numDep_sav=0;//number of deposits in savings account
 int numWith_sav=0;//number of withdrawals from savings account

 //variables for chequing account
 int numDep_cheq=0;//number of deposits in chequing account
 int numWith_cheq=0;//number of withdrawals from chequing account
 int monthlyServCharge=0; //monthly service charge
 int num_Dep=0; //Number of deposits
 int num_With=0;//Number of Withdrawals

  
  int n=201831906;
  int z=100005;
  
  AccountInfo(){ }
  AccountInfo(int b, int i){
    balance=b;
    AnnIntRate=i;
    }
  
  virtual void AccountNumber(){
    z++;
    n++;
  }

  virtual void deposit(int d){
    AmountDep=d;
    balance+=d;
    NumDep++;
  }

  virtual void withdraw(int w){
    AmountWith=w;
    balance-=w;
    NumWith++;

  }

  virtual void calcInt(){
    MonthlyIntRate=(AnnIntRate/12);
    MonthlyInt=balance*MonthlyIntRate;
    balance+=MonthlyInt;
    
  }

  virtual void monthlyProc(){
    balance-=MonthlyServiceCharges;
    calcInt();
    numDep_sav=0;
    numWith_sav=0;
    numWith_cheq=0;
    numDep_cheq=0;
    MonthlyServiceCharges=0;
  }

 

};

class SavingsAccount : public AccountInfo{
  
  protected:
  string newName_sav;
  int AccNum_sav;
  int dep_sav;

  public:
  SavingsAccount(){};

  SavingsAccount(string nme, int anum, int d){
    newName_sav=nme;
    AccNum_sav=anum;
    dep_sav=d;

  }
  int getdep_sav()const{
    return dep_sav;

  }

  string getName_sav() const {
    return newName_sav;
  }

  int getAccNum_sav() const{
    return AccNum_sav;
  }

  //using vectors of objects
  void fillVector_sav(vector<SavingsAccount>& newAcc1){
    cout<<"Enter Account Holder's Name: "<<endl;
    string name;
    cin>>name;
    AccountInfo::AccountNumber();
    cout<<"The Account Number is: "<<AccountInfo::n<<endl;
     if(status()){
      cout<<"Account is inactive."<<endl;
      cout<<"Enter Deposit Amount: ";
      cin>>a;
      if(balance+a>25){
        AccountInfo::deposit(a);
        numDep_sav++;

        cout<<"Account is active now."<<endl<<endl;
        SavingsAccount q(name,AccountInfo::n,a);
        newAcc1.push_back(q);
        cout<<endl;
      }
      else{
        cout<<"INVALID! Deposit fund to raise amount above $25 and make account active again."<<endl;
      }

    }
    

  }
    void printVector_sav(const vector<SavingsAccount>& newAcc1){
    int n;

    cout<<"Enter the account number: ";
    cin>>n;

    unsigned size=newAcc1.size();
    for(unsigned int i=0; i<size; i++)
    {
      if(n==newAcc1[i].getAccNum_sav()){
      
      cout<<"Name of Account Holder: "<< newAcc1[i].getName_sav()<<endl;
      cout<<"Account Number: "<<newAcc1[i].getAccNum_sav()<<endl;
      cout<<"Account Type: Savings Account"<<endl;
      cout<<"Available Balance: "<<newAcc1[i].getdep_sav()<<endl;
      cout<<"Month Interest: "<<newAcc1[i].getdep_sav()*(0.08/12)<<endl<<endl;}
      else
      cout<<"Account not found"<<endl<<endl;

    }

  }
  
  int a;
  bool flag=0;

  bool status(){
    if(balance<25){
      flag=1;
    }
    else flag = 0;
    return flag;
  }

  void withdraw(){
    if(status()){
      cout<<"Account is inactive."<<endl;
    }
    else{
      cout<<"Enter Withdrawal Ammount: ";
      cin>>a;
      AccountInfo::withdraw(a);
      numWith_sav++;
    }
  }
  void deposit() {
    if(status()) {
      cout<<"Account is inactive."<<endl;
      cout<<"Enter Deposit Amount: ";
      cin>>a;
      if(balance+a>25) {
        AccountInfo::deposit(a);
        numDep_sav++;
        cout<<"Account is active now."<<endl<<endl;
      }
      else{
        cout<<"INVALID! Deposit fund to raise amount above $25 and make account active again."<<endl;
      }
    }
  }

  void monthlyProc(){
    if(numWith_sav>4) {
      int n=(numWith_sav-4);
      MonthlyServiceCharges+=n;

      if(status()){
        cout<<"Account is inactive."<<endl;
      }
      else{
        MonthlyServiceCharges=1;
        AccountInfo::monthlyProc();
      }
    }
  }
};

class CheckingAccount: public AccountInfo{
  protected:
  string newName_check;
  int AccNum_check;
  int dep;

  public:
  int a;

  CheckingAccount(){};

  CheckingAccount(string nme, int anum, int d){
    newName_check=nme;
    AccNum_check=anum;
    dep=d;

  }
  
  void deposit_new(int a){
    AccountInfo::deposit(a);
    numDep_cheq++;
  }

  string getName_check() const {
    return newName_check;
  }

  int getAccNum_check() const{
    return AccNum_check;
  }
  
  int getDep_check() const{
    return dep;
  }
  
  void fillVector_check(vector<CheckingAccount>& newAcc2){
    int b;
    cout<<"Enter Account Holder's Name: "<<endl;
    string name;
    cin>>name;
    AccountInfo::AccountNumber();
    cout<<"The Account Number is: "<<AccountInfo::z<<endl;
    cout<<"Enter amount to deposit (Minimun $100 to Activate Checking Account): "<<endl;
    cin>>b;
    if(b<100)
    {
      cout<<"Account not activated. Please deposit more funds.";
    }
    else {
      deposit_new(b);
      CheckingAccount q(name,AccountInfo::z,b) ;
      newAcc2.push_back(q);
      cout<<endl;
    }
  }

  void printVector_check(const vector<CheckingAccount>& newAcc2){
    int an;
    cout<<"Enter Account Number: ";
    cin>>an;
    unsigned size=newAcc2.size();
    
    for(unsigned int i=0; i<size; i++) {
      if(an==newAcc2[i].getAccNum_check()){
        cout<<"Name of Account holder: "<< newAcc2[i].getName_check()<<endl;
        cout<<"Account Number: "<<newAcc2[i].getAccNum_check()<<endl;
        cout<<"Account Type: Checking Account"<<endl;
        cout<<"Available Balance: "<< newAcc2[i].getDep_check()<<endl;
        cout<<"Month Interest: "<<newAcc2[i].getDep_check()*(0.1/12)<<endl<<endl; 
      }
      else {
        cout<<"Account number not found."<<endl<<endl;
      }
    }
  }

  void withdraw() {
    cout<<"Enter Withdrawal Amount: ";
    cin>>a;
    if(balance-a<0) {
      MonthlyServiceCharges+=15;
      AccountInfo::withdraw(a);
      numWith_cheq++;

    }
    else {
      AccountInfo::withdraw(a);
      numWith_cheq++;
    }
  }
 
  void monthlyProc(){
    MonthlyServiceCharges+=(5+(0.1*numWith_sav));
    AccountInfo::monthlyProc(); 
  }
};

int main() {
  vector<CheckingAccount> Acc2;
  vector<SavingsAccount> Acc1;

  SavingsAccount S;
  CheckingAccount C;

  int x, ch1,ch2,ch3;
  
  while(true){
    cout<<"1. Create New Account"<<endl<<"2. For Existing Account Holder"<<endl<<"3. Access newly created accounts"<<endl;
    cin>>ch1;
    
    if(ch1==1){
      cout<<"1. Create saving account"<<endl<<"2. Create checking account"<<endl;
      cin>>ch2;
      
      if(ch2==1){
        S.fillVector_sav(Acc1);
        S.deposit();
      }
      
      else if(ch2==2){
        C.fillVector_check(Acc2);
      }
    }
 
    else if(ch1==2){
      cout<<"1. Saving Account Details"<<endl<<"2. Checking Account Details"<<endl;
      cin>>ch3;
      if(ch3==1) {
        cout<<"1. Deposit"<<endl;
        cout<<"2. Withdraw"<<endl;
        cout<<"3. MonthlyProc"<<endl;
        cout<<"4. Print"<<endl;
        cout<<"5. Quit"<<endl;
        cin>>x;

        if(x==1) {
          S.deposit();
        }
        else if(x==2) {
          S.withdraw();
        }
        else if(x==3) {
          S.monthlyProc();
        }
        else if(x==4) {  
          cout<<"**Saving Account**"<<endl;
          cout<<"Number of Deposit :"<<S.numDep_sav<<endl;
          cout<<"Number of Withdrawls :"<<S.numWith_sav<<endl;
          cout<<"Total amount of Withdraws:"<<S.AmountWith<<endl;
          cout<<"Total amount of deposits :"<<S.AmountDep<<endl;
          cout<<"Monthly service charge :"<<S.monthlyServCharge<<endl;
          cout<<"Final Balance :"<<S.balance<<endl<<endl;}
      }
      else if (ch3==2) {
        cout<<"1. Deposit"<<endl;
        cout<<"2. Withdraw"<<endl;
        cout<<"3. MonthlyProc"<<endl;
        cout<<"4. Print"<<endl;
        cout<<"5. Quit"<<endl;
        cin>>x;

        if(x==1){
          cout<<"Enter the amount to Deposit: ";
          int a;
          cin>>a;
          C.deposit(a);
          C.numDep_cheq++;
        }
        else if(x==2){
          C.withdraw();
        }
        else if(x==3){
          C.monthlyProc();
        }
        else if(x==4){
          cout<<"**Chequing Account**"<<endl;
          cout<<"Number of Deposit :"<<C.numDep_cheq<<endl;
          cout<<"Number of Withdrawls :"<<C.numWith_cheq<<endl;
          cout<<"Total amount of Withdraws:"<<C.AmountWith<<endl;
          cout<<"Total amount of deposits :"<<C.AmountDep<<endl;
          cout<<"Monthly service charge :"<<C.monthlyServCharge<<endl;
          cout<<"Final Balance :"<<C.balance<<endl<<endl;
        }
      }
    }

    else if(ch1==3) {
      int y;
      cout<<"1. Saving Accounts"<<endl;
      cout<<"2. Checking Accounts"<<endl;
      cin>>y;
      
      if(y==1) {
        S.printVector_sav(Acc1);
      }
      if(y==2) {
        C.printVector_check(Acc2);
      }
    }
  }
}