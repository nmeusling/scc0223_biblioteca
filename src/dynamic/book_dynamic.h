/** @file book_dynamic.h
 *  @brief Header file for book_dynamic.c
 *
 *  Dynamic version:
 *  This file contains the declaration for the book struct and wait list entries.
 *  It also contains the declaration of the book list and wait list data
 *  structures. It contains the prototypes for the operations that manipulate
 *  structures.
 *
 *  @author Natalie Menato (10295051)
 */

#define MAX_TITLE_SIZE 100
#define MAX_AUTHOR_SIZE 100
#define MAX_EDITOR_SIZE 100
#define MAX_ISBN_SIZE 20

#include "student_dynamic.h"


/** @struct wait_list_entry
 *  @brief Node for wait list
 *  @var student::stud
 *  @var wait_list_entry::next
 *  Member 'stud' pointer to the student on wait list
 *  Member 'next' pointer to the next student on wait list
 */
typedef struct _wait_list_entry{
    student *stud;
    struct _wait_list_entry *next;
} wait_list_entry;


/** @struct wait_list
 *  @brief Queue to store all students that are on the wait list for a book
 *  @var wait_list_entry::first
 *  @var wait_list_entry::last
 *  @var int:total
 *  Member 'first' pointer to the first student node of wait list
 *  Member 'last' pointer to the last student node of wait list
 *  Member 'total' number of students on waitlist
 */
typedef struct {
    wait_list_entry *first, *last;
    int total;
} wait_list;

/** @struct book
 *  @brief Stores all of the information related to a book
 *  @var char[]::title
 *  @var char[]::author
 *  @var char[]::editor
 *  @var int[]::isbn
 *  @var int::year
 *  @var int::edition
 *  @var int::count
 *  @var int::total
 *  @var book*::next
 *  @var wait_list::wl
 *  Member 'title' string that stores title of book
 *  Member 'author' string that stores the author of book
 *  Member 'editor' string that stores the editor of book
 *  Member 'isbn' array that stores the ISBN of book
 *  Member 'year' int that stores the year of book
 *  Member 'edition' int that stores the edition of book
 *  Member 'count' int that stores the number of available books
 *  Member 'total' int that stores the total number of books
 *  Member 'next' pointer to the next book in the book list
 *  Member 'wl' queue of students waiting to check out the book
 */
typedef struct _book {
    char title[MAX_TITLE_SIZE];
    char author[MAX_AUTHOR_SIZE];
    char editor[MAX_EDITOR_SIZE];
    int isbn[MAX_ISBN_SIZE];
    int year;
    int edition;
    int count; // 0 if none currently available (i.e. all books are checked out)
    int total;
    struct _book *next;
    wait_list wl;
} book;

/** @struct book
 *  @brief List to store book nodes
 *  @var book*::first
 *  @var book*::last
 *  Member 'first' pointer to the first book node of list
 *  Member 'last' pointer to the last book node of list
 */
typedef struct {
    book *first, *last;
} book_list;


/** @brief Creates a new book list
 *
 * Initializes a book_list in the library so that the other functions for the
 * book list can be used.
 *
 * @param book_list *books pointer to the book list to be initialized
 * initialized
 */
void create_book_list(book_list *books);


/** @brief Creates a new book
 *
 * Allocates memory for a new book and saves the passed fields to the book's
 * details. Saves the address of the new book in *bk.
 *
 * @param book** bk pointer to the address of newly created book
 * @param char[]::title string that stores title of book
 * @param char[]::author string that stores the author of book
 * @param char[]::editor string that stores the editor of book
 * @param int[]::isbn array that stores the ISBN of book
 * @param int::year int that stores the year of book
 * @param int::edition int that stores the edition of book
 * @return 1 if error occurred, 0 if book created with success
 */
int create_book(book **bk, char title[MAX_TITLE_SIZE],
                char author[MAX_AUTHOR_SIZE], char editor[MAX_EDITOR_SIZE],
                int isbn[MAX_ISBN_SIZE], int year, int edition);


/** @brief Inserts book into book list
 *
 * Adds book to the end of the book list.
 *
 * @param book_list* bks pointer to the book list where book will be added
 * @param book *bk pointer of book to be added
 */
void insert_book_booklist(book_list *books, book *bk);



/** @brief Searches for book with title in the book list
 *
 * Searches for a book in the passed book list whose title is the same as the
 * title passed to the function. Previous book in the list is saved to passed
 * parameter prev_book.
 *
 * @param book_list *books pointer to the book list where book will be searched
 * @param char[] title title of book to be searched
 * @param book** prev_book pointer to the pointer of the previous book, will
 * be NULL if book is not in list or book is first element in list
 * @return 0 if book is found on list, 1 otherwise
 */
int search_book_title(book_list *books, char title[MAX_TITLE_SIZE],
                      book **prev_book);


/** @brief Searches for book with isbn in the book list
 *
 * Searches for a book in the passed book list whose isbn is the same as the
 * isbn passed to the function. Previous book in the list is saved to passed
 * parameter prev_book.
 *
 * @param book_list *books pointer to the book list where book will be searched
 * @param int[] isbn isbn of book to be searched
 * @param book** prev_book pointer to the pointer of the previous book, will
 * be NULL if book is not in list or book is first element in list
 * @return 0 if book is found on list, 1 otherwise
 */
int search_book_isbn(book_list *books, int isbn[MAX_ISBN_SIZE],
                     book **prev_book);


/** @brief Removes next book of passed book from list
 *
 * The next book after the passed book is removed from the list and the
 * memory that was allocated to the book is freed.
 *
 * @param book_list *books pointer to the book list where book will be removed
 * @param book** prev_book pointer to the pointer of the previous book, will
 * be NULL to remove first book in list
 * @return 0 if book is removed, 1 otherwise
 */
int remove_book_booklist(book_list *books, book *prev_book);


/** @brief Gets book from book list with title
 *
 * Searches for the book in the library's book list by title and saves the book
 * to the passed book parameter if found.
 *
 * @param book_list *books pointer to book list that will be searched
 * @param char[] title title of book to search for
 * @param book **bk pointer to where the pointer to the found book will
 * be stored
 * @return 0 if book is found, 1 if not found
 */
int get_book_by_title(book_list *books, char title[MAX_TITLE_SIZE], book **bk);


/** @brief Gets book from book list with isbn
 *
 * Searches for the book in the library's book list by isbn and saves the book
 * to the passed book parameter if found.
 *
 * @param book_list *books pointer to book list that will be searched
 * @param int[] isbn title of book to search for
 * @param book **bk pointer to where the pointer to the found book will
 * be stored
 * @return 0 if student is found, 1 if not found
 */
int get_book_by_isbn(book_list *books, int isbn[MAX_ISBN_SIZE], book **bk);


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
 * @param student** stud pointer to student who was removed from wait list
 * @param wait_list* wl pointer to wait list student will be removed from
 * @return 1 if it was not possible to remove student, 0 if student removed
 */
int remove_from_waitlist(wait_list *wl, student **stud);


/** @brief Checks if student is on waitlist
 *
 * Checks if student is already on passed waitlist
 *
 * @param wait_list* wl pointer to wait list student
 * @param student** stud pointer to student who will be checked
 * @return 1 if student is on wait list, 0 if not
 */
int is_on_waitlist(wait_list *wl, student *stud);

/** @brief Removes the student from all wait lists
 *
 * Checks the waitlist for each book and removes the student from any wait list
 * they belong to
 *
 * @param book_list *bks list of all registered books
 * @param student *stud student to be removed
 */
void remove_student_all_waitlists(book_list *bks, student *stud);


