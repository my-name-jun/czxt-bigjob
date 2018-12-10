#include<iostream>
#include<cstring>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>
#include<stdlib.h>
#include<fcntl.h>
#include<time.h>
#include<queue>
#include<ftw.h>
#include<unistd.h>
#include<string.h>

#define RESET "\033[0m"
#define BLACK "\033[30m" /* Black */
#define RED "\033[31m" /* Red */
#define GREEN "\033[32m" /* Green */
#define YELLOW "\033[33m" /* Yellow */
#define BLUE "\033[34m" /* Blue */
#define MAGENTA "\033[35m" /* Magenta */
#define CYAN "\033[36m" /* Cyan */
#define WHITE "\033[37m" /* White */
#define BOLDBLACK "\033[1m\033[30m" /* Bold Black */
#define BOLDRED "\033[1m\033[31m" /* Bold Red */
#define BOLDGREEN "\033[1m\033[32m" /* Bold Green */
#define BOLDYELLOW "\033[1m\033[33m" /* Bold Yellow */
#define BOLDBLUE "\033[1m\033[34m" /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m" /* Bold Magenta */
#define BOLDCYAN "\033[1m\033[36m" /* Bold Cyan */
#define BOLDWHITE "\033[1m\033[37m" /* Bold White */

using namespace std;

void mypwd();    //show current absolute path
void mylist();   //show listectory and file
void mycd();//change listectory
void mymkdir();//make new listectory
void myrmdir(); //delete listectory
void myrename(); //rename the listectory's name
void mycopy();   //copy the file
void myfind();   //find the assign file in the assign listectory
void ls();   //show listectory and file
string pwd();  //show current absolute path
void clear();  //clear system
int fn(const char *file, const struct stat *sb, int flag);


int main(int argc, char *argv[])
{
   cout<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<endl;
   cout<<"The product has the following functions"<<endl;
   cout<<"1. mypwd "<<endl;
   cout<<"2. mylist <absolutely listname>"<<endl;
   cout<<"3. mycd <listname or path> "<<endl;
   cout<<"4. mymkdir <listname> "<<endl;
   cout<<"5. myrmdir <listname> "<<endl;
   cout<<"8. myexit "<<endl;
   cout<<"6. myrename <old filename> <new filename> "<<endl;
   cout<<"7. mycopy <filename>"<<endl;
   cout<<"9. myfind <listname> "<<endl;
   cout<<"10. ls"<<endl;
   cout<<"11. clear"<<endl;
   cout<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<endl;

   string str;
   while(str != "myexit") {

      string str1 = pwd();
      int len = str1.length();
      str1 = str1.substr(9,len);
      cout<< GREEN <<"gjh@gjh-VirtualBox:~"<<BLUE<<str1<<WHITE<<"$  ";
      cin>>str;
      if(str == "mypwd"){
         mypwd();
      }
      if(str == "mylist"){
        mylist();
      }
      if(str == "mycd"){
         mycd();
      }
      if(str == "mymkdir"){
         mymkdir();
      }
      if(str == "myrmdir"){
         myrmdir();
      }
      if(str == "myrename"){
         myrename();
      }
      if(str == "mycopy"){
         mycopy();
      }
      if(str == "myfind"){
        myfind();
      }
      if(str == "ls"){
        ls();
      }
      if(str == "clear"){
        clear();
      }

    }
    return 0;
}

//显示当前所在目录的路径名
void mypwd()
{
   char ptr[100];
   getcwd(ptr,sizeof(ptr));
   cout<<ptr<<endl;
}

void mylist()
{
  DIR * list;
  struct dirent* ptr;
  int count = 0;
  char *listname;
  char ptr1[100];
  char ptr2[100];
  cin>>ptr2;
  getcwd(ptr1,sizeof(ptr1));
  listname = ptr2;
  list = opendir(listname);
  if(list == NULL)
  {
     cout<<"cannot open listectory"<<endl;
  }
  while((ptr = readdir(list)) != NULL)
  {
      if(strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0){}
      else
          {
             string a = to_string(ptr->d_ino); 
          if(a[0] == '1'||a[0] == '2'||a[0] == '3'||a[0] == '4')
            {
               cout<<GREEN;
            }
          else{cout<<WHITE;}
          cout<<ptr->d_name<<" ";
          }
      count++;
      if(count % 8 == 0)
         cout<<endl;

   }
   closedir(list);
   cout<<endl;
}

void mycd()
{
   char listname[20];
   cin>>listname;
   if(chdir(listname) == -1)
   {
      cout<<"the listectory is not exit!!!"<<endl;

    }
    else
    {
      char ptr[100];
      getcwd(ptr,sizeof(ptr));
     }
}

void mymkdir()
{
  char filename[20];
  cin >> filename;
  if(mkdir(filename, 0777) == 0)
  {
     cout<<filename<<" indecates successful!!!"<<endl;
   }
   else
   {  cout<<filename<<" indecates failure!!!"<<endl;
   }
}

void myrmdir()
{
   char filename[20];
   cin >> filename;
   if(rmdir(filename) == 0)
   {
    cout<<filename<<" delete successful!!!"<<endl;
   }
   else
       cout<<" not found!!!"<<filename<<endl;
}

void myrename()
{
  char filename1[20], filename2[20];
  cin>>filename1>>filename2;
  if(rename(filename1, filename2) == 0)
  {
    cout<<filename1<< " success  change to "<<filename2<<endl;
   }
   else
     cout<< " not found !!!"<<filename1<<endl;

}
 
  
void mycopy()  
{  
    char filename1[20],filename2[20],file1[100],file2[100];
    cin>>filename1>>filename2;
    getcwd(file1,sizeof(file1));
    getcwd(file2,sizeof(file2));
    strcat(file1,filename1);
    strcat(file2,filename2);
//cout<<file1<<endl;
//cout<<file2<<endl;
    FILE *fp1;  
    fp1 = fopen(file1, "r");  
    FILE *fp2;  
    fp2 = fopen(file2, "w");  
  
    char buff[200] = {'\0'};  
    while(fgets(buff, sizeof(buff), fp1) != NULL)  
    {  
    fputs(buff, fp2);  
    }  
  
    fclose(fp1);  
    fclose(fp2);  
   
      
} 

void myfind()
{

   char listname[50];
   cin>>listname;
   ftw(listname, fn,500);
}


int fn(const char *file, const struct stat *sb, int flag)
{
  if(flag == FTW_D)
  {
      string str1 = pwd();
      cout << file <<"   --"<<str1<<"/"<< file <<endl;
  }
    
  else if(flag == FTW_F)
    cout << file <<"-- file"<<endl;
  return 0;
}

string pwd()
{
   char ptr[100];
   getcwd(ptr,sizeof(ptr));
   return ptr;
}

void ls()
{
  DIR * list;
  struct dirent* ptr;
  int count = 0;
  char *listname;
  char ptr1[100];
  getcwd(ptr1,sizeof(ptr1));
  listname = ptr1;
  list = opendir(listname);
  if(list == NULL)
  {
     cout<<"cannot open listectory"<<endl;
  }
  while((ptr = readdir(list)) != NULL)
  {
      if(strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0){}
      else
      {
          string a = to_string(ptr->d_ino); 
          if(a[0] == '1'||a[0] == '2'||a[0] == '3'||a[0] == '4')
            {
               cout<<GREEN;
            }
          else{cout<<WHITE;}
          cout<<ptr->d_name<<" ";
      }
          
      count++;
      if(count % 8 == 0)
         cout<<endl;

   }
   closedir(list);
   cout<<endl;
}

void clear()
{
  system("reset");
}
