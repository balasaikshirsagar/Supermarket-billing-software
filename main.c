//***************************************************************
//                   HEADER FILE USED IN PROJECT
//****************************************************************


#include<stdio.h>
#include<process.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<conio.h>
#include<dos.h>
//***************************************************************
//                   STRUCT USED IN PROJECT
//****************************************************************

typedef struct product
{
 int pno,quanavail;
 char name[50];
 float price,qty,tax,dis;

}product;         //struct ends here

typedef struct node
{
    int pr_no;
    int quan;
    struct node* info;

}node;
node *head,*end;


//***************************************************************
//    	global declaration for stream object, object
//****************************************************************

 FILE *fp;
 product pr;
//***************************************************************
//     function to enter product details
//***************************************************************
void create_product()
	{
	 printf("\nPlease Enter The Product No. of The Product ");
	 scanf("%d",&pr.pno);
	 printf("\nPlease Enter The Name of The Product ");
	 fflush(stdin);
	 gets(pr.name);
	 printf("\nPlease Enter The Price of The Product ");
	 fflush(stdin);
	 scanf("%f",&pr.price);
     printf("\nPlease Enter the Quantity available of the product");
     scanf("%d",&pr.quanavail);
	 printf("\nPlease Enter The Discount (%) ");
	 scanf("%f",&pr.dis);
	 }
//**************************************************************
//    function to show details......
//**************************************************************
void show_product()
	{
	 printf("\nThe Product No. of The Product :%d ",pr.pno);
	 printf("\nThe Name of The Product : ");
	 puts(pr.name);
     printf("\nThe Quantity remaining of the Product: %d",pr.quanavail);
	 printf("\nThe Price of The Product : %.2f",pr.price);
	 printf("\nDiscount :(%c) %.2f",37,pr.dis);
	 }
void refill_quan()
{
int n;
printf("Please enter the new stock quantity\n");
scanf("%d",&n);
pr.quanavail=pr.quanavail+n;
printf("Product has been refilled\n");
}
void cutof_quan(int no)
{

pr.quanavail=pr.quanavail-no;
}
//***************************************************************
//    	function to move pointer to desire point on screen....
//****************************************************************
void gotoxy(int x, int y)
 {
    printf("%c[%d;%df", 0x1B, y, x);
}
//***************************************************************
//      function to write in a file.............................
//***************************************************************
void write_product()
{
    fp=fopen("Shop.dat","ab+");
    create_product();
    fseek(fp,0,SEEK_END);
    fwrite(&pr,sizeof(product),1,fp);
    fclose(fp);
    printf("\n\nThe Product Has Been Created ");
    _getch();
}
//************************************************
// function for inaputing password
//*************************************************
char* input_password()
{
char *a;
free(a);
a=(char*)malloc(20*sizeof(char));
for(int i=0;i<=20;i++)
{
    gotoxy((82+i),23);
*(a+i)=_getch();
if(!isalnum(*(a+i)))
{
*(a+i)='\0';
break;
}
printf("*");
}
return(a);
}

// ***********************************************
//function creating password file
//*************************************************
void createpass()
{
char a[]="admingo\0";
FILE *fout;
fout=fopen("adminpass.txt","w");

fprintf(fout,"%s",a);
fclose(fout);
//printf("opened...");
//_getch();
}
///**************************************************************
//Function to give access to admin
//****************************************************************

int adminpass()
{
    system("cls");
    gotoxy(90,10);
    system("color  D0");
    printf("*    *      *ADMIN PANEL*      *       *\n");
    FILE *fin;
    fin=fopen("adminpass.txt","r");
    char *a,b[20],ch;
    fscanf(fin,"%s",&b);
    do
    { gotoxy(80,20);
        printf("ENTER PASSWORD:-\n");
        a=input_password();
        if(strcmpi(a,b)==0)
        {gotoxy(80,30);
        printf("\nACCESS GRANTED");
        return(1);
        }
        else
        {
            gotoxy(80,30);
        printf("Wrong password\n");
        gotoxy(80,31);
        printf("wanna try again?(y/n)\n");
        fflush(stdin);
        ch=getche();
        }

    }while(ch=='y'||ch=='Y');
fclose(fin);
   return 0;
}
//***********************************************************
//       Function to change password for admin panel
//***********************************************************
void changepass()
{
system("cls");
char *a,ch,b[20];
FILE *fin=fopen("adminpass.txt","r+");

fscanf(fin,"%s",&b);
fclose(fin);
fin=fopen("adminpass.txt","w");
do
{
    system("cls");
gotoxy(90,15);
    printf("ENTER CURRENT PASSWORD\n");
a=input_password();
if(strcmpi(a,b)==0)
{
    system("cls");
    gotoxy(90,15);

printf("\nENTER NEW PASSWORD\n");
a=input_password();
rewind(fin);
//puts(a);
//_getch();
fprintf(fin,"%s",a);
fclose(fin);
fin=fopen("adminpass.txt","r");

fscanf(fin,"%s",&b);
//puts(b);
//_getch();
fclose(fin);
break;
}
else
{
    gotoxy(90,15);

printf(" WRONG PASSWORD\n");
gotoxy(90,17);

printf(" wanna try again?(y/n)\n");
fflush(stdin);
ch=getche();
system("cls");
}
}while(ch=='y'||ch=='Y');
fclose(fin);
}


//***************************************************************
//    	function to read all records from file
//****************************************************************


void display_all()
{
    system("cls");
    printf("\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n");
    fp=fopen("Shop.dat","rb");
    while(fread(&pr,sizeof(product),1,fp)==1)
	{
	 show_product();
	 printf("\n\n====================================\n");
	 _getch();
	 }
    fclose(fp);
    _getch();
}


//***************************************************************
//    	function to read specific record from file
//****************************************************************


void display_sp(int n)
{
    int flag=0;
    fp=fopen("Shop.dat","rb");
    while(fread(&pr,sizeof(product),1,fp)==1)
	{
	 if(pr.pno==n)
		{
		 system("cls");
		 show_product();
		 flag=1;
		}
	}
    fclose(fp);
if(flag==0)
 printf("\n\nrecord not exist");
    _getch();
}


//***************************************************************
//    	function to modify record of file
//****************************************************************


void modify_product()
{
    int no,found=0;
    system("cls");
    printf("\n\n\tTo Modify ");
    printf("\n\n\tPlease Enter The Product No. of The Product");
    scanf("%d",&no);
    fp=fopen("Shop.dat","rb+");
    while(fread(&pr,sizeof(product),1,fp) && found==0)
	   {
	    if(pr.pno==no)
		   {
		    show_product();
		    printf("\nPlease Enter The New Details of Product\n");
		    create_product();
		    int pos=-1*sizeof(pr);
		    fseek(fp,pos,SEEK_CUR);
		    fwrite(&pr,sizeof(product),1,fp);
		    printf("\n\n\t Record Updated");
		    found=1;
		   }
	     }
    fclose(fp);
    if(found==0)
    printf("\n\n Record Not Found ");
    _getch();
}
//***************************************************************
//    	function to refill an product
//****************************************************************


void refill_product()
{
    int no,found=0;
    system("cls");
    printf("\n\n\tTo Modify ");
    printf("\n\n\tPlease Enter The Product No. of The Product");
    scanf("%d",&no);
    fp=fopen("Shop.dat","rb+");
    while(fread(&pr,sizeof(product),1,fp) && found==0)
	   {
	    if(pr.pno==no)
		   {

		    show_product();

		    refill_quan();
		    int pos=-1*sizeof(pr);
		    fseek(fp,pos,SEEK_CUR);
		    fwrite(&pr,sizeof(product),1,fp);
		    printf("\n\n\t Quantity Updated");
		    found=1;
		   }
	     }
    fclose(fp);
    if(found==0)
    printf("\n\n Record Not Found ");
    _getch();
}


//***************************************************************
//    	function to delete record of file
//****************************************************************


void delete_product()
   {
    int no;
    system("cls");
    printf("\n\n\n\tDelete Record");
    printf("\n\nPlease Enter The product no. of The Product You Want To Delete");
    scanf("%d",&no);
    fp=fopen("Shop.dat","rb+");
    FILE *fp2;
    fp2=fopen("Temp.dat","wb");
    fseek(fp,0,SEEK_SET);
    while(fread(&pr,sizeof(product),1,fp)==1)
	{
	 if(pr.pno!=no)
		{
        fwrite(&pr,sizeof(product),1,fp2);
		 }
	 }
    fclose(fp2);
    fclose(fp);
    remove("Shop.dat");
    rename("Temp.dat","Shop.dat");
    printf("\n\n\tRecord Deleted ..");
    _getch();
    }

//***************************************************************
//    	function to match asked Quantity with available Quantity...
//****************************************************************


int match_quan(int prodno,int askquan)
{
    int no,found=0;
    system("cls");
    fp=fopen("Shop.dat","rb+");
    while(fread(&pr,sizeof(product),1,fp) && found==0)
    {
         if(pr.pno==prodno)
		   {
            no= pr.quanavail;
		    if(askquan<=no)
            {
             printf("\n Order Booked");

		     cutof_quan(askquan);
	         return 0;
            }
            else
            {
             printf("\n Sorry!that much Quantity is not available\n");
             return(-1);
            }
		    int pos=-1*sizeof(pr);
		    fseek(fp,pos,SEEK_CUR);
		    fwrite(&pr,sizeof(product),1,fp);
           }
    }
    fclose(fp);

}

//***************************************************************
//    	function to display all products price list
//****************************************************************

    void menu()
    {
     system("cls");
     system("color A0");
     fp=fopen("Shop.dat","rb");
     if(fp==NULL)
     {
       printf("ERROR!!! FILE COULD NOT BE OPEN\n\n\n Go To Admin Menu to create File");
       printf("\n\n\n Program is closing ....");
       _getch();
       exit(0);
     }

     printf("\n\n\t\tProduct MENU\n\n");
	  printf("====================================================\n");
	  printf("P.NO.\t\tNAME\t\tPRICE\n");
	  printf("====================================================\n");

      while(fread(&pr,sizeof(product),1,fp)==1)
	 {
	   printf("%d\t\t%s\t\t%.2f\n",pr.pno,pr.name,pr.price);
	}
	_getch();
     fclose(fp);
}

void insertion(int pr_no,int quan)
{
    node *temp=(node*)malloc(sizeof(node));
    temp->pr_no=pr_no;
    temp->quan=quan;
    temp->info=NULL;
    if(head==NULL)
    {
        head=end=temp;
    }
    else{
        end->info=temp;
    end=end->info;
    }
}

void deletion(int *pr_no , int *quan)
{
    int n;
    node *temp;
        temp=head;
        head=head->info;
        *pr_no=temp->pr_no;
        *quan=temp->quan;

        free(temp);

}

//***************************************************************
//    	function to place order and generating bill for Products
//****************************************************************

   void place_order()
   {
    int  pr_no,quan;
    int c=0;
    float amt=0,damt=0;
    int total=0;
    char ch='Y';

    do{
            menu();
    printf("\n\t\t\t\t============================");
    printf("\n\t\t\t\t    PLACE YOUR ORDER");
    printf("\n\t\t\t\t============================\n");
	 printf("\n\nEnter The Product No. Of The Product: ");
	 scanf("%d",&pr_no);
	 printf("\nQuantity in number : ");
	 scanf("%d",&quan);
	 insertion(pr_no,quan);
     int check= match_quan(pr_no,quan);
     if(check==-1)
     {
     c--;
     }
	 c++;
	 printf("\nDo You Want To Order Another Product ? (y/n)");
	 fflush(stdin);
	 ch=_getch();
    }while(ch=='y' ||ch=='Y');
    printf("\n\nThank You For Placing The Order");
    _getch();
    system("cls");
      printf("\n\n********************************INVOICE************************\n");
      printf("\nPr No.\tPr Name\tQuantity \tPrice \t\tAmount \t\tAmount after discount\n");
      for(int x=0;x<c;x++)
	  {
         deletion(&pr_no,&quan);
		 fp=fopen("Shop.dat","rb");
		  while(fread(&pr,sizeof(product),1,fp)==1)
			{
			  if(pr.pno==pr_no)
				{
				 amt=(pr.price)*quan;
				 damt=(amt-(amt*pr.dis/100));
 int    np=damt;
				 printf("\n%d\t%s\t%d\t\t%3.2f\t%12.2f\t\t%3.2f",pr_no,pr.name,quan,pr.price,amt,np);
				 total+=np;


				}

			}

		 fclose(fp);

	 }
       printf("\n\n\t\t\t\t\tTOTAL = %  d",total);
       gotoxy(70,50);
       printf("-   -    -HAVE        A       NICE     DAY!!!!.....-     -      -");
    _getch();
    }

//***************************************************************
//    	INTRODUCTION FUNCTION
//****************************************************************

void _delay()
{
    gotoxy(90,15);
 int i=0;
 for(i=0;i<3;i++)
 {system("cls");
     gotoxy(90,15);

 printf("LOADING");
 delay(30);
 system("cls");
     gotoxy(90,15);

 printf("LOADING .");
  delay(30);

 system("cls");
     gotoxy(90,15);

 printf("LOADING .   .");
  delay(30);

 system("cls");
     gotoxy(90,15);

 printf("LOADING .    .      .");
  delay(30);

 }
 system("cls");
     gotoxy(90,15);

 printf("ALL SET!!!.....READY TO GO....!!!!.....") ;

}
void intro()
{
    _getch();
 system("cls");
_delay();
 _getch();
 system("cls");
 system("color A1");
gotoxy(90,20);
 printf("******************************************");
gotoxy(90,21);

 printf("**                                      **");
 gotoxy(90,22);

 printf("**                                      **");
 gotoxy(90,23);

 printf("**           SUPER MARKET BILLING       **");
 gotoxy(90,24);

 printf("**                SOFTWARE              **");
 gotoxy(90,25);

 printf("**                                      **");
 gotoxy(90,26);

 printf("******************************************");
 gotoxy(88,35);


 printf("                  PROJECT                 ");
 gotoxy(5,220);
 printf("*********************************************************");
 printf("\nMADE BY : SANYAM JAIN, NAVNEET KHANDELWAAL,AYUSH JHA");
 printf("\n\tJAYPEE INSTITUTE OF INFORMATION TECHOLOGY");
 _getch();

}




//***************************************************************
//    	ADMINSTRATOR MENU FUNCTION
//****************************************************************
int admin_menu()
{
  system("cls");
  int num;
  char ch2;
  gotoxy(90,20);

  printf("*      *       *ADMIN PANEL*       *        *");
  int n= adminpass();
  if (n==0)
  return 0;
  begin : system("cls");
  system("color E4");
    gotoxy(90,5);
  printf("*      *       *ADMIN MENU*      *     ");
      gotoxy(90,10);

  printf("1.CREATE PRODUCT");
      gotoxy(90,14);

  printf("2.DISPLAY ALL PRODUCTS");
      gotoxy(90,18);

  printf("3.QUERY ");
      gotoxy(90,22);

  printf("4.MODIFY PRODUCT");
      gotoxy(90,26);

  printf("5.DELETE PRODUCT");
      gotoxy(90,30);

  printf("6.VIEW PRODUCT MENU");
      gotoxy(90,34);

  printf("7.CHANGE PASSWORD");
      gotoxy(90,38);

  printf("8.REFILL AN PRODUCT");
      gotoxy(90,42);

  printf("9.BACK TO MAIN MENU");
      gotoxy(90,44);


  printf("Please Enter Your Choice (1-9) ");
      gotoxy(90,48);

  ch2=getche();
  switch(ch2)
  {
    case '1': system("cls");
	          write_product();
              goto begin;

	         break;
    case '2': display_all();
              goto begin;

              break;
    case '3':
	       //int num;
	       system("cls");
	       printf("\n\n\tPlease Enter The Product No. ");
	       scanf("%d",&num);
	       display_sp(num);
           goto begin;

	       break;
      case '4': modify_product();
                goto begin;

                break;
      case '5': delete_product();
                goto begin;

                break;
      case '6': menu();
                goto begin;

                _getch();
      case '7': changepass();
                goto begin;
                break;
      case '8': refill_product();
                goto begin;

      case '9': break;

      default:admin_menu();
   }
}


//***************************************************************
//    	THE MAIN FUNCTION OF PROGRAM
//****************************************************************


int main()
{
  char ch;
  int n;
  intro();
  system("color E1");
        createpass();

  do
    {
	  system("cls");
       int n;
      begin: system("color E1");
       gotoxy(90,20);
	  printf("\n\n\n\t                                                                                      *   *   * MAIN MENU *   *   *" );
	  printf("\n\n\t                                                                                         01. CUSTOMER");
	  printf("\n\n\t                                                                                         02. ADMINISTRATOR");
	  printf("\n\n\t                                                                                         03. EXIT");
	  printf("\n\n\tPlease Select Your Option (1-3) ");
	  ch=getche();
	  switch(ch)
	  {
		 case '1': system("cls");
			   place_order();
			   _getch();
			   break;
		  case '2':n= admin_menu();
			    break;
		  case '3':exit(0);
		  default :printf("\a");
	  }
    }while(ch!='3');
if(n==0)
{
    system("cls");
goto begin;
}
}

//***************************************************************
//    			END OF PROJECT
//****************************************************************
