#include <LIDARLite.h>
#include <Wire.h>
#define trigPin 13
#define echoPin 12
#define led 7
#define vibMot 6

//int ButtonValue = 0;
//int Button = 3;

LIDARLite myLidarLite;


void setup() {
    // Serial output
    Serial.begin(9600);
    //pinMode(Button, INPUT);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(led, OUTPUT);
    pinMode(vibMot, OUTPUT);
    Serial.println("< START >");

     myLidarLite.begin(0, true); 
     myLidarLite.configure(0);
}



void serialPrintRange(int pos, int dist, int test) {
    Serial.print("Position (degree): ");
    Serial.print(pos);

    Serial.print("\t Ultrasonic Distance (cm): ");
    Serial.print(test);

    Serial.print("\t\t Lidar Distance (cm): ");
    Serial.println(dist);
}

int calcUltraDist(int dura) {
  int calcUltraVal = 0;
  dura = pulseIn(echoPin, HIGH);
  calcUltraVal = (dura / 2) / 29.1;
  return calcUltraVal;
}

void loop() {
    //ButtonValue = digitalRead(Button);

        long duration, distanceUltra = 0;
        int count = 0;      // Counter
        int distLidar = 0; // Distance measured
        
        for (count = 0; count <= 180; count += 1) {

            digitalWrite(led, LOW);
            digitalWrite(vibMot, LOW);
            distLidar = myLidarLite.distance();
            digitalWrite(trigPin, LOW);
            delayMicroseconds(5);
            digitalWrite(trigPin, HIGH);
            delayMicroseconds(10);
            digitalWrite(trigPin, LOW);
            pinMode(echoPin, INPUT);
            distanceUltra =  calcUltraDist(duration);


            if (distLidar < 10 || distanceUltra < 10) { // Checking the distance, change the value if required

                digitalWrite(vibMot, HIGH);
                digitalWrite(led, HIGH);
                delay(200);
                digitalWrite(led, LOW);
                delay(200);
                digitalWrite(led, HIGH);
                delay(200);
                digitalWrite(led, HIGH);
            }
            else {

                digitalWrite(led, LOW);
                digitalWrite(vibMot, LOW);
            }

            serialPrintRange(count, distLidar, distanceUltra);
            delay(500);
        }


   }

