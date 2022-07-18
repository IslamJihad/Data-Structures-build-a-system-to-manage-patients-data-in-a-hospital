/*
ISLAM JIHAD JOMA
     1191375
     SEC 3
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Original code provided by the author Mark Allen Wiess.
//Modified by Dr. Radi Jarrar
typedef struct AVLnode *AVLNode;


//struct node for VL Node
struct AVLnode
{
    char name[30];
    char gender[2];
    char dateofAdmission[9];
    char dateofBirth[9];
    char illness[30];
    char address[20];
    char Blood[2];

    AVLNode Left;
    AVLNode Right;
    int Height; //Balance information
};

// 2 global intgers to know when to rehash and the array size
int SIZE=13;
int COUNTER=0;
typedef struct hashnode *hashTable;
struct hashnode
{
    int status;
    char name[30];
    char gender[2];
    char dateofAdmission[9];
    char dateofBirth[9];
    char illness[30];
    char address[20];
    char Blood[2];

};
//array of nodes
hashTable ar[13];




// those functions for AVL tree nose to add delete and edit etc..
AVLNode MakeEmpty( AVLNode T )
{
    if( T != NULL )
    {
        MakeEmpty( T->Left );
        MakeEmpty( T->Right );
        free( T );
    }
    return NULL;
}

// debends on name
AVLNode Find( char name[], AVLNode T )
{
    int r=strcmp(name,T->name);

    if( T == NULL )
        return NULL;
    if( r<0 )
        return Find( name, T->Left );
    else if( r>0 )
        return Find( name, T->Right );
    else
        return T;
}

AVLNode FindMin( AVLNode T )
{
    if( T == NULL )
        return NULL;
    else if( T->Left == NULL )
        return T;
    else
        return FindMin( T->Left );
}

AVLNode FindMax( AVLNode T )
{
    if( T != NULL )
        while( T->Right != NULL )
            T = T->Right;

    return T;
}

//to find the hight for balance
int Height( AVLNode P )
{
    if( P == NULL )
        return -1;
    else
        return P->Height;
}
/* END */

int Max( int Lhs, int Rhs )
{
    return Lhs > Rhs ? Lhs : Rhs;
}

/* START: fig4_39.txt */
/* This function can be called only if K2 has a left child */
/* Perform a rotate between a node (K2) and its left child */
/* Update heights, then return new root */

AVLNode SingleRotateWithLeft( AVLNode K2 )
{
    AVLNode  K1;

    K1 = K2->Left;
    K2->Left = K1->Right;
    K1->Right = K2;

    K2->Height = Max( Height( K2->Left ), Height( K2->Right ) ) + 1;
    K1->Height = Max( Height( K1->Left ), K2->Height ) + 1;

    return K1;  /* New root */
}


/* This function can be called only if K1 has a right child */
/* Perform a rotate between a node (K1) and its right child */
/* Update heights, then return new root */

AVLNode SingleRotateWithRight( AVLNode K1 )
{
    AVLNode K2;

    K2 = K1->Right;
    K1->Right = K2->Left;
    K2->Left = K1;

    K1->Height = Max( Height( K1->Left ), Height( K1->Right ) ) + 1;
    K2->Height = Max( Height( K2->Right ), K1->Height ) + 1;

    return K2;  /* New root */
}

/* START: fig4_41.txt */
/* This function can be called only if K3 has a left */
/* child and K3's left child has a right child */
/* Do the left-right double rotation */
/* Update heights, then return new root */

AVLNode DoubleRotateWithLeft( AVLNode K3 )
{
    /* Rotate between K1 and K2 */
    K3->Left = SingleRotateWithRight( K3->Left );

    /* Rotate between K3 and K2 */
    return SingleRotateWithLeft( K3 );
}
/* END */

/* This function can be called only if K1 has a right */
/* child and K1's right child has a left child */
/* Do the right-left double rotation */
/* Update heights, then return new root */

AVLNode DoubleRotateWithRight( AVLNode K1 )
{
    /* Rotate between K3 and K2 */
    K1->Right = SingleRotateWithLeft( K1->Right );

    /* Rotate between K1 and K2 */
    return SingleRotateWithRight( K1 );
}


// this function insert all the patunt data into AVL Tree aand make balance to know where to put it
AVLNode Insert( char Name[], char Gender[], char DateofAdmission[], char DateofBirth[], char Illness[], char Address[], char BloodT[], AVLNode T )
{

    if( T == NULL )
    {

        /* Create and return a one-node tree */
        T = malloc( sizeof( struct AVLnode ) );
        if( T == NULL )
            printf( "Out of space!!!" );
        else
        {
            strcpy(T->name, Name);
            strcpy(T->gender, Gender);
            strcpy(T->dateofAdmission, DateofAdmission);
            strcpy(T->dateofBirth, DateofBirth);
            strcpy(T->illness, Illness);
            strcpy(T->address, Address);
            strcpy(T->Blood, BloodT);


            T->Height = 0;
            T->Left =NULL;
            T->Right = NULL;
        }
    }

    else if( strcmp(Name,T->name)<0 )
    {
        T->Left = Insert( Name,  Gender,  DateofAdmission,  DateofBirth,  Illness,  Address,  BloodT, T->Left );
        if( Height( T->Left ) - Height( T->Right ) == 2 )
            if( strcmp(Name, T->Left->name) <0 )
                T = SingleRotateWithLeft( T );
            else
                T = DoubleRotateWithLeft( T );
    }
    else if( strcmp(Name,T->name)>0 )
    {
        T->Right = Insert( Name,  Gender,  DateofAdmission,  DateofBirth,  Illness,  Address,  BloodT, T->Right );
        if( Height( T->Right ) - Height( T->Left ) == 2 )
            if( strcmp(Name, T->Right->name) >0 )
                T = SingleRotateWithRight( T );
            else
                T = DoubleRotateWithRight( T );
    }
    /* Else X is in the tree already; we'll do nothing */

    T->Height = Max( Height( T->Left ), Height( T->Right ) ) + 1;
    return T;
}
/* END */

//reed data from file and load it into AVL tree
AVLNode rFromFile(AVLNode tree)
{
    FILE* rfile = fopen("patients.txt", "r");


    char line[500];
    char temp[7][30];

    while (fgets(line, sizeof(line), rfile))
    {

        char * token = strtok(line, "#");

        for(int i=0; i<7; i++)
        {
            strcpy(temp[i],token);
            token = strtok(NULL, "#");
        }
        tree= Insert(temp[0], temp[1], temp[2], temp[3], temp[4], temp[5], temp[6], tree);
    }



    fclose(rfile);

    return tree;
}



//in-order print to see the elements
void PrintInOrder( AVLNode t)
{

    if( t != NULL)
    {
        PrintInOrder( t->Left );
        printf("*************************************************************************************\n");
        printf("NAME: %s\t", t->name);
        printf("GENDER: %s\t", t->gender);
        printf("DATE OF ADM: %s\t", t->dateofAdmission);
        printf("DATE OF BIR: %s\n", t->dateofBirth);
        printf("ILLNESS: %s\t", t->illness);
        printf("ADDRESS: %s\t",t->address);
        printf("BLOOD TYPE: %s\n", t->Blood);

        PrintInOrder( t->Right );
    }
}

// Get Balance for one node
int BalanceTree(AVLNode N)
{
    if (N == NULL)
        return 0;
    return Height(N->Left) - Height(N->Right);
}



//delete a node and it has 4 cases to make balance
AVLNode deleteNode(char Name[], AVLNode tree)
{
    // STEP 1: PERFORM STANDARD BST DELETE

    if (tree == NULL)
        return tree;

    // If the key to be deleted is smaller than the
    // tree's key, then it lies in left subtree
    if ( strcmp(Name, tree->name)<0 )
        tree->Left = deleteNode(Name, tree->Left);

    // If the key to be deleted is greater than the
    // tree's key, then it lies in right subtree
    else if( strcmp(Name, tree->name)>0 )
        tree->Right = deleteNode(Name, tree->Right);

    // if key is same as tree's key, then This is
    // the node to be deleted
    else
    {
        // node with only one child or no child
        if( (tree->Left == NULL) || (tree->Right == NULL) )
        {
            AVLNode temp = tree->Left ? tree->Left : tree->Right;

            // No child case
            if (temp == NULL)
            {
                temp = tree;
                tree = NULL;
            }
            else // One child case
                *tree = *temp; // Copy the contents of
            // the non-empty child
            free(temp);
        }
        else
        {
            // node with two children will Get the inorder
            AVLNode temp = FindMin(tree->Right);

            // Copy the inorder data to this node

            strcpy(tree->name, temp->name);
            strcpy(tree->gender, temp->gender);
            strcpy(tree->dateofAdmission, temp->dateofAdmission);
            strcpy(tree->dateofBirth, temp->dateofBirth);
            strcpy(tree->illness, temp->illness);
            strcpy(tree->address, temp->address);
            strcpy(tree->Blood, temp->Blood);

            // Delete the inorder node
            tree->Right = deleteNode(temp->name, tree->Right);
        }
    }

    if (tree == NULL)
        return tree;

    // update hight
    tree->Height = 1 + Max(Height(tree->Left), Height(tree->Right));

    // STEP 3: find the balance
    // check whether this node became unbalanced)
    int balance = BalanceTree(tree);

    // If this node becomes unbalanced, then there are 4 cases

    // Left rotate to left
    if (balance > 1 && BalanceTree(tree->Left) >= 0)
        return SingleRotateWithLeft(tree);

    // Left rotate (double rotate)
    if (balance > 1 && BalanceTree(tree->Left) < 0)
    {
        tree->Left = SingleRotateWithRight(tree->Left);
        return SingleRotateWithLeft(tree);
    }

    // Right rotate
    if (balance < -1 && BalanceTree(tree->Right) <= 0)
        return SingleRotateWithRight(tree);

    // Right rotate (double rotate)
    if (balance < -1 && BalanceTree(tree->Right) > 0)
    {
        tree->Right = SingleRotateWithLeft(tree->Right);
        return SingleRotateWithRight(tree);
    }

    return tree;
}

// insert a new patiant data into tree
AVLNode insertNew(AVLNode tree)
{
    char name[30];
    char gender[2];
    char dateofAdmission[9];
    char dateofBirth[9];
    char illness[30];
    char address[20];
    char Blood[2];
    printf("\nenter the name: ");
    scanf("%s",name);
    printf("\nenter the gender: ");
    scanf("%s",gender);
    printf("\nenter the date of Admission: ");
    scanf("%s",dateofAdmission);
    printf("\nenter the date of Birth: ");
    scanf("%s",dateofBirth);
    printf("\nenter the illness: ");
    scanf("%s",illness);
    printf("\nenter the address: ");
    scanf("%s",address);
    printf("\nenter the Blood Type: ");
    scanf("%s",Blood);

    tree= Insert( name,  gender,  dateofAdmission,  dateofBirth,  illness,  address,  Blood, tree );
    return tree;
}

//search for the node by name and make changes into the node by delete andre add it to keep balance
AVLNode edit(AVLNode tree)
{
    printf("write the full name of the patient you want to edit info of: ");
    char nm[30];
    int x;
    scanf("%s", nm);
    AVLNode temp=NULL;
    temp= Find(nm, tree);

    if(temp==NULL)
    {
        printf("the patient is not found\n");
    }
    else
    {
        char name[30];
        char gender[2];
        char dateofAdmission[9];
        char dateofBirth[9];
        char illness[30];
        char address[20];
        char Blood[2];

        strcpy(name, temp->name);
        strcpy(gender, temp->gender);
        strcpy(dateofAdmission, temp->dateofAdmission);
        strcpy(dateofBirth, temp->dateofBirth);
        strcpy(illness, temp->illness);
        strcpy(address, temp->address);
        strcpy(Blood, temp->Blood);

        tree= deleteNode(name, tree);

        tree= Insert( name, gender, dateofAdmission, dateofBirth, illness, address, Blood, tree );

        AVLNode temp2= Find(nm,tree);
        printf("%s\n",temp2->name);

        printf("choose what to edit for the patient\n");
        printf("1-Name\t2-Gender\t3-Date of admission\t4-Date of birth\t5-Illness\t6-Address\t7-Blood type\n");
        scanf("%d",&x);
        printf("the new data is: ");
        scanf("%s", nm);
        switch(x)
        {
        case 1:
            strcpy(temp->name, nm);
            break;
        case 2:
            strcpy(temp->gender, nm);
            break;
        case 3:
            strcpy(temp->dateofAdmission, nm);
            break;
        case 4:
            strcpy(temp->dateofBirth, nm);
            break;
        case 5:
            strcpy(temp->illness, nm);
            break;
        case 6:
            strcpy(temp->address, nm);
            break;
        case 7:
            strcpy(temp->Blood, nm);
            break;
        }
        printf("\ndata have been modified successfully\n");
    }

    return tree;
}

// print all patiunt who have the same illness( search by illness
void SameIllness(char illness[], AVLNode t)
{
    if( t != NULL)
    {
        SameIllness(illness, t->Left );
        if(strcmp(illness, t->illness)==0)
        {
            printf("*************************************************************************************\n");
            printf("NAME: %s\t", t->name);
            printf("GENDER: %s\t", t->gender);
            printf("DATE OF ADM: %s\t", t->dateofAdmission);
            printf("DATE OF BIR: %s\n", t->dateofBirth);
            printf("ILLNESS: %s\t", t->illness);
            printf("ADDRESS: %s\t",t->address);
            printf("BLOOD TYPE: %s\n", t->Blood);
        }
        SameIllness(illness, t->Right );
    }
}

// this print the data into patients_hash.data file in order so the hash function can read and edit it
void printInTheFile(FILE* w, AVLNode t)
{


    if( t != NULL)
    {
        printInTheFile( w, t->Left );
        fprintf(w, "%s#", t->name);
        fprintf(w, "%s#", t->gender);
        fprintf(w, "%s#", t->dateofAdmission);
        fprintf(w, "%s#", t->dateofBirth);
        fprintf(w, "%s#", t->illness);
        fprintf(w, "%s#",t->address);
        fprintf(w, "%s", t->Blood);

        printInTheFile( w, t->Right );
    }

}

























//check if the number is prime or not
int prime(int n)
{
    int i;
    for(i=2; i<=n/2; i++)
    {
        if(n%i!=0)
            continue;
        else
            return 1;
    }
    return 0;
}

//return the new size for array which must be the first prime number> 2*old size
int getTSize(int oldSize)
{
    int check= oldSize*2;
    int newSize;
    while(prime(check)==1)
    {

        check++;
    }
    newSize=check;
    return newSize;
}

//return the index where the data must be inserted in the array by hashing
int getIndex(char name[])
{
    int index=0;
    int i=0;

    int number=0;

    if(strlen(name)>2)
    {
        for(int i=0; i<3; i++)
        {
            number = ( number << 5 ) + *name++;
        }
    }
    else if(strlen(name)==2)
    {
        for(int i=0; i<2; i++)
        {
            number = ( number << 5 ) + *name++;
        }
    }
    else
    {
        number=  name[0];
    }



    while(i<SIZE)
    {
        index= ((number + (i*i)) % SIZE);
        if(ar[index]->status==0)
        {
            break;
        }
        i++;
    }
    return index;
}

//insert a new patiunt into the hash table
void insert()
{



    int index;
    char name[15];
    char gender[2];
    char dateofAdmission[9];
    char dateofBirth[9];
    char illness[30];
    char address[20];
    char Blood[2];

    printf("\nenter the name: ");
    scanf("%s",name);
    printf("\nenter the gender: ");
    scanf("%s",gender);
    printf("\nenter the date of Admission: ");
    scanf("%s",dateofAdmission);
    printf("\nenter the date of Birth: ");
    scanf("%s",dateofBirth);
    printf("\nenter the illness: ");
    scanf("%s",illness);
    printf("\nenter the address: ");
    scanf("%s",address);
    printf("\nenter the Blood Type: ");
    scanf("%s",Blood);

    index = getIndex(name);

    strcpy(ar[index]->name, name);
    strcpy(ar[index]->gender, gender);
    strcpy(ar[index]->dateofAdmission, dateofAdmission);
    strcpy(ar[index]->dateofBirth, dateofBirth);
    strcpy(ar[index]->illness, illness);
    strcpy(ar[index]->address, address);
    strcpy(ar[index]->Blood, Blood);
    printf("\n added successfuly\n");

    ar[index]->status=1;
    COUNTER++;

    // check if the data are more than the half of the array to make a rehash
    if(COUNTER>=(SIZE/2) )
    {
        reHash();

    }


}


// the ssame for get index function but I made it to
//accept the new created array to insert on it instide the global one
int getIndexForAuto(int name[], hashTable arr[])
{
    int index;
    int i=0;

    int number=0;

    if(strlen(name)>2)
    {
        for(int i=0; i<3; i++)
        {
            number = ( number << 5 ) + *name++;
        }
    }
    else if(strlen(name)==2)
    {
        for(int i=0; i<2; i++)
        {
            number = ( number << 5 ) + *name++;
        }
    }
    else
    {
        number=  name[0];
    }



    while(i<SIZE)
    {
        index= ((number + (i*i)) % SIZE);
        if(arr[index]->status==0)
        {
            break;
        }
        i++;
    }



    return index;
}

// the same for insert function ut without asking the user to make input
//becouse it reades from file
void Autoinsert(char name[], char gender[], char dateofAdmission[], char dateofBirth[], char illness[], char address[], char Blood[], hashTable arr[])
{
    int index;
    index = getIndexForAuto(name, arr);


    strcpy(arr[index]->name, name);
    strcpy(arr[index]->gender, gender);
    strcpy(arr[index]->dateofAdmission, dateofAdmission);
    strcpy(arr[index]->dateofBirth, dateofBirth);
    strcpy(arr[index]->illness, illness);
    strcpy(arr[index]->address, address);
    strcpy(arr[index]->Blood, Blood);
    arr[index]->status=1;

}

//this function make a new array and move the data into it
// then free the old array and  malloc it again and re enter the data into it
// so we get the old array rehashed and working fine
void reHash()
{
    int oldSize= SIZE;
    SIZE= getTSize(SIZE);
    hashTable newH[SIZE];

    //the nestid loop it to make the array of characters empty=NULL
    for(int i=0; i<SIZE; i++)
    {
        newH[i]= (hashTable)malloc( sizeof( struct hashnode ));
        newH[i]->status=0;
        for(int j=0; j<30; j++)
        {
            newH[i]->name[j]=NULL;
            newH[i]->illness[j]=NULL;
        }
        for(int j=0; j<9; j++)
        {
            newH[i]->dateofAdmission[j]=NULL;
            newH[i]->dateofBirth[j]=NULL;
        }
        for(int j=0; j<2; j++)
        {
            newH[i]->gender[j]=NULL;
            newH[i]->Blood[j]=NULL;
        }
        for(int j=0; j<20; j++)
        {
            newH[i]->address[j]=NULL;
        }
    }



    for(int i=0; i<oldSize; i++)
    {
        if(ar[i]->status ==1)
        {
            Autoinsert(ar[i]->name, ar[i]->gender, ar[i]->dateofAdmission, ar[i]->dateofBirth, ar[i]->illness, ar[i]->address, ar[i]->Blood, newH);

        }
        free(ar[i]);
    }

    for(int i=0; i<SIZE; i++)
    {
        ar[i]= (hashTable)malloc( sizeof( struct hashnode ));
        ar[i]->status=0;
        for(int j=0; j<30; j++)
        {
            ar[i]->name[j]=NULL;
            ar[i]->illness[j]=NULL;
        }
        for(int j=0; j<9; j++)
        {
            ar[i]->dateofAdmission[j]=NULL;
            ar[i]->dateofBirth[j]=NULL;
        }
        for(int j=0; j<2; j++)
        {
            ar[i]->gender[j]=NULL;
            ar[i]->Blood[j]=NULL;
        }
        for(int j=0; j<20; j++)
        {
            ar[i]->address[j]=NULL;
        }

    }

    for(int i=0; i<SIZE; i++)
    {
        strcpy(ar[i]->name, newH[i]->name);
        strcpy(ar[i]->gender, newH[i]->gender);
        strcpy(ar[i]->dateofAdmission, newH[i]->dateofAdmission);
        strcpy(ar[i]->dateofBirth, newH[i]->dateofBirth);
        strcpy(ar[i]->illness, newH[i]->illness);
        strcpy(ar[i]->address, newH[i]->address);
        strcpy(ar[i]->Blood, newH[i]->Blood);
        ar[i]->status=newH[i]->status;
        free(newH[i]);
    }

}

//print the information of all pationt from the hashed arry
void printHash()
{
    for(int i=0; i<SIZE; i++)
    {
        if(ar[i]->status==1)
        {
            printf("*************************************************************************************\n");
            printf("\nthe index[%d] contain: \nname: %s\tgender: %s\t date of Admission: %s\t date of Birth: %s\t illness: %s\t address: %s\t Blood: %s\n", i, ar[i]->name, ar[i]->gender, ar[i]->dateofAdmission, ar[i]->dateofBirth, ar[i]->illness, ar[i]->address, ar[i]->Blood);
        }
    }
}

//search by name and show the index that contain the data for the mentioned patiunt
void SearchFor()
{
    char x[30];
    printf("enter the number you want to search for: ");
    scanf("%s",x);
    for(int i=0; i< SIZE; i++)
    {
        if((strcmp(x, ar[i]->name)==0) && (ar[i]->status==1))
        {
            printf("\nthe index [%d] is contaning the data for this name\n", i);
            break;
        }
    }

}

//delete the index from data to make it avilable for another inputs
void deleteHash()
{
    char x[30];
    printf("enter the name you want to delete data for: ");
    scanf("%s",x);

    for(int i=0; i< SIZE; i++)
    {
        if((strcmp(x, ar[i]->name)==0) && (ar[i]->status==1))
        {
            ar[i]->status=0;

            for(int j=0; j<30; j++)
            {
                ar[i]->name[j]=NULL;
                ar[i]->illness[j]=NULL;

            }
            for(int j=0; j<9; j++)
            {
                ar[i]->dateofAdmission[j]=NULL;
                ar[i]->dateofBirth[j]=NULL;
            }

            for(int j=0; j<2; j++)
            {
                ar[i]->gender[j]=NULL;
                ar[i]->Blood[j]=NULL;
            }

            for(int j=0; j<20; j++)
            {
                ar[i]->address[j]=NULL;
            }
            // free the index
            free(ar[i]);
            printf("\nthe number & cell are deleted\n");
            break;
        }
    }
    COUNTER--;
}

//insert the data into the index without asking the user to wrrite them
// becouse the data are wrote in the file
void FileInsert(char name[], char gender[], char dateofAdmission[], char dateofBirth[], char illness[], char address[], char Blood[])
{



    int index;
    index = getIndex(name);
    strcpy(ar[index]->name, name);
    strcpy(ar[index]->gender, gender);
    strcpy(ar[index]->dateofAdmission, dateofAdmission);
    strcpy(ar[index]->dateofBirth, dateofBirth);
    strcpy(ar[index]->illness, illness);
    strcpy(ar[index]->address, address);
    strcpy(ar[index]->Blood, Blood);
    ar[index]->status=1;
    COUNTER++;
    // check to make rehash or not
    if(COUNTER>=(SIZE/2) )
    {
        reHash();

    }


}

//read from  file and devide the line and send the data to FileInsert to insert it into hash array
void rHashFile()
{
    FILE* rfile = fopen("patients_hash.data", "r");


    char line[500];
    char temp[7][30];

    while (fgets(line, sizeof(line), rfile))
    {


        char * token = strtok(line, "#");

        for(int i=0; i<7 ; i++)
        {
            strcpy(temp[i],token);
            token = strtok(NULL, "#");
        }
        FileInsert(temp[0], temp[1], temp[2], temp[3], temp[4], temp[5], temp[6]);


    }

    fclose(rfile);


}

// print the data in the array into file
void printHashFile()
{
    FILE* w=fopen("patients_hash.data", "w");
    for(int i=0; i<SIZE; i++)
    {
        if(ar[i]->status==1)
            fprintf(w, "%s#%s#%s#%s#%s#%s#%s\n", ar[i]->name, ar[i]->gender, ar[i]->dateofAdmission, ar[i]->dateofBirth, ar[i]->illness, ar[i]->address, ar[i]->Blood);
    }
    fclose(w);
}


//show the list of the hash function
void hashlist()
{

    // malloc the array
    for(int i=0; i<SIZE; i++)
    {
        ar[i]= (hashTable)malloc( sizeof( struct hashnode ));
        ar[i]->status=0;
        for(int j=0; j<30; j++)
        {
            ar[i]->name[j]=NULL;
            ar[i]->illness[j]=NULL;
        }

        for(int j=0; j<9; j++)
        {
            ar[i]->dateofAdmission[j]=NULL;
            ar[i]->dateofBirth[j]=NULL;
        }

        for(int j=0; j<2; j++)
        {
            ar[i]->gender[j]=NULL;
            ar[i]->Blood[j]=NULL;
        }

        for(int j=0; j<20; j++)
        {
            ar[i]->address[j]=NULL;
        }
    }



    rHashFile();
    printf("hi");
    // show the list
    int z;
    printf("\n1-insert\t 2-print\t3-show table size\t4-Print used hash function\n5-Search for a specific patient\t 6-delete\t7-print in file\n");
    scanf("%d",&z);
    while(1)
    {
        if(z==1)
        {
            insert();
        }
        else if(z==2)
        {
            printHash();
        }
        else if(z==3)
        {
            printf("the size = %d", SIZE);
        }
        else if(z==4)
        {
            printf("the used hash function: Quadratic Hashing ---> h(x) = (function + i*i) %% size\n");
        }
        else if(z==5)
        {
            SearchFor();
        }
        else if(z==6)
        {
            deleteHash();
        }
        else if(z==7)
        {
            printHashFile();
            printf("data printed on file\n");
        }
        printf("\n1-insert\t 2-print\t3-show table size\t4-Print used hash function\n5-Search for a specific patient\t 6-delete \t7-print in file\n");
        scanf("%d",&z);
    }






}



int main()
{

    AVLNode tree=NULL;
    tree = MakeEmpty( tree );
    char del[30];
    char ill[30];

    int x;
    printf("\n1-Read the file (patients.txt) and load the data \n2-Insert a new patient from user with all its associated data\n");
    printf("3-Find a patient and give the user the option to update the information of the patient if found \n4-List all patients in lexicographic order with their associated information\n");
    printf("5-List all patients that have the same illness\n6-Delete a patient from the system\n7-Save all words in file (patients_hash.data)\n");
    printf("\nchoose the number of the operation: ");

    while(1)
    {
        scanf("%d",&x);
        if(x==1)
        {
            tree = rFromFile(tree);
            printf("data are loaded from file into AVL TREE\n");
        }
        else if(x==2)
        {
            tree= insertNew(tree);
            printf("a new patient is Inserted\n");
        }
        else if(x==3)
        {
            tree= edit(tree);
        }
        else if(x==4)
        {
            PrintInOrder(tree);
        }
        else if(x==5)
        {
            printf("enter the illness name: ");
            scanf("%s",ill);
            SameIllness(ill, tree);
        }
        else if(x==6)
        {
            printf("\nenter the name of the patient you want to delete: ");
            scanf("%s",del);
            deleteNode(del,tree);
            printf("\ndeletion done succesfully\n");
        }
        else if(x==7)
        {

            FILE* w=fopen("patients_hash.data", "w");
            printInTheFile(w, tree);
            fclose(w);
            printf("Data have been svaed successfully in 'patients_hash.data' file\n");
            hashlist();

        }
        else
        {
            printf("\nthe number is out of range\n");
        }

        printf("\n1-Read the file (patients.txt) and load the data \n2-Insert a new patient from user with all its associated data\n");
        printf("3-Find a patient and give the user the option to update the information of the patient if found \n4-List all patients in lexicographic order with their associated information\n");
        printf("5-List all patients that have the same illness\n6-Delete a patient from the system\n7-Save all words in file (patients_hash.data)\n");
        printf("\nchoose the number of the operation: ");


    }



    return 0;
}





