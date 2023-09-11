#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Arduino_ST7789_Fast.h>
#include <MPU6050.h>

#define TFT_DC    7
#define TFT_RST   8 
#define SCR_WD    240
#define SCR_HT    240

Arduino_ST7789 lcd = Arduino_ST7789(TFT_DC, TFT_RST);

MPU6050 mpu;
const int centreX = 120;
const int centreY = 120;
const int radius = 82;
int xn, yn, xe, ye, xs, ys, xw, yw;

int offsetRadius = 10;
int offsetCentreX = 0;
int offsetCentreY = 0;


void setup() {
  Wire.begin();
  mpu.initialize();
  
  lcd.init(SCR_WD, SCR_HT);
  lcd.fillScreen(BLACK);

}

void loop() {
  int16_t ax, ay, az;
  int16_t gx, gy, gz;
  int offsetRadius = 10;
int offsetCentreX = 0;
int offsetCentreY = 0;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  
  float angle = atan2(ax, ay) * (180.0 / PI);
  if (angle < 0) angle += 360.0;
  xn = ((radius + offsetRadius) * -cos((angle - 0) * M_PI / 180)) + centreX + offsetCentreX;
  yn = ((radius + offsetRadius) * sin((angle - 0) * M_PI / 180)) + centreY + offsetCentreY;

  xe = ((radius + offsetRadius) * -cos((angle - 90) * M_PI / 180)) + centreX + offsetCentreX;
  ye = ((radius + offsetRadius) * sin((angle - 90) * M_PI / 180)) + centreY + offsetCentreY;

  xs = ((radius + offsetRadius) * -cos((angle - 180) * M_PI / 180)) + centreX + offsetCentreX;
  ys = ((radius + offsetRadius) * sin((angle - 180) * M_PI / 180)) + centreY + offsetCentreY;

  xw = ((radius + offsetRadius) * -cos((angle - 270) * M_PI / 180)) + centreX + offsetCentreX;
  yw = ((radius + offsetRadius) * sin((angle - 270) * M_PI / 180)) + centreY + offsetCentreY;
  
  lcd.fillCircle(centreX, centreY, radius, RED);
   lcd.setTextColor(GREEN);
  lcd.setTextSize(2);
  lcd.setCursor(10, 10);
  lcd.print(angle, 0);
  lcd.println(" Deg");
lcd.fillTriangle(110, 120, 120, 40, 130,120,BLUE);
lcd.drawLine(120, 120, 120, 40,BLUE);
 
   lcd.setTextSize(3);
  lcd.setCursor(xn, yn );
  lcd.print("N");
  lcd.setCursor(xe, ye );
  lcd.print("E");
  lcd.setCursor(xs, ys );
  lcd.print("S");
  lcd.setCursor(xw, yw );
  lcd.print("W");
  
 
  delay(1000);
  lcd.fillScreen(BLACK);
}  
