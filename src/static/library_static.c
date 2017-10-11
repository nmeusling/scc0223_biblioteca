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
#include "book_static.h"

/*
 * Initializes the library, creating its associated student list and book list
 */
void create_library(library *lib){
    create_stud_list(lib);
    create_book_list(lib);
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
    int prev, index;
    //already exists book with same isbn
    if(search_book_isbn(&lib->books, isbn, &prev) == 0){
        if(prev == NULL)
            lib->books.elements[lib->books.first].count++;
        else {
            index = lib->books.elements[prev].next;
            lib->books.elements[index].count++;
        }
        return 2;
    }
    index = create_book(&lib->books, title, author, editor, isbn, year, edition);
    if( index == -1)
        return 1;
    insert_book_booklist(&lib->books, index);
    return 0;
}



//todo what about when duplicates!!!!
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
//todo what about when duplicates!!!!
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


