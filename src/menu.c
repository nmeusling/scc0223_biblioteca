//
// Created by nmeusling on 9/5/17.
//

#include "menu.h"




void print_home() {
    printf("Bem Vindo ao Sistema Biblioteca!\n" \
           "----------------------------------\n");
}

void print_menu() {
    printf("Acoes possiveis: \n" \
           "1. Cadastrar Aluno\n" \
           "2. Cadastrar Livro\n" \
           "3. Retirar Livro\n" \
           "4. Retornar Livro\n" \
           "5. Removere Livro\n" \
           "6. Remover Aluno\n" \
           "7. Imprimir Emails para um Aluno\n" \
           "8. Sair do Sistema\n");
}

int get_selection() {
    printf("\nQual acao voce gostaria de fazer?: ");
    //convert from char into the int it represtne
    int input = getchar() - 48;
    flush_std_in();
    while(input < 1 || input > 8)
    {
        printf("\nOpcao Invalida! Por favor, digite de novo: ");
        input = getchar() - 48;
        flush_std_in();
    }
    return input;
}

/*
 * Flushes any extra characters input by the user to prevent input errors from
 * causing runtime errors.
 */
void flush_std_in() {
//Flushes any extra chars input by user
    int ch = getchar();
    while ((ch != '\n') && (ch != EOF)){
        ch = getchar();
    }
}

int menu_register_student(student *stud){
    //char name[MAX_NAME_SIZE];
    //int nusp;
    //int phone[MAX_PHONE_SIZE];
    //char email[MAX_EMAIL_SIZE];
    int i = 0;

    printf("\nPorfavor, digite os dados para o aluno novo: ");
    printf("\nNome: ");
    fgets(stud->name, MAX_NAME_SIZE, stdin);
    flush_std_in();

    printf("Numero USP: ");
    while(scanf("%d", &(stud->nusp)) == 0){
        printf("Invalido! Digite de novo: ");
        flush_std_in();
    }
    flush_std_in();

    printf("Numero de telefone: ");
    int digit = getchar() - 48;
    while(digit != '\n' && digit != 'EOF' && i<MAX_PHONE_SIZE){
        if(digit >= 0 && digit <= 9){
            (stud->phone)[i] = digit;
            i++;
        }
        digit = getchar()-48;
    }
    while(i<MAX_PHONE_SIZE){
        (stud->phone)[i] = -1;
        i++;
    }

    printf("Email: ");
    fgets(stud->email, MAX_EMAIL_SIZE, stdin);

}

void print_student(student *stud){
    int i;
    printf("\nNome: %s", stud->name);
    printf("\nNumero Usp: %d", stud->nusp);
    printf("\nTelefone: ");
    for(i = 0; i<MAX_PHONE_SIZE; i++){
        if((stud->phone)[i] != -1){
            printf("%d", (stud->phone)[i]);
        }
    }
    printf("\nEmail: %s", stud->email);
}
int menu_register_book(){

}
