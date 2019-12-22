// On the Attiny we can only do classification
// since there's no serial

#include "model_attiny.h"


#define LED 0
#define S2 2
#define S3 3
#define sensorOut 4

double features[3];

void setup() {
    pinMode(S2, OUTPUT);
    pinMode(S3, OUTPUT);
    pinMode(sensorOut, INPUT);
    pinMode(LED, OUTPUT);
}

void loop() {
    readRGB();
    classify();
    delay(100);
}

int readComponent(bool s2, bool s3) {
    delay(10);
    digitalWrite(S2, s2);
    digitalWrite(S3, s3);

    return pulseIn(sensorOut, LOW);
}

void readRGB() {
    features[0] = readComponent(LOW, LOW);
    features[1] = readComponent(HIGH, HIGH);
    features[2] = readComponent(LOW, HIGH);
}

void classify() {
    analogWrite(LED, classIdxToName(predict(features)));
}