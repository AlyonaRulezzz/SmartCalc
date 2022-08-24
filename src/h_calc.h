#ifndef SRC_H_CALC_H_
#define SRC_H_CALC_H_

#ifdef __cplusplus
#define EXTERNC extern "C"  /* говорит компилятору, что написано на С */
#else
#define EXTERNC
#endif

EXTERNC typedef struct N {
    double value;
    int priority;
    struct N *next;
    int type;
} N;

EXTERNC enum type {  /* from 0 */
    number,
    x,
    open_bracket,
    close_bracket,
    plus,
    minus,
    multiple,
    divide,
    degree,
    mod_enum,
    unar_plus,
    unar_minus,
    cosinus,
    sinus,
    tangens,
    acosinus,
    asinus,
    atangens,
    sqrt_enum,
    ln_enum,
    log_enum
};

EXTERNC int check_error(char *str);  /* EXTERNC == (QT будет видеть функцию) */
EXTERNC void push(N **input, double value, int priority, int type);
EXTERNC N* parser(char *str, double xValue);
EXTERNC N* reverse_input(N* input);
EXTERNC N* pop(N** stack);
EXTERNC N* push_to_ready(N* rev_input);
EXTERNC double calc(N* rev_ready);

#endif  //  SRC_H_CALC_H_
