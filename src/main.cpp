/**
 * Created by Adly I. Ifkar
 * <adly.shadowbane@gmail.com>
 * 
 * For ITEBA Physics Laboratory
 */

#include <Arduino.h>
#include <Keyboard.h>

double a;
double c;
bool shouldRead = true;
double lastRead = 0;

int passCount = 0;

void setup()
{
    Keyboard.begin();

    pinMode(A0, INPUT);
    pinMode(2, OUTPUT);
    digitalWrite(A0, HIGH);
}

double dotSeparator(double c)
{
    int wholeSecond = int(c) * 100;
    int calculated = c * 100;
    double removedSecond = (calculated - wholeSecond);
    double returnToDec = removedSecond / 100;

    if (wholeSecond != lastRead && lastRead > 0)
    {
        removedSecond = (calculated - lastRead);
        returnToDec = removedSecond / 100;
    }
    else
    {
        lastRead = wholeSecond;
    }

    return returnToDec;
}

void loop()
{

    if (passCount > 4)
    {
        passCount = 0;
        lastRead = 0;
        a = 0;
    }

    // debug LED
    if (shouldRead)
    {
        digitalWrite(2, HIGH);
    }
    else
    {
        digitalWrite(2, LOW);
    }

    a = millis();

    if (digitalRead(A0) == LOW)
    {
        if (shouldRead)
        {
            c = a / 1000;
            double calculatedVal = dotSeparator(c);
            int finalValue = calculatedVal * 1000;

            Keyboard.print(String(finalValue));
            Keyboard.println("");

            shouldRead = false;
            passCount++;
        }
    }
    else
    {
        shouldRead = true;
    }
}