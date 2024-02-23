#include "../inc/matrix_rain.h"

wchar_t get_wchar(void) {
    wchar_t only_printable[] = {
    L"あいうえおかきくけこさしすせそたちつてとなにぬねのはひふへほまみむめもやゆよらりるれろわをん"
    };
    
    return only_printable[rand() % 46];
}

