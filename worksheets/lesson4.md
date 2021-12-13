---
title: "Übung 4"
author: [Embedded Systems]
date: ""
subject: "Mikrocontroller II"
keywords: [Mikrocontroller, Embedded Systems]
lang: "de"
page-background: "background5.pdf"
...

# Übung 4 - Mikrocontroller II

## Aufgabe 1 - Buzzer

Verbinde den Buzzer über einen Pin an das RED-V Board. Implementiere über eine doppelte Schleife das Abspielen eines Tons. Nutze dazu die innere Schleife für die Tonfrequenz (entsprechender GPIO auf high, warten, GPIO low, warten...) und die äußere Schleife für die Tondauer. Stelle die Wartezeit so ein, dass der Ton 440Hz trifft. 

## Aufgabe 2 - PCF8591

Verbinde den PCF8591 über I2C mit dem RED-V Board. Initialisiere die Verbindung mit 100kHz. Schreibe eine Funktion für das Senden und eine für das Empfangen von Daten zum PCF8591 AD-/DA-Wander. Beachte dabei genau das Auslesen des Sensors, da beispielsweise das erste gelesene Byte nicht brauchbar ist. Lies daher genau das Datenblatt.

## Aufgabe 3 - WS2812B

Letztlich verbinde den WS2812B mit dem Board. Die Ansteuerung erfolgt, indem hintereinander für die 10 LEDs die RGB-Farben gemäß dem Protokoll des Datenblatts übertragen werden. Eine Farbe wird mit 24 Bits für die RGB-Werte übertragen. Dabei werden die Werte 0 und 1 unterschiedlich kodiert (s. Datenblatt 0 code und 1 code). Die Transferzeiten sind sehr gering, so dass man diesen Teil des Bit-Banging direkt in Assembler umsetzen sollte und anhand der Taktzyklen auf die Transferzeiten schließt. Um die richtigen Transferzeiten zu treffen, sollte mit der Annahme gearbeitet werden, dass der Prozessor mit 16 MHz getaktet ist und ein _normaler_ Befehl (z.B. addi, nop) einen Takt dauert, ein Sprungbefehl kann mit vier Takten angenommen werden. 



