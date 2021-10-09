#include <iostream>
#include <list>
#include <fstream>
#include <time.h>
#include <random>


#define Numstudent 50
#define LINKEDLIST_H

using namespace std;
//Creating the student nodes including the data of Mnumber, First name, and Last Name
class Node
{
public:
    string F_name, L_name;
    int Mnum;
    Node *next;
};
//The entire student list class
class LinkedList
{

private:
    int num_nodes = 0;

public:
    //initializing all the necessary nodes
    Node *head, *tail;
    Node *sorted;
    LinkedList()
    {
        head = nullptr;
        tail = nullptr;
    }
    //Creating and adding a new student to the list
    void addStudent(string F_name, string L_name, int Mnum)
    {
        Node *student = new Node();
        student->F_name = F_name;
        student->L_name = L_name;
        student->Mnum = Mnum;
        student->next = NULL;
        if (head == NULL)
        {
            head = student;
            tail = student;
        }
        else
        {
            tail->next = student;
            tail = tail->next;
        }
    }

    //Function used to display the final output
    void display()
    {
        Node *current = head;

        if (head == NULL)
        {
            cout << "No student's record uploaded yet!\n";
        }
        else
        {
            cout << "First name" << "  \t\t" << "  Last name" << ":\t\t" << "M number" << "\n";
            while (current != NULL)
            {
                cout << current->F_name << "      \t\t  " << current->L_name << ":  \t\tM" << current->Mnum << "\n";
                current = current->next;
            }
        }
    }
    //Knowing how many students there are in the list
    int getLength()
    {
        Node *current = head;
        while (current != NULL)
        {
            num_nodes++;
            current = current->next;
        }
        return num_nodes;
    }

    /*
        Utility function to insert back the sort node. However, we made this with the first node being filled in mind so might have some
        memory problem is head == NULL
     */
    void sortedInsert(Node *tempnote, int mode)
    {
        /* Special case for the head end */
        if (sorted == NULL || sorted->L_name >= tempnote->L_name)
        {
            tempnote->next = sorted;
            sorted = tempnote;
        }
        else
        {
            if (mode == 0)
            {
                Node *current = sorted;
                /* Locate the node before the point of insertion
                */
                while (current->next != NULL && current->next->L_name < tempnote->L_name)
                {
                    current = current->next;
                }
                tempnote->next = current->next;
                current->next = tempnote;
            }
            else
            {
                Node *current = sorted;
                while (current->next != NULL && current->next->L_name > tempnote->L_name)
                {
                    current = current->next;
                }
                tempnote->next = current->next;
                current->next = tempnote;
            }
        }
    }

    void insertionSort(Node *headref, int mode)
    {
        // Initialize sorted node to final sorted list
        sorted = NULL;
        Node *current = headref;
        // Going through the linked list and insert every node to sorted
        while (current != NULL)
        {
            // Store next for next iteration
            Node *next = current->next;
            // inserting the node back
            sortedInsert(current, mode);
            // Update current node
            current = next;
        }
        // Update head_ref to point to sorted linked list
        head = sorted;
    }
    //Utility funciton for swapping nodes 
    void swapping(Node *node_1, Node *node_2)
    {
        string temp = node_1->F_name;
        node_1->F_name = node_2->F_name;
        node_2->F_name = temp;
    }

    void bubble_sort(Node *head, int mode)
    {
        int swapped;

        Node *lPtr;        // left pointer will always point to the start of the list
        Node *rPrt = NULL; // right pointer will always point to the end of the list
        if (mode == 0)
        {
            do
            {
                swapped = 0;
                lPtr = head;
                while (lPtr->next != rPrt)
                {
                    if (lPtr->F_name > lPtr->next->F_name)
                    {
                        swapping(lPtr, lPtr->next);
                        swapped = 1;
                    }
                    lPtr = lPtr->next;
                }
                //When the loop is over, the largest node will be at the end of the list. Assign it to the rPtr and we are done
                rPrt = lPtr;

            } while (swapped);
        }
        //Same thing but reversed
        else
        {
            do
            {
                swapped = 0;
                lPtr = head;
                while (lPtr->next != rPrt)
                {
                    if (lPtr->F_name < lPtr->next->F_name)
                    {
                        swapping(lPtr, lPtr->next);
                        swapped = 1;
                    }
                    lPtr = lPtr->next;
                }
                rPrt = lPtr;

            } while (swapped);
        }
    }
    //The next 2 functions are just the bubble sort algorithms but modified for Mnum and Last name since we
    //we couldnt reverse the other 2 sorting in time
    void bubble_sort_Lname(Node *head)
    {
        int swapped;

        Node *topptr;
        Node *botptr = NULL; 
        do
        {
            swapped = 0;
            topptr = head;
            while (topptr->next != botptr)
            {
                if (topptr->L_name < topptr->next->L_name)
                {
                    swapping(topptr, topptr->next);
                    swapped = 1;
                }
                topptr = topptr->next;
            }
            botptr = topptr;

        } while (swapped);
    }
    void bubble_sort_Mnum(Node *head){
        int swapped;

        Node *firptr;
        Node *lasptr = NULL; 
        do
            {
                swapped = 0;
                firptr = head;
                while (firptr->next != lasptr)
                {
                    if (firptr->Mnum < firptr->next->Mnum)
                    {
                        swapping(firptr, firptr->next);
                        swapped = 1;
                    }
                    firptr = firptr->next;
                }
                lasptr = firptr;

            } while (swapped);
    }

    //Utility function used to merge the 2 sorted list back into 1
    Node *SortedMerge(Node *a, Node *b)
    {
        Node *result = NULL;

        //Initial case
        if (a == NULL)
            return (b);
        else if (b == NULL)
            return (a);

        // Pick a and b based on sized then sort recursively
        if (a->Mnum <= b->Mnum)
        {
            result = a;
            result->next = SortedMerge(a->next, b);
        }
        else
        {
            result = b;
            result->next = SortedMerge(a, b->next);
        }
        return (result);
    }

    /* Utility function: Split the list into 2 halves. The odd node will be assigned to the second half */
    void FrontBackSplit(Node *source, Node **firsthalf, Node **secondhalf)
    {
        Node *firstnode;
        Node *secondnode;
        secondnode = source;
        firstnode = source->next;

        /*First node goes up two nodes, and second node goes up one */
        while (firstnode != NULL)
        {
            firstnode = firstnode->next;
            if (firstnode != NULL)
            {
                secondnode = secondnode->next;
                firstnode = firstnode->next;
            }
        }

        // Second node is before the midpoint in the list, so split it in two at that point.
        *firsthalf = source;
        *secondhalf = secondnode->next;
        secondnode->next = NULL;
    }

    //Appointing a new address to the head to sort it
    void MergeSort(Node **headRef)
    {
        Node *head = *headRef;
        Node *a;
        Node *b;

        // When list contains 1 node or 0
        if ((head == NULL) || (head->next == NULL))
        {
            return;
        }

        //Splitting into 2 sublists that will be sorted below
        FrontBackSplit(head, &a, &b);

        //Sort recrusively 
        MergeSort(&a);
        MergeSort(&b);

        //Merging the 2 list after done sorting
        *headRef = SortedMerge(a, b);
    }

    //Menu for user's control
    void menu()
    {
        int mode = 0;
        char y = '0';
        cout << "How would you like to sort the student: 1. M-Number? 2. First name? 3. Last name?\n";
        while (true)
        {
            cout << "Your choice: ";
            cin >> y;
            if (y == '1')
            {
                cout << "How would you like to sort it: 0. Ascending or 1. Descending\n";
                cin >> mode;
                if (mode == 0)
                {
                    MergeSort(&head);
                }
                else
                {
                    bubble_sort_Mnum(head);
                }
                display();
                break;
            }
            else if (y == '2')
            {
                cout << "How would you like to sort it: 0. Ascending or 1. Descending\n";
                cin >> mode;
                bubble_sort(head, mode);
                cout << "Student list as sorted in desired order: \n";
                display();
                break;
            }
            else if (y == '3')
            {
                cout << "How would you like to sort it: 0. Ascending or 1. Descending\n";
                cin >> mode;
                if (mode == 0)
                {
                    insertionSort(head, mode);
                }
                else
                {
                    bubble_sort_Lname(head);
                }
                cout << "Student list as sorted in desired order: \n";
                display();
                break;
            }
            else
            {
                cout << "Invalid input\n";
            }
        }
    }
};

int main()
{
    //Code was created by: Huy Le, Du Nguyen, Nhat Phan, Huu Quang Nhat Nguyen
    ifstream infile;
    string lname, fname;
    int Mnum;
    LinkedList Ucincin;
    infile.open("names.txt");
    if (!infile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }
    for(int i = 0; i < Numstudent; i++){
        infile >> fname;
        infile >> lname;
        Mnum = rand()% 10000 + 10000;
        Ucincin.addStudent(fname,lname,Mnum);
    }
    infile.close();
    cout << "Number of student: " << Ucincin.getLength() <<endl;
    Ucincin.menu();
    cout << "---------------------------------------------\nend";
    return 0;
}