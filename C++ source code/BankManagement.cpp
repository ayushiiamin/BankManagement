#include<iostream.h>
#include<stdio.h>
#include<conio.h>
#include<fstream.h>

#include<process.h>
class account
{
 char name[20];
 int  acc_no;
 char acc_type;
 int pin;
 int deposit;
public:
 void get_accinfo();
 void menu();
 void display_accinfo();
 void depos(int);
 void draw(int);
 int retacc_no();
 int retpin();
 int retdeposit();
 char retacc_type();
};
void account::get_accinfo()
{
 cout<<"\n\nEnter Customer Name : ";
   gets(name);
 cout<<"\nEnter Account Number : ";
   cin>>acc_no;
 cout<<"\nEnter Account Type(Enter C for current or S for savings) : ";
   cin>>acc_type;

 cout<<"\nEnter initial ammount(>=500 for saving and >=1000 for current) : ";
   cin>>deposit;
 cout<<"\nEnter pin number : ";
   cin>>pin;
 cout<<"\n\nAccount succesfully created";
}
void account::display_accinfo()
{
 cout<<"\n\nCustomer Name :- "<<name;
 cout<<"\nAccount Number :- "<<acc_no;
 cout<<"\nAccount Type :- "<<acc_type;
 cout<<"\nBalance amount"<<deposit;
}
void account::depos(int x)
{
 deposit+=x;
}
void account::draw(int x)
{
 deposit-=x;
}
int account::retacc_no()
{
 return acc_no;
}
int account::retdeposit()
{
 return deposit;
}
char account::retacc_type()
{
 return acc_type;
}
int account::retpin()
{
 return pin;
}
int c=0;
void write()
{
 account a;
 ofstream o1;
 o1.open("account.dat",ios::binary|ios::app);
 a.get_accinfo();
 o1.write((char*)&a,sizeof(account));
 o1.close();
}
void login()
{
 account a;
 ifstream i1("account.dat",ios::binary);
 if(!i1)
 {
  cout<<"error...File not found";
  return;
 }
 cout<<endl;
 int lid,pinno;
 cout<<"Account no : "<<endl;
 cin>>lid;
 cout<<endl;
 cout<<"PIN : "<<endl;
 cin>>pinno;
 cout<<endl;
 int i=0;
 while(i1.read((char*)&a,sizeof(a)))
 {
  if((a.retacc_no()==lid)&&(a.retpin()==pinno))
  {
   i++;
   a.menu();
  }
 }
 if(i==0)
  cout<<"invalid\n";
 i1.close();
}

 void disp_acc(int n)
 {
  int flag=0;
  account a;
  ifstream i1;
  i1.open("account.dat",ios::binary);
  if(!i1)
  {
   cout<<"file could not be opened"<<endl;
   return;
  }
  cout<<"\nBalnce Details\n";
  while(i1.read((char*)&a,sizeof(account)))
  {
   if(a.retacc_no()==n)
   {
    a.display_accinfo();
    flag=1;
   }
  }
  i1.close();
  if(flag==0)
  cout<<"\nAccount doesn't exist";
 }
 void del_acc(int n)
 {

  account a;
  ifstream i1;
  ofstream o1;
  i1.open("account.dat",ios::binary);
  if(!i1)
  {
   cout<<"file could not be opened"<<endl;
   return;
  }
  o1.open("new.dat",ios::binary);
  i1.seekg(0,ios::beg);
  while(i1.read((char*)&a,sizeof(a)))
  {
   if(a.retacc_no()!=n)
   {
    o1.write((char*)&a,sizeof(a));
   }
  }
  i1.close();
  o1.close();
  remove("account.dat");
  rename("new.dat","account.dat");
  cout<<"\n\n\tRecord deleted";
  c=0;
  return;
 }
 void deposit_withdraw(int n,int opt)
 {
  int amt,flag=0;
  account a;
  fstream f;
  f.open("account.dat",ios::binary|ios::in|ios::out);
  if(!f)
  {
   cout<<"file could not be opened"<<endl;
   return;
  }
  while(!f.eof() && flag==0)
  {
   f.read((char*)&a,sizeof(a));
   if(a.retacc_no()==n)
   {
    a.display_accinfo();
    if(opt==1)
    {
     cout<<"\n\n\tDEPOSIT AMT";
     cout<<"\n\nEnter amt to be deposited";
     cin>>amt;
     a.depos(amt);
    }
    else if(opt==2)
    {
     cout<<"\n\n\tWITHDRAW AMT";
     cout<<"\n\nEnter amt to be withdrawn";
     cin>>amt;
     int bal=a.retdeposit()-amt;
     if((bal<500&&a.retacc_type()=='S')||(bal<1000&&a.retacc_type()=='C'))
       cout<<"insufficient balnce"<<endl;
     else
       a.draw(amt);
    }
    f.seekp((-1)*sizeof(a),ios::cur);
    f.write((char*)&a,sizeof(a));
    cout<<"\n\n\tRecord updated";
    flag=1;
   }
  }
  f.close();
  if(flag==0)
  cout<<"\n\n Record not found";
 }

void account::menu()
{
 int ch;
 do
 {
  cout<<"WELCOME  "<<name<<endl;
  cout<<"\nChoose Your Choice\n";
  cout<<"1)Deposit\n";
  cout<<"2)Withdraw\n";
  cout<<"3)Balance enquiry\n";
  cout<<"4)Close account\n";
  cout<<"5)Log out\n";
  cout<<"Choose Your choice";
  cin>>ch;
  switch(ch)
  {
   case 1: deposit_withdraw(acc_no,1);
           break;
   case 2: deposit_withdraw(acc_no,2);
           break;
   case 3: disp_acc(acc_no);
           break;
   case 4: c=acc_no;

           break;
   case 5: cout<<"Thnak you, you have successfully logged out"<<endl;

           break;
  }
 }
 while(ch>=1&&ch<=5);
}
void main()
{
 cout<<"     HSBC BANK    "<<endl;
 int choice;
 do
 {
  if(c!=0)
    del_acc(c);
  cout<<" Welcome User1 What would you like to do? "<<endl;
  cout<<"1)Create account"<<endl;
  cout<<"2)login into account"<<endl;
  cout<<"3)exit"<<endl;
  cout<<"enter choice"<<endl;
  cin>>choice;
  switch(choice)
  {
   case 1: write();
           break;
   case 2: login();
           break;
   case 3: exit(0);
   default: cout<<"enter correct choice";
  }
 }
 while(choice>=1&&choice<=3);
 getch();
}
