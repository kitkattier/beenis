#include <TimerOne.h>
#define S0 6 // Please notice the Pin's define
#define S1 5
#define S2 4
#define S3 10
#define OUT 2
#define OE 7
#define LED 8
#define NUM_CLRS 6

void calibrate(int param);
void TSC_WB(int Level0, int Level1); // White Balance

typedef enum {
  RED ,
  BLUE,
  GREEN,
  YELLOW,
  MAGENTA,
  CYAN,
  WHITE,
  BLACK,
} Color;

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

Color check_color(float penis[])
{
  if (penis[0] > 190 && penis[1] < 155 && penis[2] < 155) {
    return RED; // RED
  } else if (penis[0] < 120 && penis[1] < 120 && penis[2] > 120) {
    return BLUE; // BLUE 
  } else if (penis[0] < 160 && penis[1] > 160 && penis[2] < 140) {
    return GREEN; // GREEN
  } else if (penis[0] > 225 && penis[1] > 180 && penis[2] < 180){
    return YELLOW;
  } else if (penis[0] > 180 && penis[1] < 170 && penis[2] < 190) {
    return MAGENTA;
  } else if (penis[0] < 140 && penis[1] < 175 && penis[2] > 150) { 
    return CYAN;
  } else {
    return WHITE;
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

void init_color_reader()
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
