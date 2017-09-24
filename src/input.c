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
    printf("\nQual acao voce gostaria de fazer?: ");
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
int get_remove_type(){
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
    //flush_std_in();
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
    //flush_std_in();
}

/*
 * Prompt user to enter email. Save the email to passed array.
 */
void get_email(char email[MAX_EMAIL_SIZE]){
    printf("Email: ");
    fgets(email, MAX_EMAIL_SIZE, stdin);
    //flush_std_in();
}


int get_book_info(book *bk){
    printf("\nPorfavor, digite os dados para o livro novo: ");

    get_title(bk->title);
    get_author(bk->author);
    get_editor(bk->editor);
    get_isbn(bk->isbn);
    get_year(&(bk->year));
    get_edition(&(bk->edition));


    return 1;
}

void get_title(char *title){
    printf("\nTitulo: ");
    fgets(title, MAX_TITLE_SIZE, stdin);
    //flush_std_in();
}

void get_author(char *author){
    printf("Autor: ");
    fgets(author, MAX_AUTHOR_SIZE, stdin);
    //flush_std_in();
}

void get_editor(char *editor){
    printf("Editora: ");
    fgets(editor, MAX_EDITOR_SIZE, stdin);
    //flush_std_in();
}

void get_isbn(char *isbn){
    printf("ISBN: ");
    fgets(isbn, MAX_ISBN_SIZE, stdin);
}

void get_year(int *year){
    printf("Year: ");
    while(scanf("%d", year)==0){
        printf("Invalido! Tenta de novo: ");
    }
    //flush_std_in();
}

void get_edition(int *edition) {
    printf("Edition: ");

    while (scanf("%d", edition) == 0) {
        printf("Invalido! Tenta de novo: ");
    }
}