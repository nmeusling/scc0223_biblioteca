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

    //create library
    library lib;
    create_library(&lib);

    //main loop for menu
    while(complete_action(&lib));

}

