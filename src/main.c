/** @file main.c
 *  @brief Main function for Library Management System project
 *
 *  Contains the main function for the implementation of the Library Management
 *  System.
 *
 *  To switch between the dynamic and static versions, update the include
 *  in input.h
 *
 *  @author Natalie Menato (10295051)
 */

#include "menu.h"



int main(){
    print_home();

    //create student and book lists
    student_list students;
    book_list books;

    //initialize the lists
    create_stud_list(&students);
    create_book_list(&books);

    //main loop for menu
    while(complete_action(&students, &books));

}

