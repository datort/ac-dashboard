
#include <LiquidCrystal.h>

// select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// define some values used by the panel and buttons
int lcd_key     = 0;
int adc_key_in  = 0;

const int pageBasics = 0; 
const int pageTyre = 1; 
const int pageRev = 2; 

const String keyRev = "1"; 
const String keyGear = "2"; 
const String keySetShiftIndicator = "3";

String vGear = "n";
String vRev = "0"; 

int page = pageBasics; 

int delimiter = 59; // means: ; 
int shiftIndicator = 16000;
char data[80]; 


/*#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5



// read the buttons
int read_LCD_buttons() {
 adc_key_in = analogRead(0);      // read the value from the sensor 
 // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
 // we add approx 50 to those values and check to see if we are close
 if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
 // For V1.1 us this threshold
 if (adc_key_in < 50)   return btnRIGHT;  
 if (adc_key_in < 250)  return btnUP; 
 if (adc_key_in < 450)  return btnDOWN; 
 if (adc_key_in < 650)  return btnLEFT; 
 if (adc_key_in < 850)  return btnSELECT; 


 return btnNONE;  // when all others fail, return this...
}*/

void setup() {
	lcd.begin(16, 2); 
	lcd.setCursor(0,0);

	Serial.begin(9600);
	pinMode(13, OUTPUT);
	pinMode(11, OUTPUT);
}

void loop()
{
	while (Serial.available() > 0) {

		Serial.readBytesUntil(delimiter, data, 80);
		String command = String(data);
	    
	    if (command.substring(0,1) == keyRev) {
	        vRev = command.substring(2);
	    }

	    if (command.substring(0,1) == keyGear) {
	        vGear = command.substring(2);
	    }

	    if (command.substring(0,1) == keySetShiftIndicator) {
	    	shiftIndicator = command.substring(2).toInt();
	    }

	    memset(data, '\0', 80);


    } 

    if (vRev.toInt() > (shiftIndicator - 1000)) {
    	digitalWrite(11, HIGH);
    } else {
    	digitalWrite(11, LOW);
    }

    if (vRev.toInt() > (shiftIndicator - 500)) {
    	digitalWrite(13, HIGH);
    } else {
    	digitalWrite(13, LOW);
    }

    if (vRev.toInt() > shiftIndicator) {	
    	delay(40);
    	digitalWrite(13, LOW);
    	digitalWrite(11, LOW);
    	delay(40);
    } 


	switch (page) {
		case pageBasics:
			drawPageBasics(); 
		break;
	}
}

void drawPageBasics() {
	lcd.setCursor(0,0);
	lcd.print("Gear:     Rev:");
	lcd.setCursor(0,1);

	String revOut = vRev;
	for(int i = 0; i < vRev.length(); i++) {
		revOut = revOut + " ";
	}

	lcd.print(vGear + "         " + revOut);

}