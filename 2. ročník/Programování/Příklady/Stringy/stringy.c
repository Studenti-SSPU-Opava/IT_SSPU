#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Struktura pro reprezentaci dynamického řetězce
typedef struct {
    size_t len; // délka řetězce
    size_t cap; // kapacita alokované paměti
    char *data; // ukazatel na data řetězce
} str;

// Funkce pro výpočet kapacity na základě délky
size_t compute_cap(size_t len) {
    return 2 * len * sizeof(char);
}

// Funkce pro resetování struktury řetězce
void reset_str(str *string) {
    string->len = 0;
    string->cap = 0;
    string->data = NULL;
}

// Funkce pro vytvoření nového řetězce
str new_str(char *initial_data, size_t len) {
    str string;
    string.len = len;
    string.cap = compute_cap(len);
    string.data = malloc(string.cap);
    if (string.data == NULL) {
        printf("Alokace řetězce selhala\n");
        reset_str(&string);
        return string;
    }
    memcpy(string.data, initial_data, len);

    return string;
}

// Funkce pro přidání dat do řetězce
int append_str(str *string, char *data, size_t data_len) {
    int current_len = string->len;
    string->len += data_len;
    if (string->len + data_len > string->cap) {
        string->cap = compute_cap(string->len + data_len);
        string->data = realloc(string->data, string->cap);

        if (string->data == NULL) {
            printf("Realokace řetězce selhala\n");
            reset_str(string);
            return 1;
        }
    }
    memcpy(string->data + current_len, data, data_len);

    return 0;
}

// Funkce pro spojení dvou řetězců
str concat_str(str string1, str string2) {
    str new_string;
    new_string.len = string1.len + string2.len;
    new_string.cap = compute_cap(new_string.len);
    new_string.data = malloc(new_string.cap);
    if (new_string.data == NULL) {
        printf("Alokace řetězce selhala\n");
        reset_str(&new_string);
        return new_string;
    }
    memcpy(new_string.data, string1.data, string1.len);
    memcpy(new_string.data + string1.len, string2.data, string2.len);

    return new_string;
}

// Funkce pro vytvoření podřetězce
int slice_str(str string, size_t start, size_t end) {
    str sliced_str;
    sliced_str.len = end - start;
    sliced_str.cap = sliced_str.len;
    sliced_str.data = string.data + start;
}

int main() {
    str test = new_str("David", 5);
    write(STDOUT_FILENO, test.data, test.len);
    printf("\n kapacita: %zu\n", test.cap);
    append_str(&test, " Petr", 5);
    write(STDOUT_FILENO, test.data, test.len);
    printf("\n kapacita: %zu\n", test.cap);
    return 0;
}