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
using namespace std;

void pwd();    //show current absolute path
void mylist();   //show listectory and file
void chandir();//change listectory
void makedir();//make new listectory
void deldir(); //delete listectory
void rename(); //rename the listectory's name
void find();   //find the assign file in the assign listectory
int fn(const char *file, const struct stat *sb, int flag)


int main(int argc, char *argv[])
{

   cout<<"The product has the following functions"<<endl;
   cout<<"1. pwd "<<endl;
   cout<<"2. mylist <listname>"<<endl;
   cout<<"3. mycd <listname or path> "<<endl;
   cout<<"4. mynkdir <listname> "<<endl;
   cout<<"5. myrmdir <listname> "<<endl;
   cout<<"8. myexit "<<endl;
   cout<<"6. myrename <old filename> <new filename> "<<endl;
   cout<<"7. mycopy <filename>"<<endl;
   cout<<"9. myfind <listname> "<<endl;
   cout<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<endl;

   string str;
   while(str != "exit") {
      cout<<"gjh@gjh-";
      cin>>str;
      if(str == "pwd"){
         pwd();
      }
      if(str == "mylist"){
        mylist();
      }
      if(str == "chandir"){
         chandir();
      }
      if(str == "makedir"){
         makedir();
      }
      if(str == "deldir"){
         deldir();
      }
      if(str == "rename"){
         rename();
      }
      if(str == "find"){
        find();
      }

    }
    return 0;
}

//显示当前所在目录的路径名
void pwd()
{
   char pwd_str[100];
   getcwd(ptr_str,sizeof(pwd_str));
   cout<<pwd_str<<endl;
}

void mylist()
{
  DIR * mylist;
  struct dirent* ptr;
  int count = 0;
  char *listname;
  cin>>listname;
  mylist = opendir(listname);
  if(mylist == NULL)
  {
     cout<<"cannot open listectory"<<endl;
  }
  while((ptr = readdir(mylist)) != NULL)
  {
      if(strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0){}
      else
          cout<<ptr->d_name<<" ";
      count++;
      if(count % 8 == 0)
         cout<<endl;

   }
   closedir(mylist);
   cout<<endl;
}

void chandir()
{
   char listname[20];
   cin>>listname;
   if(chdir(listname) == -1)
   {
      cout<<"the listectory is not exit!!!"<<endl;

    }
    else
    {
      cout<<"change listectory success!!!"<<endl;
     }
}

void makedir()
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

void deldir()
{
   char filename[20];
   cin >> filename;
   if(rmdir(filename) == 0)
   {
    cout<<filename<<" delete successful!!!"<<endl;
   }
   else
       cout<<filename<<" delete failure!!!"<<endl;
}

void rename()
{
  char filename1[20], filename2[20];
  cin>>filename1>>filename2;
  if(rename(filename1, filename2) == 0)
  {
    cout<<filename1<< " success  change to "<<filename2<<endl;
   }
   else
     cout<<filename1<< " failure change to "<<filename2<<endl;

}

void find()
{

   char listname[50];
   cin>>listname;
   ftw(listname, fn,500);

}

int fn(const char *file, const struct stat *sb, int flag)
{
  if(flag == FTW_D)
    cout << file <<"-- listectory"<<endl;
  else if(flag == FTW_F)
    cout << file <<"-- file"<<endl;
  return 0;
}
