/** @file menu.c
 *  @brief Contains functions related to the menu
 *
 *  This file contains the functions related to the menu. These functions
 *  allow the user to control the program and select the desired actions.
 *
 *  @author Natalie Menato (10295051)
 */

#include "menu.h"


/*
 * Prints the welcome message.
 */
void print_home() {
    printf("\nBem Vindo ao Sistema Biblioteca!" \
           "\n--------------------------------\n\n");
}

/*
 * Prints the possible menu actions.
 */
void print_menu() {
    printf("\nAcoes possiveis: \n" \
           "1. Cadastrar Aluno\n" \
           "2. Cadastrar Livro\n" \
           "3. Retirar Livro\n" \
           "4. Retornar Livro\n" \
           "5. Removere Livro\n" \
           "6. Remover Aluno\n" \
           "7. Imprimir Emails para um Aluno\n" \
           "8. Sair do Sistema\n");
}

/*
 * Gets the user's desired action and completes it. Returns 1 when action is
 * completed. Returns 0 if the desired action is to quit.
 */
int complete_action(student_list *studs) {
    print_menu();
    int selection = get_selection();
    switch (selection) {
        case 1:
            register_student(studs);
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            remove_student(studs);
            break;
        case 7:
            break;
        default:
            return 0;
    }
    return 1;
}

/*
 * Prompts user to input information for the new student. Creates a new
 * student and adds the student to the list of students. Returns 0 if student
 * was registered with success, returns 0 if an error occurred.
 */
int register_student(student_list *studs) {

    printf("\nPorfavor, digite os dados para o aluno novo: ");
    char name[MAX_NAME_SIZE];
    int nusp[MAX_NUSP_SIZE];
    int phone[MAX_PHONE_SIZE];
    char email[MAX_EMAIL_SIZE];

    get_name(name);
    get_nusp(nusp);
    get_phone(phone);
    get_email(email);

    if (insert_student(studs, name, nusp, phone, email) == 1) {
        printf("\nNao foi possivel registrar o estudante!");
        return 1;
    }

    return 0;
}

int remove_student(student_list *studs) {
    int type = get_remove_type();

    switch (type) {
        case 1:
            if (menu_remove_student_name(studs) == 1)
                printf("\nNao foi possivel remover o estudante!");
            else
                printf("\nEstudante foi removido!");
            break;
        case 2:
            if (menu_remove_student_nusp(studs) == 1)
                printf("\nNao foi possivel remover o estudante!");
            else
                printf("\nEstudante foi removido!");
            break;
        default:
            return 0;
    }

    return 0;

}

int menu_remove_student_name(student_list *studs) {
    char name[MAX_NAME_SIZE];
    printf("Digite o nome do estudante que voce quer remover: ");
    get_name(name);
    if (remove_student_name(studs, name) == 1) {
        return 1;
    }
    return 0;
}

int menu_remove_student_nusp(student_list *studs) {
    int nusp[MAX_NUSP_SIZE];
    printf("Digite o NUSP do estudante que voce quer remover: ");
    get_nusp(nusp);
    if (remove_student_nusp(studs, nusp) == 1) {
        return 1;
    }
    return 0;
}














//void print_student(student *stud){
//    int i;
//    printf("\nNome: %s", stud->name);
//    printf("Numero Usp: ");
//    for(i = 0; i<MAX_NUSP_SIZE; i++){
//        if((stud->nusp)[i] != -1){
//            printf("%d", (stud->nusp)[i]);
//        }
//    }
//    printf("\nTelefone: ");
//    for(i = 0; i<MAX_PHONE_SIZE; i++){
//        if((stud->phone)[i] != -1){
//            printf("%d", (stud->phone)[i]);
//        }
//    }
//    printf("\nEmail: %s", stud->email);
//}

void print_book(book *bk) {
    int i;
    printf("\nTitulo: %s", bk->title);
    printf("Autor: %s", bk->author);
    printf("Editora: %s", bk->editor);
    printf("ISBN: %s", bk->isbn);
    printf("Ano: %d", bk->year);
    printf("\nEdicao: %d", bk->edition);
}