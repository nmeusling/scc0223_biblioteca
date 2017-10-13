/** @file book_static.h
 *  @brief Header file for book_static.c
 *
 *  Static version:
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

#define WAIT_LIST_SIZE 1000
#define MAX_BOOKS 1000

#include "student_static.h"


/** @struct wait_list_entry
 *  @brief Node for wait list
 *  @var student::stud
 *  @var int::next
 *  Member 'stud' pointer to the student on wait list
 *  Member 'next' index of next student on wait list
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


/** @struct book
 *  @brief Stores all of the information related to a book
 *  @var student::title
 *  @var student::author
 *  @var student::editor
 *  @var student::isbn
 *  @var student::year
 *  @var student::edition
 *  @var student::count
 *  @var int::total
 *  @var int::next
 *  @var int::wait_list_first
 *  @var int::wait_list_last
 *  @var int::wait_list_total
 *  Member 'title' string that stores title of book
 *  Member 'author' string that stores the author of book
 *  Member 'editor' string that stores the editor of book
 *  Member 'isbn' array that stores the ISBN of book
 *  Member 'year' int that stores the year of book
 *  Member 'edition' int that stores the edition of book
 *  Member 'count' int that stores the number of available books
 *  Member 'total' int that stores the total number of books
 *  Member 'next' index of the next book in the book list
 *  Member 'wait_list_first' index of first entry of wait list
 *  Member 'wait_list_last' index of last entry of wait list
 *  Member 'wait_list_total' number of students on wait list
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
    int next;
    int waitlist_first, waitlist_last, waitlist_total;
} book;


/** @struct book
 *  @brief List to store book nodes
 *  @var int::first_empty
 *  @var int::first
 *  @var int::last
 *  @var wait_list::wl
 *  Member 'first_empty' index of the first empty space in book memory bank
 *  Member 'first' index of the first book of list
 *  Member 'last' index of the last book of list
 *  Member 'wl' memory bank that will be used to store wait lists of all books
 */
typedef struct {
    int first_empty, first, last;
    book elements[MAX_BOOKS];
    wait_list wl;
} book_list;


/** @brief Get next space in book list
 *
 * Find the next available space in the memory bank for the book.
 *
 * @param book_list *books book list where memory will be searched
 * @return index of available space, -1 if no available space
 */
int get_node_booklist(book_list *books);


/** @brief Free the specified index of book memory bank
 *
 * Free the specified index in the book memory bank. Adds space back to empty
 * list.
 *
 * @param book_list *books book list where memory will be freed
 * @param int index index that will be freed
 */
void free_node_booklist(book_list *books, int index);


/** @brief Get next space in wait list
 *
 * Find the next available space in the memory bank for the wait list.
 *
 * @param wait_list *wl wait list where memory will be searched
 * @return index of available space, -1 if no available space
 */
int get_node_waitlist(wait_list *wl);


/** @brief Free the specified index of wait list memory bank
 *
 * Free the specified index in the wait list memory bank.
 *
 * @param wait_list *wl wait list where memory will be freed
 * @param int index index that will be freed
 */
void free_node_waitlist(wait_list *wl, int index);


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
 * details. Returns index of new book.
 *
 * @param book_list* books pointer to book list where book memory will be allocated
 * @param char[]::title string that stores title of book
 * @param char[]::author string that stores the author of book
 * @param char[]::editor string that stores the editor of book
 * @param int[]::isbn array that stores the ISBN of book
 * @param int::year int that stores the year of book
 * @param int::edition int that stores the edition of book
 * @return index of created book, -1 if error occurred
 */
int create_book(book_list *books, char title[MAX_TITLE_SIZE],
                char author[MAX_AUTHOR_SIZE], char editor[MAX_EDITOR_SIZE],
                int isbn[MAX_ISBN_SIZE], int year, int edition);


/** @brief Inserts book into book list
 *
 * Adds book to the end of the book list.
 *
 * @param book_list* bks pointer to the book list where book will be added
 * @param book *bk pointer of book to be added
 */
void insert_book_booklist(book_list *books, int index);


/** @brief Searches for book with title in the book list
 *
 * Searches for a book in the passed book list whose title is the same as the
 * title passed to the function. Index of previous book in the list is saved to
 * passed parameter prev_book.
 *
 * @param book_list *books pointer to the book list where book will be searched
 * @param char[] title title of book to be searched
 * @param int *prev_book index of the previous book, will be -1 if book is not
 * in list or book is first element in list
 * @return 0 if book is found on list, 1 otherwise
 */
int search_book_title(book_list *books, char title[MAX_TITLE_SIZE],
                      int *prev_book);


/** @brief Searches for book with isbn in the book list
 *
 * Searches for a book in the passed book list whose isbn is the same as the
 * isbn passed to the function. Index of previous book in the list is saved to
 * passed parameter prev_book.
 *
 * @param book_list *books pointer to the book list where book will be searched
 * @param char[] title title of book to be searched
 * @param int *prev_book index of the previous book, will be -1 if book is not
 * in list or book is first element in list
 * @return 0 if book is found on list, 1 otherwise
 */
int search_book_isbn(book_list *books, int isbn[MAX_ISBN_SIZE],
                     int *prev_book);


/** @brief Removes next book of passed book from list
 *
 * The next book after the passed book is removed from the list and the
 * memory that was allocated to the book is freed.
 *
 * @param book_list *books pointer to the book list where book will be removed
 * @param int prev_book index of the previous book, will be -1 to remove first
 * book on list
 * @return 0 if book is removed, 1 otherwise
 */
int remove_book_booklist(book_list *books, int prev_book);


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
 * @return 0 if book is found, 1 if not found
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
 * pointing to -1.
 *
 * @param wait_list* wl wait list to be created
 */
void create_wait_list(wait_list *wl);


/** @brief Clears the wait list queue
 *
 * Clears the wait list and returns it to it's initial position, with first and
 * last pointing to -1. Frees the memory in the wait list memory bank of all
 * nodes that were part of the wait list.
 *
 * @param wait_list* wl wait list to be removed
 */
void remove_wait_list(book *bk, book_list *bks);


/** @brief Adds student to waitlist
 *
 * Adds the passed student as the last element in the passed wait list.
 *
 * @param student* stud pointer to student who will be added to wait list
 * @param book *bk pointer to book whose wait list student will be added
 * @param book_list* books pointer to book list that contains wait list memory
 * bank
 * @return 1 if it was not possible to add student, 0 if student added
 */
int add_to_waitlist(student *stud, book *bk, book_list *books);


/** @brief Removes student from waitlist
 *
 * Removes the first student from the waitlist and saves a pointer to the
 * student in the passed value.
 *
 * @param book *bk pointer to book whose wait list student will be removed
 * @param book_list* books pointer to book list that contains wait list memory
 * bank
 * @param student** stud where address of removed student will be saved
 * @return 1 if it was not possible to remove student, 0 if student removed
 */
int remove_from_waitlist(book *bk, book_list *books, student **stud );


/** @brief Checks if student is on waitlist
 *
 * Checks if student is already on passed waitlist
 *
 * @param book *bk pointer to book whose wait list will be checked
 * @param book_list* books pointer to book list that contains wait list memory
 * bank
 * @param student* stud who will be checked
 * @return 1 if student is on wait list, 0 if not
 */
int is_on_waitlist(book *bk, book_list *books, student *stud);


/** @brief Removes the student from all wait lists
 *
 * Checks the waitlist for each book and removes the student from any wait list
 * they belong to
 *
 * @param book_list *bks list of all registered books
 * @param student *stud student to be removed
 */
void remove_student_all_waitlists(book_list *bks, student *stud);