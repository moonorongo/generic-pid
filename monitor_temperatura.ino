#define K_UP 0
#define K_DOWN 1
#define K_ENTER 2

float temperature;
double Setpoint;
double new_SetPoint = 0;

#define MODE_SHOW_TEMPERATURE 0
#define MODE_SET_POINT 1
#define MODE_SETTINGS_LVL_1 10
#define MODE_SETTINGS_LVL_2 20
#define MODE_SETTINGS_LVL_3 30
byte mode = 0;

void setup() {
    Serial.begin(9600); 
    display_setup();
    temperature_setup();
    pid_setup();
    hid_setup();
    actions_setup();

    // tone(12, 880, 1000);

}

void loop() {
    temperature_loop();
    display_loop();

    pid_loop();
    hid_loop();
    actions_loop();
}
