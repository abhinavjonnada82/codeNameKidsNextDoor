
#include <Wire.h>

#define LIDARLite_ADDRESS 0x62 // Default I2C Address of LIDAR-Lite.
#define RegisterMeasure 0x00   // Register to write to initiate ranging.
#define MeasureValue 0x04      // Value to initiate ranging.
#define RegisterHighLowB 0x8f  // Register to get both High and Low bytes in 1 call.
#define trigPin 13
#define echoPin 12
#define led 7
#define vibMot 6

//int ButtonValue = 0;
//int Button = 3;



int pos = 0;      // Position of the servo (degress, [0, 180])
int distance = 0; // Distance measured

void setup()
{
    // Serial output
    Serial.begin(9600);
    //pinMode(Button, INPUT);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(led, OUTPUT);
    pinMode(vibMot, OUTPUT);
    Serial.println("< START >");


    // LIDAR control
    Wire.begin(); // join i2c bus
}

// Get a measurement from the LIDAR Lite
int lidarGetRange(void)
{
    int val = -1;

    Wire.beginTransmission((int)LIDARLite_ADDRESS); // transmit to LIDAR-Lite
    Wire.write((int)RegisterMeasure);               // sets register pointer to  (0x00)
    Wire.write((int)MeasureValue);                  // sets register pointer to  (0x00)
    Wire.endTransmission();                         // stop transmitting

    delay(200); // Wait 20ms for transmit

    Wire.beginTransmission((int)LIDARLite_ADDRESS); // transmit to LIDAR-Lite
    Wire.write((int)RegisterHighLowB);              // sets register pointer to (0x8f)
    Wire.endTransmission();                         // stop transmitting

    delay(200); // Wait 20ms for transmit

    Wire.requestFrom((int)LIDARLite_ADDRESS, 2); // request 2 bytes from LIDAR-Lite

    if (2 <= Wire.available()) // if two bytes were received
    {
        val = Wire.read();  // receive high byte (overwrites previous reading)
        val = val << 8;     // shift high byte to be high 8 bits
        val |= Wire.read(); // receive low byte as lower 8 bits
    }

    return val;
}

void serialPrintRange(int pos, int distance, int test)
{
    Serial.print("Position (degree): ");
    Serial.print(pos);

    Serial.print("\t Ultrasonic Distance (cm): ");
    Serial.print(test);

    Serial.print("\t\t Lidar Distance (cm): ");
    Serial.println(distance);
}

void loop()
{
    //ButtonValue = digitalRead(Button);


        long duration, distance_ultra = 0, test = 0;

        //--------------------------
        for (pos = 0; pos <= 180; pos += 1)
        {

         
            digitalWrite(led, LOW);
            digitalWrite(vibMot, LOW);
            distance = lidarGetRange();
            digitalWrite(trigPin, LOW);
            delayMicroseconds(5);
            digitalWrite(trigPin, HIGH);
            delayMicroseconds(10);
            digitalWrite(trigPin, LOW);
            pinMode(echoPin, INPUT);
            duration = pulseIn(echoPin, HIGH);
            distance_ultra = (duration / 2) / 29.1;

            //test = distance_ultra;

            if (distance < 10 || distance_ultra < 10) // Checking the distance, you can change the value
            {

                digitalWrite(vibMot, HIGH);
                digitalWrite(led, HIGH);
                delay(200);
                digitalWrite(led, LOW);
                delay(200);
                digitalWrite(led, HIGH);
                delay(200);
                digitalWrite(led, HIGH);
            }
            else
            {

                digitalWrite(led, LOW);
                digitalWrite(vibMot, LOW);
            }

            if (distance > 50 || distance_ultra > 50) {
              Serial.print("out of range");
            }

            serialPrintRange(pos, distance, distance_ultra);
            delay(500);
        }


   }
  
    

//------------------------------------

