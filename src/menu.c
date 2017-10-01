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
           "\n--------------------------------");
}

/*
 * Prints the possible menu actions.
 */
void print_menu() {
    printf("\n\nQual acao voce quer realizar?: \n" \
           "1. Cadastrar Aluno\n" \
           "2. Cadastrar Livro\n" \
           "3. Retirar Livro\n" \
           "4. Retornar Livro\n" \
           "5. Remover Livro\n" \
           "6. Remover Aluno\n" \
           "7. Imprimir Emails para um Aluno\n" \
           "8. Sair do Sistema\n");
}

/*
 * Gets the user's desired action and completes it. Returns 1 when action is
 * completed. Returns 0 if the desired action is to quit.
 */
int complete_action(student_list *studs, book_list *books) {
    print_menu();
    int selection = get_selection();
    switch (selection) {
        case 1:
            register_student(studs);
            break;
        case 2:
            register_book(books);
            break;
        case 3:
            menu_check_out_book(books, studs);
            break;
        case 4:
            menu_return_book(books);
            break;
        case 5:
            remove_book(books);
            break;
        case 6:
            remove_student(books, studs);
            break;
        case 7:
            print_emails(studs);
            break;
        default:
            return 0;
    }
    return 1;
}

/*
 * Prompts user to input information for the new student. Creates a new
 * student and adds the student to the list of students. Returns 0 if student
 * was registered with success, returns 1 if an error occurred.
 */
int register_student(student_list *studs) {

    printf("\nPor favor, digite os dados para o aluno novo: ");
    char name[MAX_NAME_SIZE];
    int nusp[MAX_NUSP_SIZE];
    int phone[MAX_PHONE_SIZE];
    char email[MAX_EMAIL_SIZE];

    get_name(name);
    get_nusp(nusp);
    get_phone(phone);
    get_email(email);

    if (insert_student(studs, name, nusp, phone, email) == 1) {
        printf("\nNao foi possivel registrar o aluno!");
        return 1;
    }

    return 0;
}

/*
 * Prompts user to input how they would like to remove a student. Calls the
 * appropriate function to delete the student based on user's selection.
 */
void remove_student(book_list *books, student_list *studs) {
    int type = get_remove_type_student();

    switch (type) {
        case 1:
            if (menu_remove_student_name(books, studs) == 1)
                printf("\nNao foi possivel remover o aluno!");
            else
                printf("\nO aluno foi removido!");
            break;
        case 2:
            if (menu_remove_student_nusp(books, studs) == 1)
                printf("\nNao foi possivel remover o aluno!");
            else
                printf("\nAluno foi removido!");
            break;
        default:
            return;
    }
}

/*
 * Prompts user to enter name of student to be deleted. Calls function to remove
 * student. Returns 0 if student is removed, 1 if the deletion was not possible.
 */
int menu_remove_student_name(book_list *books, student_list *studs) {
    char name[MAX_NAME_SIZE];
    printf("Digite o nome do aluno que voce quer remover: ");
    get_name(name);
    if (remove_student_name(books, studs, name) == 1) {
        return 1;
    }
    return 0;
}

/*
 * Prompts user to enter nusp of student to be deleted. Calls function to remove
 * student. Returns 0 if student is removed, 0 if the deletion was not possible.
 */
int menu_remove_student_nusp(book_list *books, student_list *studs) {
    int nusp[MAX_NUSP_SIZE];
    printf("Digite o NUSP do aluno que voce quer remover: ");
    get_nusp(nusp);
    if (remove_student_nusp(books, studs, nusp) == 1) {
        return 1;
    }
    return 0;
}

/*
 * Prompts user to input information for the new book. Creates a new
 * book and adds the book to the list of books. Returns 0 if book
 * was registered with success, returns 0 if an error occurred.
 */
int register_book(book_list *books) {

    printf("\nPor favor, digite os dados para o livro novo: ");
    char title[MAX_TITLE_SIZE];
    char author[MAX_AUTHOR_SIZE];
    char editor[MAX_EDITOR_SIZE];
    int isbn[MAX_ISBN_SIZE];
    int year;
    int edition;
    int result;

    get_title(title);
    get_author(author);
    get_editor(editor);
    get_isbn(isbn);
    get_year(&year);
    get_edition(&edition);

    result = insert_book(books, title, author, editor, isbn, year, edition);
    if ( result == 1) {
        printf("\nNao foi possivel registrar o livro!");
        return 1;
    }
    else if(result == 2){
        printf("\nUm livro com o mesmo ISBN ja existe. O novo livro vai ser considerado uma segunda copia do livro!");
    }

    return 0;
}

/*
 * Prompts user how they would like to remove a book. Calls the appropriate
 * function to delete the book based on user's selection.
 */
void remove_book(book_list *books) {
    int type = get_remove_type_book();

    switch (type) {
        case 1:
            if (menu_remove_book_title(books) == 1)
                printf("\nNao foi possivel remover o livro!");
            else
                printf("\nLivro foi removido!");
            break;
        case 2:
            if (menu_remove_book_isbn(books) == 1)
                printf("\nNao foi possivel remover o livro!");
            else
                printf("\nLivro foi removido!");
            break;
        default:
            return;
    }
}

/*
 * Prompts user to enter name of book to be deleted. Calls function to remove
 * book. Returns 0 if book is removed, 0 if the deletion was not possible.
 */
int menu_remove_book_title(book_list *books) {
    char title[MAX_TITLE_SIZE];
    printf("Digite o titulo do livro que voce quer remover: ");
    get_title(title);
    if (remove_book_title(books, title) == 1) {
        return 1;
    }
    return 0;
}

/*
 * Prompts user to enter ISBN of book to be deleted. Calls function to remove
 * book. Returns 0 if book is removed, 0 if the deletion was not possible.
 */
int menu_remove_book_isbn(book_list *books) {
    int isbn[MAX_ISBN_SIZE];
    printf("Digite o ISBN do livro que voce quer remover: ");
    get_isbn(isbn);
    if (remove_book_isbn(books, isbn) == 1) {
        return 1;
    }
    return 0;
}

/*
 * Prompts user to enter the student who will check out the book and the book
 * that they want to check out. Returns 1 if it was not possible to find the
 * book or the student. Returns 0 if the checkout was successful.
 */
int menu_check_out_book(book_list *books, student_list *studs) {
    char name[MAX_NAME_SIZE];
    int nusp[MAX_NUSP_SIZE];
    char title[MAX_TITLE_SIZE];
    int isbn[MAX_ISBN_SIZE];
    student *stud;
    book *book;

    printf("\nPor favor, selecione o aluno que vai retiraro livro.");

    int type = get_search_type_student();

    switch (type) {
        case 1:
            get_name(name);
            if(get_student_by_name(studs, name, &stud) == 1) {
                printf("\nNao foi possivel achar o aluno!");
                return 1;
            }
            break;
        case 2:
            get_nusp(nusp);
            if(get_student_by_nusp(studs, nusp, &stud) == 1){
                printf("\nNao foi possivel achar o aluno!");
                return 1;
            }
            break;
        default:
            return 0;
            }
    printf("\nPor favor, selecione o livro que vai ser retirado.");
    type = get_search_type_book();
    switch(type){
        case 1:
            get_title(title);
            if(get_book_by_title(books, title, &book) == 1){
                printf("\nNao foi possivel achar o livro!");
                return 1;
            }

            break;
        case 2:
            get_isbn(isbn);
            if(get_book_by_isbn(books, isbn, &book) == 1){
                printf("\nNao foi possivel achar o livro!");
                return 1;
            }
            break;
        default:
            return 0;
    }
    if(book == NULL || stud == NULL)
        return 1;
    if(checkout_book(stud, book) == 0)
        printf("\nO livro foi retirado pelo aluno. \nTitulo: %sNome: %s", get_book_title(book), get_stud_name(stud));
    else
        printf("\nO aluno foi adicionado a lista de espera para o livro. \nTitulo: %sNome: %s", get_book_title(book), get_stud_name(stud));
    return 0;

}

/*
 * Prompts user to enter the book that has been returned. Returns 1 if it was
 * not possible to find the book. Returns 0 if the return was successful.
 */
int menu_return_book(book_list *books) {
    char title[MAX_TITLE_SIZE];
    int isbn[MAX_ISBN_SIZE];
    book *bk;
    int type;

    type = get_search_type_book();
    switch(type){
        case 1:
            get_title(title);
            if(get_book_by_title(books, title, &bk) == 1){
                printf("\nNao foi possivel achar o livro!");
                return 1;
            }
            break;
        case 2:
            get_isbn(isbn);
            if(get_book_by_isbn(books, isbn, &bk) == 1){
                printf("\nNao foi possivel achar o livro!");
                return 1;
            }
        default:
            return 0;
    }
    if(bk == NULL)
        return 1;
    return_book(bk);
    printf("\nO livro foi retornado! \nTitulo: %s", get_book_title(bk));
    return 0;

}

/*
 * Prompts user to enter which student to print the emails for. Prints all
 * of the emails of chosen email.
 */
int print_emails(student_list *studs){
    char name[MAX_NAME_SIZE];
    int nusp[MAX_NUSP_SIZE];
    student *stud;

    int type = get_search_type_student();

    switch (type) {
        case 1:
            get_name(name);
            if(get_student_by_name(studs, name, &stud) == 1) {
                printf("\nNao foi possivel achar o aluno!");
                return 1;
            }
            break;
        case 2:
            get_nusp(nusp);
            if(get_student_by_nusp(studs, nusp, &stud) ==1){
                printf("\nNao foi possivel achar o aluno!");
                return 1;
            }
            break;
        default:
            return 0;
    }
    email_stack temp;
    char message[MAX_MESSAGE_SIZE];
    while(!isEmailEmpty(&stud->emails)){
        pop_email(&stud->emails, message);
        printf("\n%s", message);
        push_email(&temp, message);
    }
    while(!isEmailEmpty(&stud->emails)){
        pop_email(&temp, message);
        push_email(&stud->emails, message);
    }
    return 0;
}

/*
 * Prints all of the data related to the passed student.
 */
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

/*
 * Prints the data for each student in the student list.
 */
void print_students(student_list *studs){
    student *stud = studs->first;
    while(stud != NULL) {
        print_student(stud);
        stud = stud->next;
    }

}

/*
 * Prints all of the data related to the passed book.
 */
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

/*
 * Prints the data for each book in the book list.
 */
void print_books(book_list *bks){
    book *bk = bks->first;
    while(bk != NULL) {
        print_book(bk);
        bk = bk->next;
    }

}