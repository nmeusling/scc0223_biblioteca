//
// Created by nmeusling on 10/8/17.
//

#define MAX_TITLE_SIZE 100
#define MAX_AUTHOR_SIZE 100
#define MAX_EDITOR_SIZE 100
#define MAX_ISBN_SIZE 20

#include "student_dynamic.h"


/** @struct wait_list_entry
 *  @brief Node for wait list
 *  @var student::stud pointer to the student on wait list
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
 *  @var wait_list::first
 *  @var wait_list::last
 *  Member 'first' pointer to the first student node of wait list
 *  Member 'last' pointer to the last student node of wait list
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
 *  @var book*::next
 *  @var wait_list::wl
 *  Member 'title' string that stores title of book
 *  Member 'author' string that stores the author of book
 *  Member 'editor' string that stores the editor of book
 *  Member 'isbn' array that stores the ISBN of book
 *  Member 'year' int that stores the year of book
 *  Member 'edition' int that stores the edition of book
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
 * @param library* lib pointer to the library where the book list will be
 * initialized
 */
void create_book_list(book_list *books);


int create_book(book **bk, char title[MAX_TITLE_SIZE],
                char author[MAX_AUTHOR_SIZE], char editor[MAX_EDITOR_SIZE],
                int isbn[MAX_ISBN_SIZE], int year, int edition);




/** @brief Creates a new book and adds it to library's book list
 *
 * Allocates memory for a new book. Saves the passed title, author, editor,
 * isbn, year, and edition to the new book. Adds the new book to the end of
 * existing book list of passed library. If the ISBN is duplicated, a new record
 * will not be added to the list. Instead the count of books of the original
 * will be incremented.
 *
 * @param library* lib pointer to the library that contains the book list
 * @param char[] title title of the book to be added
 * @param char[] author author of the book to be added
 * @param char[] editor editor of the book to be added
 * @param int[] isbn ISBN of the book to be added
 * @param int year year of the book to be added
 * @param int edition edition of the book to be added
 * @return 1 if an error occurred, 0 if student inserted successfully, 2 for dupliacte
 */
void insert_book_booklist(book_list *books, book *bk);



/** @brief Searches for book with title in the library's book list
 *
 * Searches for a book in the library's book list whose title is the same as the
 * title passed to the function. Previous book in the list is saved to passed
 * parameter prev_book.
 *
 * @param library* lib pointer to the library that contains book list
 * @param char[] title title of book to be searched
 * @param book** prev_book pointer to the pointer of the previous book, will
 * be NULL if book is not in list or book is first element in list
 * @return 0 if book is found on list, 1 otherwise
 */
int search_book_title(book_list *books, char title[MAX_TITLE_SIZE],
                      book **prev_book);


/** @brief Searches for book with ISBN in the library's book list
 *
 * Searches for a book in the library's book list whose ISBN is the same as the
 * ISBN passed to the function. Previous book in the list is saved to passed
 * parameter prev_book.
 *
 * @param library* lib pointer to the library
 * @param int[] isbn ISBN of book to be searched
 * @param book** prev_book pointer to the pointer of the previous book, will
 * be NULL if book is not in list or book is first element in list
 * @return 0 if book is found on list, 1 otherwise
 */
int search_book_isbn(book_list *books, int isbn[MAX_ISBN_SIZE],
                     book **prev_book);


int remove_book_booklist(book_list *books, book *prev_book);



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
int get_book_by_title(book_list *books, char title[MAX_TITLE_SIZE], book **bk);


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



