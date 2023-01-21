/*************************************************************
Title         :   Home automation using blynk
Description   :   To control light's brigntness with brightness,monitor temperature , monitor water level in the tank through blynk app
Pheripherals  :   Arduino UNO , Temperature system, LED, LDR module, Serial Tank, Blynk cloud, Blynk App.
 *************************************************************/

// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID "TMPL1UzVRyf8"
#define BLYNK_DEVICE_NAME "Homeautomation"
#define BLYNK_AUTH_TOKEN "-DoTY2CoC5nG9n2XhVhXASAVdH2CoESA"

// Comment this out to disable prints 
#define BLYNK_PRINT Serial

#include <SPI.h>
#include <Ethernet.h>
#include <BlynkSimpleEthernet.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include "main.h"
#include "temperature_system.h"
#include "ldr.h"
#include "serial_tank.h"

char auth[] = BLYNK_AUTH_TOKEN;
bool heater_sw,inlet_sw,outlet_sw;
unsigned int tank_volume;

BlynkTimer timer;

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

// This function is called every time the Virtual Pin 0 state changes
/*To turn ON and OFF cooler based virtual PIN value*/
BLYNK_WRITE(COOLER_V_PIN)
{
  int value = param.asInt();
  if (value)
  {
    cooler_control(ON);
    lcd.setCursor(7,0);
    lcd.print("CO_LR ON ");
  }
  else
  {
    cooler_control(OFF);
    lcd.setCursor(7,0);
    lcd.print("CO_LR OFF ");
  }
  
}
/*To turn ON and OFF heater based virtual PIN value*/
BLYNK_WRITE(HEATER_V_PIN )
{
  int value = param.asInt();
  if (value)
  {
    heater_control(ON);
    lcd.setCursor(7,0);
    lcd.print("HT_R ON ");
  }
  else
  {
    heater_control(OFF);
    lcd.setCursor(7,0);
    lcd.print("HT_R OFF ");
  }
}
/*To turn ON and OFF inlet vale based virtual PIN value*/
BLYNK_WRITE(INLET_V_PIN)
{
  
}
/*To turn ON and OFF outlet value based virtual switch value*/
BLYNK_WRITE(OUTLET_V_PIN)
{
  
}
/* To display temperature and water volume as gauge on the Blynk App*/  
void update_temperature_reading()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(TEMPERATURE_GAUGE,read_temperature());
}

/*To turn off the heater if the temperature raises above 35 deg C*/
void handle_temp(void)
{
  
}

/*To control water volume above 2000ltrs*/
void handle_tank(void)
{
  
  

}


void setup(void)
{
  Blynk.begin(BLYNK_AUTH_TOKEN);
  /*initialize the lcd*/
    lcd.init();  
    /*turn the backlight */                   
    lcd.backlight();
    /*clear the clcd*/
    lcd.clear();
    /*cursor to the home */
    lcd.home();
    init_ldr();
    init_temperature_system();

    lcd.setCursor(0,0);
    lcd.print("T=");
    timer.setInterval(500L,update_temperature_reading);
    
    
    
    
}

void loop(void) 
{
      
      brightness_control();
      lcd.setCursor(0,2);
      String temperature;
      temperature = String(read_temperature(),2);
      lcd.print(temperature);
      Blynk.run();
      timer.run();
      
}
