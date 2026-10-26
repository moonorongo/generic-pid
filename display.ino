#define dataPin  2  
#define latchPin 3
#define clockPin 4  

#define BLINK_TIME 100

unsigned long displayEllapsedTime;
bool enableDisplay = true;

byte digits[] = {0, 0, 0, 0, 0};
//              m  c  d  u. decimas

/*     -6543210
    0b 00000000
         0
       -----
    6 |  5  | 1
       -----
    4 |     | 2
       -----
         3
*/

byte const chars[27] = {
    0b00000000, // ' '
    0b01110111, // 'A'
    0b01111100, // 'B'
    0b01011001, // 'C'
    0b00111110, // 'D'
    0b01111001, // 'E'
    0b01110001, // 'F'
    0b01011101, // 'G'
    0b01110110, // 'H'
    0b00000100, // 'I'
    0b00001110, // 'J'
    0b01111010, // 'K'
    0b01011000, // 'L'
    0b01010111, // 'M'
    0b00110100, // 'N'
    0b00111100, // 'O'
    0b01110011, // 'P'
    0b01100111, // 'Q'
    0b00110000, // 'R'
    0b01101101, // 'S'
    0b01111000, // 'T'
    0b01011110, // 'U'
    0b00011100, // 'V'
    0b01011110, // 'W'
    0b01110110, // 'X'
    0b01101110, // 'Y'
    0b00111011  // 'Z'
};



byte const numbers[10] = {
    0b01011111, // 0 
    0b00000110, // 1
    0b00111011, // 2 
    0b00101111, // 3 
    0b01100110, // 4
    0b01101101, // 5
    0b01111100, // 6
    0b00000111, // 7
    0b01111111, // 8
    0b01100111  // 9
};


void clearDigits() {
    digits[0] = 0;    
    digits[1] = 0;    
    digits[2] = 0;    
    digits[3] = 0;    
    digits[4] = 0;    
}


byte display_get_code(byte codigo) {
    if (codigo == 32) { // si es espacio
        return chars[0];
    } else if (codigo < 58) { // si es numero
        return numbers[codigo - 48];
    } else { // si es caracter
        return chars[codigo - 64];
    }
}

// ES OBLIGATORIO QUE LA ENTRADA text TENGA EXACTAMENTE 5 CARACTERES, 
// QUE PUEDEN SER UNICAMENTE EL ESPACIO Y A-Z EN MAYUSCULAS
    // aca habria que sanitizar text
    // pero sanitizar es para pel*****s, 
    // si hay menos chars de 5 rompera
    // y si hay mas... los ignora
void display_text(char text[]) {
    shiftOut(dataPin, clockPin, MSBFIRST, display_get_code(text[4]) );
    shiftOut(dataPin, clockPin, MSBFIRST, display_get_code(text[3]) );
    shiftOut(dataPin, clockPin, MSBFIRST, display_get_code(text[2]) );
    shiftOut(dataPin, clockPin, MSBFIRST, display_get_code(text[1]) );
    shiftOut(dataPin, clockPin, MSBFIRST, display_get_code(text[0]) );
}


void refreshDisplay(byte st = 0)
{
    if(st == 0) {
        digitalWrite(latchPin, LOW); 

        if(mode == MODE_SET_POINT) {
            // en MODE_SET_POINT debe parpadear el display,
            // asi como en los modos en los que estamos editando algun valor (en Kp, Ki, o Kd)

            // POR FAVOR OPTIMIZAR TODA ESTA POR***A HORRIBLE
            if(enableDisplay) {
                shiftOut(dataPin, clockPin, MSBFIRST, display_get_code(digits[4]));
                shiftOut(dataPin, clockPin, MSBFIRST, display_get_code(digits[3]));
                shiftOut(dataPin, clockPin, MSBFIRST, display_get_code(digits[2]));
                shiftOut(dataPin, clockPin, MSBFIRST, display_get_code(digits[1]));
                shiftOut(dataPin, clockPin, MSBFIRST, display_get_code(digits[0]));
            } else {
                display_text("     ");
            }
        } else { // muestro normal
            shiftOut(dataPin, clockPin, MSBFIRST, display_get_code(digits[4]));
            shiftOut(dataPin, clockPin, MSBFIRST, display_get_code(digits[3]));
            shiftOut(dataPin, clockPin, MSBFIRST, display_get_code(digits[2]));
            shiftOut(dataPin, clockPin, MSBFIRST, display_get_code(digits[1]));
            shiftOut(dataPin, clockPin, MSBFIRST, display_get_code(digits[0]));
        }

        digitalWrite(latchPin, HIGH);
    } else {

        // show Status Msg
        // 1 - 20 : errores
        // 21 - resto : mensajes generales (??)
        digitalWrite(latchPin, LOW);
        display_text("AB 01"); // sample
        digitalWrite(latchPin, HIGH);
        // delay(2000);

    }
}

void toArrayDigits(float value) {
    // Obtener la parte entera
    int entera = (int)value;

    // Obtener el primer dígito decimal
    int decimal = (int)(value * 10) % 10;

    // Formatear la parte entera con 4 dígitos
    char buffer[5];
    sprintf(buffer, "%04d", entera);

    char temperatura_formateada[6];
    sprintf(temperatura_formateada, "%s%d", buffer, decimal);

    for(int i=0; i<5; i++) {
        digits[4-i] = temperatura_formateada[4 - i] - '0'; // esta estupidez de - '0' sirve para convertir de char a int
        digits[4-i] = digits[4-i] + 48; // corrige para devolver codigo ascii 
    }
}


void display_setup() {
    pinMode(latchPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
    pinMode(clockPin, OUTPUT);

    displayEllapsedTime = millis();

    refreshDisplay();
}


void display_loop() {
    unsigned long currentMillis = millis();

    // enableDisplay: se utiliza para hacer parpadear un elemento que estoy editando (SET POINT o alguna configuracion)
    if (currentMillis - displayEllapsedTime >= BLINK_TIME) {
        enableDisplay = !enableDisplay;
        displayEllapsedTime = currentMillis;
    }
}