#include<stdio.h>

struct student
{
    char name[50],father[50],mother[50],date_of_birth[50],blood_group[50],address[50],major[50];
    float cgpa;
    int id;
} s[100];
void menu();
void read(struct student s[]);
void search(struct student s[]);
void edit(struct student s[]);
void insert(struct student s[]);
void delete(struct student s[]);
void output(struct student s[]);
int num = 0;
FILE *file;

void main()
{
    file = fopen ("students.txt","r");
    if (file == NULL)
    {
        printf("Error opening students.txt\n");
        printf("Enter the number of students: ");
        scanf("%d", &num);
        fflush(stdin);
        printf("\n");
        read(s);
        menu();
    }else{
        num = fread(s, sizeof(struct student), 100, file);
        //printf("%d", num);
        menu();
    }
    fclose(file);

}

void menu(){
    char a;
    file = fopen ("students.txt","r");
    while(1){
        printf("\nEnter 1 to  close window\n");
        printf("Enter 2 to output the information of students\n");
        printf("Enter 3 to search the information of students\n");
        printf("Enter 4 to edit the information of students\n");
        printf("Enter 5 to insert the information of students\n");
        printf("Enter 6 to delete the information of students\n\n");

        printf("Enter the number which you want : ");
        fflush(stdin);
        scanf("%c", &a);
        if(a == '1'){
            break;
        }else if(a == '2'){
            output(s);
        }else if(a== '3'){
            search(s);
        }else if(a== '4'){
            edit(s);
            output(s);
        }else if(a== '5'){
            insert(s);
            output(s);
        }else if(a== '6'){
            delete(s);
            output(s);
        }
    }
}

void read(struct student s[]){
    system("cls");
    int i;
    file = fopen ("students.txt","w");
    fflush(stdin);
    for(i=0; i<num; i++)
    {
        printf("Name: ");
        gets(s[i].name);
        fflush(stdin);
        printf("ID: ");
        scanf("%d", &s[i].id);
        fflush(stdin);
        printf("Father's name: ");
        gets(s[i].father);
        fflush(stdin);
        printf("Mother's name: ");
        gets(s[i].mother);
        fflush(stdin);
        printf("Date Of Birth: ");
        gets(s[i].date_of_birth);
        fflush(stdin);
        printf("Address: ");
        gets(s[i].address);
        printf("Blood Group: ");
        gets(s[i].blood_group);
        fflush(stdin);
        printf("Major Course: ");
        gets(s[i].major);
        fflush(stdin);
        printf("CGPA: ");
        scanf("%f", &s[i].cgpa);
        fflush(stdin);
    }
    fwrite(s, sizeof(struct student), i, file);
    fclose(file);
    //printf("\n");

}

void search(struct student s[]){
    system("cls");
    int id,i,flag=0;
    printf("\nEnter the id you want to search: \n");
    scanf("%d", &id);
    fflush(stdin);

    for(i=0; i<num; i++)
    {
        if(id == s[i].id){
            flag=1;
            printf("\nName: %s\n", s[i].name);
            printf("Id: %d\n", s[i].id);
            printf("Father's name: %s\n", s[i].father);
            printf("Mother's name: %s\n", s[i].mother);
            printf("Date Of Birth: %s\n", s[i].date_of_birth);
            printf("Address: %s\n", s[i].address);
            printf("Blood group: %s\n", s[i].blood_group);
            printf("Major course: %s\n", s[i].major);
            printf("CGPA: %.2f\n", s[i].cgpa);
            printf("\n");
        }
    }
    if(flag==0){
        printf("Not found the searched id \n");
    }
}

void edit(struct student s[]){
    system("cls");
    int id,i, flag =0;

    printf("\nEnter the id you want to edit: \n");
    scanf("%d", &id);
    fflush(stdin);

    file = fopen ("students.txt","w");

    for(i=0; i<num; i++)
    {
        if(id==s[i].id){
            flag =1;
            printf("\nEnter name: ");
            gets(s[i].name);
            fflush(stdin);
            printf("Enter ID: ");
            scanf("%d", &s[i].id);
            fflush(stdin);
            printf("Father's name: ");
            gets(s[i].father);
            fflush(stdin);
            printf("Mother's name: ");
            gets(s[i].mother);
            fflush(stdin);
            printf("Enter Date Of Birth: ");
            gets(s[i].date_of_birth);
            fflush(stdin);
            printf("Enter address: ");
            gets(s[i].address);
            printf("Blood Group: ");
            gets(s[i].blood_group);
            fflush(stdin);
            printf("Enter Major Course: ");
            gets(s[i].major);
            fflush(stdin);
            printf("Enter CGPA: ");
            scanf("%f", &s[i].cgpa);
            fflush(stdin);
        }
    }
    fwrite(s, sizeof(struct student), i, file);
    fclose(file);
    if(flag==0){
        printf("Not found the searched id \n");
    }
}

void insert(struct student s[]){
    system("cls");
    int n,i;
    printf("\nHow many you want to insert: ");
    scanf("%d", &n);
    fflush(stdin);

    file = fopen ("students.txt","w");

    for(i=0; i<n; i++)
    {
        printf("\nEnter name: ");
        gets(s[num+i].name);
        fflush(stdin);
        printf("Enter ID: ");
        scanf("%d", &s[num+i].id);
        fflush(stdin);
        printf("Father's name: ");
        gets(s[num+i].father);
        fflush(stdin);
        printf("Mother's name: ");
        gets(s[num+i].mother);
        fflush(stdin);
        printf("Enter Date Of Birth: ");
        gets(s[num+i].date_of_birth);
        fflush(stdin);
        printf("Enter address: ");
        gets(s[num+i].address);
        printf("Blood Group: ");
        gets(s[num+i].blood_group);
        fflush(stdin);
        printf("Enter Major Course: ");
        gets(s[num+i].major);
        fflush(stdin);
        printf("Enter CGPA: ");
        scanf("%f", &s[num+i].cgpa);
        fflush(stdin);

        printf("\n");
    }
    num+=n;
    //printf("%d",num);
    fwrite(s, sizeof(struct student), num, file);
    fclose(file);
}

void delete(struct student s[]){
    system("cls");
    int id,i,index,flag =0;
    printf("Enter the id you want to delete: \n");
    scanf("%d", &id);
    fflush(stdin);

    file = fopen ("students.txt","w");

    for(i=0; i<num; i++)
    {   if(id == s[i].id){
            flag=1;
            //s[i].id = 0;
            index = i;
        }
    }

    for(i=index; i<num-1; i++)
    {
        s[i]= s[i+1];
    }

    num= num-1;
    fwrite(s, sizeof(struct student), num, file);
    fclose(file);
    if(flag==0){
        printf("Not found the searched id \n");
    }
}

void output(struct student s[]){
    system("cls");
    int i;

    file = fopen ("students.txt","r");

    printf("\nInformations of all students data: \n");
    int n = fread(s, sizeof(struct student), 100, file);

    for(i=0; i<n; i++)
    {
            printf("Name: ");puts(s[i].name);
            printf("Id: %d\n", s[i].id);
            printf("Father's name: ");puts(s[i].father);
            printf("Mother's name: ");puts(s[i].mother);
            printf("Date Of Birth: ");puts(s[i].date_of_birth);
            printf("Address: ");puts(s[i].address);
            printf("Blood group: ");puts(s[i].blood_group);
            printf("Major course: ");puts(s[i].major);
            printf("CGPA: %.2f\n\n", s[i].cgpa);

    }
    fclose(file);

}



