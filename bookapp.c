#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Book
{
    int id;
    char name[20];
    int price;
    int qty;
};

struct Bill
{
    int pid;
    char pname[20];
    int pprice;
};

void addBook();
void displayAllBooks();
void deleteBook();
void search();
struct Book findBook(int id);
void updateBook(int id, int qty);
int billFileNo();
int getID();
void payment();
void manageBooks();
void purchaseBook();

char mygetch();

char fbook[]={"book.dat"};
char fbill[] = {"bill.dat"};

int main()
{
    FILE *fp;
    int ch;

    system("clear");

    while(1)
    {
    system("clear"); //clrscr();

    printf("==================Online Shopping (Books)=============\n\n");

    printf("1. Manage Book Catalog\n\n");
    printf("2. Search for book\n\n");
    printf("3. Purchase Book\n\n");
    printf("0. Exit\n\n");

    printf("========================================================\n\n");

    printf("\nPlease enter your Choice:");
    scanf("%d",&ch);

    switch(ch)
    {
    case 1: manageBooks();
    break;

    case 2: search();
    break;

    case 3: purchaseBook();
    break;

    case 4: payment();
    break;

    case 0: exit(0);
    }

    mygetch();
    }

    return 0;
    }
    int getID()
    {
        FILE *fp;
        int value = 0;
        fp = fopen("prodid.txt", "r");

        if(fp == NULL)
        {
            fp = fopen("prodid.txt", "w");
            fprintf(fp, "%d", 0);
            fclose(fp);
            fp = fopen("prodid.txt", "r");
        }

        fscanf(fp, "%d", &value);

        fclose(fp);

        fp = fopen("prodid.txt", "w");
        fprintf(fp, "%d", value+1);
        fclose(fp);

        return value + 1;
    }

    void manageBooks()
    {
        int ch;
        int back = 0;
        while(1)
        {
            system("clear"); //clrscr();

            printf("========================================================\n\n");

            printf("==================Online Shopping (Books)=============\n\n");

            printf("========================================================\n\n");

            printf("1. Add New Book\n\n");
            printf("2. Display All Books\n\n");

            printf("3. Delete a Book\n\n");

            printf("0. Back \n\n");

            printf("========================================================\n\n");

            printf("Please enter your choice:");
            scanf("%d", &ch);

            switch(ch)
            {
                case 1: addBook();
                break;

                case 2: displayAllBooks();
                break;

                case 3: deleteBook();
                break;

                case 0: back=1;
                        break;
            }
            if(back==1)
            {
                break;
            }
            else{
                mygetch();
            }

        }
    }
    void addBook()
    {
    FILE *fp;
    struct Book t1;

    fp=fopen(fbook,"ab");

    t1.id = getID();

    printf("\nEnter Book Name:");
    scanf("%s",&t1.name);
    printf("\nEnter book price:");
    scanf("%d",&t1.price);
    printf("\nEnter number of books:");
    scanf("%d",&t1.qty);
    fwrite(&t1,sizeof(t1),1,fp);

    fclose(fp);
    }

    

    void deleteBook()
    {
    FILE *fp,*fp1;
    struct Book t,t1;
    int id,found=0,count=0;

    fp=fopen(fbook,"rb");
    fp1=fopen("temp.dat","wb");

    printf("\nEnter the BookID of the book you want to Delete:");
    scanf("%d",&id);

    while(1)
    {
    fread(&t,sizeof(t),1,fp);

    if(feof(fp))
    {
    break;
    }
    if(t.id==id)
    {
    found=1;
    }
    else
    {
    fwrite(&t,sizeof(t),1,fp1);
    }
    }
    fclose(fp);
    fclose(fp1);

    if(found==0)
    {
    printf("Sorry No Record Found\n\n");
    }
    else
    {
    fp=fopen(fbook,"wb");
    fp1=fopen("temp.dat","rb");

    while(1)
    {
    fread(&t,sizeof(t),1,fp1);

    if(feof(fp1))
    {
    break;
    }
    fwrite(&t,sizeof(t),1,fp);
    }
    }
    fclose(fp);
    fclose(fp1);
    }

    void search()
    {
    FILE *fp;
    struct Book t;
    int found=0;
    char name[20];

    fp=fopen(fbook,"rb");

    printf("\nEnter the name of the book:");
    scanf("%s",&name);

    while(1)
    {
    fread(&t,sizeof(t),1,fp);

    if(feof(fp))
    {
    break;
    }
    if(strcmp(name,t.name)==0)
    {
    printf("\n========================================================\n\n");
    printf("\t\t Book Details %d\n\n",t.id);
    printf("========================================================\n\n");

    printf("Name\tPrice\n\n");

    printf("%s\t",t.name);
    printf("%d\t\n\n",t.price);

    printf("========================================================\n\n");

    }
    }
    if(found==0)
    {
    printf("\nSorry No Record Found");
    }
    fclose(fp);
    }
    void displayAllBooks()
    {
    FILE *fp;
    struct Book t;

    system("clear");

    fp=fopen(fbook,"rb");

    printf("\n========================================================\n\n");
    printf("\t\t All Books\n\n");
    printf("========================================================\n\n");

    printf("ID\tName\tQuantity\tPrice\n\n");

    while(1)
        {
        fread(&t,sizeof(t),1,fp);

        if(feof(fp))
        {
            break;
        }
        printf("%d\t",t.id);
        printf("%s\t",t.name);
        printf("%d\t",t.qty);
        printf("%d\t\n\n",t.price);

        }
        printf("========================================================\n\n");

        fclose(fp);
    }

    char mygetch()
    {
        char val;
        char rel;

        scanf("%c",&val);
        scanf("%c",&rel);
        return (val);
    }
    void purchaseBook(){
        char ch1,ch2;
        int id;
        system("clear");
        printf("========================================================\n\n");

        printf("\t\t Welcome to the Online Book Shop\n\n");

        printf("========================================================\n\n");

        while (1)
        {
            displayAllBooks();
            __fpurge(stdin);

            printf("\n\n\n Do you want to purchase [Y/N]:");
            scanf("%c", &ch1);

            if(ch1=='Y'){
                FILE *fp;
                struct Bill t1;
                struct Book t2;

                fp = fopen(fbill, "ab");

                printf("\n\nEnter the Book ID to Purchase:");
                scanf("%d", &id);

                t2 = findBook(id);

                t1.pid = t2.id;
                strcpy(t1.pname, t2.name);
                t1.pprice = t2.price;

                fwrite(&t1, sizeof(t1),1, fp);

                fclose(fp);
            }
            __fpurge(stdin);
            printf("\n\nDo you want to continue [Y/N]:");
            scanf("%c", &ch2);

            if(ch2 == 'N')
            {
                break;
            }
            mygetch();
        }
        


    }

    struct Book findBook(int id){
        FILE *fp;
        struct Book t;

        fp = fopen(fbook, "rb");

        while(1)
        {
            fread(&t,sizeof(t), 1, fp);
            if(feof(fp))
            {
                break;
            }

            if(t.id == id)
            {
                updateBook(id,t.qty-1);
                break;
            }
        }
        fclose(fp);
        return t;
    }

    void updateBook(int id, int qty)
    {
        FILE *fp, *fp1;
        struct Book t, t1;
        int found = 0;

        fp = fopen(fbook, "rb");
        fp1 = fopen("temp.dat", "wb");

        while(1)
        {
            fread(&t, sizeof(t),1,fp);

            if(feof(fp))
            {
                break;
            }

            if(t.id==id)
            {
                found = 1;
                t.qty = qty;
                fwrite(&t, sizeof(t),1, fp1);
            }
            else
            {
                fwrite(&t, sizeof(t),1,fp1);
            }
        }
        fclose(fp);
        fclose(fp1);

        if(found == 0)
        {
            printf("Sorry no record found\n\n");
        }
        else
        {
            fp = fopen(fbook, "wb");
            fp1 = fopen("temp.dat", "rb");

            while(1)
            {
                fread(&t, sizeof(t), 1, fp1);

                if(feof(fp1))
                {
                    break;
                }

                fwrite(&t, sizeof(t), 1, fp);

            }
        }
        fclose(fp);
        fclose(fp1);
    }

    void payment()
    {
        FILE *fp, *fp1;
        struct Bill t;
        int id, total, found = 0;
        char ch1;
        int brel = 0;
        char billname[20];

        system("clear");

        fp = fopen(fbill, "rb");

        printf("========================================================\n\n");
        printf("\t\t Amount Payable\n\n");
        printf("========================================================\n\n");

        printf("Pro-ID \tPro-Name\tPro-Price \n\n");

        while(1)
        {
            fread(&t, sizeof(t), 1, fp);

            if(feof(fp))
            {
                break;
            }
            printf("%d\t", t.pid);
            printf("%s\t", t.pname);
            printf("%d\t\t\t\n", t.pprice);
            total = total + t.pprice;
        }

        printf("\n\n======================>>>>>>>>>Total Bill Amount [Rs: %d]\n\n", total);

        fclose(fp);

        if(total!=0)
        {
            __fpurge(stdin);

            printf("\n\n\n Do you want to generate Final Bill [Y/N] :");
            scanf("%c", &ch1);

            if(ch1 == 'Y')
            {
                brel = billFileNo();
                sprintf(billname, "%s%d","",brel);
                strcat(billname, ".dat");

                fp = fopen(fbill, "rb");
                fp1 = fopen(billname, "wb");

                while(1)
                {
                    fread(&t, sizeof(t), 1, fp);

                    if(feof(fp))
                    {
                        break;
                    }
                    fwrite(&t, sizeof(t), 1, fp1);

                }
                fclose(fp);
                fclose(fp1);

                fp = fopen(fbill, "wb");
                fclose(fp);
                total = 0;
            }
        }
        else
        {
            printf("\n\n Sorry item selected \n\n");
        }

    }

    int billFileNo ()
    {
        FILE *fp;
        int value = 0;
        fp = fopen("billno.txt", "r");

        if(fp == NULL)
        {
            fp = fopen("billno.txt", "w");
            fprintf(fp, "%d", 0);
            fclose(fp);
            fp = fopen("billno.txt", "r");
        }

        fscanf(fp, "%d", &value);

        fclose(fp);

        fp = fopen("billno.txt", "w");
        fprintf(fp, "%d", value+1);
        fclose(fp);

        return value + 1;
}