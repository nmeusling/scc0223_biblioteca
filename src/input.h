/** @file input.h
 *  @brief Header file for input.c
 *
 *  This file contains the declaration for the functions related to user input.
 *
 *  @author Natalie Menato (10295051)
 */



#include <stdio.h>
#include <string.h>
#include "dynamic/library_dynamic.h"
//#include "static/library_static.h"

/** @brief Prompts user to enter desired action
 *
 * Prompts user to enter their desired action and validates that the selection
 * is valid.
 * @return validated user selection
 */
int get_selection();


/** @brief Flushes any extra characters input by user
 *
 * If the user inputs more than the expected number of characters, the extra
 * character are disregarded to prevent errors from occurring during program
 * execution.
 */
void flush_std_in();


/** @brief Prompts user to enter how they want to remove student
 *
 * Prompts user to enter how they want to remove the student. User can select to
 * remove by name or nusp.
 * @return 1 to remove by name, 2 to remove by nusp, 3 to return to menu
 */
int get_remove_type_student();


/** @brief Prompts user to enter how they want to remove book
 *
 * Prompts user to enter how they want to remove the book. User can select to
 * remove by title or ispn.
 * @return 1 to remove by title, 2 to remove by ispn, 3 to return to menu
 */
int get_remove_type_book();


/** @brief Prompts user to enter student's name
 *
 * Prompts user to enter the name of the student.
 * @param char[] name array to store entered name
 */
void get_name(char name[MAX_NAME_SIZE]);


/** @brief Prompts user to enter student's numero usp
 *
 * Prompts user to enter the numero usp of the student.
 * @param int[] nusp array to store entered nusp
 */
void get_nusp(int nusp[MAX_NUSP_SIZE]);


/** @brief Prompts user to enter student's phone
 *
 * Prompts user to enter the phone number of the student.
 * @param int[] phone array to store entered phone
 */
void get_phone(int phone[MAX_PHONE_SIZE]);


/** @brief Prompts user to enter student's email
 *
 * Prompts user to enter the email of the student.
 * @param char[] name array to store entered email
 */
void get_email(char email[MAX_EMAIL_SIZE]);


/** @brief Prompts user to enter book's title
 *
 * Prompts user to enter the title of the book.
 * @param char[] title array to store book's title
 */
void get_title(char title[MAX_TITLE_SIZE]);


/** @brief Prompts user to enter book's author
 *
 * Prompts user to enter the author of the book.
 * @param char[] author array to store book's author
 */
void get_author(char author[MAX_EDITOR_SIZE]);


/** @brief Prompts user to enter book's editor
 *
 * Prompts user to enter the editor of the book.
 * @param char[] editor array to store book's editor
 */
void get_editor(char editor[MAX_EDITOR_SIZE]);


/** @brief Prompts user to enter book's isbn
 *
 * Prompts user to enter the ISBN of the book.
 * @param int[] isbn array to store book's isbn
 */
void get_isbn(int isbn[MAX_ISBN_SIZE]);


/** @brief Prompts user to enter book's year
 *
 * Prompts user to enter the year of the book.
 * @param int year stores the year of the book
 */
void get_year(int *year);


/** @brief Prompts user to enter book's edition
 *
 * Prompts user to enter the edition of the book.
 * @param int edition stores the edition of the book
 */
void get_edition(int *edition);


/** @brief Prompts user to enter how they want to search for student
 *
 * Prompt user to enter if they want to search for the student by name or by
 * nusp. Return user's selection.
 * @return int 1 to search by name, 2 to search by nusp
 */
int get_search_type_student();


/** @brief Prompts user to enter how they want to search for book
 *
 * Prompt user to enter if they want to search for the book by title or by
 * isbn. Return user's selection.
 * @return int 1 to search by title, 2 to search by isbn
 */
int get_search_type_book();

