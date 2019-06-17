#include <SoftwareSerial.h>


// Mux control pins
/* #define s0 9
#define s1 10
#define s2 11
#define s3 12
*/

#define s0 4    // use PD4 from ATMEGA328P-AU for MUX_selector0
#define s1 7    // use PD5 from ATMEGA328P-AU for MUX_selector1
#define s2 8    // use PD6 from ATMEGA328P-AU for MUX_selector2

byte val;

//Mux in "SIG" pin
//int SIG_pin = 0;
//int z = 0;                                                                      



int deltaT = 0;
unsigned long previousTime = 0;
unsigned long currentTime = 0;


void setup() {

  // set MUX_Selector Pins from ATMEGA328P-AU output pins //
  pinMode(s0, OUTPUT);    
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  //pinMode(s3, OUTPUT);

  // Initialize MUX_Selector Pins from ATMEGA328P-AU to 0V //
  digitalWrite(s0, LOW);
  digitalWrite(s1, LOW);
  digitalWrite(s2, LOW);
  digitalWrite(13, LOW);
  //digitalWrite(s3, LOW);

  // adjust boardrate 1Mega at the board. You need to adjust the boardrate at PC separately to receive the signal from the board. // 
  Serial.begin(115200);//1硫붽�  


}

int sensor1[] = {
  0,0,0,0,0,0,0,0
  };


void loop() {
  // put your main code here, to run repeatedly:

    currentTime = millis();
    deltaT = (currentTime - previousTime); // time to cycle 1 loop.
    
    // save the sensor signal value at the 9x1 buffer(='sensor1[]')
    // Pin I13 from the MUX helps to remove the remaining voltage in Cap at MUX.

  for (int i = 0; i < 8 ; i ++)
  {
    sensor1[i] = readMux(i);
    
    analogRead(A1);
    delay(10);
  }
 //sensor1[0] = readMux(0);    readMux(13);
 //sensor1[1] = readMux(1);    readMux(13);
 //sensor1[2] = readMux(2);    readMux(13);
 //sensor1[3] = readMux(3);    readMux(13);
 //sensor1[4] = readMux(4);    readMux(13);
 //sensor1[5] = readMux(5);    readMux(13);
 //sensor1[6] = readMux(6);    readMux(13);
 //sensor1[7] = readMux(7);    readMux(13);
 //sensor1[8] = readMux(8);    readMux(13);
 
  

  
   Serial.print(deltaT);
   Serial.print(" ");
     for (int i = 0; i<8 ; i++)
      {
        //Serial.print("(");
       Serial.print(sensor1[i]);
         
        Serial.print(" ");
        //Serial.print(i);
        //Serial.print(")");
      
      }

      Serial.println();

  
    previousTime = currentTime;
    //delay(5);
}


int readMux(int channel) {
  int controlPin[] = {s0, s1, s2};

  int muxChannel[8][3] = {
  {0, 0, 0}, //0
  {1, 0, 0}, //1
  {0, 1, 0}, //2
  {1, 1, 0}, //3
  {0, 0, 1}, //4
  {1, 0, 1}, //5
  {0, 1, 1}, //6
  {1, 1, 1}, //7
  
  
  };

  for (int i = 0; i < 3; i ++) {
    digitalWrite(controlPin[i], muxChannel[channel][i]);  // S0, S1, S2�뿉 0 0 0 �쓣 �꽔�쓬.
  
  }
   //   Serial.println();
   // if((channel) %2 == 1 || channel == 8 || channel == 0 ){
 //if(channel == 1){
    //delay(2);
   //}
   
  //read the value at the SIG pin
 delay(1);
 int val = analogRead(A0);

  //return the value
  return val;

}
