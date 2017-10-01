/** @file library_dynamic.h
 *  @brief Header file for library_dynamic.c
 *
 *  This file contains the declaration for the library structs, including the
 *  student list, book list, and wait list. It also contains the prototypes for
 *  the operations that manipulate these lists.
 *
 *  @author Natalie Menato (10295051)
 */


#ifndef SCC0223_BIBLIOTECA_LIBRARY_DYNAMIC_H
#define SCC0223_BIBLIOTECA_LIBRARY_DYNAMIC_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>



#define MAX_TITLE_SIZE 100
#define MAX_AUTHOR_SIZE 100
#define MAX_EDITOR_SIZE 100
#define MAX_ISBN_SIZE 20

#define MAX_NAME_SIZE 100
#define MAX_NUSP_SIZE 15
#define MAX_PHONE_SIZE 15
#define MAX_EMAIL_SIZE 100
#define MAX_MESSAGE_SIZE 500

typedef struct _student student;

/** @struct wait_list_entry
 *  @brief Node for wait list
 *  @var student::stud pointer to the student on wait list
 *  @var wait_list_entry::next
 *  Member 'next' pointer to the next student on wait list
 */
typedef struct _wait_list_entry{
    student *stud;
    struct _wait_list_entry *next;
} wait_list_entry;

/** @struct wait_list
 *  @brief Queue to store all students that are on the wait list for a book
 *  @var wait_list::first
 *  @var wait_list::last
 *  Member 'first' pointer to the first student node of wait list
 *  Member 'last' pointer to the last student node of wait list
 */
typedef struct {
    wait_list_entry *first, *last;
    int total;
} wait_list;


typedef struct _email{
    char message[MAX_MESSAGE_SIZE] ;
    struct _email *next;
}email;

typedef struct{
    email *top;
}email_stack;

/** @struct student
 *  @brief Stores all of the information related to a student
 *  @var student::name
 *  @var student::nusp
 *  @var student::phone
 *  @var student::email
 *  @var student::next
 *  Member 'name' string that stores name of student
 *  Member 'nusp' stores the numero USP of student
 *  Member 'phone' stores the student's phone number
 *  Member 'email' string that stores student's email
 *  Member 'next' pointer to the next student in the student list
 */
struct _student {
    char name[MAX_NAME_SIZE];
    int nusp[MAX_NUSP_SIZE];
    int phone[MAX_PHONE_SIZE];
    char email[MAX_EMAIL_SIZE];
    struct _student *next;
    email_stack emails;
    //stud_bklist bks;
    //wait_list *bks[MAX_WAITLISTS_PER_STUD];
   // int num_wait_lists;

};


/** @struct student_list
 *  @brief List to store student nodes
 *  @var student_list::first
 *  @var student_list::last
 *  Member 'first' pointer to the first student node of list
 *  Member 'last' pointer to the last student node of list
 */
typedef struct {
    student *first, *last;
} student_list;


typedef struct _book book;


/** @struct book
 *  @brief Stores all of the information related to a book
 *  @var student::title
 *  @var student::author
 *  @var student::editor
 *  @var student::isbn
 *  @var student::year
 *  @var student::edition
 *  @var student::count
 *  @var student::next
 *  @var wait_list::
 *  Member 'title' string that stores title of book
 *  Member 'author' string that stores the author of book
 *  Member 'editor' string that stores the editor of book
 *  Member 'isbn' string that stores the ISBN of book
 *  Member 'year' int that stores the year of book
 *  Member 'edition' int that stores the edition of book
 *  Member 'next' pointer to the next book in the book list
 */
struct _book {
    char title[MAX_TITLE_SIZE];
    char author[MAX_AUTHOR_SIZE];
    char editor[MAX_EDITOR_SIZE];
    int isbn[MAX_ISBN_SIZE];
    int year;
    int edition;
    int count; // 0 if none currently available (i.e. all books are checked out)
    struct _book *next;
    wait_list wl;
};


/** @struct book
 *  @brief List to store book nodes
 *  @var book_list::first
 *  @var book_list::last
 *  Member 'first' pointer to the first book node of list
 *  Member 'last' pointer to the last book node of list
 */
typedef struct {
    book *first, *last;
} book_list;


/** @brief Creates a new student list
 *
 * Initializes a student_list so that the other functions for the list can be
 * used.
 *
 * @param student_list* studs pointer to student list to be initialized
 */
void create_stud_list(student_list *studs);


/** @brief Creates a new student and adds it to student list
 *
 * Allocates memory for a new student. Saves the passed name, nusp, phone, and
 * email to the new student. Adds the new student to the end of existing
 * student list.
 *
 * @param student_list* studs student list where student will be added
 * @param char[] name name of student to be added
 * @param int[] nusp Numero USP of student to be added
 * @param int[] phone Phone number of student to be added
 * @param char[] email Email of student to be added
 * @return 1 if an error occurred, 0 if student inserted successfully
 */
int insert_student(student_list *studs, char name[MAX_NAME_SIZE],
                   int nusp[MAX_NUSP_SIZE], int phone[MAX_PHONE_SIZE],
                   char email[MAX_EMAIL_SIZE]);


/** @brief Searches for student with name in the list
 *
 * Searches for a student in the student list whose name is the same as the
 * name passed to the function. Previous student in the list is saved to passed
 * parameter prev_stud.
 *
 * @param student_list* studs student list where student will be searched
 * @param char[] name name of student to be searched
 * @param student** prev_stud pointer to the pointer of the previous student, will
 * be NULL if student is not in list or student is first element in list
 * @return 0 if student is found on list, 1 otherwise
 */
int search_student_name(student_list *studs, char name[MAX_NAME_SIZE],
                        student **prev_stud);


/** @brief Searches for student with nusp in the list
 *
 * Searches for a student in the student list whose nusp is the same as the
 * nusp passed to the function. Previous student in the list is saved to passed
 * parameter prev_stud.
 *
 * @param student_list* studs student list where student will be searched
 * @param int[] nusp nusp of student to be searched
 * @param student** prev_stud pointer to the pointer of the previous student, will
 * be NULL if student is not in list or student is first element in list
 * @return 0 if student is found on list, 1 otherwise
 */
int search_student_nusp(student_list *studs, int nusp[MAX_NUSP_SIZE],
                        student **prev_stud);


/** @brief Removes student with name from the list
 *
 * Uses search function to find previous student in list and then remove the
 * desired student.
 *
 * @param student_list* studs student list where student will be removed
 * @param char[] name name of student to be removed
 * @param student** prev_stud pointer to the pointer of the previous student, will
 * be NULL if student is not in list or student is first element in list
 * @return 0 if student removed successfully, 1 otherwise
 */
int remove_student_name(book_list *books, student_list *studs, char name[MAX_NAME_SIZE]);


/** @brief Removes student with nusp from the list
 *
 * Uses search function to find previous student in list and then remove the
 * desired student.
 *
 * @param student_list* studs student list where student will be removed
 * @param int[] nusp nusp of student to be removed
 * @param student** prev_stud pointer to the pointer of the previous student, will
 * be NULL if student is not in list or student is first element in list
 * @return 0 if student removed successfully, 1 otherwise
 */
int remove_student_nusp(book_list *books, student_list *studs, int nusp[MAX_NUSP_SIZE]);


/** @brief Creates a new book list
 *
 * Initializes a book_list so that the other functions for the list can be
 * used.
 *
 * @param book_list* studs pointer to book list to be initialized
 */
void create_book_list(book_list *books);


/** @brief Creates a new book and adds it to book list
 *
 * Allocates memory for a new book. Saves the passed title, author, editor,
 * isbn, year, and edition to the new book. Adds the new book to the end of
 * existing book list.
 *
 * @param book_list* books book list where book will be added
 * @param char[] title title of the book to be added
 * @param char[] author author of the book to be added
 * @param char[] editor editor of the book to be added
 * @param int[] isbn ISBN of the book to be added
 * @param int year year of the book to be added
 * @param int edition edition of the book to be added
 * @return 1 if an error occurred, 0 if student inserted successfully
 */
int insert_book(book_list *books, char title[MAX_TITLE_SIZE],
                char author[MAX_AUTHOR_SIZE], char editor[MAX_EDITOR_SIZE],
                int isbn[MAX_ISBN_SIZE], int year, int edition);


/** @brief Searches for book with title in the list
 *
 * Searches for a book in the book list whose title is the same as the
 * title passed to the function. Previous book in the list is saved to passed
 * parameter prev_book.
 *
 * @param book_list* books book list where book will be searched
 * @param char[] title title of book to be searched
 * @param book** prev_book pointer to the pointer of the previous book, will
 * be NULL if book is not in list or book is first element in list
 * @return 0 if book is found on list, 1 otherwise
 */
int search_book_title(book_list *bks, char title[MAX_TITLE_SIZE],
                      book **prev_book);


/** @brief Searches for book with ISBN in the list
 *
 * Searches for a book in the book list whose ISBN is the same as the
 * ISBN passed to the function. Previous book in the list is saved to passed
 * parameter prev_book.
 *
 * @param book_list* books book list where book will be searched
 * @param int[] isbn ISBN of book to be searched
 * @param book** prev_book pointer to the pointer of the previous book, will
 * be NULL if book is not in list or book is first element in list
 * @return 0 if book is found on list, 1 otherwise
 */
int search_book_isbn(book_list *books, int isbn[MAX_ISBN_SIZE],
                     book **prev_book);


/** @brief Removes book with title from the list
 *
 * Uses search function to find previous book in list and then remove the
 * desired book.
 *
 * @param book_list* books book list where book will be removed
 * @param char[] title title of book to be removed
 * @return 0 if book removed successfully, 1 otherwise
 */
int remove_book_title(book_list *books, char title[MAX_TITLE_SIZE]);


/** @brief Removes book with ISBN from the list
 *
 * Uses search function to find previous book in list and then remove the
 * desired book.
 *
 * @param book_list* books book list where book will be removed
 * @param int[] isbn ISBN of book to be removed
 * @return 0 if book removed successfully, 1 otherwise
 */
int remove_book_isbn(book_list *books, int isbn[MAX_ISBN_SIZE]);


/** @brief Copies elements of an int array to a second int array
 *
 * Copies elements from array2 to array 1. Both arrays must have size
 * elements.
 *
 * @param int* array1 destination array (copied to)
 * @param int* array2 origin array (copied from)
 * @param int size number of elements to be copied
 */
void copy_int_array(int *array1, int *array2, int size);


/** @brief Compares two int arrays to see if they are the same
 *
 * Compares the elements of array 1 with array 2 to see if the arrays contain
 * the same elements in the same order.
 *
 * @param int* array1 first array to be compared
 * @param int* array2 second array to be compated
 * @param int size number of elements to be compared
 * @return 0 if the arrays are the same, 1 if they are different
 */
int compare_int_array(int *array1, int *array2, int size);



void create_wait_list(wait_list *wl);

void remove_wait_list(wait_list *wl);

int add_to_waitlist(student *stud, wait_list *wl);

int remove_from_waitlist(student *stud, wait_list *wl);

void create_email_stack(email_stack *emls);

int push_email(email_stack *emls, char message[MAX_MESSAGE_SIZE]);

int pop_email(email_stack *emls, char message[MAX_MESSAGE_SIZE]);

void delete_email_stack(email_stack *emls);

int isEmailEmpty(email_stack *emls);

int get_student_by_name(student_list *studs, char name[MAX_NAME_SIZE], student **stud);

int get_student_by_nusp(student_list *studs, int nusp[MAX_NUSP_SIZE], student **stud);

int get_book_by_title(book_list *bks, char title[MAX_TITLE_SIZE], book **bk);

int get_book_by_isbn(book_list *bks, int isbn[MAX_ISBN_SIZE], book **bk);

void remove_student_all_waitlists(book_list *bks, student *stud);

//int add_to_stud_wtlist(stud *stud, stud_bklist *bl);

//int remove_from_stud_wtlist(book *bk, stud_bklist *bl);

//returns 1 if book is available, 0 if not available
int book_available(book *bk);

int checkout_book(student *stud, book *bk);

void return_book(book *bk);

char * get_book_title(book *bk);

char* get_stud_name(student *stud);


#endif //SCC0223_BIBLIOTECA_LIBRARY_DYNAMIC_H
