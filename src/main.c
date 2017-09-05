//
// Created by nmeusling on 9/5/17.
//

#include "menu.h"
int main(){
    print_home();
    print_menu();
    int input = get_selection();
    printf("Opcao selecionada: %d", input);
    student stud;
    menu_register_student(&stud);
    print_student(&stud);
}