//Library Management System including following data
/*
 Fine, Date of Issue, Date of Return, Book ID, Book Holder

*************************->->->  DATA STRUCTURE USED : AVL TREE  <-<-<-*************************************
*/
#include <bits/stdc++.h>

using namespace std;




struct Book
{
    Book* left;
    Book* right;
    string date_of_issue;
    string book_holder;
    int book_id;
    int height;
};


//Functions Used

Book* newBook(string doi, string bh, int id);
int getHeight (Book* node);
int getBalance (Book* node);
Book* left_rotate(Book* node);
Book* right_rotate(Book* node);
Book* insertNode(Book* node, string doi, string bh, int id);
Book* InorderSuccessor(Book* node);
Book* deleteNode(Book* node);
void copy_node(Book* root, Book* temp);
int calculate_fine(Book* node, string dor);


Book* newBook(string doi, string bh, int id)
{
    Book* nBook = new Book;
    nBook->left=nBook->right=NULL;
    nBook->date_of_issue = doi;
    nBook->book_holder = bh;
    nBook->book_id = id;

    return nBook;
}

int getHeight (Book* node)
{
    if(node==NULL)
        return 0;
    return node->height;
}

int getBalance (Book* node)
{
    if(node==NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

void copy_node(Book* root, Book* temp)
{
    root->date_of_issue = temp->date_of_issue;
    root->book_holder = temp->book_holder;
    root->book_id = temp->book_id;
}

Book* left_rotate(Book* z)
{
    Book* y = z->right;
    Book* T2 = y->left;

    y->left = z;
    z->right = T2;

    y->height = max(getHeight(y->left),getHeight(y->right));
    z->height = max(getHeight(z->left),getHeight(z->right));

    return y;
}

Book* right_rotate(Book* z)
{
    Book* y = z->left;
    Book* T3 = y->right;

    y->right = z;
    z->left = T3;

    y->height = max(getHeight(y->left),getHeight(y->right));
    z->height = max(getHeight(z->left),getHeight(z->right));
    return y;
}

Book* insertNode(Book* root, string doi, string bh, int id)
{
    if(root==NULL)
    {
        return newBook(doi,bh,id);
    }

    if(id<root->book_id)
        root->left = insertNode(root->left,doi,bh,id);
    else if(id>root->book_id)
    {
        root->right = insertNode(root->right,doi,bh,id);
    }
    else
        return root;

    root->height = 1 + max(getHeight(root->left),getHeight(root->right));

    int balance = getBalance(root);

    if( balance>1 && id < root->book_id )
        return left_rotate(root);

    if( balance<-1 && id>root->book_id )
        return right_rotate(root);

    if(balance>1 && id>root->book_id)
       {
           root->left = left_rotate(root->left);
           return right_rotate(root);
       }

    if(balance<-1 && id< root->book_id)
    {
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }

    return root;
}

Book* InorderSuccessor(Book* node)
{
    Book* current = node;

    while(current->left)
        current=current->left;

    return current;
}

Book* deleteNode(Book* root, int id)
{
    if(root==NULL)
        return root;

    if(id<root->book_id)
        root->left = deleteNode(root->left,id);
    else if(id>root->book_id)
        root->right = deleteNode(root->right,id);
    else
    {
        if(root->left==NULL || root->right==NULL)
        {
            Book* temp = root->left==NULL ? root->right : root->left;

            if(temp==NULL)
            {
                temp = root;
                root = NULL;
            }
            else
            {
                copy_node(root,temp);
                delete(temp);
            }
        }
        else
        {
            Book* temp = InorderSuccessor(root->right);
            copy_node(root,temp);
            root->right = deleteNode(root->right,temp->book_id);
        }
    }

    if(root==NULL)
    {
        return root;
    }

    root->height = 1 + max(getHeight(root->left),getHeight(root->right));

    int balance = getBalance(root);

    if (balance > 1 &&
        getBalance(root->left) >= 0)
        return right_rotate(root);


    if (balance > 1 &&
        getBalance(root->left) < 0)
    {
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }


    if (balance < -1 &&
        getBalance(root->right) <= 0)
        return left_rotate(root);


    if (balance < -1 &&
        getBalance(root->right) > 0)
    {
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }

    return root;

}

int calculate_fine(string dor,string exp)
{
    int d1 = atoi(exp.substr(0,2));
    int m1 = atoi(exp.substr(3,2));
    int y1 = atoi(exp.substr(6,4));
    int d2 = atoi(dor.substr(0,2));
    int m2 = atoi(dor.substr(3,2));
    int y2 = atoi(dor.substr(6,4));
    int fine = 0;

      if(y2-y1<0)
        fine=0;
    else if(y2-y1>0)
        fine=10000;
    else if(m2-m1<0)
        fine=0;
    else if(m2-m1>0)
        fine=500*(m2-m1);
    else if(actual[0]-expected[0]>0)
        fine=15*(d2-d1);
    else
        fine=0;

    return 0;

}

int main()
{
    system("color 65");
    cout<<endl<<endl;
    Book* root=NULL;
    for(int i=0;i<120;i++)
        cout<<"*";
    cout<<endl<<endl;
    cout<<"\t\t\t\t\tLIBRARY DATABASE...\n\n";
    cout<<"\t\t 1) ISSUE BOOK\n\n";
    cout<<"\t\t 2) RETURN BOOK\n\n";
    cout<<"\t\t 3) EXIT\n\n";


    cout<<"\n\n\n";
  X:  cout<<"Select your choice : ";
    int c;
    cin>>c;
    string bh,doi,dor,exp;
    int id;
    switch(c)
    {
        //.....................Dates should be entered in dd/mm/yyyy format...........................
        case 1: cout<<"\n\n\tEnter the name of BOOK HOLDER: ";

             cin>>bh;
             cout<<"\n\n\tEnter BOOK ID: ";
             cin>>id;
             cout<<"\n\n\tEnter date of issue: ";
             cin>>doi;
             insertNode(root,doi,bh,id);
             cout<<"\n\n\t\t\t...BOOK ISSUED SUCCESSFULLY...\n\n";
             goto X;
             break;
        case 2: cout<<"\n\n\tEnter the date of return : ";
             cin>>dor;
             cout<<"\n\n\tExpected date of return : ";
             cin>>exp;  // 30days after date of issue
             cout<<"\n\n\tEnter BOOK ID: ";
             cin>>id;
             cout<<"\n\n\tFine incurred is : "<<calculate_fine(dor,exp)<<"\n";
             deleteNode(root,id);
             cout<<"\n\n\tBook returned Successfully...\n\n";
             goto X;
             break;
        case 3: goto Y;
    }

    Y: return 0;

    return 0;
}


