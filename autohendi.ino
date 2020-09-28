#include <uStepperSLite.h>
#include <OneWire.h>

#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

uStepperSLite stepper;

// Nominal power input
float P = 0;
// Pot temperature (celsius)
float T_pot = 0.0;
// Pot temperature reference
float T_pot_r = 66.0;
// Pot temperature error
float e = 0.0;
// Pot temperature error integral
//float ei = 0.0;
// Control input
float u = 0.0;

void power_input(float power){
    stepper.moveToAngle(power * 0.20 + 180.0, HARD);
}

void turn_off(){
    stepper.moveToAngle(0.0, HARD);
}

void setup(void){
    Serial.begin(9600);
    sensors.begin();

    stepper.setup();

    power_input(0.0);
    delay(5000);
}

float sample_temperature(){
    sensors.requestTemperatures();
    return sensors.getTempCByIndex(1);
}

void loop(void){
    T_pot = sample_temperature();
    
    // Error
    e = T_pot_r - T_pot;
    //ei += e * 5;

    //ei = constrain(ei, -900, 2200);

    u = e * 60.0;

    if (e < 0.0) {
        P = -900;
    } else {
        P = constrain(u, -900, 2200);
    }

    // Set power input
    power_input(P);

    Serial.print("T_pot = ");
    Serial.print(T_pot);
    Serial.print(" [degC] | ");
    Serial.print("e = ");
    Serial.print(e);
    Serial.print(" [degC] | ");
    //Serial.print("ei = ");
    //Serial.print(ei);
    //Serial.print(" [.] | ");
    Serial.print("P = ");
    Serial.print(P);
    Serial.println(" [W]");
    
    // Sample freq.
    delay(5000);
}
