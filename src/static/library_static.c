/** @file library_static.c
 *  @brief Static Abstract Data Type for Library Management
 *
 *  Contains the operations to manipulate the library data structure. Includes
 *  operations to register a new student, remove a student, register a new book,
 *  remove a book from the library, check out a book and return a book.
 *
 *  @author Natalie Menato (10295051)
 */


#include "library_static.h"

/*
 * Initializes the library, creating its associated student list and book list
 */
void create_library(library *lib){
    create_stud_list(lib);
    create_book_list(lib);
}




/*
 * Find the next available space in the memory bank for the book. Return -1
 * if there is no more available space.
 */
int get_node_booklist(book_list *books){
    int index = books->first_empty;
    if(index == -1 )
        return -1;
    books->first_empty = books->elements[index].next;
    books->elements[index].next = -1;
    return index;

}


/*
 * Frees the space of passed index in the book list memory bank. Adds space
 * back to empty list.
 */
void free_node_booklist(book_list *books, int index){
    books->elements[index].next = books->first_empty;
    books->first_empty =  index;
}

/*
 * Allocates memory in memory bank for a new student. Saves the passed name,
 * nusp, phone, and email to the new student. Adds the new student to the end
 * of existing student list for the passed library.
 */
int insert_student(library *lib, char name[MAX_NAME_SIZE],
                   int nusp[MAX_NUSP_SIZE], int phone[MAX_PHONE_SIZE],
                   char email[MAX_EMAIL_SIZE]){

    int index = create_student(&lib->students, name, nusp, phone, email);
    if(index == -1)
        return 1;
    insert_student_to_list(&lib->students, index);
    return 0;

}




//todo verify logic and try to clean
/*
 * Uses search function to find previous student in library's student list and
 * then removes the desired student.
 */
int remove_student_name(library *lib, char name[MAX_NAME_SIZE]){
    int prev_stud;
    int index = lib->students.first;
    //list is empty
    if (index == -1) {
        return 1;
    }
    //student not found in list
    if (search_student_name(lib, name, &prev_stud) == 1) {
        return 1;
    }
    remove_student_studentlist(&lib->students, prev_stud);
    //remoce all wait lists!
}

//todo verify logic and try to clean
/*
 * Uses search function to find previous student in library's student list and
 * then removes the desired student.
 */
int remove_student_nusp(library *lib, int nusp[MAX_NUSP_SIZE]) {
    int prev_stud;
    int index = lib->students.first;
    //list is empty
    if (index == -1) {
        return 1;
    }
    //student not found in list
    if (search_student_nusp(lib, nusp, &prev_stud) == 1) {
        return 1;
    }
    remove_student_studentlist(&lib->students, prev_stud);
    //remoce all wait lists!
}






/*
 * Initializes the memory bank for the book_list in the library so that the
 * other functions for the book list can be used.
 */
void create_book_list(library *lib){
    int i;
    for(i=0; i<MAX_BOOKS-1; i++){
        lib->books.elements[i].next = i+1;
    }
    lib->books.elements[MAX_STUDENTS -1].next = -1;
    lib->books.first_empty = 0;
    lib->books.first = -1;
    lib->books.last = -1;
}

//todo logic for duplicate book, shouldn't allocate memory
/*
 * Allocates memory in the memory bank for a new book. Saves the passed title,
 * author, editor, isbn, year, and edition to the new book. Adds the new book
 * to the end of existing book list of passed library. If the ISBN is
 * duplicated, a new record will not be added to the list. Instead the count of
 * books of the original will be incremented.
 */
int insert_book(library *lib, char title[MAX_TITLE_SIZE],
                char author[MAX_AUTHOR_SIZE], char editor[MAX_EDITOR_SIZE],
                int isbn[MAX_ISBN_SIZE], int year, int edition){

    int index =  get_node_booklist(&lib->books);
    int prev;
    if (index == -1) {
        return 1;
    }
    create_wait_list(&lib->books.elements[index].wl);
    strcpy(lib->books.elements[index].title, title);
    strcpy(lib->books.elements[index].author, author);
    strcpy(lib->books.elements[index].editor, editor);
    copy_int_array(lib->books.elements[index].isbn, isbn, MAX_ISBN_SIZE);
    lib->books.elements[index].year = year;
    lib->books.elements[index].edition = edition;

    lib->books.elements[index].next = -1;
    //there is already a book with same ISBN
    if(search_book_isbn(lib, isbn, &prev) == 0){
        if(prev == -1 ){
            lib->books.elements[lib->books.first].count ++;
            return 2;
        }
        lib->books.elements[lib->books.elements[prev].next].count++;
        return 2;
    }
    //if list is currently empty
    if (lib->books.first == -1) {
        lib->books.first = index;
    } else { //list has at least one element already
        lib->books.elements[lib->books.last].next = index;
    }
    lib->books.last = index;
    lib->books.elements[index].count = 1;

    return 0;
}


/*
 * Searches for a book in the library's book list whose title is the same as the
 * title passed to the function. Previous book in the list is saved to passed
 * parameter prev_book.
 */
int search_book_title(library *lib, char title[MAX_TITLE_SIZE],
                      int *prev_book){
    int index = lib->books.first;
    if(index == -1)
        return 1;
    //If the student is the first in the list
    if (strcmp(lib->books.elements[index].title, title) == 0) {
        *prev_book = -1;
        return 0;
    }
    while (lib->books.elements[index].next != -1) {
        if (strcmp(lib->books.elements[index].title, title) == 0) {
            *prev_book = index;
            return 0;
        }
        index = lib->books.elements[index].next;

    }
    return 1;
}


/*
 * Searches for a book in the library's book list whose ISBN is the same as the
 * ISBN passed to the function. Previous book in the list is saved to passed
 * parameter prev_book.
 */
int search_book_isbn(library *lib, int isbn[MAX_ISBN_SIZE],
                     int *prev_book){
    int index = lib->books.first;
    if(index == -1)
        return 1;
    //If the student is the first in the list
    if (compare_int_array(lib->books.elements[index].isbn, isbn, MAX_ISBN_SIZE) == 0) {
        *prev_book = -1;
        return 0;
    }
    while (lib->books.elements[index].next != -1) {
        if (compare_int_array(lib->books.elements[index].isbn, isbn, MAX_ISBN_SIZE) == 0) {
            *prev_book = index;
            return 0;
        }
        index = lib->books.elements[index].next;

    }
    return 1;
}

//todo verify logic and try to clean last element, separate functions
/*
 * Uses search function to find previous book in library's book list and then
 * removes the desired book.
 */
int remove_book_title(library *lib, char title[MAX_TITLE_SIZE]){
    int prev;
    int index = lib->books.first;
    //list is empty
    if (index == -1) {
        return 1;
    }
    //book not found in list
    if (search_book_title(lib, title, &prev) == 1) {
        return 1;
    }
    //book is 1st element
    if (prev == -1) {
        lib->books.first = lib->books.elements[index].next;
        remove_wait_list(&(lib->books.elements[index].wl));
        free_node_booklist(&lib->books, index);
        //book was only element, list is not empty
        if (lib->books.first == -1)
            lib->books.last = -1;
        return 0;
    }
    index = lib->books.elements[prev].next;
    lib->books.elements[prev].next = lib->books.elements[index].next;
    remove_wait_list(&(lib->books.elements[index].wl));
    free_node_booklist(&lib->books, index);
    return 0;
}

//todo verify logic and try to clean last element, separate functions
/*
 * Uses search function to find previous book in library's book list and then
 * removes the desired book.
 */
int remove_book_isbn(library *lib, int isbn[MAX_ISBN_SIZE]){
    int prev;
    int index = lib->books.first;
    //list is empty
    if (index == -1) {
        return 1;
    }
    //book not found in list
    if (search_book_isbn(lib, isbn, &prev) == 1) {
        return 1;
    }
    //book is 1st element
    if (prev == -1) {
        lib->books.first = lib->books.elements[index].next;
        remove_wait_list(&(lib->books.elements[index].wl));
        free_node_booklist(&lib->books, index);
        //book was only element, list is not empty
        if (lib->books.first == -1)
            lib->books.last = -1;
        return 0;
    }
    index = lib->books.elements[prev].next;
    lib->books.elements[prev].next = lib->books.elements[index].next;
    remove_wait_list(&(lib->books.elements[index].wl));
    free_node_booklist(&lib->books, index);
    return 0;
}


/*
 * Creates the waitlist memory bank with initialized values.
 */
void create_wait_list(wait_list *wl){
    int i;
    for(i=0; i<MAX_BOOKS-1; i++){
        wl->items[i].next = i+1;
    }
    wl->items[MAX_BOOKS-1].next = -1;
    wl->first_empty= 0;
}


/** @brief Clears the wait list queue
 *
 * Clears the wait list and returns it to it's initial position, with first and
 * last pointing to NULL. Frees the memory of all nodes that were part of the
 * wait list.
 *
 * @param wait_list* wl wait list to be removed
 */
void remove_wait_list(wait_list *wl);


/** @brief Adds student to waitlist
 *
 * Adds the passed student as the last element in the passed wait list.
 *
 * @param student* stud pointer to student who will be added to wait list
 * @param wait_list* wl pointer to wait list student will be added to
 * @return 1 if it was not possible to add student, 0 if student added
 */
int add_to_waitlist(student *stud, wait_list *wl);


/** @brief Removes student from waitlist
 *
 * Removes the first student from the waitlist and saves a pointer to the
 * student in the passed value.
 *
 * @param student* stud pointer to student who was removed from wait list
 * @param wait_list* wl pointer to wait list student will be removed from
 * @return 1 if it was not possible to remove student, 0 if student removed
 */
int remove_from_waitlist(student *stud, wait_list *wl);


/** @brief Removes the student from all wait lists
 *
 * Checks the waitlist for each book and removes the student from any wait list
 * they belong to
 *
 * @param book_list *bks list of all registered books
 * @param student *stud student to be removed
 */
void remove_student_all_waitlists(book_list *bks, student *stud);


/** @brief Creates an email stack setting it to the correct initial position
 *
 * Initializes the email stack to it's initial position, with top pointing to
 * NULL.
 *
 * @param email_stack* emls email stack to be created
 */
void create_email_stack(email_stack *emls);


/** @brief Adds email to email stack
 *
 * Creates a new node in the email stack and saves the passed message to the
 * new node.
 *
 * @param email stack* emls pointer to the email stack where message will be
 * added
 * @param char[] email message message to be added in the stack
 * @return 1 if it was not possible to add email, 0 if email added
 */
int push_email(email_stack *emls, char message[MAX_MESSAGE_SIZE]);


/** @brief Removes top email from stack
 *
 * Removes the top message. Saves message of removed email to the passed
 * parameter.
 *
 * @param email stack* emls pointer to the email stack where message will be
 * removed
 * @param char[] email message message that was removed from stack
 * @return 1 if it was not possible to remove email, 0 if email removed
 */
int pop_email(email_stack *emls, char message[MAX_MESSAGE_SIZE]);


/** @brief Clears the email stack
 *
 * Clears the email stack and returns it to it's initial position, with top
 * pointing to NULL. Frees the memory of all nodes that were part of the
 * email stack.
 *
 * @param wait_list* wl wait list to be removed
 */
void delete_email_stack(email_stack *emls);


/** @brief Checks if email stack is empty
 *
 * Verifies if the email stick is empty
 *
 * @param email_stack *emls email stack to be checked
 * @return 1 if empty, 0 if not empty
 */
int isEmailEmpty(email_stack *emls);


/** @brief Searches for student and saves student to passed parameter if found
 *
 * Searches for the student in the library's student list  by name and saves
 * the student to the passed student parameter if found.
 *
 * @param student_list *studs list of all registered students
 * @param char[] name name of student to search for
 * @param student **stud pointer to where the pointer to the found student will
 * be stored
 * @return 0 if student is found, 1 if not found
 */
int get_student_by_name(library *lib, char name[MAX_NAME_SIZE], student **stud);


/** @brief Searches for student and saves student to passed parameter if found
 *
 * Searches for the student by nusp in the library's student list and saves
 * the student to the passed student parameter if found.
 *
 * @param library* lib pointer to the library
 * @param int[] nusp nusp of student to search for
 * @param student **stud pointer to where the pointer to the found student will
 * be stored
 * @return 0 if student is found, 1 if not found
 */
int get_student_by_nusp(library *lib, int nusp[MAX_NUSP_SIZE], student **stud);


/** @brief Searches for book and saves book to passed parameter if found
 *
 * Searches for the book in the library's book list by title and saves the book
 * to the passed book parameter if found.
 *
 * @param library* lib pointer to the library
 * @param char[] title title of book to search for
 * @param book **bk pointer to where the pointer to the found book will
 * be stored
 * @return 0 if student is found, 1 if not found
 */
int get_book_by_title(library *lib, char title[MAX_TITLE_SIZE], book **bk);


/** @brief Searches for book and saves book to passed parameter if found
 *
 * Searches for the book in the library's book list by isbn and saves the book
 * to the passed book parameter if found.
 *
 * @param library* lib pointer to the library
 * @param int[] isbn title of book to search for
 * @param book **bk pointer to where the pointer to the found book will
 * be stored
 * @return 0 if student is found, 1 if not found
 */
int get_book_by_isbn(library *lib, int isbn[MAX_ISBN_SIZE], book **bk);


/** @brief Returns the title of passed book
 *
 * Gets the title of the passed book and returns it as a string.
 *
 * @param book *bk book to get title
 * @return string of book's title
 */
char* get_book_title(book *bk);


/** @brief Checks if a book is currently available
 *
 * Checks if passed book is available to be checked out by a student
 *
 * @param book *bk book to be checked
 * @return 1 if available, 0 if not available
 */
int book_available(book *bk);


/** @brief Completes necessary actions to check out a book
 *
 * If book is available, decrements the number of available copies. If book is
 * not available, student is added to the wait list.
 *
 * @param student *stud student who is checking out book
 * @param book *bk book to be checked out
 * @return 1 if added to waitlist, 0 if book was available
 */
int checkout_book(student *stud, book *bk);


/** @brief Completes necessary actions to return a book
 *
 * If book does not have a waitlist, increments the number of available copies.
 * If book has a waitlist, sends an email to the next student and removes them
 * from wait list.
 *
 * @param book *bk book that was returned
 */
void return_book(book *bk);


