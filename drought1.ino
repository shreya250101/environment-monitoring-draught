
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


//INITIALIZE
int temperature = 0;
int gaslevel = 0;
int moist = 0;
int rainfall=0;

//pressure in water
int force1 = 0;
//pressure in Hg
int force2 = 0;
double airvelocity;

//rainfall in precent
int value =0;
//moist in percentage
int moistper=0;

int led = 13;
int piezo=7;

//temporary variables;
double temp; 
double pressure1;
double pressure2;
double d;



void setup()
{
Serial.begin(9600);
  lcd.begin(16, 2);
}



void loop()
{
  force1 = analogRead(A2);
  pressure1=(double)force1/1; //calculating pressure for force in water
  
  force2 = analogRead(A5);
pressure2=(double)force2/1;//calculating pressure for force in Hg
  
  temperature = analogRead(A3);
  gaslevel = analogRead(A4);
  rainfall = analogRead(A1);
  moist = analogRead(A0);
  
   d=(double)1.325*(pressure2/temp);
   airvelocity=(double)1096.7*sqrt(pressure1/d);
  
 airvelocity= airvelocity/197;//converting ft/s to m/s
  
  
  Serial.println(airvelocity);
   temp = (double)temperature / 1024;       //find percentage of input reading
  temp = temp * 5;                 //multiply by 5V to get voltage
  temp = temp - 0.5;               //Subtract the offset 
  temp = temp * 100;               //Convert to degrees 

  lcd.setCursor(0, 1);
  
 value =(rainfall)*100L/1023;
  
 moistper =(moist)*100L/1023;
  
  if (gaslevel>100){
    value=value+10;
  }
  if(temperature>40){
    
    moistper=moistper-10;}
  
  if(airvelocity>25)
  {value=value-25; }
  
   if ((moistper<30) && (value<25))
{
	lcd.print("severe        ");
   digitalWrite(led, HIGH);
    tone(7, 247, 10);
}
  else if ((moistper<50)&& (value<40))
  {	lcd.setCursor(0, 1);
    lcd.print("mild effect  ");
    digitalWrite(led, HIGH);
    noTone(7); 
  }
  else{
    lcd.setCursor(0, 1);
    lcd.print("normal         ");
    digitalWrite(led, LOW);
    noTone(7); 
    
  } 
       

}





