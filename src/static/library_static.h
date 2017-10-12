/** @file library_static.h
 *  @brief Header file for library_static.c
 *
 *  This file contains the declaration for the library structs, including the
 *  student list, book list, and wait list. It also contains the prototypes for
 *  the operations that manipulate these lists.
 *
 *  @author Natalie Menato (10295051)
 */


#include "book_static.h"


/** @struct library
 *  @brief Contains the book list and student list of the library
 *  @var book_list::books
 *  @var student_list::students
 *  Member 'books' list of all books in the library
 *  Member 'students' list of all students in the library
 */
typedef struct{
    book_list books;
    student_list students;
} library;


/** @brief Creates a new library
 *
 * Initializes a library so that the other functions for related to the
 * library can be used successfully.
 *
 * @param library* lib pointer to the library
 */
void create_library(library *lib);




/** @brief Creates a new student and adds it to student list of library
 *
 * Allocates memory in memory bank for a new student. Saves the passed name,
 * nusp, phone, and email to the new student. Adds the new student to the end
 * of existing student list for the passed library.
 *
 * @param library* lib pointer to the library
 * @param char[] name name of student to be added
 * @param int[] nusp Numero USP of student to be added
 * @param int[] phone Phone number of student to be added
 * @param char[] email Email of student to be added
 * @return 1 if an error occurred, 0 if student inserted successfully
 */
int insert_student(library *lib, char name[MAX_NAME_SIZE],
                   int nusp[MAX_NUSP_SIZE], int phone[MAX_PHONE_SIZE],
                   char email[MAX_EMAIL_SIZE]);

int remove_student(library *lib, int prev_stud);


/** @brief Removes student with name from the student list
 *
 * Uses search function to find previous student in library's student list and
 * then removes the desired student.
 *
 * @param library* lib pointer to the library where student will be removed
 * @param char[] name name of student to be removed
 * @param student** prev_stud pointer to the pointer of the previous student, will
 * be NULL if student is not in list or student is first element in list
 * @return 0 if student removed successfully, 1 otherwise
 */
int remove_student_name(library *lib, char name[MAX_NAME_SIZE]);


/** @brief Removes student with nusp from the student list
 *
 * Uses search function to find previous student in library's student list and
 * then removes the desired student.
 *
 * @param library* lib pointer to the library where student will be removed
 * @param int[] nusp nusp of student to be removed
 * @param student** prev_stud pointer to the pointer of the previous student, will
 * be NULL if student is not in list or student is first element in list
 * @return 0 if student removed successfully, 1 otherwise
 */
int remove_student_nusp(library *lib, int nusp[MAX_NUSP_SIZE]);



/** @brief Creates a new book and adds it to library's book list
 *
 * Allocates memory in the memory bank for a new book. Saves the passed title,
 * author, editor, isbn, year, and edition to the new book. Adds the new book
 * to the end of existing book list of passed library. If the ISBN is
 * duplicated, a new record will not be added to the list. Instead the count of
 * books of the original will be incremented.
 *
 * @param library* lib pointer to the library that contains the book list
 * @param char[] title title of the book to be added
 * @param char[] author author of the book to be added
 * @param char[] editor editor of the book to be added
 * @param int[] isbn ISBN of the book to be added
 * @param int year year of the book to be added
 * @param int edition edition of the book to be added
 * @return 1 if an error occurred, 0 if student inserted successfully
 */
int insert_book(library *lib, char title[MAX_TITLE_SIZE],
                char author[MAX_AUTHOR_SIZE], char editor[MAX_EDITOR_SIZE],
                int isbn[MAX_ISBN_SIZE], int year, int edition);



/** @brief Removes book with title from the library's book list
 *
 * Uses search function to find previous book in library's book list and then
 * removes the desired book.
 *
 * @param library* lib pointer to the library
 * @param char[] title title of book to be removed
 * @return 0 if book removed successfully, 1 otherwise
 */
int remove_book_title(library *lib, char title[MAX_TITLE_SIZE]);


/** @brief Removes book with ISBN from the library's book list
 *
 * Uses search function to find previous book in library's book list and then
 * removes the desired book.
 *
 * @param library* lib pointer to the library
 * @param int[] isbn ISBN of book to be removed
 * @return 0 if book removed successfully, 1 otherwise
 */
int remove_book_isbn(library *lib, int isbn[MAX_ISBN_SIZE]);


/** @brief Completes necessary actions to check out a book
 *
 * If book is available, decrements the number of available copies. If book is
 * not available, student is added to the wait list.
 *
 * @param student *stud student who is checking out book
 * @param book *bk book to be checked out
 * @return 1 if added to waitlist, 0 if book was available
 */
int checkout_book(library *lib, student *stud, book *bk);


/** @brief Completes necessary actions to return a book
 *
 * If book does not have a waitlist, increments the number of available copies.
 * If book has a waitlist, sends an email to the next student and removes them
 * from wait list. Returns 1 if no student on waitlist, 0 if next student was
 * notified.
 *
 * @param book *bk book that was returned
 */
int return_book(library *lib, book *bk);


