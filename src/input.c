/** @file input.c
 *  @brief Contains functions related to user input
 *
 *  All of the functions that prompt the user for input are in this file.
 *
 *  @author Natalie Menato (10295051)
 */

#include "input.h"

/*
 * Prompts the user to input the desired action and returns selection as int.
 */
int get_selection() {
    printf("\nAcao (1-8): ");
    //convert from char into the int that it represents
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
    int ch;
    while (((ch = getchar()) != '\n') && (ch != EOF));
}

/*
 * Prompts user to enter how they want to remove the student. Returns 1 if
 * user wants to remove by name, 2 if user wants to remove by NUSP, 3 if the
 * user wants to return to main menu.
 */
int get_remove_type_student(){
    printf("\nRemover Aluno: ");
    printf("\n1 - Remover por nome");
    printf("\n2 - Remover por Numero USP");
    printf("\n3 - Voltar ao Menu Principal");
    printf("\nQual acao voce gostaria de fazer?: ");
    //convert from char into the int that it represents
    int input = getchar() - 48;
    flush_std_in();
    while(input < 1 || input > 3)
    {
        printf("\nOpcao Invalida! Por favor, digite de novo: ");
        input = getchar() - 48;
        flush_std_in();
    }
    return input;
}

/*
 * Prompts user to enter how they want to remove the book. Returns 1 if
 * user wants to remove by title, 2 if user wants to remove by ISBN, 3 if the
 * user wants to return to main menu.
 */
int get_remove_type_book(){
    printf("\nRemover Livro: ");
    printf("\n1 - Remover por titulo");
    printf("\n2 - Remover por ISBN");
    printf("\n3 - Voltar ao Menu Principal");
    printf("\nQual acao voce gostaria de fazer?: ");
    //convert from char into the int that it represents
    int input = getchar() - 48;
    flush_std_in();
    while(input < 1 || input > 3)
    {
        printf("\nOpcao Invalida! Por favor, digite de novo: ");
        input = getchar() - 48;
        flush_std_in();
    }
    return input;
}

/*
 * Prompt user to enter name. Save the name to passed array.
 */
void get_name(char name[MAX_NAME_SIZE]){
    //char name[MAX_NAME_SIZE];
    printf("\nNome: ");
    fgets(name, MAX_NAME_SIZE, stdin);
    //flush_std_in();
    //return name;
}

/*
 * Prompt user to enter Numero USP. Save the NUSP to passed array.
 */
void get_nusp(int nusp[MAX_NUSP_SIZE]){
    printf("Numero USP: ");
    int i = 0;
    int digit = getchar();
    while(digit != '\n' && i<MAX_NUSP_SIZE){
        if(digit - 48 >= 0 && digit - 48 <= 9){
            nusp[i] = digit-48;
            i++;
        }
        digit = getchar();
    }
    while(i<MAX_NUSP_SIZE){
        nusp[i] = -1;
        i++;
    }
}

/*
 * Prompt user to enter Phone. Save the phone to passed array.
 */
void get_phone(int phone[MAX_PHONE_SIZE]){
    printf("Numero de telefone: ");
    int i = 0;
    int digit = getchar();
    while(digit != '\n' && i<MAX_PHONE_SIZE){
        if(digit - 48 >= 0 && digit - 48 <= 9){
            phone[i] = digit-48;
            i++;
        }
        digit = getchar();
    }
    while(i<MAX_PHONE_SIZE){
        phone[i] = -1;
        i++;
    }
}

/*
 * Prompt user to enter email. Save the email to passed array.
 */
void get_email(char email[MAX_EMAIL_SIZE]){
    printf("Email: ");
    fgets(email, MAX_EMAIL_SIZE, stdin);
}

/*
 * Prompt user to enter title. Save the title to passed array.
 */
void get_title(char title[MAX_TITLE_SIZE]){
    printf("\nTitulo: ");
    fgets(title, MAX_TITLE_SIZE, stdin);
}

/*
 * Prompt user to enter author. Save the author to passed array.
 */
void get_author(char author[MAX_AUTHOR_SIZE]){
    printf("Autor: ");
    fgets(author, MAX_AUTHOR_SIZE, stdin);
}

/*
 * Prompt user to enter editor. Save the editor to passed array.
 */
void get_editor(char editor[MAX_EDITOR_SIZE]){
    printf("Editora: ");
    fgets(editor, MAX_EDITOR_SIZE, stdin);
}

/*
 * Prompt user to enter ISBN. Save the ISBN to passed array.
 */
void get_isbn(int isbn[MAX_ISBN_SIZE]){
    printf("ISBN: ");
    int i = 0;
    int digit = getchar();
    while(digit != '\n' && i<MAX_ISBN_SIZE){
        if(digit - 48 >= 0 && digit - 48 <= 9){
            isbn[i] = digit-48;
            i++;
        }
        digit = getchar();
    }
    while(i<MAX_ISBN_SIZE){
        isbn[i] = -1;
        i++;
    }
}

/*
 * Prompt user to enter year. Save the year to passed int.
 */
void get_year(int *year){
    printf("Year: ");
    while(scanf("%d", year)==0){
        printf("Invalido! Tenta de novo: ");
    }
    flush_std_in();
}

/*
 * Prompt user to enter edition. Save the edition to passed int.
 */
void get_edition(int *edition) {
    printf("Edition: ");

    while (scanf("%d", edition) == 0) {
        printf("Invalido! Tenta de novo: ");
    }
    flush_std_in();
}

/*
 * Prompt user to enter if they want to search for the student by name or by
 * nusp. Return user's selection.
 */
int get_search_type_student(){
    printf("\nBuscar Aluno: ");
    printf("\n1 - Buscar por Nome");
    printf("\n2 - Buscar por Numero USP");
    printf("\n3 - Voltar ao Menu Principal");
    printf("\nQual acao voce gostaria de fazer?: ");
    //convert from char into the int that it represents
    int input = getchar() - 48;
    flush_std_in();
    while(input < 1 || input > 3)
    {
        printf("\nOpcao Invalida! Por favor, digite de novo: ");
        input = getchar() - 48;
        flush_std_in();
    }
    return input;
}

/*
 * Prompt user to enter if they want to search for the student by name or by
 * nusp. Return user's selection.
 */
int get_search_type_book(){
    printf("\nBuscar Livro: ");
    printf("\n1 - Buscar por titulo");
    printf("\n2 - Buscar por ISBN");
    printf("\n3 - Voltar ao Menu Principal");
    printf("\nQual acao voce gostaria de fazer?: ");
    //convert from char into the int that it represents
    int input = getchar() - 48;
    flush_std_in();
    while(input < 1 || input > 3)
    {
        printf("\nOpcao Invalida! Por favor, digite de novo: ");
        input = getchar() - 48;
        flush_std_in();
    }
    return input;
}

