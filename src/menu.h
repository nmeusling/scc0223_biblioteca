/** @file menu.h
 *  @brief Header file for menu.c
 *
 *  This file contains the declaration for the functions related to the menu.
 *
 *  @author Natalie Menato (10295051)
 */

#include "input.h"



/** @brief Prints welcome screen
 *
 * Prints the program's home screen, welcoming the user.
 */
void print_home();


/** @brief Prints menu
 *
 * Prints the menu that shows all of the available actions
 */
void print_menu();


/** @brief Completes user's desired action
 *
 * Prompts the user for their desired action and then calls all necessary
 * functions to complete the action.
 *
 * @param student_list* studs current list of all students in library system
 * @return 1 when action is completed, 0 to quit program
 */
int complete_action(student_list * studs, book_list *books);


/** @brief Registers a new student into the library system
 *
 * Prompts user for the new student's info. Then calls function to create the
 * student and insert it into student list.
 *
 * @param student_list* studs current list of all students in library system
 * @return 1 if an error occurred during registration, 0 if student was
 * registered successfully
 */
int register_student(student_list *studs);


/** @brief Menu to allow user to select how to remove student
 *
 * Prompts user to select how they would like to remove the student. Calls the
 * appropriate function to delete the student based on user's selection.
 *
 * @param student_list* studs current list of all students in library system
 */
void remove_student(book_list *books, student_list *studs);


/** @brief Reads in name of student and calls function to delete student
 *
 * Prompts user to input the name of the student to be deleted. Then calls the
 * function to remove the student with this name from the student list.
 *
 * @param student_list* studs current list of all students in library system
 * @return 0 if student was removed, 1 if it was not possible to remove student
 */
int menu_remove_student_name(book_list *books, student_list *studs);


/** @brief Reads in nusp of student and calls function to delete student
 *
 * Prompts user to input the nusp of the student to be deleted. Then calls the
 * function to remove the student with this nusp from the student list.
 *
 * @param student_list* studs current list of all students in library system
 * @return 0 if student was removed, 1 if it was not possible to remove student
 */
int menu_remove_student_nusp(book_list *books, student_list *studs);


/** @brief Registers a new book into the library system
 *
 * Prompts user for the new book's info. Then calls function to create the
 * book and insert it into book list.
 *
 * @param book_list* books current list of all students in library system
 * @return 1 if an error occurred during registration, 0 if book was
 * registered successfully
 */
int register_book(book_list *books);


/** @brief Menu to allow user to select how to remove book
 *
 * Prompts user to select how they would like to remove the book. Calls the
 * appropriate function to delete the book based on user's selection.
 *
 * @param book_list* books current list of all books in library system */
void remove_book(book_list *books);


/** @brief Reads in title of book and calls function to delete book
 *
 * Prompts user to input the title of the book to be deleted. Then calls the
 * function to remove the book with this title from the book list.
 *
 * @param book_list* books current list of all books in library system
 * @return 0 if book was removed, 1 if it was not possible to remove book.
 */
int menu_remove_book_title(book_list *books);


/** @brief Reads in ISBN of book and calls function to delete book
 *
 * Prompts user to input the ISBN of the book to be deleted. Then calls the
 * function to remove the book with this ISBN from the book list.
 *
 * @param book_list* books current list of all books in library system
 * @return 0 if book was removed, 1 if it was not possible to remove book.
 */
int menu_remove_book_isbn(book_list *books);


/** @brief Prompts user to enter student and book for check out
 *
 * Prompts user to input the student and the book they wish to check out. Calls
 * the functions to necessary to complete check out action.
 *
 * @param book_list* books current list of all books in library system
 * @param student_list *studs current list of all students in library system
 * @return 0 if book was removed, 1 if it was not possible to remove book.
 */
int menu_check_out_book(book_list *books, student_list *studs);


/** @brief Prompts user to enter the book that will be returned
 *
 * User can return book by title or ISBN number. Calls all functions necessary
 * to return the book.
 *
 * @param book_list* books current list of all books in library system
 * @param student_list studs current list of all students in library system
 * @return 0 if book was returned, 1 if it was not possible to return book.
 */
int menu_return_book(book_list *books);


/** @brief Prints all emails in stack for student
 *
 * Prompt user to select the desired student and then ṕrints all of the
 * available email messages for the selected student.
 *
 * @param student_list* studs current list of all students in library system
 * @return 0 if student is found, 1 if it was not possible to find student.
 */
int print_emails(student_list *studs);


/** @brief Prints all of the data related to the passed student
 *
 * Prints the name, numero usp, phone and email of the student.
 *
 * @param student* stud student whose data will be printed
 */
void print_student(student *stud);


/** @brief Prints the data of all the students in the student list
 *
 * Prints the name, numero usp, phone and email of each student in the list.
 *
 * @param student_list* studs list of all registered students
 */
void print_students(student_list *studs);


/** @brief Prints all of the data related to the passed book
 *
 * Prints the title, author, editor, ISBN, year, and edition of the book.
 *
 * @param book* bk book whose data will be printed
 */
void print_book(book *bk);


/** @brief Prints the data of all the books in the book list
 *
 * Prints the title, author, editor, ISBN, year, and edition of each book in
 * the list.
 *
 * @param sbook_list* bks list of all registered books
 */
void print_books(book_list *bks);