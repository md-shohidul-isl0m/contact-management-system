# contact-management-system
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

bool isRunning = true;
void Menu();                    //shoaib
void AddNewContact();           //shohidul
void ShowAllContacts();         //Muhtasim
void SearchContact();           //Muhtasim
void EditContact();             //shohidul
void DeleteContact();           //shohidul
void DeleteAllContacts();       //shohidul
void ClearWindow();
void PrintLineWithSpace(char *Name[20],char ContactInfo);   //muhtasim
int  Name_Check(char *Name);    //shohidul
int  No_check(char *number);    //shohidul
int  Email_check(char *Email);  //shohidul
void ErrorAndRestart(char *error[100]);     //shoaib
bool AlreadyExists(char *GivenLine[30],char ContactInfo);       //muhtasim
void GoBackOrExit();            //Shoaib
void Exit();                    //Shoaib

int main(){
    system("cls");
    system("color 2f");
    int i;
    printf("\t\t");
    char AppStarting[100] = "Application is Starting.....";     //starting the programm
    for(i=0;i<strlen(AppStarting);i++){
        printf("%c",AppStarting[i]);
        Sleep(40);                  //displaying the line character by character after 40 ms.
    }
    system("cls");


    while(isRunning == true){
        Menu();                     //displaying the menu.
        char str[100];
        char option;
        scanf(" %s",str);           //taking the option.
        option = str[0];
        switch(option){             //checking the option.
            case '0':
                Exit();
                break;
            case '1':
                AddNewContact();
                break;
            case '2':
                ShowAllContacts();
                break;
            case '3':
                SearchContact();
                break;
            case '4':
                EditContact();
                break;
            case '5':
                DeleteContact();
                break;
            case '6':
                DeleteAllContacts();
                break;
            case '7':
                system("cls");
                break;
            default:
                ErrorAndRestart("Option not found!");
                break;
        }
    }


return 0;
}
//Main Menu.

void Menu()
{
    system("color 3f");
    printf("\n\t\t ***** My-Contact Management System Using C *****\n\n\n");
    printf("\t\t\t\tMAIN MENU\n");
    printf("\t\t\t=====================\n");
    printf("\t\t\t[1] Add a new Contact\n");
    printf("\t\t\t[2] Show all Contacts\n");
    printf("\t\t\t[3] Search for contact\n");
    printf("\t\t\t[4] Edit a Contact\n");
    printf("\t\t\t[5] Delete a Contact\n");
    printf("\t\t\t[6] Delete All Contact\n");
    printf("\t\t\t[7] Clear Window\n");
    printf("\t\t\t[0] Exit\n\n\t\t\t=================\n");
    printf("\t\t\tEnter the choice:");
}

//add a contact.

void AddNewContact(){
    system("cls");
    system("color 2f");
    printf("\n\t\t **** Add new Contact ****\n\n");
    char Name[20];
    char Phone[20];
    char Email[30];
    char NewContact[100];
    NewContact[0] = 0;
    Enter_name:
    printf("*Name should be unique and maximum 20 characters long.\n");
    printf("Enter The Name: ");
    scanf(" %[^\n]s",Name);
    if(Name_Check(Name)==0)             //checking the name is valid or not.
        goto Enter_name;

    Enter_Number:
    printf("\n*Phone should be unique and maximum 20 characters long.\n");
    printf("Enter The Phone Number: ");
    scanf("%s",Phone);
    if(No_check(Phone)==0)              //checking the number is valid or not.
        goto Enter_Number;

    Enter_Email:
    printf("\n*Email should be unique and maximum 30 characters long.\n");
    printf("Enter The Email: ");

    scanf("%s",Email);
    if(Email_check(Email)==0)           //checking the e-mail is valid or not.
        goto Enter_Email;

    strcat(NewContact,Name);
    strcat(NewContact,"\n");
    strcat(NewContact,Phone);
    strcat(NewContact,"\n");
    strcat(NewContact,Email);
    strcat(NewContact,"\n");

    FILE *allContactTxtFile = fopen("All-Contact.txt","a"); // create file and open in append mood
    fprintf(allContactTxtFile,NewContact);                  // store contact in file
    fclose(allContactTxtFile);                              // close the file
    printf("\nContact Added Successfully!\n");
    GoBackOrExit();
}

//Showing all contacts.

void ShowAllContacts()
{
    system("cls");
    system("color 8f");
    printf("\n\t\t ***** All Contacts *****\n\n");
    FILE* AllContactTextFile;
    int LineLength = 300;
    char Line[LineLength];

    printf("|====================|====================|==============================|\n");
    printf("|        Name        |    Phone Number    |          Email               |\n");
    printf("|====================|====================|==============================|\n");

    AllContactTextFile = fopen("All-Contact.txt", "r");
    int TotalContact = 0;
    int LineCount = 0;
    while(fgets(Line, LineLength, AllContactTextFile))
    {
        LineCount++;
        if(LineCount==1)
        {
            // name
            PrintLineWithSpace(Line,'n');
        }
        else if(LineCount == 2)
        {
            // phone
            PrintLineWithSpace(Line,'p');
        }
        else if(LineCount == 3)
        {
            // email
            PrintLineWithSpace(Line,'e');
            LineCount=0;
            TotalContact++;                 //counting the contacts.
        }
    }
    printf("You Have Total %d Contacts.\n\n",TotalContact);
    fclose(AllContactTextFile);
    GoBackOrExit();
}

//Presenting the contacts .

void PrintLineWithSpace(char *Name[20],char ContactInfo)
{
    int i;
    char *FormatedName = NULL;
    FormatedName = strdup(Name);
    int FormatedNameLenght = strlen(FormatedName);

    int TotalSpace = 0;
    if(ContactInfo == 'n')
    {
        TotalSpace = 20 - FormatedNameLenght; // name
    }
    else if(ContactInfo == 'p')
    {
        TotalSpace = 20 - FormatedNameLenght; // phone
    }
    else if(ContactInfo == 'e')
    {
        TotalSpace = 30 - FormatedNameLenght; // email
    }

    printf("|");
    for(i=0; i<FormatedNameLenght-1; i++)
    {
        printf("%c",FormatedName[i]);
    }

    for(i=0; i<=TotalSpace; i++)
    {
        printf(" ");
    }

    if(ContactInfo == 'e')
    {
        printf("|\n");
        printf("|--------------------|--------------------|------------------------------|\n");
    }
}

//searching a contact.

void SearchContact()
{
    system("cls");
    system("color 5f");
    printf("\n\t\t ***** Search Contact *****\n\n");

    int FoundContact = 0;
    char Name[100];
    re_search:                  //searching label.
    printf("*Name should be maximum 20 characters long.\n");
    printf("Enter The Name: ");
    scanf(" %[^\n]s",Name);
    if(strlen(Name) > 20)
    {
        printf("\n!!!!Name Length Error!!!\n\n");
        goto re_search;
    }
    strcat(Name,"\n");

    FILE* AllContactFile;
    int LineLength = 255;
    char Line[LineLength];
    AllContactFile = fopen("All-Contact.txt", "r");
    int LineCount = 0;
    int NeedToPrintLine = 0;
    while(fgets(Line, LineLength, AllContactFile))      //searching the contact is there or not.
    {
        LineCount++;
        if(LineCount == 1 && strcmpi(Name, Line) == 0)
        {   // we found the contact.
            FoundContact = 1;
            NeedToPrintLine = 3;
        }
        if(NeedToPrintLine > 0)
        {
            if(LineCount==1)
            {
                printf("\nContact information of : %s",Name);
                printf("\nName: %s",Line);                      //printing the name.
                NeedToPrintLine = 2;
            }
            else if(LineCount == 2)
            {
                printf("Phone: %s",Line);                       //printing the number.
                NeedToPrintLine = 1;
            }
            else if(LineCount == 3)
            {
                printf("Email: %s\n",Line);                     //printing the e-mail.
                NeedToPrintLine = 0;
            }
        }

        if(LineCount == 3)
        {
            LineCount=0;
        }
    }
    fclose(AllContactFile);
    if(FoundContact == 0)
    {
        printf("\nSorry no contact found for %s\n",Name);
        goto re_search;
    }


    GoBackOrExit();
}

//Edit a contact.

void EditContact(){
    system("cls");
    system("color 2f");
    printf("\n\t\t **** Edit Contact ****\n\n");

    int LineCount = 0;
    int FoundContact = 0;
    int SkipLines = 0;
    char GivenName[100];
    char NewName[100];
    char NewPhone[20];
    char NewEmail[100];
    char NewFullContact[300];
    NewFullContact[0] = 0;
    edit:
    printf("*Name should be maximum 20 characters long.\n");
    printf("Enter The Name which one you want to edit: ");
    scanf(" %[^\n]s",GivenName);
    if(strlen(GivenName) > 20){
        printf("\n!!!!Name Length Error!!!\n\n");
        goto edit;                              //re-taking the name user looking for.
    }

    strcat(GivenName,"\n");

    FILE* OurExistingFile;
    FILE* NewTempFile;
    int LineLength = 255;
    char Line[LineLength];
    OurExistingFile = fopen("All-Contact.txt", "r");
    NewTempFile = fopen("temp-file.txt", "w");
    while(fgets(Line, LineLength, OurExistingFile)) {

        LineCount++;

        if(LineCount == 1 && strcmpi(GivenName, Line) == 0){
            // we found the contact
            FoundContact = 1;
            SkipLines = 3;
        }

        if(SkipLines > 0){
            if(LineCount == 1){
                Edit_Name:
                printf("\n*New Name should be unique and maximum 20 characters long.\n");
                printf("Old Name is: %s",Line);
                printf("New Name(0 for skip): ");
                scanf(" %[^\n]s",NewName);              //taking the new name & 0 for skip editing the old name.
                if(strcmp(NewName, "0") == 0){
                    strcat(NewFullContact,Line);
                }else{
                    if(Name_Check(NewName)==0)
                    {
                        goto Edit_Name;             //re-taking the new-name.
                    }

                    strcat(NewFullContact,NewName);
                    strcat(NewFullContact,"\n");
                }
                SkipLines = 2;
            }else if(LineCount == 2){
                Edit_Number:
                printf("\n*New Phone should be unique and maximum 20 characters long.\n");
                printf("Old Phone is: %s",Line);
                printf("New Phone(0 for skip): ");
                scanf("%s",NewPhone);                       //taking the new number & 0 for skip editing the old number.
                if(strcmp(NewPhone, "0") == 0){
                    strcat(NewFullContact,Line);
                }else{
                    if(No_check(NewPhone)==0)
                    {
                        goto Edit_Number;               //re-taking the new-number.
                    }
                    strcat(NewFullContact,NewPhone);
                    strcat(NewFullContact,"\n");
                }
                SkipLines = 1;
            }else if(LineCount == 3){
                Edit_Mail:
                printf("\n*New Email should be unique and maximum 30 characters long.\n");
                printf("Old Email is: %s",Line);
                printf("New Email(0 for skip): ");
                scanf("%s",NewEmail);                           //taking the new e-mail & 0 for skip editing the old-e-mail.

                if(strcmp(NewEmail, "0") == 0){
                    strcat(NewFullContact,Line);
                }else{
                    if(Email_check(NewEmail)==0)
                    {
                        goto Edit_Mail;                 //re-taking the new-e-mail.
                    }
                    strcat(NewFullContact,NewEmail);
                    strcat(NewFullContact,"\n");
                }
                SkipLines = 0;
                fprintf(NewTempFile,NewFullContact);
            }
        }else{
            fprintf(NewTempFile,Line);
        }

        if(LineCount == 3){
            LineCount = 0;
        }
    }
    fclose(NewTempFile);
    fclose(OurExistingFile);

    if(FoundContact == 0){
        //contact not found.
        printf("Contact Not Found!\n");

        remove("temp-file.txt");
    }else{
        printf("\nContact Edited Successfully!\n\n");
        remove("All-Contact.txt");
        rename("temp-file.txt", "All-Contact.txt");
    }
    GoBackOrExit();
}

void DeleteContact()
{

    system("cls");
    system("color 4f");
    printf("\n\t\t ***** Delete Contact *****\n\n");

    int lineCount = 0;
    int FoundTheContact = 0;
    int SkipLines = 0;
    char GivenName[100];
    work:
    printf("\n*Name should be maximum 20 characters long.\n");
    printf("Enter The Name which one you want to delete: ");
    fflush(stdin);
    gets(GivenName);
    if(strlen(GivenName) > 20)
    {
        printf("\n!!!!Name Length Error!!!\n");
        goto work;
    }
    strcat(GivenName,"\n");

    FILE* OurExistingFile;
    FILE* NewTempFile;
    int LineLenght = 300;
    char line[LineLenght];
    OurExistingFile = fopen("All-Contact.txt", "r");
    NewTempFile = fopen("temp-file.txt", "w");
    while(fgets(line, LineLenght, OurExistingFile))
    {
        lineCount++;

        if(lineCount == 1 && strcmpi(GivenName, line) == 0)
        {
            // we found the contact
            FoundTheContact = 1;
            SkipLines = 3;
        }

        if(SkipLines > 0)
        {
            SkipLines--;
        }
        else
        {
            fprintf(NewTempFile,line);
        }

        if(lineCount == 3)
        {
            lineCount = 0;
        }
    }
    fclose(NewTempFile);
    fclose(OurExistingFile);

    if(FoundTheContact == 0)
    {
        printf("\nContact Not Found!\n\n");
        remove("temp-file.txt");
        goto work;
    }
    else
    {
        printf("\nContact Deleted Successfully!\n\n");
        remove("All-Contact.txt");
        rename("temp-file.txt", "All-Contact.txt");
    }
    GoBackOrExit();
}

void DeleteAllContacts()
{
    system("cls");
    system("color 4f");
    printf("\n\t\t ***** Delete All The Contacts *****\n\n");

    char Option;
    printf("Are you sure want to delete all the contacts? (Y,N)?: ");
    fflush(stdin);
    scanf(" %c",&Option);
    if(Option=='Y' || Option=='y')
    {
        remove("All-Contact.txt");
        FILE *AllContactTxtFile = fopen("All-Contact.txt","a");
        fclose(AllContactTxtFile);

        char Deleting[100] = "Deleting.....";
        for(int i=0; i<strlen(Deleting); i++)
        {
            printf("%c",Deleting[i]);
            Sleep(40);
        }
        printf("\nSuccessfully Deleted All Contacts!\n\n");

    }
    GoBackOrExit();
}

bool AlreadyExists(char *GivenLine[30],char ContactInfo)
{
    char *ThisLine[35];
    ThisLine[0] = 0;
    strcat(ThisLine,GivenLine);
    strcat(ThisLine,"\n");
    int FileLineNumber = 0;
    if(ContactInfo == 'n')
    {
        FileLineNumber = 1; // name
    }
    else if(ContactInfo == 'p')
    {
        FileLineNumber = 2; // phone
    }
    else if(ContactInfo == 'e')
    {
        FileLineNumber = 3; // email
    }


    FILE* AllContactFile;
    int LineLength = 300;
    char Line[LineLength];
    AllContactFile = fopen("All-Contact.txt", "r");
    int LineCount = 0;
    int Found = 0;
    while(fgets(Line, LineLength, AllContactFile))
    {
        LineCount++;
        if(LineCount == FileLineNumber && strcmpi(ThisLine, Line) == 0)
        {
            Found = 1;
        }
        if(LineCount == 3)
        {
            LineCount = 0;
        }
    }
    fclose(AllContactFile);
    if(Found == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void ErrorAndRestart(char *error[100])
{
    printf("%s\n",error);
    int i = 0;
    printf("Restarting the program: ");
    for(i=0; i<10; i++)
    {
        printf(".");
        Sleep(50);
    }
    system("cls");
    main();
}

int Name_Check(char *Name)
{
    int wrongchar=1;
    if(strlen(Name) > 20)
    {
        printf("!!!!Name Length Error!!!\n\n");     //checking the name length....
        return 0;
    }

    if(AlreadyExists(Name,'n') == 1)
    {
        printf("\n!!!!Name Already Exists!!!\n\n");     //checking the name is already exist or not...
        return 0;
    }

    for( int i=0; Name[i]!= NULL; i++)
    {
        if(!((Name[i] >='A' && Name[i] <= 'Z') || (Name[i] >= 'a' && Name[i] <= 'z') || Name[i]==' '))  //checking the characters are valid nor not...
        {
            wrongchar=0;
        }
    }

    if(wrongchar==0)
    {
        printf("\n!!!Only Letters Are Allowed!!!\n\n");
        return 0;
    }
    else
        return 1;
}



int No_check(char *number)
{
    int wrongchar=1;

    if(strlen(number) != 11)                //checking the number length....
    {
        printf("\n!!!!Number Length Error!!!\n\n");
        return 0;
    }

    if(AlreadyExists(number,'p') == 1)
    {
        printf("\n!!!!Phone Number Already Exists!!!\n");       //checking the number is already exist or not...
        return 0;
    }

    for( int i=0; number[i]!= NULL; i++)
    {
        if(!(number[i]>='0' && number[i] <= '9'))               //checking the characters are valid nor not...
        {
            wrongchar=0;
        }
    }

    if(wrongchar==0)
    {
        printf("\n!!!Entered Wrong Character!!!\n\n");
        return 0;
    }
    else
        return 1;
}

int Email_check(char *Email)
{
    int sp=0,dot=0;

    for(int i=0; i<strlen(Email); i++)          //checking the number length....
    {
        if(Email[i] == '@')
        {
            sp++;
        }
        else if(Email[i]=='.')
        {
            dot++;
        }
    }

    if(strlen(Email) > 30)
    {

        printf("\n!!!!Email Length Error!!!\n\n");
        return 0;
    }

    if(AlreadyExists(Email,'e') == 1)
    {
        printf("\n!!!!Email Already Exists!!!\n");      //checking the E-mail is already exist or not...
        return 0;
    }

    if((sp==1) && (dot>=1))                 //checking the characters are valid nor not...
    {
        return 1;
    }
    else
    {
        printf("\n!!!Sorry,Entered Wrong Email!!!\n\n");
        return 0;
    }
}

void GoBackOrExit()
{
    char option;
    printf("\nGo Back to Menu (b)? or Exit(0)?");
    fflush(stdin);
    scanf("%c",&option);                        //Enter b to go back to main menu.... & Enter 0 to exit.
    if(option=='0')
    {
        Exit();
    }
    else
    {
        system("cls");
    }
}

void Exit()
{
    getchar();
    printf("Are You Sure Want to Exit? (Y,N): ");
    char YesOrNO;
    scanf(" %c",&YesOrNO);                          //Enter y to close the program.....&Enter n to go back to the Main Menu....
    if(YesOrNO == 'Y' || YesOrNO == 'y')
    {
        system("cls");
        system("color 8f");
        printf("\n");
        printf("\n");

        char ThankYou[100] = "=====Thank You=====\n";
        char SeeYouSoon[100] = "=====See You Soon=====\n\nThis program was created by NSU_DIRECTORY.....\n\n";
        int i=0;
        for(i=0; i<strlen(ThankYou); i++)
        {
            printf("%c",ThankYou[i]);
            Sleep(40);
        }
        for(i=0; i<strlen(SeeYouSoon); i++)
        {
            printf("%c",SeeYouSoon[i]);
            Sleep(40);
        }
        isRunning =  false;
    }
    else
        system("cls");
}

