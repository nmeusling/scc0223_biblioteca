/** @file library_static.h
 *  @brief Header file for library_static.c
 *
 *  This file contains the declaration for the library structs, including the
 *  student list, book list, and wait list. It also contains the prototypes for
 *  the operations that manipulate these lists.
 *
 *  @author Natalie Menato (10295051)
 */


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

#define WAIT_LIST_SIZE 1000
#define MAX_EMAILS_PER_STUDENT 10
#define MAX_STUDENTS 100
#define MAX_BOOKS 1000

typedef struct _student student;

/** @struct wait_list_entry
 *  @brief Node for wait list
 *  @var student::stud
 *  @var int::next
 *  Member 'next' index of next student on wait list
 *  Member 'stud' pointer to the student on wait list
 */
typedef struct _wait_list_entry{
    student *stud;
    int next;
} wait_list_entry;


/** @struct wait_list
 *  @brief Memory bank to store all students that are on the wait list for a book
 *  @var int::first_empty
 *  @var wait_list::items
 *  Member 'first_empty' index of the first empty space in memory bank
 *  Member 'items' array to store all of the wait lists for all books
 */
typedef struct {
    int first_empty;
    wait_list_entry items[WAIT_LIST_SIZE];
} wait_list;


/** @struct email
 *  @brief Email node to store the email message for a student
 *  @var char[]::message
 *  Member 'message' message of the email
 */
typedef struct _email{
    char message[MAX_MESSAGE_SIZE] ;
}email;


/** @struct email_stack
 *  @brief Stack to store all emails for a student
 *  @var int::top
 *  @var email::emails
 *  Member 'top' index of the first email in the stack
 *  Member 'emails' array to store the email stack
 */
typedef struct{
    int top;
    email emails [MAX_EMAILS_PER_STUDENT];
}email_stack;


/** @struct student
 *  @brief Stores all of the information related to a student
 *  @var char[]::name
 *  @var int[]::nusp
 *  @var int[]::phone
 *  @var char[]::email
 *  @var int::next
 *  @var email_stack::emails
 *  @var int::waitlist_beg
 *  @var int::waitlist_end
 *  Member 'name' string that stores name of student
 *  Member 'nusp' stores the numero USP of student
 *  Member 'phone' stores the student's phone number
 *  Member 'email' string that stores student's email
 *  Member 'next' index of the next student in the student list
 *  Member 'emails' stack of all of the students' emails
 *  Member 'waitlist_first' index of the first student on waitlist
 *  Member 'waitlist_last' index of the last student on waitlist
 */
struct _student {
    char name[MAX_NAME_SIZE];
    int nusp[MAX_NUSP_SIZE];
    int phone[MAX_PHONE_SIZE];
    char email[MAX_EMAIL_SIZE];
    int next;
    email_stack emails;
    int waitlist_first, waitlist_last;
};


/** @struct student_list
 *  @brief List to store student nodes
 *  @var int::first_empty
 *  @var int::beg
 *  @var int::end
 *  Member 'first_empty' index of the first empty space in student memory bank
 *  Member 'first' index of the first student of list
 *  Member 'last' index of the last student of list
 */
typedef struct {
    int first_empty, first, last;
    student students[MAX_STUDENTS];
} student_list;


/** @struct book
 *  @brief Stores all of the information related to a book
 *  @var student::title
 *  @var student::author
 *  @var student::editor
 *  @var student::isbn
 *  @var student::year
 *  @var student::edition
 *  @var student::count
 *  @var int::next
 *  @var wait_list::
 *  Member 'title' string that stores title of book
 *  Member 'author' string that stores the author of book
 *  Member 'editor' string that stores the editor of book
 *  Member 'isbn' string that stores the ISBN of book
 *  Member 'year' int that stores the year of book
 *  Member 'edition' int that stores the edition of book
 *  Member 'next' index of the next book in the book list
 */
typedef struct _book {
    char title[MAX_TITLE_SIZE];
    char author[MAX_AUTHOR_SIZE];
    char editor[MAX_EDITOR_SIZE];
    int isbn[MAX_ISBN_SIZE];
    int year;
    int edition;
    int count; // 0 if none currently available (i.e. all books are checked out)
    int next;
    wait_list wl;
} book;


/** @struct book
 *  @brief List to store book nodes
 *  @var int::first_empty
 *  @var int::first
 *  @var int::last
 *  Member 'first' index of the first empty space in book memory bank
 *  Member 'first' index of the first book of list
 *  Member 'last' index of the last book of list
 */
typedef struct {
    int first_empty, first, last;
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


/** @brief Returns the name of passed student
 *
 * Gets the name of the passed student and returns it as a string.
 *
 * @param stud *stud student to get name
 * @return string of student's name
 */
char* get_stud_name(student *stud);


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
 * existing book list. If the ISBN is duplicated, a new record will not be
 * added to the list. Instead the count of books of the original will be
 * incremented.
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


/** @brief Creates a wait list queue setting it to the correct initial position
 *
 * Initializes the wait list to it's initial position, with first and last
 * pointing to NULL.
 *
 * @param wait_list* wl wait list to be created
 */
void create_wait_list(wait_list *wl);


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
 * Searches for the student in the student list by name and saves the student
 * to the passed student parameter if found.
 *
 * @param student_list *studs list of all registered students
 * @param char[] name name of student to search for
 * @param student **stud pointer to where the pointer to the found student will
 * be stored
 * @return 0 if student is found, 1 if not found
 */
int get_student_by_name(student_list *studs, char name[MAX_NAME_SIZE], student **stud);


/** @brief Searches for student and saves student to passed parameter if found
 *
 * Searches for the student by nusp in the student list and saves the student
 * to the passed student parameter if found.
 *
 * @param student_list *studs list of all registered students
 * @param int[] nusp nusp of student to search for
 * @param student **stud pointer to where the pointer to the found student will
 * be stored
 * @return 0 if student is found, 1 if not found
 */
int get_student_by_nusp(student_list *studs, int nusp[MAX_NUSP_SIZE], student **stud);


/** @brief Searches for book and saves book to passed parameter if found
 *
 * Searches for the book in the book list by title and saves the book
 * to the passed book parameter if found.
 *
 * @param book_list *bks list of all registered books
 * @param char[] title title of book to search for
 * @param book **bk pointer to where the pointer to the found book will
 * be stored
 * @return 0 if student is found, 1 if not found
 */
int get_book_by_title(book_list *bks, char title[MAX_TITLE_SIZE], book **bk);


/** @brief Searches for book and saves book to passed parameter if found
 *
 * Searches for the book in the book list by isbn and saves the book
 * to the passed book parameter if found.
 *
 * @param book_list *bks list of all registered books
 * @param int[] isbn title of book to search for
 * @param book **bk pointer to where the pointer to the found book will
 * be stored
 * @return 0 if student is found, 1 if not found
 */
int get_book_by_isbn(book_list *bks, int isbn[MAX_ISBN_SIZE], book **bk);


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
