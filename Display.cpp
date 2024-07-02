#include "Display.h"
#include <LiquidCrystal_I2C.h>

using namespace std;

bool lcd_initialization = true;
bool display_screen = 0;


Display::Display(byte pin) {
  this->pin = pin;
  this->text = "";

  init();
}



void Display::init() {  // put your setup code here, to run once:
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void Display::run(Clara &clara, LiquidCrystal_I2C &lcd) {
  

  state = clara.get_state();
  String state_string = "";
  switch (state) {
    case 1:
      state_string = String("Initialization");
      break;
    case 2:
      state_string = String("Stand by");
      break;
    case 3:
      state_string = String("In Production");
      break;
    case 4:
      state_string = String("Settling");
      break;
    case 5:
      state_string = String("Transfering Fluid");
      break;
  }


  String flow_string = String(clara.get_flow()) + " l/min";
  String NaClO_pumped = String(clara.get_setpoint());
  String C_flow = String(clara.c_flowrate);
  String Target_frc = String(clara.target_naclo_con);
  String dummy_voltage = String(clara.get_voltage());
  String dummy_time_left = String(clara.pr_time_min);

  String prod_time = String(clara.pr_time_min);
  String transfer_time = String(clara.target_naclo_con);
  String settling_time = String(clara.settling_min);

  unsigned long currentDisplay_state_Millis = millis();  // Get the current time
    


  if (currentDisplay_state_Millis - previousMainMillisDisplay >= intervalDisplaymain) {
    Serial.print("State: ");
    Serial.println(state);


    // Check if it's time to call function1 (every second)
    //inital welcome screen
    if (state == 0 && (lcd_initialization == true)) {
      // unsigned long current_init_Millis = millis();  // Get the current time
      // unsigned long previousMillisLCDinit = 0;
      // if (current_init_Millis - previousMillisLCDinit >= initializationDelay) {

      String message1 = "Clara Begins";
      String message2 = "Add 350ml Of Brine";
      String message3 = "& Add 4L of Water";
      String message4 = "Into The Prod Bottle";
      Serial.println("Inside Initalization");


      LCDWrite(message1, message2, message3, message4, lcd);

      //previousMillisLCDinit = current_init_Millis;
      //} else {
      delay(5000);
      lcd_initialization = false;
      clara.set_state(2);
      //}

    }


    else if (state == 2) {


      unsigned long current_state_Millis = millis();  // Get the current time

      if (current_state_Millis - previousMillisDisplay >= intervalDisplay) {

        previousMillisDisplay = current_state_Millis;
        display_screen = !display_screen;
      }

      if (display_screen == 0) {
        LCDWrite("Flow: " + flow_string, "NaClO.Pumped: " + NaClO_pumped + " L", "Comm.Flow:" + C_flow + " m3", "Target FRC: " + Target_frc, lcd);
      } else if (display_screen == 1) {
        LCDWrite("State: " + state_string, "Voltage: " + dummy_voltage + " V", lcd);
        //LCDWrite("State: " + state, "Time left: " + NaClO_pumped + " L", "Voltage:" + C_flow + " V", "Target FRC: "+Target_frc, lcd);
      }


    }

    else if (state == 3) {

      unsigned long current_state_Millis = millis();  // Get the current time

      if (current_state_Millis - previousMillisDisplay >= intervalDisplay) {

        previousMillisDisplay = current_state_Millis;
        display_screen = !display_screen;
      }

      if (display_screen == 0) {
        LCDWrite("Flow: " + flow_string, "NaClO.Pumped: " + NaClO_pumped + " L", "Comm.Flow:" + C_flow + " m3", "Target FRC: " + Target_frc, lcd);
      } else if (display_screen == 1) {
        LCDWrite("State: " + state_string, "Time Left: " + prod_time + " min", "Voltage: " + dummy_voltage + " V", "Target FRC: " + Target_frc, lcd);
        //LCDWrite("State: " + state, "Time left: " + NaClO_pumped + " L", "Voltage:" + C_flow + " V", "Target FRC: "+Target_frc, lcd);
      }
    }


    else if (state == 4) {
      unsigned long current_state_Millis = millis();  // Get the current time

      if (current_state_Millis - previousMillisDisplay >= intervalDisplay) {

        previousMillisDisplay = current_state_Millis;
        display_screen = !display_screen;
      }

      if (display_screen == 0) {
        LCDWrite("Flow: " + flow_string, "NaClO.Pumped: " + NaClO_pumped + " L", "Comm.Flow:" + C_flow + " m3", "Target FRC: " + Target_frc, lcd);
      } else if (display_screen == 1) {
        LCDWrite("State: " + state_string, "Time Left: " + settling_time + " min", "Voltage: " + dummy_voltage + " V", "Target FRC: " + Target_frc, lcd);
        //LCDWrite("State: " + state, "Time left: " + NaClO_pumped + " L", "Voltage:" + C_flow + " V", "Target FRC: "+Target_frc, lcd);
      }


    } else if (state == 5) {
      unsigned long current_state_Millis = millis();  // Get the current time

      if (current_state_Millis - previousMillisDisplay >= intervalDisplay) {

        previousMillisDisplay = current_state_Millis;
        display_screen = !display_screen;
      }

      if (display_screen == 0) {
        LCDWrite("Flow: " + flow_string, "NaClO.Pumped: " + NaClO_pumped + " L", "Comm.Flow:" + C_flow + " m3", "Target FRC: " + Target_frc, lcd);
      } else if (display_screen == 1) {
        LCDWrite("State: " + state_string, "Time Left: " + transfer_time + " min", "Voltage: " + dummy_voltage + " V", "Target FRC: " + Target_frc, lcd);
        //LCDWrite("State: " + state, "Time left: " + NaClO_pumped + " L", "Voltage:" + C_flow + " V", "Target FRC: "+Target_frc, lcd);
      }




    }

    else if (state == 6) {
    }
    previousMainMillisDisplay = currentDisplay_state_Millis;
  }
}


void Display::LCDWrite(String text1, String text2, String text3, String text4, LiquidCrystal_I2C &lcd) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(text1);
  lcd.setCursor(0, 1);
  lcd.print(text2);
  lcd.setCursor(0, 2);
  lcd.print(text3);
  lcd.setCursor(0, 3);
  lcd.print(text4);
}
// function that takes two parameters as an argument and display
void Display::LCDWrite(String text1, String text2, LiquidCrystal_I2C &lcd) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(text1);
  lcd.setCursor(0, 1);
  lcd.print(text2);
  
}