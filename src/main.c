//
// Created by nmeusling on 9/5/17.
//

#include "menu.h"

int main(){
    print_home();
    print_menu();
    int input = get_selection();
    int error;
    student stud;
    //get_student_info(&stud);
    //print_student(&stud);
    book bk;
    get_book_info(&bk);
    print_book(&bk);

    //Consider changing ISBN to array of ints
    //Improve error checking for input (flush and etc)



}