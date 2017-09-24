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

void print_book(book *bk) {
    int i;
    printf("\nTitulo: %s", bk->title);
    printf("Autor: %s", bk->author);
    printf("Editora: %s", bk->editor);
    printf("ISBN: ");
    for(i = 0; i<MAX_ISBN_SIZE; i++){
        if((bk->isbn)[i] != -1){
            printf("%d", (bk->isbn)[i]);
        }
    }
    printf("\nAno: %d", bk->year);
    printf("\nEdicao: %d", bk->edition);
}

void print_books(book_list *bks){
    book *bk = bks->first;
    while(bk != NULL) {
        print_book(bk);
        bk = bk->next;
    }

}

int main(){
    print_home();

    student_list students;
    book_list books;
    //student* prev_stud;
    //char name[MAX_NAME_SIZE];
    //get_name(name);

    create_stud_list(&students);
    create_book_list(&books);
//    register_student(&students);
//    register_student(&students);
//    register_student(&students);
//    printf("Result of search: %d" ,search_student_name(&students, name, &prev_stud));
    while(complete_action(&students, &books)){
       print_students(&students);
        print_books(&books);
    }


}

