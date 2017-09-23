/** @file main.c
 *  @brief Main function for Library Management System project
 *
 *  Contains the main function for the implementation of the Library Management
 *  System.
 *
 *  @author Natalie Menato (10295051)
 */

#include "menu.h"

void print_student(student *stud){
    int i;
    printf("\nNome: %s", stud->name);
    printf("Numero Usp: ");
    for(i = 0; i<MAX_NUSP_SIZE; i++){
        if((stud->nusp)[i] != -1){
            printf("%d", (stud->nusp)[i]);
        }
    }
    printf("\nTelefone: ");
    for(i = 0; i<MAX_PHONE_SIZE; i++){
        if((stud->phone)[i] != -1){
            printf("%d", (stud->phone)[i]);
        }
    }
    printf("\nEmail: %s", stud->email);
}

void print_students(student_list *studs){
    student *stud = studs->first;
    while(stud != NULL) {
        print_student(stud);
        stud = stud->next;
    }

}

int main(){
    print_home();
    student_list students;
    create_stud_list(&students);
    while(complete_action(&students)){
       // print_students(&students);
    }


}

