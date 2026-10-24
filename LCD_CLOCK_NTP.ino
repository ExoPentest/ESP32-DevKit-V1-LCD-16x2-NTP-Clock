#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <time.h>

// Here is the initial functions and setups
LiquidCrystal_I2C lcd(0x27,16,2); // LCD Followings
// Wifi Credentials for Connection
;const char ssid[] = "YOUR_WIFI_NAME"; // SSID Name & PUT YOUR OWN SSID 
;const char pass[] = "YOUR_WIFI_PASSWORD"; // PASSWORD & PUT YOUR OWN SSID PASS
// GPIO Settings
int Pin_Poi = 2; // GPIO 2
// Country Time
const int GMT_CURRENT = 6 * 3600 ; // Customize this according to your country
const int DAYLIGHT_OFFSET = 0; // Same as above



void setup() {
  Serial.begin(115200); // Serial baund
  Wire.begin(21,22); // SDA & SCL
  WiFi.mode(WIFI_STA); // WIFI MODE (STA=OWN,AP=CREATED)
  pinMode(Pin_Poi,OUTPUT); // 2,OUTPUT
  lcd.init(); // Initializing LCD 
  lcd.backlight(); // Turning on BackLight 

  WiFi.begin(ssid,pass); // Wifi Initialize
  Serial.println("Connecting to Wifi"); // Serial Monitor
  lcd.setCursor(0,0); // (0,0 = Top Box) (0,1 = Lower Box)
  lcd.print("Connecting to,"); // LCD Print for Upper Box (e.g=TOP)
  lcd.setCursor(0,1); // (0,1 = Lower Box)
  lcd.print("Wifi...."); // LCD Print for Lower Box

  while (WiFi.status() != WL_CONNECTED) {  // Status Verification
    delay(500); // Delay
  }
  // Validation
  Serial.println("Connected"); // Serial Monitor
  Serial.println(ssid); // Your SSID Print
  Serial.println(WiFi.localIP()); // ESP32 LOCALIP 

  lcd.clear(); // Clear Text in LCD
  lcd.print("Initializing,"); // LCD Print
  lcd.setCursor(0,1); // (0,1 = Lower Box)
  lcd.print("Time...."); // LCD Print for Lower Box
  // Time Config

  configTime(GMT_CURRENT , DAYLIGHT_OFFSET,     
              "pool.ntp.org", "time.google.com"); // configTime Function for NTP
  
  



  struct tm tmInfo ; // Date & Time Info Fetched by NTP in Differ Fields, Initially this fields are empty but it is filled by getLocalTime (ex:-MONTH,YEAR,HOUR,SECONDS)

  while(!getLocalTime(&tmInfo)) { // Validation & Fills Data in MONTH,YEAR,HOUR,SECONDS etc
    delay(500); // Delayed
  }

  lcd.clear(); // Clear Text in LCD

}

void loop() {
  struct tm tmInfo ; // For LOOP

  if (getLocalTime(&tmInfo)) { // For LOOP
    char TimeText[17]; // TimeText for Time & 17 Meaning 17 Bytes with following NULL TERMINATOR \n
    char DateText[17]; // DateText for Date & 17 Meaning 17 Bytes with following NULL TERMINATOR \n
  

  strftime(TimeText , sizeof(TimeText), //  TimeText , SIZE, %I = HOUR , %M = MINUTES , %S = SECONDS , tmInfo
           "%I:%M:%S %p" , &tmInfo); 
  
  strftime(DateText , sizeof(DateText), // DateText , SIZE, %d = DAY , %b = MONTH , %Y = YEAR, tmInfo
           "%d %b %Y" , &tmInfo);

  
  lcd.setCursor(0,0); // (0,0 = Top Box)
  lcd.print(TimeText); // TimeText to Display TIME
  lcd.print("  "); // Imaginary Spaces 

  lcd.setCursor(0,1); // (0,1 = Lower Box)
  lcd.print(DateText); // DateText to Display Date
  lcd.print("  "); // Imaginary Spaces



  }

  delay(500); // Delayed for Valdation



}