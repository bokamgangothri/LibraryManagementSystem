#include <iostream>
#include<conio.h>
#include<iomanip>//input-output manipulator
#include<stdlib.h> 
#include<string.h>
#include<stdio.h>
#include<fstream>
#include<stdlib.h>
#include <windows.h>
class book
{
	char bno[6];//bookno.
	char bname[50];//bookname
	char aname[20];//authorname
	public:
	void createbook()
	{
		std::cout<<"\nNEW BOOK ENTRY...\n";
		std::cout<<"\nENTER BOOK NO.";
		std::cin>>bno;
		std::cout<<"\nENTER BOOK NAME";
		gets(bname);//enables enter with space
		std::cout<<"\nENTER AUTHOR NAME";
		gets(aname);
		std::cout<<"\n\n\nBook Created..";
	}
	void showbook()
	{
		std::cout<<"\nBook Number: "<<bno;
		std::cout<<"\nBook Name: ";
		puts(bname);
		std::cout<<"\nBook Author Name: ";
		puts(aname);
	}
	void modifybook()
	{
		std::cout<<"\nBook Number: "<<bno;
		std::cout<<"\nModify Book Name :";
		gets(bname);
		std::cout<<"\nModify Author's Name :";
		gets(aname);
		
	}
	
	char* retbno()//string return
	{
		return bno;
	
	}
	void report()
	{
		std::cout<<bno<<std::setw(30)<<bname<<std::setw(30)<<aname<<std::endl;
	}
};
class student
{
	char admno[6];//admission no.
	char name[20];
	char stbno[6];// student book no 
	int token;//total book of student
	public:
	void createstudent()
	{
		
		std::cout<<"\nNEW STUDENT ENTRY...\n";
		std::cout<<"\nEnter The Admission No. ";
		std::cin>>admno;
		std::cout<<"Enter The Student Name ";
		gets(name);
		token=0;
		stbno[0]='\0';
		std::cout<<"\n\nStudent Record Created...";
	}
	void showstudent()
	{
		std::cout<<"\nAdmission Number : "<<admno;
		std::cout<<"\nStudent Name : ";
		puts(name);
		std::cout<<"\nNo of Book Issued : "<<token;
		if(token==1)
		{
			std::cout<<"\nBook Number "<<stbno;
		}
	}
	void modifystudent()
	{
		std::cout<<"\nAdmission No. "<<admno;
		std::cout<<"\nModify Student Name : ";
		gets(name);
	}
	char* retadmno()
	{
		return admno;
	}
	char* retstbno()
	{
		return stbno;
	}
	int rettoken()
	{
		return token;
	}
	void addtoken()
	{
		token=1;
	}
	void resettoken()
	{ 
	token=0;
	}
	void getstbno(char t[])
	{
		strcpy(stbno,t);
	}
	void report()
	{
		std::cout<<"\t"<<admno<<std::setw(20)<<name<<std::setw(10)<<token<<std::endl ;
	}
};//class ends here
std::fstream fp,fp1;
book bk;//book class object
student st;//student class object

void writebook()
{
	char ch;
	fp.open("book.dat",std::ios::out|std::ios::app);//write and append data
	do{
		//clrscr();
		bk.createbook();
		fp.write((char*)&bk,sizeof(book));//size of class
		std::cout<<"\n\nDo you want to add more record...(y/n?) ";
		std::cin>>ch;
	}while(ch=='y'||ch=='Y');
	fp.close();
}

void writestudent()
{
	char ch;
	fp.open("student.dat",std::ios::out|std::ios::app);//write and append data
	do{
		//clrscr();
		st.createstudent();
		fp.write((char*)&st,sizeof(student));//size of class
		std::cout<<"\n\nDo you want to add more record...(y/n?) ";
		std::cin>>ch;
	}while(ch=='y'||ch=='Y');
	fp.close();
}
 void displayspb(char n[])
 {
	 std::cout<<"\nBOOK DETAILS\n";
	 int flag=0;//book not found
	 fp.open("book.dat",std::ios::in);//read data
	 while(fp.read((char *)&bk,sizeof(book)))
	 {
		 if(strcmpi(bk.retbno(),n)==0)//not case sensitive
		 {
			  bk.showbook();
			  flag=1;
		 }
	 }
	 fp.close();
	 if(flag==0)//book not found
	 {
		 std::cout<<"\n\nBook does not exist";
         		 
	 }
	 getch();
}
 void displaysps(char n[])
 {
	 std::cout<<"\nSTUDENT DETAILS\n";
	 int flag=0;//student not found
	 fp.open("student.dat", std::ios::in);//read data
	 while(fp.read((char *)&st,sizeof(student)))
	 {
		 if(strcmpi(st.retadmno(),n)==0)//not case sensitive
		 {
			  st.showstudent();
			  flag=1;
		 }
	 }
	 fp.close();
	 if(flag==0)//student not found
	 {
		 std::cout<<"\n\nStudent does not exist";
         		 
	 }
	 getch();
}
void modifybook()
{
	char n[6];
	int found=0;//seach book of given data
	//clrscr();
	std::cout<<"\n\nMODIFY BOOK RECORD...";
	std::cout<<"\n\nEnter the book no. ";
	std::cin>>n;
	fp.open("book.dat",std::ios::in|std::ios::out);
	while(fp.read((char*)&bk,sizeof(book)) && found==0)
	{
		if(strcmpi(bk.retbno(),n)==0)
		{
			bk.showbook();
			std::cout<<"\nEnter the new details book";
			bk.modifybook();
			int pos=-1*sizeof(bk);
			fp.seekp(pos,std::ios::cur);//back from current position
			fp.write((char *)&bk,sizeof(book));
			std::cout<<"\n\nRecord Updated";
			found=1;
		}
			
	}
	fp.close();
	if(found==0)
	{
		std::cout<<"\n\nRecord Not Found";
		
	}
	getch();//press key to get out	
}
 void modifystudent()
{
	char n[6];
	int found=0;//seach book of given data
//	clrscr();
	std::cout<<"\n\nMODIFY STUDENT RECORD...";
	std::cout<<"\n\nEnter the Admission no. ";
	std::cin>>n;
	fp.open("student.dat",std::ios::in|std::ios::out);
	while(fp.read((char*)&st,sizeof(student)) && found==0)
	{
		if(strcmpi(st.retadmno(),n)==0)
		{
			st.showstudent();
			std::cout<<"\nEnter the new details of student";
			st.modifystudent();
			int pos=-1*sizeof(st);
			fp.seekp(pos,std::ios::cur);//back from current position
			fp.write((char *)&st,sizeof(student)); 
			std::cout<<"\n\nRecord Updated";
			found=1;
		}
			
	}
	fp.close();
	if(found==0)
	{
		std::cout<<"\n\nRecord Not Found";
		
	}
	getch();//press key to get out	
}
 
 void deletestudent()
 {
	 char n[6];
	 int flag=0;
	 //clrscr();
	 std::cout<<"\n\n\n\tDELETE STUDENT...";
	 std::cout<<"\n\nEnter the Admission no> : ";
	 std::cin>>n;
	 fp.open("student.dat",std::ios::in|std::ios::out);
	 std::fstream fp2;
	 fp2.open("temp.dat",std::ios::out);
	 fp.seekg(0,std::ios::beg);
	 while(fp.read((char*)&st,sizeof(student)))
	 {
		 if(strcmpi(st.retadmno(),n)!=0)
		 {
			 fp2.write((char*)&st,sizeof(student));
		 }
		 else{
			 flag=1;//student found
		 }
	 } 
	 fp2.close();
	 fp.close();
	 remove("student.dat");
	 rename("temp.dat","student.dat");//data after deletion moved to temp
	 if(flag==1)
	 {
		 std::cout<<"\n\n\tRecord Deleted..";
	 }
	 else
	 {
		std::cout<<"\n\nRecord not Found"; 
	 }
	 getch();
 }
  void deletebook()
 {
	 char n[6];//book no.
	 int flag=0;
	 //clrscr();
	 std::cout<<"\n\n\n\tDELETE BOOK...";
	 std::cout<<"\n\nEnter the Book no> : ";
	 std::cin>>n;
	 fp.open("book.dat",std::ios::in|std::ios::out);
	 std::fstream fp2;//New onject
	 fp2.open("Temp.dat",std::ios::out);//temp having data else than that to be deleted
	 fp.seekg(0,std::ios::beg);
	 while(fp.read((char*)&bk,sizeof(book)))
	 {
		 if(strcmpi(bk.retbno(),n)!=0)
		 {
			 fp2.write((char*)&st,sizeof(book));
		 }
		 else{
			 flag=1;//student found
		 }
	 } 
	 fp2.close();
	 fp.close();
	 remove("book.dat");
	 rename("Temp.dat","book.dat");//data after deletion moved to temp
	 if(flag==1)
	 {
		 std::cout<<"\n\n\tRecord Deleted... ";
	 }
	 else
	 {
		std::cout<<"\n\nRecord not Found"; 
	 }
	 getch();
 }
 void displayalls()
 {
	 //clrscr();
	 fp.open("student.dat",std::ios::in);//read mode
	 if(!fp)
	 {
		 std::cout<<"File Could Not Be Open";
		 getch();
		 return;//press any key and return
	 }
	 std::cout<<"\n\n\t\tStudent List\n\n";
	 std::cout<<"==================================================================\n";
	 std::cout<<"\tAdmission No."<<std::setw(10)<<"Name"<<std::setw(20)<<"Book Issued\n";
	 std::cout<<"==================================================================\n";
	 while(fp.read((char*)&st,sizeof(student)))
	 {
		 st.report();
	 }
	 fp.close();
	 getch();
 }
  void displayallb()
 {
	 //clrscr();
	 fp.open("book.dat",std::ios::in);//read mode
	 if(!fp)
	 {
		 std::cout<<"File Could Not Be Open";
		 getch();
		 return;//press any key and return
	 }
	 std::cout<<"\n\n\t\tBook List\n\n";
	 std::cout<<"==================================================================\n";
	 std::cout<<"\tBook No."<<std::setw(20)<<"Book Name"<<std::setw(25)<<"Book Author\n";
	 std::cout<<"==================================================================\n";
	 while(fp.read((char*)&bk,sizeof(book)))
	 {
		 bk.report();
	 }
	 fp.close();
	 getch();
 }
 void bookissue()
 {
	 char sn[6],bn[6];
	 int found=0,flag=0;
	 //clrscr();
	 std::cout<<"\n\nBOOK ISSUE...";
	 std::cout<<"\n\n\tEnter Admission no.";
	 std::cin>>sn;
	 fp.open("student.dat",std::ios::in|std::ios::out);
	 fp1.open("book.dat",std::ios::in|std::ios::out);
	 while(fp.read((char*)&st,sizeof(student))&& found==0)
	 {
		 if(strcmpi(st.retadmno(),sn)==0)//compare admsn no.
		 {
			 found=1;
			 if(st.rettoken()==0)//if book not issued
			 {
				 std::cout<<"\n\n\tEnter The Book No.";
			 std::cin>>bn;
			  while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
			  {
				   if(strcmpi(bk.retbno(),bn)==0)//compare book no.
		             {
			          flag=1;
					  st.addtoken();
					  st.getstbno(bk.retbno());//pass book no.
					  int pos=-1*sizeof(st);
					  fp.seekg(pos,std::ios::cur);
					  fp.write((char*)&st,sizeof(student));
					  std::cout<<"\n\n\tBook Issued Successfully\n\n Please Note The Book Issue Date On Backside Of Your Book And Return Book Within 15 Days, Otherwise Fine Of 15 Rs Per Day";
					  
					
			  }
		 }
		 if(flag==0)
		 {
			 std::cout<<"Book No. Does Not Exists";
		 }
		 
	 } 
	 
	 else
	 {
		 
		 std::cout<<"You Have Not Returned The Last Book";
		 
	 }
	 
		 
 
	 }
 
 }
 if(found==0)
 {
	 std::cout<<"Student Record Not Exists...";
	 
 }
 getch();
 fp.close();
 fp1.close();
 }
 
 void bookdeposit()
 {
	 char sn[6],bn[6];
	 int found=0,flag=0,day,fine;
	 //clrscr();
	 std::cout<<"\n\nBOOK DEPOSIT...";
	 std::cout<<"\n\n\tEnter Admission no. Of Student";
	 std::cin>>sn;
	 fp.open("student.dat",std::ios::in|std::ios::out);
	 fp1.open("book.dat",std::ios::in|std::ios::out);
	 while(fp.read((char*)&st,sizeof(student))&& found==0)
	 {
		 if(strcmpi(st.retadmno(),sn)==0)//compare admsn no.
		 {
			 found=1;
			 if(st.rettoken()==1)//if book issued
			 {
				 while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
			  {
				   if(strcmpi(bk.retbno(),st.retstbno())==0)
		             {
			          flag=1;
					  bk.showbook();
					  std::cout<<"\n\n Book Deposited In No. Of Days";
					  std::cin>>day;
					  if(day>15)
					  {
						  fine=(day-15)*1;
						  std::cout<<"\n\n Fine = "<<fine;
					  }
					  st.resettoken();
					 
					  int pos=-1*sizeof(st);
					  fp.seekg(pos,std::ios::cur);
					  fp.write((char*)&st,sizeof(student));
					  std::cout<<"\n\n\tBook Deposited Successfully";
					  
					
			  }
		 }
		 if(flag==0)
		 {
			 std::cout<<"Book No. Does Not Exists";
		 }
		 
	 } 
	 
	 else
	 {
		 
		 std::cout<<"No Book Issued";
		 
	 }
	 
		 
 
	 }
 
 }
 if(found==0)
 {
	 std::cout<<"Student Record Not Exists...";
	 
 }
 getch();
 fp.close();
 fp1.close();
 }
 
 void gotoxy(short x, short y) {
COORD pos = {x, y};
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void start()
{ //clrscr();
gotoxy(35,11);
std::cout<<"LIBRARY";
gotoxy(35,14);
std::cout<<"MANAGEMENT";
gotoxy(35,17);
std::cout<<"SYSTEM";
std::cout<<" \n  by: Gangothri"; 
getch();
}
void adminmenu()
{
	//clrscr();
	int ch2;
	std::cout<<"\n\n\n\tADMINISTRATOR MENU";
	std::cout<<"\n\n\n\t1.CREATE STUDENT RECORD";
	std::cout<<"\n\n\n\t2.DISPLAY ALL STUDENT RECORD";
	std::cout<<"\n\n\n\t3.DISPLAY SPECIFIC STUDENT RECORD";
	std::cout<<"\n\n\n\t4.MODIFY STUDENT RECORD";
	std::cout<<"\n\n\n\t5.DELETE STUDENT RECORD";
	std::cout<<"\n\n\n\t6.CREATE BOOK";
	std::cout<<"\n\n\n\t7.CREATE ALL BOOKS";
	std::cout<<"\n\n\n\t8.DISPLAY SPECIFIC BOOK";
	std::cout<<"\n\n\n\t9.MODIFY BOOK RECORD";
	std::cout<<"\n\n\n\t10.DELETE BOOK RECORD";
	std::cout<<"\n\n\n\t11.BACK TO MAIN MENU";
	std::cout<<"\n\n\n\tPLEASE ENTER YOUR CHOICE(1-11)";
	std::cin>>ch2;
	switch(ch2)
	{
		case 1: writestudent();
		break;
		case 2: displayalls();
		break;
		case 3: char num[6];
		//clrscr();
		std::cout<<"\n\n\t Please enter admission no.";
		std::cin>>num;
		displaysps(num);
		break;
		case 4: modifystudent();
		break;
		case 5:deletestudent();
		break;
		case 6:writebook();
		break;
		case 7:displayallb();
		break;
		case 8:
	    {char num[6];
		//clrscr();
		std::cout<<"\n\n\tPlease enter book no.";
		std::cin>>num;
		displayspb(num);
		break;
		}
		case 9:modifybook();
		break;
		case 10:deletebook();
		break;
		case 11:
		return;
		default:
		std::cout<<"Invalid choice"; 
	}
	adminmenu();
} 
int main()

{ 
char ch;
//clrscr();
start();
do{
	//clrscr();
	std::cout<<"\n\n\n\t MAIN MENU";
	std::cout<<"\n\n\n\t1 BOOK ISSUE";
	std::cout<<"\n\n\n\t2 BOOK DEPOSIT";
	std::cout<<"\n\n\n\t3 ADMINISTRATOR MENU"; 
	std::cout<<"\n\n\n\t4 EXIT";
	std::cout<<"\n\n\n\t PLEASE SELECT YOUR OPTION(1-4)";  
	ch=getche();
	switch(ch)
	{ case '1': bookissue(); 
	  break;
	  case '2': bookdeposit();
	  break;
	  case '3': 
	  adminmenu();
	  break;
	  case '4': 
	  exit(0); 
	  break;
	  default:
	  std::cout<<"INVALID CHOICE"; 
	  
	}         
}while(ch!=4 ); 
return 0;

}

