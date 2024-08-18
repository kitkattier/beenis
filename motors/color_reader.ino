#include <TimerOne.h>
#define S0 6 // Please notice the Pin's define
#define S1 5
#define S2 4
#define S3 10
#define OUT 2
#define OE 7
#define LED 8
#define NUM_CLRS 6
#include "motor_functions.h"

void calibrate(int param);

typedef enum {
  RED , BLUE, 
} Colour;

int nums_colors = 0;

int g_count = 0; // count the frequecy
int g_array[3]; // store the RGB value
int g_flag = 0; // filter of RGB queue
float g_SF[3]; // save the RGB Scale factor

// Init TSC230 and setting Frequency.

void calibrate() {
  //for (int i=0; i < NUM_CLRS; i++)
  Serial.print("guhhh");
  // make motor go forward and stop
  

}

void TSC_Init()
{
    pinMode(S0, OUTPUT);
    pinMode(S1, OUTPUT);
    pinMode(S2, OUTPUT);
    pinMode(S3, OUTPUT);
    pinMode(OUT, INPUT);
    digitalWrite(S0, LOW); // OUTPUT FREQUENCY SCALING 2%
    digitalWrite(S1, HIGH);
}

char check_color(float penis[])
{
  if (penis[0] > 175 && penis[1] < 105 && penis[2] < 100) {
    return 'R'; // RED
  } else if (penis[0] < 120 && penis[1] < 120 && penis[2] > 120) {
    return 'B'; // BLUE 
  } else if (penis[0] < 210 && penis[1] > 200 && penis[2] < 170) {
    return 'G'; // GREEN
  } else if (penis[0] > 225 && penis[1] > 180 && penis[2] < 180){
    return 'Y';
  } else if (penis[0] > 180 && penis[1] < 170 && penis[2] < 190) {
    return 'M';
  } else if (penis[0] < 210 && penis[1] < 225 && penis[2] > 215) { 
    return 'C';
  } else {
    return 'L';
  }
}

// Select the filter color
void TSC_FilterColor(int Level01, int Level02)
{
    if (Level01 != 0) {
        Level01 = HIGH;
    }
    if (Level02 != 0) {
        Level02 = HIGH;
    }
    digitalWrite(S2, Level01);
    digitalWrite(S3, Level02);
}

void TSC_Count()
{
    g_count++;
}

void TSC_Callback()
{
    switch (g_flag) {
        //Serial.println(g_flag);
    case 0:
        //Serial.println("->WB Start");
        TSC_WB(LOW, LOW); // Filter without Red
        break;
    case 1:
        //Serial.print("->Frequency R=");

        //Serial.println(g_count);
        g_array[0] = g_count;
        TSC_WB(HIGH, HIGH); // Filter without Green
        break;
    case 2:
        //Serial.print("->Frequency G=");
        //Serial.println(g_count);
        g_array[1] = g_count;
        TSC_WB(LOW, HIGH); // Filter without Blue
        break;
    case 3:
        //Serial.print("->Frequency B=");
        //Serial.println(g_count);
        //Serial.println("->WB End");
        g_array[2] = g_count;
        TSC_WB(HIGH, LOW); // Clear(no filter)
        break;
    default:
        g_count = 0;
        break;
    }
}

void TSC_WB(int Level0, int Level1) // White Balance
{
    g_count = 0;
    g_flag++;
    TSC_FilterColor(Level0, Level1);
    Timer1.setPeriod(50000); // set 1s period
}

void setup()
{
    pinMode(OE, OUTPUT);
    pinMode(LED, OUTPUT);
    digitalWrite(OE, LOW);
    digitalWrite(LED, LOW);
    TSC_Init();
    Serial.begin(9600);
    Timer1.initialize(); // defaulte is 1s
    Timer1.attachInterrupt(TSC_Callback);
    attachInterrupt(0, TSC_Count, RISING);
    delay(4000);
    for (int i = 0; i < 3; i++) {
        //Serial.println(g_array[i]);
    }
    g_SF[0] = 255.0 / g_array[0]; // R Scale factor
    g_SF[1] = 255.0 / g_array[1]; // G Scale factor
    g_SF[2] = 255.0 / g_array[2]; // B Scale factor
    Serial.println(g_SF[0]);
    Serial.println(g_SF[1]);
    Serial.println(g_SF[2]);

    

}

// I kind of hate it but i think we need this to be global here
char previous = 'L';

void loop()
{
    g_flag = 0;
    float drake[3];
    for (int i = 0; i < 3; i++) {
        Serial.println(int(g_array[i] * g_SF[i]));
        drake[i] = int(g_array[i] * g_SF[i]);
    }

    //delay(5000);
    //while (check_color(drake) == 'L') { 
    //  move_forward(75);
    //}

    //move_forward(65); // constant speed
    move_forward(110, 110);
    delay(100);
    move_forward(80, 80);
    delay(100);
    brake();
    



    Serial.println("PENIS!!!!");

    char bum = check_color(drake);
    
    if (bum != 'L') {
      Serial.println("SKIBIDID");
      Serial.println(bum);
      if (bum == 'B' && previous != 'B') {
        Serial.println("BLUE DETECTED");
        brake();
        delay(5000);
      } else if (bum == 'R' && previous != 'R') {
        Serial.println("RED DETECTED");
        brake();
        delay(5000);
      } else if (bum == 'C' && previous != 'C') {
        Serial.println("CYAN DETECTED");
        brake();
        delay(5000);
        } else if (bum == 'M' && previous != 'M') {
        Serial.println("MAGENTA DETECTED");
        brake();
        delay(5000);
        } else if (bum == 'Y' && previous != 'Y') {
        Serial.println("YELLOW DETECTED");
        brake();
        delay(5000);
        } else {
        Serial.println("This is probably the same as before!!");
        brake();
      }
    } else {
      Serial.println("NOT SKIBIDDIDIDID");
    }
    previous = bum;
    //Serial.println(check_color(drake));
    delay(200);
}