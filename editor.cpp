#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h>
using namespace std;

// Function to set cursor position on console
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Node class for doubly linked list
class node {
public:
    char data;
    node* next;
    node* prev;
    node* up;
    node* down;
    node(char c) {
        data = c;
        next = NULL;
        prev = NULL;
        up = NULL;
        down = NULL;
    }
};

// Two-dimensional Doubly Linked List ADT
class TwoDDLLADT {
    node* first, * cursor;

public:
    TwoDDLLADT() {
        first = NULL;
        cursor = NULL;
    }

    // Insert a character at the cursor position
    void Insert(char c) {
        node* temp = new node(c);
        if (first == NULL) {
            first = temp;
            cursor = temp;
        }
        else {
            if (cursor->next == NULL) {
                cursor->next = temp;
                temp->prev = cursor;
                cursor = temp;
            }
            else {
                temp->next = cursor->next;
                cursor->next->prev = temp;
                cursor->next = temp;
                temp->prev = cursor;
                cursor = temp;
            }
        }
    }

    // Print all nodes of the list
    void PrintAll() {
        node* temp = first;
        int i = 0;
        while (temp != NULL) {
            cout << temp->data;
            temp = temp->next;
        }
    }

    // Save the current state of the list to a file
    void Save() {
        ofstream file("save.txt");
        if (!file.is_open()) {
            cout << "Failed to open the file!" << endl;
            return;
        }

        node* temp = first;
        while (temp != NULL) {
            file << temp->data;
            temp = temp->next;
        }

        file.close();
    }

    // Load data from a file into the list
    void Load() {
        ifstream file("save.txt");
        if (!file.is_open()) {
            cout << "Failed to open the file!" << endl;
            return;
        }

        node* temp = first;
        while (temp != NULL) {
            node* next = temp->next;
            delete temp;
            temp = next;
        }
        first = NULL;
        cursor = NULL;

        char c;
        while (file >> c) {
            Insert(c);
        }

        file.close();
    }

    // Move cursor up
    void Up() {
        if (cursor->up != NULL) {
            cursor = cursor->up;
        }
    }

    // Move cursor down
    void Down() {
        if (cursor->down != NULL) {
            cursor = cursor->down;
        }
    }

    // Move cursor left
    void Left() {
        if (cursor->prev != NULL) {
            cursor = cursor->prev;
        }
    }

    // Move cursor right
    void Right() {
        if (cursor->next != NULL) {
            cursor = cursor->next;
        }
    }

    // Insert a new line at the cursor position
    void NewLine() {
        node* temp = new node('\n');
        if (cursor->next == NULL) {
            cursor->next = temp;
            temp->prev = cursor;
            cursor = temp;
        }
        else {
            temp->next = cursor->next;
            cursor->next->prev = temp;
            cursor->next = temp;
            temp->prev = cursor;
            cursor = temp;
        }
    }

    // Delete the node at the cursor position
    void Delete() {
        if (cursor->next == NULL) {
            if (cursor->prev == NULL) {
                delete cursor;
                cursor = NULL;
                first = NULL;
            }
            else {
                cursor = cursor->prev;
                delete cursor->next;
                cursor->next = NULL;
            }
        }
        else {
            if (cursor->prev == NULL) {
                first = cursor->next;
                delete cursor;
                cursor = first;
                cursor->prev = NULL;
            }
            else {
                cursor->prev->next = cursor->next;
                cursor->next->prev = cursor->prev;
                node* temp = cursor;
                cursor = cursor->next;
                delete temp;
            }
        }
    }
};

int main() {
    TwoDDLLADT t;
    t.Load(); // Load data from file

    // Main loop for interacting with the text editor
    char c;
    while (true) {
        c = _getch();
        if (c == 13) { // Enter key
            t.NewLine();
        }
        else if (c == 8) { // Backspace key
            t.Delete();
        }
        else if (c == 27) { // Escape key
            t.Save(); // Save data to file
            break;
        }
        else if (c == 72) { // Arrow up key
            t.Up();
        }
        else if (c == 80) { // Arrow down key
            t.Down();
        }
        else if (c == 75) { // Arrow left key
            t.Left();
        }
        else if (c == 77) { // Arrow right key
            t.Right();
        }
        else { // Insert character
            t.Insert(c);
        }

        system("cls"); // Clear console screen
        t.PrintAll(); // Print the entire content of the text editor
    }

    return 0;
}
