#include <bits/stdc++.h>
#include <cstdio>
#define pub push_back
using namespace std;

class new_reg;
class login;
class complain;

class lalon
{
    int seats=100,last_filled=0;
public:
    void setlf()
    {
        ifstream infile;
        infile.open("last_filled.txt");
        string j;
        getline(infile,j);
        while(j[last_filled]=='f' && last_filled<seats)
        {
            last_filled++;
        }
        last_filled++;
    }
    void upstat(int n)
    {
        ifstream infile;
        infile.open("last_filled.txt");
        string j;
        getline(infile,j);
        infile.close();
        if(j[n-1]=='f') {j[n-1]='v';}
        else {j[n-1]='f';}
        ofstream outfile;
        outfile.open("last_filled.txt");
        outfile<<j;
        outfile.close();
    }
    virtual void details()
    {
        ifstream infile;
        infile.open("details.txt");
        while(infile)
        {
            string s;
            getline(infile,s);
            cout<<s<<endl;
        }
        infile.close();
    }
    void contact()
    {
        ifstream infile;
        infile.open("contact.txt");
        while(infile)
        {
            string s;
            getline(infile,s);
            cout<<s<<endl;
        }
        infile.close();
    }
    friend new_reg;
};

class student:public lalon
{
    int seatno,roll,batch;
    string name,dept,id,password_stud,meal_stat;
public:
    void details()
    {
        cout<<"Name: "<<name<<endl;
        cout<<"Student ID: "<<id<<endl;
        cout<<"Department Name: "<<dept<<endl;
        cout<<"Roll No.: "<<roll<<endl;
        cout<<"Batch: "<<batch<<endl;
        cout<<"Seat NO.: "<<seatno<<endl<<endl;
    }
    friend new_reg;
    friend login;
    friend void student_login(student a);
    friend class meal;
    friend void all_students();
};

string pasify(string a)
{
    for(char &i:a)
    {
        if(i==' ') i='_';
    }
    return a;
}

string idfy(string a)
{
    string k;
    int len=a.size();
    for(int i=0;i<len;i++)
    {
        if(a[i]==' ' || i==len) break;
        else k+=a[i];
    }
    return k;

}
class new_reg:public student
{
public:
    string n,d,s;
    int r,b,flag=0;
    void getinfo()
    {
        cout<<"=============================="<<endl;
        cout<<"REGISTRATION PORTAL"<<endl;
        cout<<"=============================="<<endl<<endl;
        cout<<"Enter Your Name: ";
        getline(cin,s);
        getline(cin,name);
        cout<<"Enter Department Name(Abbreviation Only): ";
        getline(cin,dept);
        dept=idfy(dept);
        cout<<"Enter Roll No.: ";
        cin>>roll;
        cout<<"Enter Batch: ";
        cin>>batch;
        cout<<endl;

    }
    void confirm()
    {
        setlf();
        if(last_filled<seats)
        {
            student::id=idfy(name)+to_string(roll);
            student::password_stud=pasify(name)+to_string(roll)+to_string(last_filled);
            cout<<"Registration confirmed.\nYour ID is: "<<id<<"\n"<<"Your Password: "<<password_stud<<endl;
            cout<<"Allotted seat: "<<last_filled<<endl;
            upstat(last_filled);
            ofstream outfile;
            string fname= id+".txt";
            outfile.open(fname);
            outfile<<last_filled<<'\n'<<id<<'\n'<<password_stud<<'\n'<<name<<'\n'<<dept<<'\n'<<roll<<'\n'<<batch<<'\n'<<"nnn"<<endl;
            outfile.close();
            outfile.open("all_students.txt",ios::app);
            outfile<<id<<endl;
            outfile.close();
        }
        else
        {
            cout<<"No Vacancy."<<endl;
        }
    }
    friend string pasify(string a);
};

void printify(string s, int n)
{
    int k=n-2-s.size();
    cout<<s;
    for(int i=0;i<k;i++) cout<<" ";
    cout<<"||";
}

void all_students()
{
    vector<string>v;
    ifstream infile;
    infile.open("all_students.txt");
    while(infile)
    {
        string k;
        getline(infile,k);
        if(k!="\n")
        {
            k=k+".txt";
            v.pub(k);
        }
    }
    infile.close();
    cout<<"Student Name                     |ID                     ||Roll NO.\t||Department\t||Batch   ||Seat NO."<<endl;
    cout<<"============================================================================================================"<<endl;
    int len=v.size()-1;
    for(int i=0;i<len;i++)
    {
        student a;
        string s,k=v[i];
        if(v[i]!="\n") {
        infile.open(k);
        getline(infile,s);
        a.seatno=stoi(s);
        getline(infile,s);
        a.id=s;
        getline(infile,s);
        a.password_stud=s;
        getline(infile,s);
        a.name=s;
        getline(infile,s);
        a.dept=s;
        getline(infile,s);
        a.roll=stoi(s);
        getline(infile,s);
        a.batch=stoi(s);
        infile.close();
        printify(a.name,35);
        printify(a.id,24);
        printify(to_string(a.roll),15);
        printify(a.dept,16);
        printify(to_string(a.batch),10);
        cout<<a.seatno<<endl;
    }
    }
    cout<<"============================================================================================================"<<endl;
}

void notify()
{
    string s,g;
    cout<<"Notice Statement: ";
    getline(cin,g);
    getline(cin,s);
    cout<<endl;
    ofstream outfile;
    outfile.open("notice.txt",ios::app);
    outfile.seekp(0);
    if(s!="\n")
    outfile<<"# "<<s<<endl;
    outfile.close();
}

class complain
{
    string id,statement,s;
public:
    void add()
    {
        cout<<"Enter ID: ";
        cin>>id;
        cout<<"Enter Complain Statement: ";
        getline(cin,s);
        getline(cin,statement);
    }
    friend istream &operator>>(istream &cin,complain &c);
    friend ostream &operator<<(ostream &cout,complain &c);

};

ostream &operator<<(ostream &cout,complain &c)
{
    cout<<"=============================="<<endl;
    cout<<"ALL COMPLAINS"<<endl;
    cout<<"=============================="<<endl;
    ifstream infile;
    infile.open("complain.txt");
    while(infile)
    {
        getline(infile,c.id);
        cout<<c.id<<endl;
        getline(infile,c.statement);
        cout<<c.statement<<endl;
    }
    infile.close();
    return cout;
}
istream &operator>>(istream &cin,complain &c)
{
    ofstream outfile;
    outfile.open("complain.txt",ios::app);
    outfile<<c.id<<endl;
    outfile<<c.statement<<endl<<endl;
    outfile.close();
    return cin;
}

class admin:public lalon
{
    string id, password_adm;
public:
    void authority()
    {
        cout<<"=============================="<<endl;
        cout<<"Welcome Provost"<<endl;
        cout<<"=============================="<<endl<<endl;
        cout << "Enter number to access menu" << endl;
        cout<<"1.Get List of All Students"<<endl;
        cout<<"2.View Complains"<<endl;
        cout<<"3.Add Notice"<<endl;
        cout<<"0. Log Out"<<endl<<endl;
        while(1)
        {
            int n; cout<<"Choose a Provost Menu: ";
            cin>>n; cout<<endl;
            if(n==0) break;
            else if(n==1) all_students();
            else if(n==3) notify();
            else if(n==2)
            {
                complain c;
                cout<<c;
            }
            else cout<<"Invalid Choice"<<endl<<endl;
        }
    }
    void show_notice()
    {
        ifstream infile;
        infile.open("notice.txt");
        cout<<"=============================="<<endl;
        cout<<"NOTICE BOARD"<<endl;
        cout<<"=============================="<<endl<<endl;
        while(infile)
        {
            string s;
            getline(infile,s);
            cout<<s<<endl;
        }
        infile.close();
    }
    friend login;
};

class login:virtual public student, virtual public admin
{
public:
    void process()
    {
        int n;
        cout<<"=============================="<<endl;
        cout <<"LOGIN PORTAL"<<endl<<endl;
        cout << "Enter number to access menu" << endl;
        cout << "1.Student Login" << endl;
        cout << "2.Provost Login" << endl;
        cout<<"=============================="<<endl;
        cout<<endl<<"Choose a login Option: ";
        cin>>n;
        cout<<endl;
        if(n==1)
        {
            string id,pass;
            cout << "Enter Student ID: ";
            cin>>id;
            cout << "Enter Password: " ;
            cin>>pass;
            cout<<endl;
            string f=id+".txt";
            ifstream infile;
            infile.open(f);
            if(infile.is_open())
            {
                student a;
                string s;
                getline(infile,s);
                a.seatno=stoi(s);
                getline(infile,s);
                a.id=s;
                getline(infile,s);
                a.password_stud=s;
                if(a.password_stud==pass)
                {
                    getline(infile,s);
                    a.name=s;
                    getline(infile,s);
                    a.dept=s;
                    getline(infile,s);
                    a.roll=stoi(s);
                    getline(infile,s);
                    a.batch=stoi(s);
                    getline(infile,s);
                    a.meal_stat=s;
                    infile.close();
                    student_login(a);
                }
                else
                {
                    cout<<"Wrong ID or Password."<<endl;
                }
            }
            else
            {
                cout<<"Account Does Not Exist."<<endl;
            }
        }
        else if(n==2)
        {
            string id,pass;
            cout << "Enter Provost ID: ";
            cin>>id;
            cout << "Enter Password: " ;
            cin>>pass;
            cout<<endl;
            admin ad;
            ifstream infile;
            infile.open("admin.txt");
            getline(infile,ad.id);
            getline(infile,ad.password_adm);
            if(ad.id==id && ad.password_adm==pass)
            {
                ad.authority();
            }
            else cout<<"Wrong ID or Password."<<endl;
        }
    }
    friend void student_login(student a);
};

class meal:public login
{
    student a;
public:
    meal(student &s){ a=s;}
    void mealify()
    {
        cout<<"=============================="<<endl;
        cout<<"Meal Menu"<<endl;
        cout<<"=============================="<<endl<<endl;
        cout << "Enter number to access menu" << endl;
        cout<<"1.View Today's Meal Status."<<endl;
        cout<<"2.Update Today's Meal Status."<<endl;
        cout<<"0.Go to Student Menu"<<endl;
        cout<<"=============================="<<endl;
        while(1){
        cout<<"\nChoose a Meal Option: ";
        int n; cin>>n;
        cout<<endl;
        if(n==0) break;
        else if(n==1)
        {
            if(a.meal_stat=="nnn") cout<<"No Meal is Requested"<<endl;
            else{
            cout<<"Requested Meal/s: "<<endl;
            if(a.meal_stat[0]=='y') cout<<"==>>Breakfast\n";
            if(a.meal_stat[1]=='y') cout<<"==>>Lunch\n";
            if(a.meal_stat[2]=='y') cout<<"==>>Dinner\n";
            }
        }
        else if(n==2)
        {
            cout<<"=============================="<<endl;
            cout<<"Change Current Status for"<<endl;
            cout<<"1.Breakfast\n";
            cout<<"2.Lunch\n";
            cout<<"3.Dinner\n";
            cout<<"0.Go to Previous Menu"<<endl;
            cout<<"=============================="<<endl;
            while(1)
            {
                cout<<"\nChoose a Meal Status Option: ";
                cin>>n; cout<<endl;
                if(n==0) break;
                else if(n==1)
                {
                    if(a.meal_stat[0]=='y')
                    {
                        a.meal_stat[0]='n';
                        cout<<"Breakfast is Cancelled"<<endl;
                    }
                    else
                    {
                        a.meal_stat[0]='y';
                        cout<<"Breakfast is Requested"<<endl;
                    }
                }
                else if(n==2)
                {
                    if(a.meal_stat[1]=='y')
                    {
                        a.meal_stat[1]='n';
                        cout<<"Lunch is Cancelled"<<endl;
                    }
                    else
                    {
                        a.meal_stat[1]='y';
                        cout<<"Lunch is Requested"<<endl;
                    }
                }
                else if(n==3)
                {
                    if(a.meal_stat[2]=='y')
                    {
                        a.meal_stat[2]='n';
                        cout<<"Dinner is Cancelled"<<endl;
                    }
                    else
                    {
                        a.meal_stat[2]='y';
                        cout<<"Dinner is Requested"<<endl;
                    }
                }
                else cout<<"Invalid Choice"<<endl;
            }
            cout<<"=============================="<<endl;
            ofstream outfile;
            string fname=a.id+".txt";
            outfile.open(fname);
            outfile<<a.seatno<<'\n'<<a.id<<'\n'<<a.password_stud<<'\n'<<a.name<<'\n'<<a.dept<<'\n'<<a.roll<<'\n'<<a.batch<<'\n'<<a.meal_stat<<endl;
            outfile.close();
        }
       else cout<<"Invalid Choice"<<endl;
    }
}
};

 void student_login(student a)
{
    cout<<"=============================="<<endl;
    cout<<"Welcome "<<a.name<<endl;
    cout<<"=============================="<<endl<<endl;
    cout << "Enter number to access menu" << endl;
    cout<<"1. Information"<<endl;
    cout<<"2. Meal On/Off"<<endl;
    cout<<"3. Seat Cancellation"<<endl;
    cout<<"0. Log Out"<<endl;
    cout<<"=============================="<<endl;
    cout<<endl;
    while(1)
    {
        int n; cout<<"Choose a Student Menu: ";
        cin>>n; cout<<endl;
        if(n==0) break;
        else if(n==1) a.details();
        else if(n==3)
        {
            char k[30];
            int len=a.id.size();
            for(int i=0;i<len;i++)
            {
                k[i]=a.id[i];
            }
            strcat(k,".txt");
            if(remove(k)!=0)
            {
                cout<<"Cancellation Unsuccessful"<<endl<<endl;
            }
            else
            {
                a.upstat(a.seatno);
                vector<string> v;
                ifstream infile;
                infile.open("all_students.txt");
                while(infile)
                {
                    string s;
                    getline(infile,s);
                    if(s!=a.id) v.pub(s);
                }
                infile.close();
                ofstream outfile;
                outfile.open("all_students.txt");
                int len=v.size()-1;
                for(int i=0;i<len;i++)
                {
                    outfile<<v[i]<<endl;
                }
                outfile.close();
                cout<<"Cancellation Successful"<<endl<<endl;
                break;
            }
        }
        else if(n==2)
        {
            meal m(a);
            m.mealify();
        }
        else cout<<"Invalid Selection"<<endl;
    }

}

int main()
{
    cout<<"=============================="<<endl;
    cout << "WELCOME TO LALON SHAH HALL" << endl;
    cout<<"=============================="<<endl;
    cout << "MAIN MENU\n\nEnter number to access menu" << endl<<endl;
    cout << "1. Hall Details" << endl;
    cout << "2. New Registration" << endl;
    cout << "3. Login" << endl;
    cout << "4. Notice Board" << endl;
    cout << "5. Complain Box" << endl;
    cout << "6. Contact Info" << endl;
    cout<<"0. Terminate Session"<<endl;
    cout<<"=============================="<<endl;
    cout<<endl;
    while(1)
    {
        int n; cout<<"Choose a Main Option: ";
        cin>>n; cout<<endl;
        lalon l;
        if(n==0) break;
        else if(n==1) l.details();
        else if(n==6) l.contact();
        else if(n==2)
        {
            new_reg r;
            r.getinfo();
            r.confirm();
        }
        else if(n==3)
        {
            login l;
            l.process();
        }
        else if(n==4)
        {
            admin ad;
            ad.show_notice();
        }
        else if(n==5)
        {
            complain c;
            c.add();
            cin>>c;
        }
        else cout<<"Invalid Choice"<<endl;
        cout<<endl;
    }

}


