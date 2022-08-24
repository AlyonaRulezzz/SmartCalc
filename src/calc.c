 #include "h_calc.h"
 #include <string.h>
 #include <stdio.h>
 #include <stdlib.h>  //Для atof() и malloc
 #include <math.h>

void displayList (N* head) {  /* вывод на печать односвязного списка */
    N* tmp = head;

    while (tmp) {
        printf("value = %lf\t| ", tmp->value);
        printf("priority = %d\t\t| ", tmp->priority);
        printf("type = %d\t\t| ", tmp->type);
        printf("next = %p\t|\n", tmp->next);
        printf("------------------------\n");

        tmp = tmp->next;
    }

    printf("\n");
}

/* проверка корректности поданного выражения  */
int check_error(char *str) {
    int ERROR = 0;
    int open_bracket_counter = 0, close_bracket_counter = 0;
    int print_error_counter = 0;
    for (int i = 0; i < (int)strlen(str); i++) {
        /* operations */
        if ((str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '^' || str[i] == 'd' /* for mod_enum */ )
            && (str[i + 1] == '+' || str[i + 1] == '-' || str[i + 1] == '*' || str[i + 1] == '/' || str[i + 1] == '^' || str[i + 1] == 'm' /* for mod_enum */
                || !str[i + 1])) {
            // printf("Invalid value\n");
            ERROR = 1;
            print_error_counter++;
            break;
        }

        if ((str[i] == '*' || str[i] == '/' || str[i] == '^' || str[i] == 'm' /* for mod_enum */ )
            && !str[i - 1]) {
            // printf("Invalid value\n");
            ERROR = 1;
            print_error_counter++;
            break;
        }

        /* numbers with points */
        if (str[i] == '.'
            && ((char)str[i + 1] < 48 || (char)str[i + 1] > 57
            || (char)str[i - 1] < 48 || (char)str[i - 1] > 57)) {
            // printf("Invalid value\n");
            ERROR = 1;
            print_error_counter++;
            break;
        }
        /* open bracket */
        if ((str[i] == '(' && (char)str[i - 1] >= 48 && (char)str[i - 1] <= 57)
            || (str[i] == '(' && str[i + 1] == ')')
            || (str[i] == '(' && (str[i + 1] == 'm' /* for mod_enum */ || str[i + 1] == '/' || str[i + 1] == '*'  || str[i + 1] == '^'))) {
            // printf("Invalid value\n");
            ERROR = 1;
            print_error_counter++;
            break;
        }
        /* close bracket */
        if ((str[i] == ')' && (char)str[i + 1] >= 48 && (char)str[i + 1] <= 57)
            || (str[i] == ')' && (char)str[i + 1] == '(')
            || (str[i] == ')' && (str[i - 1] == 'd' /* for mod_enum */ || str[i - 1] == '+' || str[i - 1] == '-' || str[i - 1] == '*' || str[i - 1] == '/' || str[i - 1] == '^'))) {
            // printf("Invalid value\n");
            ERROR = 1;
            print_error_counter++;
            break;
        }
        /* both brackets */
        if (str[i] == '(')
            open_bracket_counter++;

        if (str[i] == ')') {
            if (open_bracket_counter > close_bracket_counter) {
                close_bracket_counter++;
            } else {
                // printf("Invalid value\n");
                ERROR = 1;
                print_error_counter++;
                break;
            }
        }
        /* functions after numbers without * sign */
        if (((char)str[i] >= 48 && (char)str[i] <= 57) &&
            (str[i+1] == 's' || str[i+1] == 'c' || str[i+1] == 't' || str[i+1] == 'a' || str[i+1] == 'l')) {
            // printf("Invalid value\n");
            ERROR = 1;
            print_error_counter++;
            break;
        }
        /* stroke ends with operation or function (no number on it) */
        if (!(((char)str[i] >= 48 && (char)str[i] <= 57) || str[i] == ')') && (str[i+1] == '\0')) {
            // printf("Invalid value\n");
            ERROR = 1;
            print_error_counter++;
            break;
        }
        /* check that after function goes number or open bracket */
        // if ((str[i] == 's' || str[i] == 'n' || str[i] == 't' || str[i] == 'g') &&
        //     !((str[i + 1] >= 48 && str[i + 1] <= 57) || str[i + 1] == '(')) {
        //     printf("Invalid value\n");
        //     ERROR = 1;
        //     print_error_counter++;
        //     break; 
        // } /* нужно ещё добавить проверок, а то, например, в tan t в начале и всё ломается  */
    }
    if (open_bracket_counter != close_bracket_counter && !print_error_counter){
        // printf("Invalid value\n");
        ERROR = 1;
    }


    return ERROR;
}

/* обратная польская нотация 1 */
/* push an element to input stack*/
void push(N **input, double value, int priority, int type) {
    N *tmp = (N*) malloc(sizeof(N));
    tmp->value = value;
    tmp->priority = priority;
    tmp->type = type;
    tmp->next = (*input);
    (*input) = tmp;
}

/* парсер */
N* parser(char *str, double xValue) {
    N* input = NULL;

    char numeric[256] = {0};
    int numeric_counter = 0;

    for (int i = 0; i < (int)strlen(str); i++) {

        /* number parsing */
        if (((char)str[i] >= 48 && (char)str[i] <= 57) || str[i] == '.') {
            numeric[numeric_counter] = str[i];
            numeric_counter++;
            if(!(((char)str[i + 1] >= 48 && (char)str[i + 1] <= 57) || str[i + 1] == '.')) {
                double value_numeric = atof(numeric);
                push(&input, value_numeric, 0, number); /* добавляем элемент в список */
                memset(numeric, 0, 256); /* обнуляем массив под число */
                numeric_counter = 0; /* сбрасываем счётчик */
            }
        }
        /* x parsing */
        else if (str[i] == 'x') {
            push(&input, xValue, 0, x);
        }
        /* open_bracket parsing */
        else if (str[i] == '(') {
            push(&input, 0, 5, open_bracket);
        }
        /* close_bracket parsing */
        else if (str[i] == ')') {
            push(&input, 0, 5, close_bracket);
        }
        /* PLUS & UNAR_PLUS parsing */
        else if (str[i] == '+') {
            if (!str[i - 1] || str[i - 1] == '(') {
                continue;  /* (+2) == 2 */
            } else {
                push(&input, 0, 1, plus);
            }
        }
        /* MINUS & UNAR_MINUS parsing */
        else if (str[i] == '-') {
            if (!str[i - 1] || str[i - 1] == '(') {
                push(&input, 0, 0, number);  /* (-2) == (0 - 2) */
            }
            push(&input, 0, 1, minus);
        }
        /* mul parsing */
        else if (str[i] == '*') {
            push(&input, 0, 2, multiple);
        }
        /* divide parsing */
        else if (str[i] == '/') {
            push(&input, 0, 2, divide);
        }
        /* degree parsing */
        else if (str[i] == '^') {
            push(&input, 0, 3, degree);
        }
        /* mod parsing */
        else if (str[i] == 'm') {
            push(&input, 0, 1, mod_enum);
            i = i + 2;
        }
        /* cos parsing */
        else if (str[i] == 'c') {
            push(&input, 0, 4, cosinus);
            i = i + 2;
        }
        /* SIN & SQRT parsing */
        else if (str[i] == 's') {
            if (str[i + 1] == 'i') {
                push(&input, 0, 4, sinus);
                // printf("%d\n", input->type);
                i = i + 2;
            }
            if (str[i + 1] == 'q') {
                push(&input, 0, 4, sqrt_enum);
                i = i + 3;
            }
        }
        /* tan parsing */
        else if (str[i] == 't') {
            push(&input, 0, 4, tangens);
            i = i + 2;
        }
        /* ACOS, ASIN & ATAN parsing */
        else if (str[i] == 'a') {
            if (str[i + 1] == 'c') {
                push(&input, 0, 4, acosinus);
                i = i + 3;
            }
            if (str[i + 1] == 's') {
                push(&input, 0, 4, asinus);
                i = i + 3;
            }
            if (str[i + 1] == 't') {
                push(&input, 0, 4, atangens);
                i = i + 3;
            }
        }
        /* LN & LOG parsing */
        else if (str[i] == 'l') {
            if (str[i + 1] == 'n') {
                push(&input, 0, 4, ln_enum);
                i = i + 1;
            }
            if (str[i + 1] == 'o') {
                push(&input, 0, 4, log_enum);
                i = i + 2;
            }
        }
    }
    return input;  /* парсер возвращвет input стек */
}

/* обратная польская нотация 2 */
/* reverse input stack for easy calculation */
N* reverse_input(N* input) {
    N* rev_input = NULL;
    while (input) {
        push(&rev_input, input->value, input->priority, input->type);
        input = input->next;
    }
    return rev_input;
}

/* pop an element from stack */
N* pop(N** stack) {
    N* pop_stack;
    pop_stack = *stack;
    *stack = (*stack)->next;
    return pop_stack;
}

/* push an element from reverse input stack to ready stack or support stack */
N* push_to_ready(N* rev_input) {
    N* ready = NULL;
    N* support = NULL;
    N* pop_support = NULL;
    
    while (rev_input) {
        /* обработка скобок */
        if (rev_input->type == open_bracket) {
            push(&support, rev_input->value, rev_input->priority, rev_input->type);
            rev_input = rev_input->next;
        } else if (rev_input->type == close_bracket) {
            while (support->type != open_bracket) {  /* пока support стек до открывающей скобки не пуст */
                pop_support = pop(&support);  /* перекидывем вершину support стека в ready стек */
                push(&ready, pop_support->value, pop_support->priority, pop_support->type);
            }
            pop(&support);
            rev_input = rev_input->next;
        /* обработка чисел и х */
        } else if (rev_input->priority == 0) {  /* числа  и x пушим сразу в ready стек */
            push(&ready, rev_input->value, rev_input->priority, rev_input->type);
            rev_input = rev_input->next;
        /* обработка операций и функций */
        } else {
            if ((support == NULL) || (support->priority == 5) || (support->priority < rev_input->priority)) {  /* операции и функции с приоритетом меньшим, чем вершина support стека, пушим в support стек */
                push(&support, rev_input->value, rev_input->priority, rev_input->type);
                rev_input = rev_input->next;
            } else if (support->priority >= rev_input->priority) {  /* операции и функции с приоритетом большим, чем вершина support стека */
                while ((support != NULL) && (support->priority >= rev_input->priority) && (support->priority != 5)) {  /* пока support стек не пуст и приоритет его вершины больше подаваемой операции или функции */
                    pop_support = pop(&support);  /* перекидывем вершину support стека в ready стек */
                    push(&ready, pop_support->value, pop_support->priority, pop_support->type);
                }
                push(&support, rev_input->value, rev_input->priority, rev_input->type);  /* пушим операцию в support стек */
                rev_input = rev_input->next;
            }
        }
        // // /* 
        // printf("SUPPORT\n");
        // displayList(support);
        // printf("READY\n");
        // displayList(ready);
        // printf("ok\n");
        // // */
    }
    while (support) {  /* когда rev_input стек закончится, всё, что осталось в support стеке, перекидываем в ready стек */
        pop_support = pop(&support);
        push(&ready, pop_support->value, pop_support->priority, pop_support->type);
    }
        /*
        printf("SUPPORT\n");
        displayList(support);
        printf("READY\n");
        displayList(ready);
        printf("ok\n");
        // */
    return ready;
}

/* вычисление конечного результата */
double calc(N* rev_ready) {
    double res = rev_ready->value;  /* res будем возвращать, если ввели только одно положительное число и нажали равно */

    N* calc_support = NULL;  /* стек для сохранения нескольких чисел подряд */
    N* pop_rev_ready = NULL;
    int flag = 0;
    N* pop_calc_support = NULL;

    while(rev_ready != NULL) {
        if (rev_ready->priority == 0) {  /* для чисел ищем операцию или функцию */
            if ((rev_ready->next) && (rev_ready->next->priority == 4)) {  /* здесь ищем функцию */
                switch (rev_ready->next->type) {
                    case cosinus:
                        rev_ready->value = cos(rev_ready->value);  /* записываем в узел новое значение */
                        pop(&rev_ready->next);  /* удаляем использованные в вычислениях числа из rev_ready стека */
                        break;
                    case sinus:
                        rev_ready->value = sin(rev_ready->value);
                        pop(&rev_ready->next);
                        break;
                    case tangens:
                        rev_ready->value = tan(rev_ready->value);
                        pop(&rev_ready->next);
                        break;
                    case acosinus:
                        rev_ready->value = acos(rev_ready->value);
                        pop(&rev_ready->next);
                        break;
                    case asinus:
                        rev_ready->value = asin(rev_ready->value);
                        pop(&rev_ready->next);
                        break;
                    case atangens:
                        rev_ready->value = atan(rev_ready->value);
                        pop(&rev_ready->next);
                        break;
                    case sqrt_enum:
                        rev_ready->value = sqrt(rev_ready->value);
                        pop(&rev_ready->next);
                        break;
                    case ln_enum:
                        rev_ready->value = log(rev_ready->value);
                        pop(&rev_ready->next);
                        break;
                    case log_enum:
                        rev_ready->value = log10(rev_ready->value);
                        pop(&rev_ready->next);
                        break;
                }
            } else if ((rev_ready->next) && (rev_ready->next->priority == 0) && (rev_ready->next->next != NULL) &&
                ((rev_ready->next->next->priority == 1) ||
                (rev_ready->next->next->priority == 2) ||
                (rev_ready->next->next->priority == 3))) {  /* здесь ищем операцию */
                switch (rev_ready->next->next->type) {
                    case plus:
                        rev_ready->value += rev_ready->next->value;
                        pop(&rev_ready->next);
                        pop(&rev_ready->next);  /* удаляем опять &rev_ready->next, а не &rev_ready->next, т. к. один элемент мы только что удалили */
                        break;
                    case minus:
                        rev_ready->value -= rev_ready->next->value;
                        pop(&rev_ready->next);
                        pop(&rev_ready->next);
                        break;
                    case multiple:
                        rev_ready->value *= rev_ready->next->value;
                        pop(&rev_ready->next);
                        pop(&rev_ready->next);
                        break;
                    case divide:
                        rev_ready->value /= rev_ready->next->value;
                        pop(&rev_ready->next);
                        pop(&rev_ready->next);
                        break;
                    case degree:
                        rev_ready->value = pow(rev_ready->value, rev_ready->next->value);
                        pop(&rev_ready->next);
                        pop(&rev_ready->next);
                        break;
                    case mod_enum:
                        rev_ready->value = fmod(rev_ready->value, rev_ready->next->value);
                        pop(&rev_ready->next);
                        pop(&rev_ready->next);
                        break;
                }
            } else {  /* если после числа  идёт ещё два числа или ещё одно число и конец списка, то мы перекидываем его в calc_support стек из rev_ready стека */
                pop_rev_ready = pop(&rev_ready);
                push(&calc_support, pop_rev_ready->value, pop_rev_ready->priority, pop_rev_ready->type);
                flag = 1;  /* помечаем, что текущий rev_ready ещё не обработан */
            }
        } else {  /* если в вершине списка знак или функция, то числа переносятся обратно в rev_ready стек из calc_support стека */
            while (calc_support) {
                pop_calc_support = pop(&calc_support);
                push(&rev_ready, pop_calc_support->value, pop_calc_support->priority, pop_calc_support->type);
            }
        }

        if ((rev_ready) && (rev_ready->next != NULL) && (rev_ready->priority != 0) && (flag == 0)) {  /* проверяем, что rev_ready не число или х, он обработан и у него есть rev_ready->next */
            rev_ready = rev_ready->next;
        }

        flag = 0;
        if ((rev_ready) && (rev_ready->value == reverse_input(rev_ready)->value) &&
            (rev_ready->priority == reverse_input(rev_ready)->priority) &&
            (rev_ready->priority == 0) && (rev_ready->next == NULL)) {
            break;  /* выходим из цикла, если в списке остался только один элемент и это число или х */
        // }
        } else if ((rev_ready) && (rev_ready->next == NULL) && (rev_ready->priority == 0)) {
            break;
        }
        // /*
        // printf("SUPPORT\n");
        // displayList(support);
        // printf("READY\n");
        // displayList(rev_ready);
        // printf("ok\n");
        // */

    }
    return rev_ready ? rev_ready->value : res;
}

// int main() {

//     // char str[1024] = "-(+2*asin(3.89745-4)*(4-4*(4))^(8))";
//     // char str[1024] = "(-123.456*9+45.25)-(4-5/sin10)";
//     // char str[1024] = "sqrt-9";  /* добавить проверку */
//     // printf("%lf\n", sqrt(-9));
//     char str[1024] = "sqrt(-9)";
//     // char str[1024] = "atan(-0.5)";
//     // printf("atan bibl = %lf\n", atan(-0.5));
//     // char str[1024] = "-(-20)";
//     // char str[1024] = "20"; 
//     // char str[1024] = "-10-(-3+4)";
//     // char str[1024] = "(asin(1))";
//     // char str[1024] = "1+2-10*13+452.2146/11";
//     // char str[1024] = "1*(10-4/2+8^2)*3+ln(2.7)";

//     if (!check_error(str)) {  /* проверка корректности поданного выражения  */

// //         // parser(str);  /* парсер */
// //         N* k = parser(str, 0);
// //         // printf("%lf\n", k->value);
// //         // printf("%d\n", k->type);

// // //         // reverse_input(parser(str));  /* перевернём input стек для удобной работы с ним, (чтобы он читался слева направо) */
// //         N* z = reverse_input(k);
// //         // printf("%.7lf\n", z->value);
// //         // printf("%d\n", z->type);

// // //         // push_to_ready(reverse_input(parser(str)));  /* применим обратную польскую нотацию к reverse_input стеку */
// //         N* w = push_to_ready(z);
//         // printf("%lf\n", w->next->value);
//         // printf("%d\n", w->next->type);

// //         // reverse_input(push_to_ready(reverse_input(parser(str))));  /* перевернём ready стек для удобной работы с ним, (чтобы он читался слева направо) */
// //         // N* r = reverse_input(push_to_ready(reverse_input(parser(str))));
// //         // printf("%lf\n", r->next->value);
// //         // printf("%d\n", r->next->type);

//         double d = calc(reverse_input(push_to_ready(reverse_input(parser(str, 0)))));  /* вычисление конечного результата */
//         printf("\ncalc=%.8lf\n", d);
//     }

//     return 0;
// }
