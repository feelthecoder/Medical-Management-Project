#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<iostream.h>
#include<iomanip.h>
#include<fstream.h>
#include<dos.h>
#include<graphics.h>
void menu();
void treat();
void bill();
void tandc();
void welcome_page();
void last();
void main_menu();
char c;
int flag;

class med
{
char medicine[50],disease[50],manu[50];
int medno;
public:
	void in() ;

	void out()
	{
		cout<<"\n\t"<<medno<<" \t      "<<medicine<<"\t         "<<disease<<"   \t     "<<manu;
	}
	void mod();

	int medpno()
	{
		return medno;
	}
	void dishead()
	{
		cout<<"\n | Medicine number  |  Medicine name  | Disease Handled   | Manufacturer| ";
		cout<<"\n  ---------------------------------------------------------------------";
	}
	void head()
	{
		cout<<"\n   **************** P A V V    M E D I C A L    C A R E****************";
		cout<<"\n\n\t\t\t    MEDICINE MENU";
		cout<<"\n\t\t\t  -----------------";
	}
};
void med::in()
	{
		cout<<"\n * Enter the medicine number:";
		cin>>medno;
		cout<<"\n * Enter the disease for which medicine is specified:";
		gets(disease);
		cout<<"\n * Enter the Name of medicine:";
		gets(medicine);
		cout<<"\n * Enter the manufacturer of medicine:";
		gets(manu);
		cout<<"\n Saving the given credentials,please wait";
		for(int k=0; k<10;k++)
		{
			delay(300);
			cout<<".";
		}
		cout<<"\n\n Saved Successfully!";
	}
void med::mod()
{
		cout<<"\n * Enter The New Details.";
		cout<<"\n * Enter the medicine number:";
		cin>>medno;
		cout<<"\n * Enter the disease for which medicine is specified:";
		gets(disease);
		cout<<"\n * Enter the medicine:";
		gets(medicine);
		cout<<"\n * Enter the manufacturer of medicine:";
		gets(manu);
		cout<<"\n\n Saving the given credentials,please wait";
		for(int i=0;i<10;i++)
		{
			delay(300);
			cout<<".";
		}
		cout<<"\n\n Saved Successfully!";
	}


void menu()
{
	clrscr();
	int e;
	ofstream fo;
	fstream fi;
	ifstream fifo;
	med l;
	l.head();
	cout<<"\n                           1.Add medicine\n       ";
	cout<<"		           2.Remove Medicine\n    ";
	cout<<"                       3.Search Medicine\n    ";
	cout<<"                       4.Modify Medicine\n    ";
	cout<<"                       5.Display Medicine\n   ";
	cout<<"                        6.Exit                 ";
	cout<<"\n\n  Enter your choice:";
	cin>>e;
	clrscr();
	switch(e)
	{
		case 1:
		l.head();
		cout<<"\n                           FORM FOR ADDING A MEDICINE              ";
		fo.open("medicine",ios::binary|ios::app);
		do
		{
			l.in();
			fo.write((char*)&l,sizeof(l));
			cout<<"\n\n Do Yo Want To Add More(Y/N):";
			cin>>c;
		}while(c=='y'||c=='Y');
		fo.close();
		cout<<"\n\n Do You Want To Go To Medicine Menu(Y/N):";
		cin>>c;
		if(c=='y'||c=='Y')
			menu();
		else
		{
			cout<<"\n\n Do You Want To Main Menu(Y/N):";
			cin>>c;
			if(c=='y'||c=='Y')
				main_menu();
			else
				last();
		}
		break;
		case 2:
		int x;
		flag=0;
		l.head();
		cout<<"\nEnter medicine number to be removed:";
		cin>>x;
		fifo.open("medicine",ios::binary);
		if(!fifo)
		{
			cout<<"\n File Could Not Be Opened!!! Press Any Key...";
			return;
		}
		while(fifo.read((char*)&l,sizeof(l)))
		{
			if(l.medpno()==x)
			{
				l.dishead();
				l.out();
				flag++;
			}
		}
		fifo.close();
		if(flag==0)
			cout<<"\n Record Not Found.";
		else
		{
			cout<<"\n Do You Want To Delete It(Y/N):";
			cin>>c;
			if(c=='y'||c=='Y')
			{
			    fifo.open("medicine",ios::binary);
			    fo.open("temp",ios::binary);
			    while(fifo.read((char*)&l,sizeof(l)))
			    {
				if(l.medpno()!=x)
				{
					fo.write((char*)&l,sizeof(l));
				}
			    }
			    fifo.close();
			    fo.close();
			    remove("medicine");
			    rename("temp","medicine");
			    cout<<"\n Record Deleted!!!";
			}
		}
		cout<<"\n\n Do You Want To Go To Medicine Menu(Y/N):";
		cin>>c;
		if(c=='y'||c=='Y')
			menu();
		else
		{
			cout<<"\n\n Do You Want To Main Menu(Y/N):";
			cin>>c;
			if(c=='y'||c=='Y')
				main_menu();
			else
				last();
		}
		break;
		case 3:
		int search;
		flag=0;
		l.head();
		cout<<"\n Enter medicine number to be searched:";
		cin>>search;
		fi.open("medicine",ios::binary|ios::in|ios::out);
		if(!fi)
		{
			cout<<"\n File could not be opened!! Press any key!!";
			return;
		}
		while(fi.read((char*)&l,sizeof(l)))
		{
			if(l.medpno()==search)
			{
				l.dishead();
				l.out();
				flag++;
				break;
			}
		}
		fi.close();
		if(flag==0)
			cout<<"\n Record Not Found.";
		cout<<"\n\n Do You Want To Go To Medicine Menu(Y/N):";
		cin>>c;
		if(c=='y'||c=='Y')
			menu();
		else
		{
			cout<<"\n\n Do You Want To Main Menu(Y/N):";
			cin>>c;
			if(c=='y'||c=='Y')
				main_menu();
			else
				last();
		}
		break;
		case 4:
		int n;
		flag=0;
		l.head();
		cout<<"\n Enter medicine number to be modified:";
		cin>>n;
		fi.open("medicine",ios::binary|ios::in|ios::out);
		if(!fi)
		{
			cout<<"\n File could not be opened!! Press any key!!!";
			return;
		}
		while(fi.read((char*)&l,sizeof(l)))
		{
			if(l.medpno()==n)
			{
				l.dishead();
				l.out();
				l.mod();
				int pos=(-1)*sizeof(l);
				fi.seekp(pos,ios::cur);
				fi.write((char*)&l,sizeof(l));
				cout<<"\n Record Updated" ;
				flag++;
			}
		}
		fi.close();
		if(flag==0)
			cout<<"\n Record Not Found.";
		cout<<"\n\n Do You Want To Go To Medicine Menu(Y/N):";
		cin>>c;
		if(c=='y'||c=='Y')
			menu();
		else
		{
			cout<<"\n\n Do You Want To Main Menu(Y/N):";
			cin>>c;
			if(c=='y'||c=='Y')
				main_menu();
			else
				last();
		}
		break;
		case 5:
		clrscr();
		l.head();
		fifo.open("medicine",ios::binary);
		l.dishead();
		while(fifo.read((char*)&l,sizeof(l)))
		{
			l.out();
		}
		fifo.close();
		cout<<"\n\n Do You Want To Go To Medicine Menu(Y/N):";
		cin>>c;
		if(c=='y'||c=='Y')
			menu();
		else
		{
			cout<<"\n\n Do You Want To Main Menu(Y/N):";
			cin>>c;
			if(c=='y'||c=='Y')
				main_menu();
			else
				last();
		}
		break;
		case 6:
		l.head();
		last();
		break;
		default:
		cout<<"\n Enter Valid Choice.";
		break;
	}
}


class treat1
{
char treatement[50],disease[50];
int tno;
public:
	void dishead()
	{
		cout<<"\n\n | Treatement number  |  Treatement name  | Disease handled   | ";
		cout<<"\n ---------------------------------------------------------------";
	}
	void head()
	{
		cout<<"\n   **************** P A V V    M E D I C A L    C A R E****************";
		cout<<"\n\n\t\t\t   TREATMENT MENU";
		cout<<"\n\t\t\t  -----------------";
	}

	void outtreat()
	{
		cout<<"\n"<<tno<<"\t\t       "<<treatement<<"\t         "<<disease;
	}
	void modtreat()
	{
		cout<<"\n Enter New Details Of Treatment.";
		cout<<"\n * Enter the treatement number:";
		cin>>tno;
		cout<<"\n * Enter the disease for which treatement is specified:";
		gets(disease);
		cout<<"\n * Enter the treatement:";
		gets(treatement);
		cout<<"\n\n Saving the given credentials,please wait";
		for(int i=0;i<10;i++)
		{
			delay(300);
			cout<<".";
		}
		cout<<"\n\n Saved Successfully!";
	}

	void intreat();
	int tpno()
	{
		return tno;
	}
};
void treat1::intreat()
	{
		cout<<"\n * Enter the treatement number:";
		cin>>tno;
		cout<<"\n * Enter the disease for which treatement is specified:";
		gets(disease);
		cout<<"\n * Enter the treatement:";
		gets(treatement);
		cout<<"\n\n Saving the given credentials,please wait";
		for(int i=0;i<10;i++)
		{
			delay(300);
			cout<<".";
		}
		cout<<"\n\n Saved Successfully!";
	}


void treat()
{
	clrscr();
	int s;
	ofstream a;
	fstream b;
	ifstream car;
	treat1 l;
	l.head();
	cout<<"\n                       1.Add Treatement\n";
	cout<<"	               2.Remove Treatement\n";
	cout<<"                       3.Search Treatement\n";
	cout<<"                       4.Modify Treatement\n";
	cout<<"                       5.Display Treatements\n";
	cout<<"                       6.Exit";
	cout<<"\n   Enter your choice:";
	cin>>s;
	clrscr();
	switch(s)
	{
		case 1:
		a.open("treatu",ios::binary|ios::app);
		do
		{
		clrscr();
		l.head();
		cout<<"\n\n                  FORM FOR ADDING A TREATEMENT              ";
		l.intreat();
		a.write((char*)&l,sizeof(l));
		cout<<"\n Do You Want To Add More(Y/N):";
		cin>>c;
		}while(c=='y'||c=='Y');
		a.close();
		cout<<"\n Do You Want To Go To Treatment Menu(Y/N):";
		cin>>c;
		if(c=='y'||c=='Y')
			treat();
		else
		{
			cout<<"\n Do You Want To Go To Main Menu(Y/N):";
			cin>>c;
			if(c=='y'||c=='Y')
				main_menu();
			else
				last();
		}
		break;
		case 2:
		int x;
		do
		{
		clrscr();
		flag=0;
		l.head();
		cout<<"\n Enter treatement number to be removed:";
		cin>>x;
		car.open("treatu",ios::binary);
		if(!car)
		{
			cout<<"\n File Could Not Be Opened!!! Press Any Key...";
			return;
		}
		while(car.read((char*)&l,sizeof(l)))
		{
			if(l.tpno()==x)
			{
				l.dishead();
				l.outtreat();
				flag++;
			}
		}
		car.close();
		if(flag==0)
			cout<<"\n Record Not Found.";
		else
		{
		cout<<"\n\n Do You Want To Delete It(Y/N):";
		cin>>c;
		if(c=='y'||c=='Y')
		{
			car.open("treatu",ios::binary);
			a.open("temp",ios::binary);
			while(car.read((char*)&l,sizeof(l)))
			{
				if(l.tpno()!=x)
				{
					a.write((char*)&l,sizeof(l));				}
			}
			car.close();
			a.close();
			remove("treatu");
			rename("temp","treatu");
			cout<<"\n Record Deleted!!!";
		}
		}
		cout<<"\n Delete More(Y/N):";
		cin>>c;
		}while(c=='y'||c=='Y');
		cout<<"\n Do You Want To Go To Treatment Menu(Y/N):";
		cin>>c;
		if(c=='y'||c=='Y')
			treat();
		else
		{
			cout<<"\n Do You Want To Go To Main Menu(Y/N):";
			cin>>c;
			if(c=='y'||c=='Y')
				main_menu();
			else
				last();
		}
		break;
		case 3:
		int search;
		do
		{
		clrscr();
		flag=0;
		l.head();
		cout<<"\n Enter treatement number to be searched:";
		cin>>search;
		b.open("treatu",ios::binary|ios::in|ios::out);
		if(!b)
		{
			cout<<"\n File could not be opened!! Press any key!!";
			return;
		}
		while(b.read((char*)&l,sizeof(l)))
		{
			if(l.tpno()==search)
			{
				l.dishead();
				l.outtreat();
				flag++;
				break;
			}
		}
		b.close();
		if(flag==0)
			cout<<"\n Record Not Found.";
		cout<<"\n\n Search More(Y/N):";
		cin>>c;
		}while(c=='y'||c=='Y');
		cout<<"\n Do You Want To Go To Treatment Menu(Y/N):";
		cin>>c;
		if(c=='y'||c=='Y')
			treat();
		else
		{
			cout<<"\n Do You Want To Go To Main Menu(Y/N):";
			cin>>c;
			if(c=='y'||c=='Y')
				main_menu();
			else
				last();
		}
		break;
		case 4:
		int n;
		do
		{
		clrscr();
		flag=0;
		l.head();
		cout<<"\n Enter treatement number to be modified:";
		cin>>n;
		b.open("treatu",ios::binary|ios::in|ios::out);
		if(!b)
		{
			cout<<"\n File could not be opened!! Press any key!!!";
			return;
		}
		while(b.read((char*)&l,sizeof(l)))
		{
			if(l.tpno()==n)
			{
				l.dishead();
				l.outtreat();
				l.modtreat();
				int pos=(-1)*sizeof(l);
				b.seekp(pos,ios::cur);
				b.write((char*)&l,sizeof(l));
				cout<<"\n Record Updated" ;
				flag++;
			}
		}
		b.close();
		if(flag==0)
			cout<<"\n Record Not Found.";
		cout<<"\n\n Modify More Records(Y/N):";
		cin>>c;
		}while(c=='y'||c=='Y');
		cout<<"\n Do You Want To Go To Treatment Menu(Y/N):";
		cin>>c;
		if(c=='y'||c=='Y')
			treat();
		else
		{
			cout<<"\n Do You Want To Go To Main Menu(Y/N):";
			cin>>c;
			if(c=='y'||c=='Y')
				main_menu();
		}
		break;
		case 5:
		clrscr();
		car.open("treatu",ios::binary);
		l.head();
		l.dishead();
		while(car.read((char*)&l,sizeof(l)))
		{
			l.outtreat();
		}
		car.close();
		cout<<"\n Do You Want To Go To Treatment Menu(Y/N):";
		cin>>c;
		if(c=='y'||c=='Y')
			treat();
		else
		{
			cout<<"\n Do You Want To Go To Main Menu(Y/N):";
			cin>>c;
			if(c=='y'||c=='Y')
				main_menu();
			else
				last();
		}
		break;
		case 6:
		last();
		break;
		default:
		cout<<"\n Enter Valid Number";
	}
}


class pat
{
int pt_no,age;
long int mob;
char pt_name[50],address[50],rela[50],prob[50],ch,stat[10];
public:
	void pat_insert()
	{
		cout<<"\n * Enter the patient registration number:";
		cin>>pt_no;
		cout<<"\n * Enter the name of patient:";
		gets(pt_name);
		cout<<"\n * Enter the age of patient:";
		cin>>age;
		cout<<"\n * Enter the address  of patient:";
		gets(address);
		cout<<"\n * Enter the mobile number of patient:";
		cin>>mob;
		cout<<"\n * Enter the problem/disease patient suffered:";
		gets(prob);
		cout<<"\n * Enter any known person or relatives:";
		gets(rela);
		cout<<"\n * Enter the status of payment:";
		gets(stat);
		cout<<"\n Saving the given credentials,please wait";
		for(int j=1;j<=10;j++)
		{
			delay(300);
			cout<<".";
		}
		cout<<"\n\n Saved Successfully!";
	}
	void display()
	{
		cout<<"\n "<<pt_no<<"      "<<pt_name<<"      "<<age<<"   "<<mob<<"    "<<address<<"    "<<prob<<"    "<<rela<<"     "<<stat;
	}
	void pat_modify()
	{
		cout<<"\n Enter the new name of patient:";
		gets(pt_name);
		cout<<"\n * Enter the new address  of patient:";
		gets(address);
		cout<<"\n * Enter the new age of patient:";
		cin>>age;
		cout<<"\n * Enter the new mobile number of patient:";
		cin>>mob;
		cout<<"\n * Enter the new problem/disease patient suffered:";
		gets(prob);
		cout<<"\n * Enter any other known person or relatives:";
		gets(rela);
		cout<<"\n * Enter the updated status of payment:";
		gets(stat);
		cout<<"\n Saving the given credentials,please wait";
		for(int l=0;l<8;l++)
		{
			delay(300);
			cout<<".";
		}
		cout<<"\n Saved Successfully!";
	}
	int getpno()
	{
		return pt_no;
	}
	void dishead()
	{

	   cout<<"\n|PatReg| Pat Name | Age |  Mobile   | Address | Problem | Relatives | Status| ";
	   cout<<"\n-----------------------------------------------------------------------------";
	}
	void head()
	{
		cout<<"\n **************** P A V V    M E D I C A L    C A R E****************";

	}
};


	void main_menu()
	{
		D:
		fstream f;
		ofstream fout;
		ifstream fin;
		clrscr();
		int x;
		char c;
		pat p;
		int ch;
		cout<<"\n          W E L C O M E   T O   P A V V    M E D I C A L   C A R E         ";
		cout<<"               -------------   ---   -------    -------------   -------     ";
		cout<<"\n\n                            PATIENT MENU                          ";
		cout<<"\n                           --------------                        ";
		cout<<"\n                           1.Admit patient                             ";
		cout<<"\n			   2.Delete pateient record                    ";
		cout<<"\n			   3.Search patient                            ";
		cout<<"\n			   4.Modify                                    ";
		cout<<"\n			   5.Display all                               ";
		cout<<"\n			   6.Medicines                                 ";
		cout<<"\n			   7.Treatment                                 ";
		cout<<"\n			   8.Bill Calculation                          ";
		cout<<"\n          		   9.Terms And Conditions                      ";
		cout<<"\n			   10.Exit                                     ";
		cout<<"\n\n                    Enter your choice(1-10):";
		cin>>ch;
		clrscr();
		switch(ch)
		{
			case 1:
			fout.open("pat",ios::binary|ios::app);
			do
			{
			clrscr();
			p.head();
			cout<<"                        A D M I T     F O R M                        ";
			p.pat_insert();
			fout.write((char*)&p,sizeof(p));
			textcolor(BLUE);
			cprintf("\n Do You Want To Add More(Y/N):");
			cin>>c;
			}while(c=='y'||c=='Y');
			fout.close();
			if(c=='n'||c=='N')
			{
				textcolor(BLUE);
				cprintf("\n Do You Want To Go To Main Menu(Y/N):");
				cin>>c;
				if(c=='y'||c=='Y')
					main_menu();
				else
					last();
			}
			break;

			case 2:
			int x;
			p.head();
			cout<<"\n Enter patient registration number to be deleted:";
			cin>>x;
			fin.open("pat",ios::binary);
			if(!fin)
			{
				cout<<"\n File Could Not Be Opened!!! Press Any Key...";
				return;
			}
			while(fin.read((char*)&p,sizeof(p)))
			{
				if(p.getpno()==x)
				{
					p.dishead();
					p.display();
				}
			}
			fin.close();
			cout<<"\n Do You Want To Delete It(Y/N):";
			cin>>c;
			if(c=='y'||c=='Y')
			{
			fin.open("pat",ios::binary);
			fout.open("temp",ios::binary);
			while(fin.read((char*)&p,sizeof(p)))
			{
				if(p.getpno()!=x)
				{
					fout.write((char*)&p,sizeof(p));
				}
			}
			fin.close();
			fout.close();
			remove("pat");
			rename("temp","pat");
			cout<<"Record Deleted!!!";
			}
			cout<<"\n Do you want to go to main menu(y/n):";
			cin>>c;
			if(c=='y'||c=='Y')
				main_menu();
			else
			{
				last();
			}
			break;

		case 3:
		int search;
		flag=0;
		p.head();
		cout<<"\n Enter patient registration number to be searched:";
		cin>>search;
		f.open("pat",ios::binary|ios::in|ios::out);
		if(!f)
		{
			cout<<"\n File could not be opened!! Press any key!!";
			return;
		}
		while(f.read((char*)&p,sizeof(p)))
		{
			if(p.getpno()==search)
			{
				p.dishead();
				p.display();
				flag++;
				break;
			}
		}
		if(flag==0)
			textcolor(BLUE);
			cprintf("\n Record Not Found");
		cprintf("\n Do you want to go to main menu(y/n):");
		cin>>c;
		if(c=='y'||c=='Y')
			main_menu();
		else
		{
			last();
		}
		break;

		case 4:
		int n;
		flag=0;
		p.head();
		cout<<"\n Enter patient registration number to be modified:";
		cin>>n;
		f.open("pat",ios::binary|ios::in|ios::out);
		if(!f)
		{
			cout<<"\n File could not be opened!! Press any key!!!";
			return;
		}
		while(f.read((char*)&p,sizeof(p)))
		{
			if(p.getpno()==n)
			{
				p.dishead();
				p.display();
				int pos=(-1)*sizeof(p);
				cout<<"\n Enter the new details of patient";
				p.pat_modify();
				f.seekp(pos,ios::cur);
				f.write((char*)&p,sizeof(p));
				cout<<"\n Record Updated" ;
				flag++;
			}
		}
		f.close();
		if(flag==0)
		textcolor(BLUE);
			cprintf("\n Record Not Found");
		cprintf("\n Do you want to go to main menu(y/n):");
		cin>>c;
		if(c=='y'||c=='Y')
			main_menu();
		else
		{
			last();
		}
		break;

		case 5:
		clrscr();
		p.head();
		cout<<endl;
		fin.open("pat",ios::binary);
		p.dishead();
		while(fin.read((char*)&p,sizeof(p)))
		{
			p.display();
		}
		fin.close();
		cout<<"\n\nDo You Want To Go To Main Menu(Y/N):";
		cin>>c;
		if(c=='y'||c=='Y')
			main_menu();
		else
			last();
		break;

		case 6:
		menu();
		break;


		case 7:
		treat();
		break;

		case 8:
		bill();
		clrscr();
		textcolor(BLUE);
		cprintf("\n Do you want to go to main menu(y/n):");
		cin>>c;
		if(c=='y'||c=='Y')
			main_menu();
		else
		{
			last();
		}
		break;

		case 9:
		tandc();
		textcolor(BLUE);
		cprintf("\n Do you want to go to main menu(y/n):");
		cin>>c;
		if(c=='y'||c=='Y')
			main_menu();
		else
		{
		       last();
		}
		break;

		case 10:
		last();
		break;

		default:
		textcolor(BLUE);
		cprintf("\n Please Enter Valid Number");
	}
}


void main()
{
	clrscr();
	welcome_page();
	main_menu();
	getch();
}


void bill()
{
	fstream ff;
	pat p;
	char cha;
	int doc_fee,c_p,n,c_m,t_m,x;
	char pro[50];
	flag=0;
	clrscr();
	cout<<"\nW E L C O M E   T O  T H E  C O U N T E R  O F  P A V V   M E D I C A L  C A R E ";
	cout<<"\n\n Enter the patient registration number:";
	cin>>x;
	ff.open("pat",ios::binary|ios::out|ios::in);
	while(ff.read((char*)&p,sizeof(p)))
	{
		if(p.getpno()==x)
		{
			cout<<"\n Patient's Details:\n";
			p.dishead();
			p.display();
			flag++;
		}
	}
	if(flag==0)
		{
		cout<<"\n Record Not Found.";
		delay(5);
		last(); }
	else
	{
	cout<<"\n * Enter the problem listed:";
	gets(pro);
	cout<<"\n * Enter the number of days for which patient is admitted:";
	cin>>n;
	cout<<"\n * Enter the charges per day for bed:";
	cin>>c_p;
	cout<<"\n * Enter the medicine fee:";
	cin>>c_m;
	cout<<"\n * Enter the doctor fee:";
	cin>>doc_fee;
	cout<<"\n Do you want to proceed to calculate the bill(Y/N):";
	cin>>c;
	if(c=='y'||c=='Y')
	{
		cout<<"\n Please wait while your bill is calulated";
		for(int o=0;o<5;o++)
		{
			delay(100);
			cout<<".";
		}
		t_m=(c_p*n)+c_m+doc_fee;
		cout<<"\n Your calculated bill is:";
		cout<<t_m;
	}
	}
getch();
}
void tandc()
{
	clrscr();
	cout<<"\n                 T E R M S   A N D     C O N D I T I O N S             ";
	cout<<"\n 1.Each and every patient are equal for us and we treat them equal.";
	cout<<"\n 2.PAVV medical care is registered clinic so no argument to be listened about the service.";
	cout<<"\n 3.If you have any problem then please kindly contact us and feel free.";
	cout<<"\n 4.Payment to the clinic must be made available before patient leave the clinic.";
	cout<<"\n 5.Payment made avialable is not refundable.";
	cout<<"\n 6.People should pre book their appointments to avoid inconvinance.";
	cout<<"\n 7.In case of emegency extra charge is taken.";
	cout<<"\n 8.For any dispute last decision is of PAVV medical care authorities.";
getch();
}
void welcome_page()
{
gotoxy(25,13);
textcolor(BLUE);
cprintf("Loading Application...");
delay(1000);
for(int i=0;i<10;i++)
{
delay(500);
textcolor(BLUE);
cprintf(".");
}
}
void last()
{
	clrscr();
	cout<<"\n\t    \t           P A V V   M E D I C A L    C A R E     ";
	cout<<"\n\n\n\n\t\t    ~~~** - - Thanks For Using Our Project. - - **~~~";
	cout<<"\n\n\t\t\t!! -.-.- Have A Nice Day -.-.- !!";
	cout<<"\n\n\t\t\t Created By:";
	cout<<" **V I K A S   K U M A R**"<<endl;
	cout<<" \t\t\t           **CSE DEPARTMENT**"<<endl;
	cout<<"\t\t         **RAKIYA ENGINEERING COLLEGE BIJNOR**";
}
