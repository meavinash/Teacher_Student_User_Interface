#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define teachcode 1337
void welscr();
void newid();
void login();
void adminmenu();
void teachmenu();
void teachdispdet();
void entmarks(char sub[4],int sem);
int studteachrel(char id[4],char sub[4],int sem);
void entattend(char sub[4],int sem);
void dispfeedback();
void studmenu();
void studispdet();
void dispmarks();
void getmaxminmarks(char subj[4],int *maxmarks,int *minmarks);
void checattend();
int getsubid(char sub[4],char uid[16]);
char *getsub(int index, char uid[16]);
void givefeedback(char crsid[4],int sem);
void check();
void sublist();
void subadd();
void subdelete();
void subsearch();
void classlist();
void clsadd();
void clsdelete();
void clssearch();
void teachmap();
void teachassign(char id[16]);
void teachunassign(char id[16]);
void teachcheck(char id[16]);
void studmap();
void studassign(char id[16]);
void studunassign(char id[16]);
void studcheck(char id[16]);
void genid(char name[20],char dob[20],char role,char finid[16]);
struct person
{
    char id[16],name[20],dob[15],sex,role,password[20];
};
struct person loginuser;
struct teacher
{
    char id[16],sub[4];
    int sem;
};
struct student
{
    char id[16],crsid[4];
    int sem;
};
struct marks
{
    char id[16],sub[4];
    int markobt;
};
struct attendance
{
    char id[16],sub[4],date[20];
    char state;
};
struct feedback
{
    char studid[16],teachid[16],fb[200];
};
struct subject
{
    char id[4],name[20];
    int maxmarks,minmarks;
};
struct clas
{
    char id[4],name[20];
    int sem;
    char sub[6][4];
};
int main()
{
    do
    {
   	 welscr();
    }while(1);
    return 0;
}
void welscr()
{
    int welopt;
    system("clear");
    printf("Welcome to TSUI (Teacher Student User Interface)\n");
    printf("1.Login\n2.Register\n3.Exit\nchoice:");
    scanf("%d",&welopt);
    switch (welopt)
    {
   	 case 1:    login();
   		 break;
   	 case 2: newid();
   		 break;
   	 case 3: exit(0);
   		 break;
   	 default: printf("Invalid input,retry\n");
   		  //getch();
   		  return;
 
    }
}
void login()
{
    char temppassword[20];
    system("clear");
    memset(&loginuser,0,sizeof(struct person));
    printf("Enter id: ");
    scanf("%s",loginuser.id);
    check();
    if(loginuser.password[0]=='\0')
    {
   	 printf("Invalid userid");
      	 return;
    }
    printf("Enter password: ");
    scanf("%s",temppassword);
    if(strcmp(temppassword,loginuser.password)!=0)
    {
   	 printf("Wrong password, retry");
   	 return;
    }
    if(loginuser.role=='t')
    {
   	 teachmenu();
    }
    else if(loginuser.role=='s')
    {
   	 studmenu();
    }
    else if(loginuser.role=='a')
    {
   	 adminmenu();
    }
}
void newid()
{
    struct person ind;
    FILE *fp;
    int i,code;
    system("clear");
    printf("Enter your details :");
    printf("\nName: ");
    scanf("%s",ind.name);
    printf("Date of birth(dd/mm/yyyy): ");
    scanf("%s",ind.dob);
    getchar();
    printf("Sex : ");
    scanf("%c",&ind.sex);
retry:
    getchar();
    printf("\nTeacher or Student (T/S): ");
    scanf("%c",&ind.role);
    switch(ind.role)
    {
       	case 't': printf("Enter Teacher code given by the prinicipal: ");
   		  scanf("%d",&code);
   		  if(code != teachcode)
   		  {
   			 printf("Wrong teacher code,retry");
   			 goto retry;
   		  }
   		  break;
       	case 's': break;
       	default : printf("Invalid input, retry");
   		  goto retry;
    }
    genid(ind.name,ind.dob,ind.role,ind.id);
    printf("Your new id: %s",ind.id);
    printf("\nEnter password: ");
    scanf("%s",ind.password);
    fp=fopen("indi","a");
    if(!fp)
    {
   	 printf("Error!!");
   	 return;
    }
    fwrite(&ind,sizeof(struct person),1,fp);
    fclose(fp);
    return;
}
void genid(char name[],char dob[],char role, char finid[15])
{
    int i,remsl=0;
    if(role == 't'|| role == 'T')
    {
   	 finid[0]='t';
   	 finid[1]='e';
    }
    else
    {
       	finid[0]='s';
       	finid[1]='t';
    }
    for(i=2;i<=15;i++)
    {
   	 if(i<5)
   	 {
   		 if(name[i-2]=='\0')
   		 {
   			 finid[i]='~';
   			 continue;
   		 }
   		 finid[i]=name[i-2];
   	 }
   	 else
   	 {
   		 if(dob[i-5]=='\0')
   		 {
   			 break;
   		 }
   		 if(dob[i-5+remsl]=='/')
   		 {
   			 remsl++;
   		 }
   		 finid[i]=dob[i-5+remsl];
   	 }
    }
    finid[i]='\0';
}
void check()
{
    FILE *fp;
    if(strcmp(loginuser.id,"admin")==0)
    {
   	 strcpy(loginuser.password,"admin");
   	 loginuser.role='a';
   	 strcpy(loginuser.name,"admin");
    }
    else
    {
   	 struct person ind;
   	 fp=fopen("indi","r");
   	 if(!fp)
   	 {
   		 printf("Error!!");
   		 return;
   	 }
   	 loginuser.password[0]='\0';
   	 while(!feof(fp))
   	 {
   		 fread(&ind,sizeof(struct person),1,fp);
   		 if(strcmp(loginuser.id,ind.id)==0)
   		 {
   			 memcpy(&loginuser,&ind,sizeof(struct person));
   			 break;
   		 }
   	 }
   	 fclose(fp);
    }
}
void adminmenu()
{
    int i,opt;
    system("clear");
    do{
   	 printf("\t\tAdmin Menu\n");
   	 printf("1.Subject list\n2.Class list\n3.Assign Teacher to class\n4.Assign student to class\n5.Exit\nchoice:");
   	 scanf("%d",&opt);
   	 switch(opt)
   	 {
   		 case 1: sublist();
   			 break;
   		 case 2: classlist();
   			 break;
   		 case 3:    teachmap();
   			 break;
   		 case 4: studmap();
   			 break;
   		 case 5: return;
   		 default: printf("\ninvalid option");
   			  break;
   	 }
    }while(opt<=5&&opt>0);
}
void sublist()
{
    int opt;
    char id[4];
    system("clear");
    do{
   	 printf("1.Add subjects\n2.Delete subjects\n3.Subject search\n4.Exit\nchoice:");
   	 scanf("%d",&opt);
   	 switch(opt)
   	 {
   		 case 1:    subadd();
   			 break;
   		 case 2:    subdelete();
   			 break;
   		 case 3:    subsearch();
   			 break;
   		 case 4: return;
   		 default: printf("\ninvalid option");
   			  break;
   	 }
    }while(opt<=4&&opt>0);
}
void subadd()
{
    FILE *fp;
    struct subject subj;
    printf("Enter subject id to add: ");
    scanf("%s",subj.id);
    fp=fopen("sublis","a");
    if(!fp)
    {
   	 printf("Error!!");
   	 return;
    }
    printf("Enter subject name: ");
    scanf("%s",subj.name);
    getchar();
    printf("Enter maxmarks: ");
    scanf("%d",&subj.maxmarks);
    printf("Enter minmarks: ");
    scanf("%d",&subj.minmarks);
    fwrite(&subj,sizeof(struct subject),1,fp);
    fclose(fp);
}
void subdelete()
{
    FILE *fp;
    FILE *fp_temp;
    int found=0;
    char id[4];
    struct subject subj;
    printf("Enter subject id to delete: ");
    scanf("%s",id);
    fp=fopen("sublis","r");
    if(!fp)
    {
   	 printf("Error!!");
   	 return;
    }
    fp_temp=fopen("temp","a");
    if(!fp_temp)
    {
   	 printf("Error!!");
   	 return;
    }
    while(!feof(fp))
    {
   	 fread(&subj,sizeof(struct subject),1,fp);
   	 if(strcmp(id,subj.id)==0)
   	 {
   		 printf("Record deleted");
   		 found=1;
   	 }
   	 else
   	 {
   		 fwrite(&subj,sizeof(struct subject),1,fp_temp);
   	 }
    }
    if(!found)
    {
   	 printf("Record not found");
    }
    fclose(fp);
    fclose(fp_temp);
    remove("sublis");
    rename("temp","sublis");
}
void subsearch()
{
    FILE *fp;
    int found=0;
    char id[4];
    struct subject subj;
    printf("Enter subject id to search: ");
    scanf("%s",id);
    fp=fopen("sublis","r");
    if(!fp)
    {
   	 printf("Error!!");
   	 return;
    }
    while(!feof(fp))
    {
   	 fread(&subj,sizeof(struct subject),1,fp);
   	 if(strcmp(id,subj.id)==0)
   	 {
   		 system("clear");
   		 printf("Record found\n");
   		 printf("Name: %s\n",subj.name);
   		 printf("Max marks: %d\n",subj.maxmarks);
   		 printf("Min marks: %d\n",subj.minmarks);
   		 found=1;
   		 break;
   	 }
    }
    fclose(fp);
    if(!found)
    {
   	 printf("Record not found");
   	 return;
    }
}
void classlist()
{
    int opt;
    char id[4];
    system("clear");
    do{
   	 printf("1.Enter course\n2.Delete course\n3.Course search\n4.Exit\nchoice:");
   	 scanf("%d",&opt);
   	 switch(opt)
   	 {
   		 case 1:    clsadd();
   			 break;
   		 case 2: clsdelete();
   			 break;
   		 case 3: clssearch();
   			 break;
   		 case 4: return;
   		 default: printf("\ninvalid option");
   			  //getch();
   			  break;
   	 }
    }while(opt<=4&&opt>0);
    //getch();
}
void clsadd()
{
    FILE *fp;
    int i;
    struct clas cls;
    printf("Enter course id to add: ");
    scanf("%s",cls.id);
    fp=fopen("clslis","a");
    if(!fp)
    {
   	 printf("Error!!");
   	 return;
    }
    printf("Enter course name: ");
    scanf("%s",cls.name);
    getchar();
    printf("Enter semester: ");
    scanf("%d",&cls.sem);
    printf("Enter 6 subjects for this class:\n");
    for(i=0;i<6;i++)
    {
   	 printf("sub%d.",i+1);
   	 scanf("%s",cls.sub[i]);
    }
    fwrite(&cls,sizeof(struct clas),1,fp);
    fclose(fp);
}
void clsdelete()
{
    FILE *fp;
    FILE *fp_temp;
    int sem;
    char id[4];
    int found=0;
    struct clas cls;
    printf("Enter course id to delete: ");
    scanf("%s",id);
    printf("Enter semester: ");
    scanf("%d",&sem);
    fp=fopen("clslis","r");
    if(!fp)
    {
   	 printf("Error!!");
   	 return;
    }
    fp_temp=fopen("temp","a");
    if(!fp_temp)
    {
   	 printf("Error!!");
   	 return;
    }
    while(!feof(fp))
    {
   	 fread(&cls,sizeof(struct clas),1,fp);
   	 if((strcmp(id,cls.id)==0)&&(sem==cls.sem))
   	 {
   		 printf("Record deleted");
   		 found=1;
   	 }
   	 else
   	 {
   		 fwrite(&cls,sizeof(struct clas),1,fp_temp);
   	 }
    }
    if(!found)
    {
   	 printf("Record not found");
    }
    fclose(fp);
    fclose(fp_temp);
    //getch();
    remove("clslis");
    rename("temp","clslis");
}
void clssearch()
{
    int found=0,sem;
    char id[4];
    FILE *fp;
    struct clas cls;
    int i;
    printf("Enter course id to search: ");
    scanf("%s",id);
    printf("Enter semester: ");
    scanf("%d",&sem);
    fp=fopen("clslis","r");
    if(!fp)
    {
   	 printf("Error!!");
   	 return;
    }
    while(!feof(fp))
    {
   	 fread(&cls,sizeof(struct clas),1,fp);
   	 if((strcmp(id,cls.id)==0)&&(sem==cls.sem))
   	 {
   		 system("clear");
   		 printf("Record found\n");
   		 printf("Name: %s\n",cls.name);
   		 printf("Semester: %d\n",cls.sem);
   		 printf("Enter 6 subjects for this class:\n ");
   		 for(i=0;i<6;i++)
   		 {
   			 printf("sub%d.%s\n",i+1,cls.sub[i]);
   		 }
   		 found=1;
   		 break;
   	 }
    }
    fclose(fp);
    if(!found)
    {
   	 printf("Record not found");
    }
    //getch();
}
void studmap()
{
    int opt=0;
    char id[16];
    system("clear");
    do{
   	 printf("1.Assign\n2.Unassign\n3.check\n4.Exit\nchoice:");
   	 scanf("%d",&opt);
   	 switch(opt)
   	 {
   		 case 1: printf("Enter student id: ");
   			 scanf("%s",id);
   			 studassign(id);
   			 break;
   		 case 2: printf("Enter student id: ");
   			 scanf("%s",id);
   			 studunassign(id);
   			 break;
   		 case 3: printf("Enter student id: ");
   			 scanf("%s",id);
   			 studcheck(id);
   			 break;
   		 case 4:    return;
   		 default: printf("\ninvalid option");
   			  //getch();
   			  break;
   	 }
    }while(opt>0&&opt<=4);
    //getch();
}
void studassign(char id[])
{
    struct student stud;
    FILE *fp;
    strcpy(stud.id,id);
    printf("Enter the course that the student has chosen: ");
    scanf("%s",stud.crsid);
    getchar();
    printf("Enter the semester: ");
    scanf("%d",&stud.sem);
    fp=fopen("studmap","a");
    if(!fp)
    {
   	 printf("Error!!");
   	 return;
    }
    fwrite(&stud,sizeof(struct student),1,fp);
    fclose(fp);
}
void studunassign(char id[])
{
    FILE *fp;
    FILE *fp_temp;
    int found=0;
    struct student stud;
    fp=fopen("studmap","r");
    if(!fp)
    {
   	 printf("Error!!");
   	 return;
    }
    fp_temp=fopen("temp","a");
    if(!fp_temp)
    {
   	 printf("Error!!");
   	 return;
    }
    while(!feof(fp))
    {
   	 fread(&stud,sizeof(struct student),1,fp);
   	 if(strcmp(id,stud.id)==0)
   	 {
   		 printf("Record deleted");
   		 found=1;
   	 }
   	 else
   	 {
   		 fwrite(&stud,sizeof(struct student),1,fp_temp);
   	 }
    }
    if(!found)
    {
   	 printf("Student not found");
    }
    fclose(fp);
    fclose(fp_temp);
    //getch();
    remove("studmap");
    rename("temp","studmap");
}
void studcheck(char id[])
{
    FILE *fp;
    int found=0;
    struct student stud;
    fp=fopen("studmap","r");
    if(!fp)
    {
   	 printf("Error!!");
   	 return;
    }
    while(!feof(fp))
    {
   	 fread(&stud,sizeof(struct student),1,fp);
   	 if(strcmp(id,stud.id)==0)
   	 {
   		 system("clear");
   		 printf("Record found\n");
   		 printf("Course: %s\n",stud.crsid);
   		 printf("Semester: %d\n",stud.sem);
   		 found=1;
   		 break;
   	 }
    }
    fclose(fp);
    if(!found)
    {
   	 printf("Record not found");
    }
    //getch();
}
void teachmap()
{
    int opt;
    char id[16];
    system("clear");
    do{
   	 printf("1.Assign\n2.Unassign\n3.check\n4.Exit\nchoice:");
   	 scanf("%d",&opt);
   	 switch(opt)
   	 {
   		 case 1: printf("Enter teacher id: ");
   			 scanf("%s",id);
   			 teachassign(id);
   			 break;
   		 case 2: printf("Enter teacher id: ");
   			 scanf("%s",id);
   			 teachunassign(id);
   			 break;
   		 case 3: printf("Enter teacher id: ");
   			 scanf("%s",id);
   			 teachcheck(id);
   			 break;
   		 case 4:    return;
   		 default: printf("\ninvalid option");
   			  //getch();
   			  break;
   	 }
    }while(opt<=4&&opt>0);
    //getch();
}
void teachassign(char id[])
{
    struct teacher teach;
    FILE *fp;
    strcpy(teach.id,id);
    printf("Enter the subject that the teacher has chosen: ");
    scanf("%s",teach.sub);
    getchar();
    printf("Enter the semester: ");
    scanf("%d",&teach.sem);
    fp=fopen("teachmap","a");
    if(!fp)
    {
   	 printf("Error!!");
   	 return;
    }
    fwrite(&teach,sizeof(struct teacher),1,fp);
    fclose(fp);
}
void teachunassign(char id[])
{
    FILE *fp;
    FILE *fp_temp;
    int found=0;
    struct teacher teach;
    fp=fopen("teachmap","r");
    if(!fp)
    {
   	 printf("Error!!");
   	 return;
    }
    fp_temp=fopen("temp","a");
    if(!fp_temp)
    {
   	 printf("Error!!");
   	 return;
    }
    while(!feof(fp))
    {
   	 fread(&teach,sizeof(struct teacher),1,fp);
   	 if(strcmp(id,teach.id)==0)
   	 {
   		 printf("Record deleted");
   		 found=1;
   	 }
   	 else
   	 {
   		 fwrite(&teach,sizeof(struct teacher),1,fp_temp);
   	 }
    }
    if(!found)
    {
   	 printf("Teacher not found");
    }
    fclose(fp);
    fclose(fp_temp);
    //getch();
    remove("teachmap");
    rename("temp","teachmap");
}
void teachcheck(char id[])
{
    FILE *fp;
    int found=0;
    struct teacher teach;
    fp=fopen("teachmap","r");
    if(!fp)
    {
   	 printf("Error!!");
   	 return;
    }
    while(!feof(fp))
    {
   	 fread(&teach,sizeof(struct teacher),1,fp);
   	 if(strcmp(id,teach.id)==0)
   	 {
   		 system("clear");
   		 printf("Record found\n");
   		 printf("Subject: %s\n",teach.sub);
   		 printf("Semester: %d\n",teach.sem);
   		 found=1;
   		 break;
   	 }
    }
    fclose(fp);
    if(!found)
    {
   	 printf("Record not found");
    }
    //getch();
}
void teachmenu()
{
    int opt,found=0;
    FILE *fp;
    struct teacher teach;
    fp=fopen("teachmap","r");
    if(!fp)
    {
   	 printf("Error!!");
   	 //getch();
   	 return;
    }
    while(!feof(fp))
    {
   	 fread(&teach,sizeof(struct teacher),1,fp);
   	 if(strcmp(loginuser.id,teach.id)==0)
   	 {
   		 found=1;
   		 break;
   	 }
    }
    fclose(fp);
    if(!found)
    {
   	 printf("You are not in the database. The administrator has either removed you or not yet entered your details.");
   	 //getch();
   	 return;
    }
    system("clear");
    do{
   	 printf("\tTeacher Menu\n");
   	 printf("Hello %s\n",loginuser.name);
   	 printf("what would you like to do\n");
   	 printf("1.See your details\n2.Enter marks\n3.Enter attendance\n4.see your feedback\n5.Exit\nchoice: ");
   	 scanf("%d",&opt);
   	 switch(opt)
   	 {
   		 case 1: teachdispdet();
   			 break;
   		 case 2: entmarks(teach.sub,teach.sem);
   			 break;
   		 case 3:    entattend(teach.sub,teach.sem);
   			 break;
   		 case 4: dispfeedback();
   			 break;
   		 case 5: return;
   		 default: printf("\ninvalid option");
   			  //getch();
   			  break;
   	 }
    }while(opt<=5&&opt>0);
    //getch();
}
void teachdispdet()
{
    FILE *fp;
    struct teacher teach;
    system("clear");
    fp=fopen("teachmap","r");
    if(!fp)
    {
   	 printf("Error!!");
   	 return;
    }
    while(!feof(fp))
    {
   	 fread(&teach,sizeof(struct teacher),1,fp);
   	 if(strcmp(loginuser.id,teach.id)==0)
   	 {
   		 printf("\t\tYour Details\n");
   		 printf("Id: %s\n",loginuser.id);
   		 printf("Name: %s\n",loginuser.name);
   		 printf("Date of birth: %s\n",loginuser.dob);
   		 printf("Sex: %c\n",loginuser.sex);
   		 printf("Subject taught: %s\n",teach.sub);
   		 printf("Semester taught: %d\n",teach.sem);
   		 break;
   	 }
    }
    fclose(fp);
    //getch();
}
void entmarks(char sub[],int sem)
{
    int found=0;
    struct marks mk;
    struct student stud;
    FILE *fp;
    system("clear");
    printf("Enter student id: ");
    scanf("%s",mk.id);
    fp=fopen("studmap","r");
    if(!fp)
    {
   	 printf("Error!!");
   	 return;
    }
    while(!feof(fp))
    {
   	 fread(&stud,sizeof(struct student),1,fp);
   	 if(strcmp(mk.id,stud.id)==0)
   	 {
   		 if(studteachrel(stud.crsid,sub,sem)==1)
   		 {
   			 strcpy(mk.sub,sub);
   			 printf("Enter marks: ");
   			 scanf("%d",&mk.markobt);
   			 found=1;
   			 break;
   		 }
   	 }
    }
    fclose(fp);
    if(!found)
    {
   	 printf("Invalid ID");
   	 //getch();
   	 return;
    }
    fp=fopen("marks","a");
    if(!fp)
    {
   	 printf("Error!!");
   	 return;
    }
    fwrite(&mk,sizeof(struct marks),1,fp);
    fclose(fp);
    //getch();
}
void entattend(char sub[4],int sem)
{
    int found=0;
    struct attendance at;
    struct student stud;
    FILE *fp;
    system("clear");
    printf("Enter student id: ");
    scanf("%s",at.id);
    fp=fopen("studmap","r");
    if(!fp)
    {
   	 printf("Error!!");
   	 return;
    }
    while(!feof(fp))
    {
   	 fread(&stud,sizeof(struct student),1,fp);
   	 if(strcmp(at.id,stud.id)==0)
   	 {
   		 if(studteachrel(stud.crsid,sub,sem)==1)
   		 {
   			 strcpy(at.sub,sub);
   			 printf("Enter date(dd/mm/yyyy): ");
   			 scanf("%s",at.date);
   			 getchar();
   			 printf("Present or absent(p/a): ");
   			 scanf("%c",&at.state);
   			 found=1;
   			 break;
   		 }
   	 }
    }
    fclose(fp);
    if(!found)
    {
   	 printf("Invalid ID");
   	 //getch();
   	 return;
    }
    fp=fopen("attend","a");
    if(!fp)
    {
   	 printf("Error!!");
   	 return;
    }
    fwrite(&at,sizeof(struct attendance),1,fp);
    fclose(fp);
    //getch();
}
int studteachrel(char id[],char sub[],int sem)
{
    FILE *fp;
    int i;
    struct clas cls;
    fp=fopen("clslis","r");
    if(!fp)
    {
   	 printf("Error!!");
   	 return -1;
    }
    while(!feof(fp))
    {
   	 fread(&cls,sizeof(struct clas),1,fp);
   	 if((strcmp(id,cls.id)==0)&&(sem==cls.sem))
   	 {
   		 for(i=0;i<6;i++)
   		 {
   			 if(strcmp(sub,cls.sub[i])==0)
   			 {
   				 fclose(fp);
   				 return 1;
   			 }
   		 }
   	 }
    }
    fclose(fp);
    return 0;
}
void dispfeedback()
{
    FILE *fp;
    int count=0;
    struct feedback feed;
    fp=fopen("feeba","r");
    if(!fp)
    {
   	 printf("Error!!");
   	 //getch();
   	 return;
    }
    system("clear");
    printf("\t\tFeedback\n");
    while(!feof(fp))
    {
   	 fread(&feed,sizeof(struct feedback),1,fp);
   	 if(strcmp(loginuser.id,feed.teachid)==0)
   	 {
   		 count++;
   		 printf("%3d. %s",count,feed.fb);
   	 }
    }
    fclose(fp);
    if(!count)
    {
   	 printf("No feedbacks");
    }
    //getch();
}
void studmenu()
{
    int opt,found=0;
    FILE *fp;
    struct student stud;
    fp=fopen("studmap","r");
    if(!fp)
    {
   	 printf("Error!!");
   	 //getch();
   	 return;
    }
    while(!feof(fp))
    {
   	 fread(&stud,sizeof(struct student),1,fp);
   	 if(strcmp(loginuser.id,stud.id)==0)
   	 {
   		 found=1;
   		 break;
   	 }
    }
    fclose(fp);
    if(!found)
    {
   	 printf("You are not in the database. The administrator has either removed you or not yet entered your details.");
   	 //getch();
   	 return;
    }
    system("clear");
    do{
   	 printf("\tStudent Menu\n");
   	 printf("Hello %s\n",loginuser.name);
   	 printf("what would you like to do\n");
   	 printf("1.See your details\n2.See marks\n3.Check attendance\n4.Give feedback\n5.Exit\nchoice: ");
   	 scanf("%d",&opt);
   	 switch(opt)
   	 {
   		 case 1: studispdet();
   			 break;
   		 case 2: dispmarks();
   			 break;
   		 case 3:    checattend();
   			 break;
   		 case 4: givefeedback(stud.crsid,stud.sem);
   			 break;
   		 case 5: return;
   		 default: printf("\ninvalid option");
   			  //getch();
   			  break;
   	 }
    }while(opt<=5&&opt>0);
    //getch();
}
void studispdet()
{
    int i;
    FILE *fp;
    struct student stud;
    struct clas cls;
    system("clear");
    fp=fopen("studmap","r");
    if(!fp)
    {
   	 printf("Error!!");
   	 //getch();
   	 return;
    }
    while(!feof(fp))
    {
   	 fread(&stud,sizeof(struct student),1,fp);
   	 if(strcmp(loginuser.id,stud.id)==0)
   	 {
   		 printf("\t\tYour Details\n");
   		 printf("Id: %s\n",loginuser.id);
   		 printf("Name: %s\n",loginuser.name);
   		 printf("Date of birth: %s\n",loginuser.dob);
   		 printf("Sex: %c\n",loginuser.sex);
   		 printf("Course: %s\n",stud.crsid);
   		 printf("Semester: %d\n",stud.sem);
   		 break;
   	 }
    }
    fclose(fp);
    fp=fopen("clslis","r");
    if(!fp)
    {
   	 printf("Error!!");
   	 //getch();
   	 return;
    }
    printf("Subject:\n");
    while(!feof(fp))
    {
   	 fread(&cls,sizeof(struct clas),1,fp);
   	 if((strcmp(stud.crsid,cls.id)==0)&&(stud.sem==cls.sem))
   	 {
   		 for(i=0;i<6;i++)
   		 {
   			 printf("%d. %s\n",i+1,cls.sub[i]);
   		 }
   		 break;
   	 }
    }
    //getch();
}
void dispmarks()
{
    FILE *fp;
    int count=1;
    struct marks mk;
    int maxmarks,minmarks;
    float percent;
    fp=fopen("marks","r");
    if(!fp)
    {
   	 printf("Error!!");
   	 //getch();
   	 return;
    }
    system("clear");
    printf("\t\tMarks\n");
    while(!feof(fp))
    {
   	 fread(&mk,sizeof(struct marks),1,fp);
   	 if(strcmp(loginuser.id,mk.id)==0)
   	 {
   		 printf("%d. %3s %3d ",count,mk.sub,mk.markobt);
   		 getmaxminmarks(mk.sub,&maxmarks,&minmarks);
   		 percent= (mk.markobt*100)/maxmarks;
   		 printf("%3.1f ",percent);
   		 if(mk.markobt<minmarks)
   		 {
   			 printf("Fail\n");
   		 }
   		 else
   		 {
   			 printf("Pass\n");
   		 }
   		 count++;
   	 }
    }
    fclose(fp);
    count--;
    if(!count)
    {
   	 printf("No Marks available Yet");
    }
    //getch();
}
void getmaxminmarks(char subj[],int *maxmarks,int *minmarks)
{
    struct subject sub;
    FILE *fp;
    fp=fopen("sublis","r");
    if(!fp)
    {
   	 printf("Error!!");
   	 //getch();
   	 return;
    }
    while(!feof(fp))
    {
   	 fread(&sub,sizeof(struct subject),1,fp);
   	 if(strcmp(subj,sub.id)==0)
   	 {
   		 *maxmarks=sub.maxmarks;
   		 *minmarks=sub.minmarks;
   		 break;
   	 }
    }
    fclose(fp);
}
void checattend()
{
    FILE *fp;
    int i;
    int count=1,present[6]={0,0,0,0,0,0},absent[6]={0,0,0,0,0,0},subid;
    struct student stud;
    struct attendance at;
    fp=fopen("attend","r");
    if(!fp)
    {
   	 printf("Error!!");
   	 //getch();
   	 return;
    }
    system("clear");
    printf("\t\tAttendance\n");
    while(!feof(fp))
    {
   	 fread(&at,sizeof(struct attendance),1,fp);
   	 if(feof(fp))
   	 {
   		 break;
   	 }
   	 if(strcmp(loginuser.id,at.id)==0)
   	 {
   		 subid=getsubid(at.sub,loginuser.id);
   		 if(at.state=='p'||at.state=='P')
   		 {
   			 present[subid]+=1;
   		 }
   		 else
   		 {
   			 absent[subid]+=1;
   		 }
   	 }
    }
    fclose(fp);
    printf("Your attendance status is as follows\n");
    printf("Subject\tAbsent per\tPresent per\n");
    for (i=0;i<6;++i)
    {
   	 float presentPercent=0,absentPercent=0;
   	 char subje[4];
   	 if(present[i]>0)
   	 {
   		 presentPercent = 100*present[i]/(present[i]+absent[i]);
   	 }
   	 if(absent[i]>0)
   	 {
   		 absentPercent= 100*absent[i]/(present[i]+absent[i]);
 
   	 }
   	 strcpy(subje,getsub(i,loginuser.id));
   	 printf("%3s\t%4.2f\t%6.2f\n",subje,absentPercent,presentPercent);
    }
    //getch();
}
void givefeedback(char crsid[],int sem)
{
    int found=0,i;
    struct feedback feed;
    struct teacher teach;
    FILE *fp;
    system("clear");
    printf("Enter teacher id: ");
    scanf("%s",feed.teachid);
    getchar();
    fp=fopen("teachmap","r");
    if(!fp)
    {
   	 printf("Error!!");
   	 //getch();
   	 return;
    }
    while(!feof(fp))
    {
   	 fread(&teach,sizeof(struct teacher),1,fp);
   	 if(strcmp(feed.teachid,teach.id)==0)
   	 {
   		 if(studteachrel(crsid,teach.sub,sem)==1)
   		 {
   			 strcpy(feed.studid,loginuser.id);
   			 printf("Enter feedback: ");
   			 scanf("%[^\n]s",feed.fb);
   			 found=1;
   			 break;
   		 }
   	 }
    }
    fclose(fp);
    if(!found)
    {
   	 printf("Invalid ID");
   	 //getch();
   	 return;
    }
    fp=fopen("feeba","a");
    if(!fp)
    {
   	 printf("Error!!");
   	 //getch();
   	 return;
    }
    fwrite(&feed,sizeof(struct feedback),1,fp);
    fclose(fp);
    //getch();
}
int getsubid(char sub[4],char uid[16])
{
    FILE *fp;
    int i;
    char crs[4];
    struct student stud;
    struct clas cls;
    fp=fopen("studmap","r");
    if(!fp)
    {
   	 printf("Error!!");
   	 //getch();
   	 return -1;
    }
    while(!feof(fp))
    {
   	 fread(&stud,sizeof(struct student),1,fp);
   	 if(strcmp(uid,stud.id)==0)
   	 {
   		 strcpy(crs,stud.crsid);
   		 break;
   	 }
    }
    fclose(fp);
    fp=fopen("clslis","r");
    if(!fp)
    {
   	 printf("Error!!");
   	 //getch();
   	 return -1;
    }
    while(!feof(fp))
    {
   	 fread(&cls,sizeof(struct clas),1,fp);
   	 if(strcmp(crs,cls.id)==0)
   	 {
   	    	for(i=0;i<6;i++)
   	    	{
   		    	if(strcmp(sub,cls.sub[i])==0)
   		    	{
   				 fclose(fp);
   				 return i;
   		    	}
   	    	}
   	 }
    }
    fclose(fp);
    return -1;
}
char *getsub(int index, char uid[16])
{
    FILE *fp;
    int i;
    char crs[4];
    struct student stud;
    struct clas cls;
    fp=fopen("studmap","r");
    if(!fp)
    {
   	 printf("Error!!");
   	 //getch();
   	 return NULL;
    }
    while(!feof(fp))
    {
   	 fread(&stud,sizeof(struct student),1,fp);
   	 if(strcmp(uid,stud.id)==0)
   	 {
   		 strcpy(crs,stud.crsid);
   		 break;
   	 }
    }
    fclose(fp);
    fp=fopen("clslis","r");
    if(!fp)
    {
   	 printf("Error!!");
   	 //getch();
   	 return NULL;
    }
    while(!feof(fp))
    {
   	 fread(&cls,sizeof(struct clas),1,fp);
   	 if(strcmp(crs,cls.id)==0)
   	 {
   		 fclose(fp);
   		 return cls.sub[index];
 
   	 }
    }
    fclose(fp);
    return NULL;
}
