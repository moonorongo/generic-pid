/*
    PENDIENTE: 
        - CONFIGURACION: definir un codigo generico que me permita navega un menu con 2 niveles
            el primero con las opciones principales
            el segundo con los valores de la configuracion  a editar
            el tercero tendria el numero a modificar - este no es un nivel, sino que surge del nivel 2 (el valor parpadeando que queremos editar)

            con esto ya tenemos la estructura de configuracion

        - EEPROM: implementar un salvado inteligente que no sobreescriba siempre la misma parte de la memoria EEPROM (si no no me va a durar nada)
           VER COMO LO IMPLEMENTE EN EL PROGRAMA DE MEDIDAS

        - CUANDO SE MODIFIQUE un parametro y salgamos del modo configuracion se deben salvar los datos en EEPROM, y se debe reinicializar todo (o el PID)
            si se complica le pongo un boton que resetee el PID, y a la mierda
*/


// usado en display
#define latchPin 3

// constantes utilizadas por HID
#define K_UP 0
#define K_DOWN 1
#define K_ENTER 2

// modos de trabajo del controlador
#define MODE_SHOW_TEMPERATURE 0     // muestra temperatura - modo por defecto
#define MODE_SET_POINT 1            // establece Setpoint (usado en PID, CONTROL)
#define MODE_CONTROL 2              // modo control (control de temperatura mas simple, similar a camara fermento)
#define MODE_LOGGER 2               // modo data logger, para analizar funcionamiento heladeras
#define MODE_SETTINGS_LVL_1 10      // LVL1: nivel 1 settings
#define MODE_SETTINGS_LVL_2 20      // LVL2: nivel 2 valores
#define MODE_SETTINGS_LVL_3 30      // LVL1: nivel 3 edicion


// variables globales
float temperature;          // temperatura global, sensada por temperature2.ino
double Setpoint;            // utilizado por pid.ino    
double new_SetPoint = 0;    // utilizado temporalmente en el modo SET_POINT (actions.ino y temperature2.ino)
byte mode = 0;              // modo de trabajo (SHOW TEMP, SET POINT, CONTROL, LOGGER)

void setup() {
    Serial.begin(9600); 
    display_setup();
    temperature2_setup();
    pid_setup();
    hid_setup();
    actions_setup();
    actions_config_setup();
}

void loop() {
    temperature2_loop();
    display_loop();
    pid_loop();
    hid_loop();
    actions_loop();
}
