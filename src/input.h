/** @file input.h
 *  @brief Header file for input.c
 *
 *  This file contains the declaration for the functions related to user input.
 *
 *  @author Natalie Menato (10295051)
 */


#ifndef SCC0223_BIBLIOTECA_INPUT_H
#define SCC0223_BIBLIOTECA_INPUT_H

#include <stdio.h>
#include <string.h>
#include "library_dynamic.h"

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
int get_remove_type();

/** @brief Prompts user to enter student's name
 *
 * Prompts user to enter the name of the student.
 * @param char[] name location to store entered name
 */
void get_name(char name[MAX_NAME_SIZE]);

/** @brief Prompts user to enter student's numero usp
 *
 * Prompts user to enter the numero usp of the student.
 * @param int[] nusp location to store entered nusp
 */
void get_nusp(int nusp[MAX_NUSP_SIZE]);

/** @brief Prompts user to enter student's phone
 *
 * Prompts user to enter the phone number of the student.
 * @param int[] phone location to store entered phone
 */
void get_phone(int phone[MAX_PHONE_SIZE]);

/** @brief Prompts user to enter student's email
 *
 * Prompts user to enter the email of the student.
 * @param char[] name location to store entered email
 */
void get_email(char email[MAX_EMAIL_SIZE]);

int get_book_info(book *bk);

void get_title(char *title);

void get_author(char *author);

void get_editor(char *editor);

void get_isbn(char *isbn);

void get_year(int *year);

void get_edition(int *edition);


#endif //SCC0223_BIBLIOTECA_INPUT_H
