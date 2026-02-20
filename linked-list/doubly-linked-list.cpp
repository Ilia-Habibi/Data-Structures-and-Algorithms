/*
 * Doubly Linked List - Student Records Manager
 * 
 * A doubly linked list implementation that stores student records and supports
 * insertion, deletion, and GPA-based filtering queries. Each node holds a Student
 * object and has pointers to both the next and previous nodes.
 *
 * Built for my university DSA course :)
 *
 * Operations supported:
 *   - Insert at front, back, or after a specific student (by ID)
 *   - Delete from front, back, or after a specific student (by ID)
 *   - Query students by GPA criteria (all A's, only total A, conditional)
 *
 * Time Complexity:
 *   - Insert front/back: O(1)
 *   - Insert/Delete after: O(n) — need to search for the target node
 *   - Print / Filter queries: O(n)
 */

#include <iostream>
#include <string>

using namespace std;

// ========================== Student Class ==========================
// Represents a single student with their name, ID, and GPA info.
// This is the data we store inside each node of the linked list.
// ===================================================================

class Student {
private:
    string firstName;
    string lastName;
    long studentID;
    float totalGPA;      // overall GPA across all semesters
    float semester1GPA;  // GPA for the first semester
    float semester2GPA;  // GPA for the second semester

public:
    // Parameterized constructor — lets us create a student with all their info at once
    Student(string fName, string lName, long id, float total, float s1, float s2)
        : firstName(fName), lastName(lName), studentID(id), totalGPA(total), semester1GPA(s1), semester2GPA(s2) {}

    // Default constructor — needed so we can create empty Student objects if necessary
    Student() : studentID(0), totalGPA(0), semester1GPA(0), semester2GPA(0) {}

    // Overloading << so we can easily print student info with cout
    friend ostream& operator<<(ostream& os, const Student& s) {
        os << "ID: " << s.studentID 
           << " | Name: " << s.firstName << " " << s.lastName 
           << " | Total: " << s.totalGPA 
           << " | S1: " << s.semester1GPA 
           << " | S2: " << s.semester2GPA;
        return os;
    }

    // Getters — keeping things encapsulated
    long getID() const { return studentID; }
    float getTotalGPA() const { return totalGPA; }
    float getSemester1GPA() const { return semester1GPA; }
    float getSemester2GPA() const { return semester2GPA; }
};


// ==================== Doubly Linked List Class =====================
// The main data structure! Each node points to the next AND previous
// node, so we can traverse the list in both directions. We also keep
// track of both head and tail for efficient front/back operations.
// ===================================================================

class DoublyLinkedList {
private:
    // Internal node structure — holds a Student and two pointers
    struct Node {
        Student data;
        Node* next;
        Node* prev;

        Node(Student s) : data(s), next(nullptr), prev(nullptr) {}
    };

    Node* head;  // points to the first node in the list
    Node* tail;  // points to the last node in the list

public:
    // Constructor — start with an empty list
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    // Destructor — walk through the list and free every node to prevent memory leaks
    ~DoublyLinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        cout << "Destructor called: Memory cleared." << endl;
    }

    // -------------------- Insertion Methods --------------------

    // Insert a new student at the FRONT of the list — O(1)
    void insertFront(Student s) {
        Node* newNode = new Node(s);
        if (head == nullptr) {
            // list is empty, so new node is both head and tail
            head = tail = newNode;
        } else {
            // link new node before current head
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    // Insert a new student at the BACK of the list — O(1)
    void insertBack(Student s) {
        Node* newNode = new Node(s);
        if (tail == nullptr) {
            // list is empty
            head = tail = newNode;
        } else {
            // link new node after current tail
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // Insert a new student AFTER the node with the given target ID — O(n)
    // We have to search for the target node first, hence linear time.
    void insertAfter(long targetID, Student s) {
        Node* current = head;

        // search for the node with matching ID
        while (current != nullptr && current->data.getID() != targetID) {
            current = current->next;
        }

        if (current == nullptr) {
            cout << "Node with ID " << targetID << " not found." << endl;
            return;
        }

        // create new node and wire up the pointers
        Node* newNode = new Node(s);
        newNode->next = current->next;
        newNode->prev = current;
        
        if (current->next != nullptr) {
            current->next->prev = newNode;
        } else {
            // inserting after the last node, so update tail
            tail = newNode; 
        }
        current->next = newNode;
    }

    // -------------------- Deletion Methods --------------------

    // Delete the FRONT node of the list — O(1)
    void deleteFront() {
        if (head == nullptr) return;  // nothing to delete
        
        Node* temp = head;
        if (head == tail) {
            // only one node in the list
            head = tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }
        delete temp;
    }

    // Delete the BACK node of the list — O(1)
    // (this is where doubly linked list shines compared to singly linked list!)
    void deleteBack() {
        if (tail == nullptr) return;  // nothing to delete

        Node* temp = tail;
        if (head == tail) {
            // only one node in the list
            head = tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        delete temp;
    }

    // Delete the node right AFTER the node with the given target ID — O(n)
    void deleteAfter(long targetID) {
        Node* current = head;

        // find the node with matching ID
        while (current != nullptr && current->data.getID() != targetID) {
            current = current->next;
        }

        // check if target exists and if there's actually a node after it
        if (current == nullptr || current->next == nullptr) {
            cout << "No node exists after ID " << targetID << " to delete." << endl;
            return;
        }

        Node* nodeToDelete = current->next;
        current->next = nodeToDelete->next;

        if (nodeToDelete->next != nullptr) {
            nodeToDelete->next->prev = current;
        } else {
            // we're deleting the tail, so update it
            tail = current; 
        }

        delete nodeToDelete;
    }

    // -------------------- Query / Filter Methods --------------------
    // These methods filter students based on GPA criteria.
    // In our grading system, a GPA >= 17 (out of 20) is considered grade "A".
    // A GPA < 12 means the student is on academic probation (conditional).

    // Print students who got grade A in ALL categories (total + both semesters)
    void printAllGradeA() {
        cout << "\n--- Students with All 'A' Grades (Total, S1, S2 >= 17) ---\n";
        Node* current = head;
        bool found = false;
        while (current != nullptr) {
            if (current->data.getTotalGPA() >= 17 && 
                current->data.getSemester1GPA() >= 17 && 
                current->data.getSemester2GPA() >= 17) {
                cout << current->data << endl;
                found = true;
            }
            current = current->next;
        }
        if (!found) cout << "None found.\n";
    }

    // Print students who ONLY have grade A in their total GPA
    // (but NOT in both individual semesters)
    void printOnlyTotalGradeA() {
        cout << "\n--- Students with Only Total Grade 'A' (Total >= 17) ---\n";
        Node* current = head;
        bool found = false;
        while (current != nullptr) {
            // check if they have A in both semesters
            bool allA = (current->data.getSemester1GPA() >= 17 && current->data.getSemester2GPA() >= 17);
            
            // we want total >= 17 but NOT all A's (so at least one semester is below 17)
            if (current->data.getTotalGPA() >= 17 && !allA) {
                cout << current->data << endl;
                found = true;
            }
            current = current->next;
        }
        if (!found) cout << "None found.\n";
    }

    // Print students on academic probation (GPA < 12 in at least one semester)
    void printConditionalStudents() {
        cout << "\n--- Conditional Students (GPA < 12 in at least one semester) ---\n";
        Node* current = head;
        bool found = false;
        while (current != nullptr) {
            if (current->data.getSemester1GPA() < 12 || current->data.getSemester2GPA() < 12) {
                cout << current->data << endl;
                found = true;
            }
            current = current->next;
        }
        if (!found) cout << "None found.\n";
    }
    
    // -------------------- Display Method --------------------

    // Print the entire list from head to tail
    void printList() {
        cout << "\n--- Full Student List ---\n";
        Node* current = head;
        while (current != nullptr) {
            cout << current->data << endl;
            current = current->next;
        }
        cout << "-------------------------\n";
    }
};


// ========================== Main / Demo ==========================
// Quick demo that shows off all the features of our doubly linked list.
// We add some sample students, run queries, and test deletion.
// =================================================================

int main() {
    DoublyLinkedList list;
    
    // inserting some students at the back (builds the list in order)
    list.insertBack(Student("Amir", "Khodaei", 9901, 18.5, 18.0, 19.0));
    list.insertBack(Student("Sara", "Mehrabi", 9902, 16.0, 15.4, 16.6));
    list.insertBack(Student("Aryan", "Samin", 9903, 17.2, 16.0, 18.4));
    list.insertBack(Student("Mehrad", "Rahimi", 9904, 13.0, 11.5, 14.5));

    // insert at front — Mona will become the new head
    list.insertFront(Student("Mona", "Zare", 9900, 19.5, 19.5, 19.5));

    // insert after a specific student (the one with ID 9901)
    list.insertAfter(9901, Student("Mohammad", "Zafari", 9905, 11.0, 10.0, 12.0));

    // print full list to see all students
    list.printList();

    // run GPA-based queries
    list.printAllGradeA();            // students with A in everything
    list.printOnlyTotalGradeA();      // students with A only in total GPA
    list.printConditionalStudents();  // students on academic probation

    // test deletion — remove the front node (Mona)
    cout << "\n...Deleting student with ID 9900 (Front) and 9902 (After 9901 - logic varies)..." << endl;
    list.deleteFront(); 
    list.printList();

    return 0;
}