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

/** @brief Menu to allow user to select how to remove student
 *
 * Prompts user to select how they would like to remove the student. Calls the
 * appropriate function to delete the student based on user's selection.
 *
 * @param student_list* studs current list of all students in library system
 */
void remove_student(student_list *studs);

/** @brief Reads in name of student and calls function to delete student
 *
 * Prompts user to input the name of the student to be deleted. Then calls the
 * function to remove the student with this name from the student list.
 *
 * @param student_list* studs current list of all students in library system
 * @return 0 if student was removed, 1 if it was not possible to remove student
 */
int menu_remove_student_name(student_list *studs);

/** @brief Reads in nusp of student and calls function to delete student
 *
 * Prompts user to input the nusp of the student to be deleted. Then calls the
 * function to remove the student with this nusp from the student list.
 *
 * @param student_list* studs current list of all students in library system
 * @return 0 if student was removed, 1 if it was not possible to remove student
 */
int menu_remove_student_nusp(student_list *studs);


//void print_student(student *stud);

void print_book(book *bk);

