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
        int ch;
        while (((ch = getchar()) != '\n') && (ch != EOF));
}

int get_student_info(student *stud){

    printf("\nPorfavor, digite os dados para o aluno novo: ");

    get_name(stud->name);
    get_nusp((stud->nusp));
    get_phone(stud->phone);
    get_email(stud->email);


    return 1;
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

void get_name(char *name){
    printf("\nNome: ");
    fgets(name, MAX_NAME_SIZE, stdin);
    //flush_std_in();
}

void get_nusp(int *nusp){
    printf("Numero USP: ");
//   while(scanf("%d", nusp) == 0){
//        printf("Invalido! Digite de novo: ");
//        flush_std_in();
//    }
    //flush_std_in();

    int i = 0;
    int digit = getchar();
    while(digit != '\n' && digit != 'EOF' && i<MAX_PHONE_SIZE){
        if(digit - 48 >= 0 && digit - 48 <= 9){
            nusp[i] = digit-48;
            i++;
        }
        digit = getchar();
    }
    while(i<MAX_PHONE_SIZE){
        nusp[i] = -1;
        i++;
    }
    //flush_std_in();
}

void get_email(char *email){
    printf("Email: ");
    fgets(email, MAX_EMAIL_SIZE, stdin);
    //flush_std_in();
}

void get_phone(int *phone){
    printf("Numero de telefone: ");
    int i = 0;
    int digit = getchar();
    while(digit != '\n' && digit != 'EOF' && i<MAX_PHONE_SIZE){
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

void print_book(book *bk){
    int i;
    printf("\nTitulo: %s", bk->title);
    printf("Autor: %s", bk->author);
    printf("Editora: %s", bk->editor);
    printf("ISBN: %s", bk->isbn);
    printf("Ano: %d", bk->year);
    printf("\nEdicao: %d", bk->edition);
}