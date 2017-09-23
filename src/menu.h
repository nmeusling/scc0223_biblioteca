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
int complete_action(student_list * studs);

/** @brief Registers a new system into the library system
 *
 * Prompts user for the new student's info. Then calls function to create the
 * student and insert them into student list.
 *
 * @param student_list* studs current list of all students in library system
 * @return 1 if an error occurred during registration, 0 if student was
 * registered successfully
 */
int register_student(student_list *studs);






//void print_student(student *stud);

void print_book(book *bk);

