#include<iostream>
#include<vector>
#include<cstdlib>
#include<fstream>
#include<map>
using namespace std;
#define MIN_BALANCE 500
class insufficientBalance{};
class account{
    private:
    long accountNumber;
    string firstName;
    string lastname;
    float balance;
    static long nextAccountNumber;
    public:
    account(){};
    account(string fname , string lname , float balance){
        nextAccountNumber++;
        accountNumber = nextAccountNumber;
        firstName = fname;
        lastname = lname;
        this->balance = balance;
    }
    long getAccNo(){
        return accountNumber;
    }
        
    string getFirstname(){
        return firstName;
    }
    string getLastname(){
        return lastname;
    }
    float getBalance(){
        return balance;
    }
    void deposit(float amount){
        balance = balance + amount;
    }
    void withdraw(float amount){
        if(balance - amount < MIN_BALANCE){
            throw insufficientBalance();
        }
        balance = balance - amount;
    }
    static void setLastAccoutnumber(long accountNumber){
        nextAccountNumber = accountNumber;
    }
    static long getLastAccountnumber(){
        return nextAccountNumber;
    }
    friend ifstream & operator>>(ifstream &ifs,account &acc);
    friend ofstream & operator<<(ofstream &ofs,account &acc);
    friend ostream & operator<<(ostream &os,account &acc);
    
};
long account::nextAccountNumber =0;
class bank{
    private:
    map<long,account> accounts;
    public:
    bank(){
        account Account;
        ifstream infile;
        infile.open("Bank.data");
        if(!infile){
            cout<<"Error in opening!! File not found!!!"<<endl;
            return;
        }
        while(!infile.eof()){
            infile>>Account;
            accounts.insert(pair<long,account>(Account.getAccNo(),Account));
        }
        account::setLastAccoutnumber(Account.getAccNo());
        infile.close();
    }
    account openAccount(string fname , string lname ,float balance){
        ofstream outfile;
        account Account(fname,lname,balance);
        accounts.insert(pair<long,account>(Account.getAccNo(),Account));
        outfile.open("Bank.data",ios::trunc);
        map<long,account>::iterator itr;
        for(itr = accounts.begin();itr !=accounts.end();itr++){
            outfile<<itr->second;
        }
        outfile.close();
        return Account;
    }
    account balanceEnquiry(long accountNumber){
        map<long,account>::iterator itr = accounts.find(accountNumber);
        return itr->second;
    }
    account deposit(long accountNumber , float amount){
        map<long,account>:: iterator itr = accounts.find(accountNumber);
        itr->second.deposit(amount);
        return itr->second;
    }
    account withdraw(long accountNumber , float amount){
        map<long,account>::iterator itr = accounts.find(accountNumber);
        itr->second.withdraw(amount);
        return itr->second;
    }
    void closeAccount(long accountNumber){
        map<long,account>::iterator itr = accounts.find(accountNumber);
        cout<<"Acoount is deleted"<<endl<<itr->second;
        accounts.erase(accountNumber);
    }
    void showAllAccounts(){
        map<long,account>::iterator itr;
        for(itr = accounts.begin();itr!=accounts.end();itr++){
            cout<<"Account"<<itr->first<<endl<<itr->second<<endl;
        }
    }
    ~bank(){
        ofstream outfile;
        outfile.open("Bank.data",ios::trunc);
        map<long,account>::iterator itr;
        for(itr = accounts.begin();itr !=accounts.end();itr++){
            outfile<<itr->second;
        }
        outfile.close();
    }
};
int main(){
    account acc;
    bank b;
    int choice;
    string fname,lname;
    long accountNumber;
    float balance;
    float amount;
    cout<<"****This is a Banking System*****"<<endl;
    do{
        cout<<"\n\t Select one option below ";
        cout<<"\n\t1 Open an Account";
        cout<<"\n\t2 Balance Enquiry";
        cout<<"\n\t3 Deposit Amount";
        cout<<"\n\t4 Withdraw Amount";
        cout<<"\n\t5 CLose an Account";
        cout<<"\n\t6 Show all Accounts";
        cout<<"\n\t7 Quit the System";
        cout<<"\n Enter your choice: ";
        cin>>choice;
        switch(choice){
            case 1:
            cout<<"***To open an account please provide following information***"<<endl;
            cout<<"Enter your First name: ";
            cin>>fname;
            cout<<"Enter your last name: ";
            cin>>lname;
            cout<<"Enter your initial balance: ";
            cin>>balance;
            acc = b.openAccount(fname,lname,balance);
            cout<<endl<<"Congratulations!! your account has been created"<<endl;
            cout<<acc;
            break;
            case 2:
            cout<<"Enter your account number: ";
            cin>>accountNumber;
            acc = b.balanceEnquiry(accountNumber);
            cout<<endl<<"Following are your account details:"<<endl;
            cout<<acc;
            break;
            case 3:
            cout<<"Enter your account number: ";
            cin>>accountNumber;
            cout<<"Enter amount to deposit: ";
            cin>>amount;
            acc = b.deposit(accountNumber,amount);
            cout<<endl<<"Congratulations , the amount has been deposited."<<endl;
            cout<<acc;
            break;
            case 4:
            cout<<"Enter your account Number: ";
            cin>>accountNumber;
            cout<<"Enter amount to withdraw from initial balance: ";
            cin>>amount;
            acc= b.withdraw(accountNumber,amount);
            cout<<endl<<"Amount is successfully withdrawn."<<endl;
            cout<<acc;
            break;
            case 5:
            cout<<"Enter Account Number: ";
            cin>>accountNumber;
            b.closeAccount(accountNumber);
            cout<<endl<<"Your account has been successfully closed"<<endl;
            cout<<acc;
            break;
            case 6:
            b.showAllAccounts();
            break;
            case 7:
            break;
            default:
            cout<<"\nEnter correct choice. ";
            exit(0);
        }
    }while(choice!=7);
    return 0;
}
ifstream & operator >>(ifstream &ifs,account &acc){
    ifs>>acc.accountNumber;
    ifs>>acc.firstName;
    ifs>>acc.lastname;
    ifs>>acc.balance;
    return ifs;

}
ofstream & operator << (ofstream &ofs , account &acc){
    ofs<<acc.accountNumber<<endl;
    ofs<<acc.firstName<<endl;
    ofs<<acc.lastname<<endl;
    ofs<<acc.balance<<endl;
    return ofs;
}
 ostream & operator<<(ostream &os,account &acc)
 {
    os<<"First Name:"<<acc.getFirstname()<<endl;
    os<<"Last Name:"<<acc.getLastname()<<endl;
    os<<"Account Number:"<<acc.getAccNo()<<endl;
    os<<"The final balance in your account is:"<<acc.getBalance()<<endl;
    return os;
 }