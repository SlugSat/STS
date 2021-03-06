EESchema Schematic File Version 4
LIBS:STS_DAQ_PCB-cache
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Device:Rotary_Encoder SW?
U 1 1 5EABB72B
P 9100 1200
F 0 "SW?" V 9350 1250 50  0000 L CNN
F 1 "Rotary_Encoder" V 9500 900 50  0000 L CNN
F 2 "" H 8950 1360 50  0001 C CNN
F 3 "~" H 9100 1460 50  0001 C CNN
	1    9100 1200
	0    -1   -1   0   
$EndComp
$Comp
L Sensor_Motion:ADXL343 U?
U 1 1 5EABCDFB
P 9100 3950
F 0 "U?" H 9644 3996 50  0000 L CNN
F 1 "ADXL343" H 9644 3905 50  0000 L CNN
F 2 "Package_LGA:LGA-14_3x5mm_P0.8mm_LayoutBorder1x6y" H 9100 3950 50  0001 C CNN
F 3 "https://www.analog.com/media/en/technical-documentation/data-sheets/ADXL343.pdf" H 9100 3950 50  0001 C CNN
	1    9100 3950
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5EABF405
P 6900 1400
F 0 "C?" H 7015 1446 50  0000 L CNN
F 1 "C" H 7015 1355 50  0000 L CNN
F 2 "" H 6938 1250 50  0001 C CNN
F 3 "~" H 6900 1400 50  0001 C CNN
	1    6900 1400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5EABF864
P 6900 1650
F 0 "#PWR?" H 6900 1400 50  0001 C CNN
F 1 "GND" H 6905 1477 50  0000 C CNN
F 2 "" H 6900 1650 50  0001 C CNN
F 3 "" H 6900 1650 50  0001 C CNN
	1    6900 1650
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5EABFD6C
P 6900 1150
F 0 "#PWR?" H 6900 1000 50  0001 C CNN
F 1 "+3.3V" H 6915 1323 50  0000 C CNN
F 2 "" H 6900 1150 50  0001 C CNN
F 3 "" H 6900 1150 50  0001 C CNN
	1    6900 1150
	1    0    0    -1  
$EndComp
Wire Wire Line
	6900 1550 6900 1650
Wire Wire Line
	6900 1150 6900 1250
$Comp
L power:GND #PWR?
U 1 1 5EAC104A
P 7400 2050
F 0 "#PWR?" H 7400 1800 50  0001 C CNN
F 1 "GND" H 7405 1877 50  0000 C CNN
F 2 "" H 7400 2050 50  0001 C CNN
F 3 "" H 7400 2050 50  0001 C CNN
	1    7400 2050
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R?
U 1 1 5EAC19C0
P 7400 1400
F 0 "R?" H 7468 1446 50  0000 L CNN
F 1 "60" H 7468 1355 50  0000 L CNN
F 2 "" V 7440 1390 50  0001 C CNN
F 3 "~" H 7400 1400 50  0001 C CNN
	1    7400 1400
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D?
U 1 1 5EAC26C4
P 7400 1800
F 0 "D?" V 7439 1683 50  0000 R CNN
F 1 "LED" V 7348 1683 50  0000 R CNN
F 2 "" H 7400 1800 50  0001 C CNN
F 3 "~" H 7400 1800 50  0001 C CNN
	1    7400 1800
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7400 1550 7400 1650
Wire Wire Line
	7400 1950 7400 2050
$Comp
L power:+3.3V #PWR?
U 1 1 5EAC3774
P 7400 1150
F 0 "#PWR?" H 7400 1000 50  0001 C CNN
F 1 "+3.3V" H 7415 1323 50  0000 C CNN
F 2 "" H 7400 1150 50  0001 C CNN
F 3 "" H 7400 1150 50  0001 C CNN
	1    7400 1150
	1    0    0    -1  
$EndComp
Wire Wire Line
	7400 1150 7400 1250
Text GLabel 8650 3000 0    50   BiDi ~ 0
SCL
Text GLabel 9350 3000 0    50   BiDi ~ 0
SDA
$Comp
L Device:R_US R?
U 1 1 5EAC9ACD
P 8800 2850
F 0 "R?" H 8868 2896 50  0000 L CNN
F 1 "4.7k" H 8868 2805 50  0000 L CNN
F 2 "" V 8840 2840 50  0001 C CNN
F 3 "~" H 8800 2850 50  0001 C CNN
	1    8800 2850
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R?
U 1 1 5EACA6C1
P 9500 2850
F 0 "R?" H 9568 2896 50  0000 L CNN
F 1 "4.7k" H 9568 2805 50  0000 L CNN
F 2 "" V 9540 2840 50  0001 C CNN
F 3 "~" H 9500 2850 50  0001 C CNN
	1    9500 2850
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5EACAF63
P 8800 2700
F 0 "#PWR?" H 8800 2550 50  0001 C CNN
F 1 "+3.3V" H 8815 2873 50  0000 C CNN
F 2 "" H 8800 2700 50  0001 C CNN
F 3 "" H 8800 2700 50  0001 C CNN
	1    8800 2700
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5EACB8A7
P 9500 2700
F 0 "#PWR?" H 9500 2550 50  0001 C CNN
F 1 "+3.3V" H 9515 2873 50  0000 C CNN
F 2 "" H 9500 2700 50  0001 C CNN
F 3 "" H 9500 2700 50  0001 C CNN
	1    9500 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	8650 3000 8800 3000
Wire Wire Line
	9350 3000 9500 3000
Text GLabel 8400 3950 0    50   BiDi ~ 0
SDA
Wire Wire Line
	8400 3950 8600 3950
Text GLabel 8400 4050 0    50   BiDi ~ 0
SCL
Wire Wire Line
	8400 4050 8600 4050
$Comp
L power:+3.3V #PWR?
U 1 1 5EAD416C
P 8300 3750
F 0 "#PWR?" H 8300 3600 50  0001 C CNN
F 1 "+3.3V" H 8315 3923 50  0000 C CNN
F 2 "" H 8300 3750 50  0001 C CNN
F 3 "" H 8300 3750 50  0001 C CNN
	1    8300 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	8600 3850 8300 3850
Wire Wire Line
	8300 3850 8300 3750
$Comp
L power:GND #PWR?
U 1 1 5EAD52F5
P 9100 4450
F 0 "#PWR?" H 9100 4200 50  0001 C CNN
F 1 "GND" H 9105 4277 50  0000 C CNN
F 2 "" H 9100 4450 50  0001 C CNN
F 3 "" H 9100 4450 50  0001 C CNN
	1    9100 4450
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5EAD56E8
P 9100 3450
F 0 "#PWR?" H 9100 3300 50  0001 C CNN
F 1 "+3.3V" H 9115 3623 50  0000 C CNN
F 2 "" H 9100 3450 50  0001 C CNN
F 3 "" H 9100 3450 50  0001 C CNN
	1    9100 3450
	1    0    0    -1  
$EndComp
$Comp
L Sensor_Motion:ADXL343 U?
U 1 1 5EAEAD5F
P 9100 5500
F 0 "U?" H 9644 5546 50  0000 L CNN
F 1 "ADXL343" H 9644 5455 50  0000 L CNN
F 2 "Package_LGA:LGA-14_3x5mm_P0.8mm_LayoutBorder1x6y" H 9100 5500 50  0001 C CNN
F 3 "https://www.analog.com/media/en/technical-documentation/data-sheets/ADXL343.pdf" H 9100 5500 50  0001 C CNN
	1    9100 5500
	1    0    0    -1  
$EndComp
Text GLabel 8400 5500 0    50   BiDi ~ 0
SDA
Wire Wire Line
	8400 5500 8600 5500
Text GLabel 8400 5600 0    50   BiDi ~ 0
SCL
Wire Wire Line
	8400 5600 8600 5600
$Comp
L power:+3.3V #PWR?
U 1 1 5EAEAD69
P 8300 5300
F 0 "#PWR?" H 8300 5150 50  0001 C CNN
F 1 "+3.3V" H 8315 5473 50  0000 C CNN
F 2 "" H 8300 5300 50  0001 C CNN
F 3 "" H 8300 5300 50  0001 C CNN
	1    8300 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	8600 5400 8300 5400
Wire Wire Line
	8300 5400 8300 5300
$Comp
L power:GND #PWR?
U 1 1 5EAEAD71
P 9100 6000
F 0 "#PWR?" H 9100 5750 50  0001 C CNN
F 1 "GND" H 9105 5827 50  0000 C CNN
F 2 "" H 9100 6000 50  0001 C CNN
F 3 "" H 9100 6000 50  0001 C CNN
	1    9100 6000
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5EAEAD77
P 9100 5000
F 0 "#PWR?" H 9100 4850 50  0001 C CNN
F 1 "+3.3V" H 9115 5173 50  0000 C CNN
F 2 "" H 9100 5000 50  0001 C CNN
F 3 "" H 9100 5000 50  0001 C CNN
	1    9100 5000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5EAF4803
P 9100 1500
F 0 "#PWR?" H 9100 1250 50  0001 C CNN
F 1 "GND" H 9105 1327 50  0000 C CNN
F 2 "" H 9100 1500 50  0001 C CNN
F 3 "" H 9100 1500 50  0001 C CNN
	1    9100 1500
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5EAF502E
P 8650 1150
F 0 "#PWR?" H 8650 1000 50  0001 C CNN
F 1 "+3.3V" H 8665 1323 50  0000 C CNN
F 2 "" H 8650 1150 50  0001 C CNN
F 3 "" H 8650 1150 50  0001 C CNN
	1    8650 1150
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5EAF571F
P 9550 1150
F 0 "#PWR?" H 9550 1000 50  0001 C CNN
F 1 "+3.3V" H 9565 1323 50  0000 C CNN
F 2 "" H 9550 1150 50  0001 C CNN
F 3 "" H 9550 1150 50  0001 C CNN
	1    9550 1150
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R?
U 1 1 5EAF5FD1
P 8650 1300
F 0 "R?" H 8582 1254 50  0000 R CNN
F 1 "10k" H 8582 1345 50  0000 R CNN
F 2 "" V 8690 1290 50  0001 C CNN
F 3 "~" H 8650 1300 50  0001 C CNN
	1    8650 1300
	1    0    0    1   
$EndComp
$Comp
L Device:R_US R?
U 1 1 5EAF6864
P 9550 1300
F 0 "R?" H 9618 1346 50  0000 L CNN
F 1 "10k" H 9618 1255 50  0000 L CNN
F 2 "" V 9590 1290 50  0001 C CNN
F 3 "~" H 9550 1300 50  0001 C CNN
	1    9550 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	8650 1450 8650 1500
Wire Wire Line
	8650 1500 9000 1500
Wire Wire Line
	9200 1500 9550 1500
Wire Wire Line
	9550 1500 9550 1450
$Comp
L Device:C C?
U 1 1 5EAF81A7
P 8650 1650
F 0 "C?" H 8765 1696 50  0000 L CNN
F 1 "C" H 8765 1605 50  0000 L CNN
F 2 "" H 8688 1500 50  0001 C CNN
F 3 "~" H 8650 1650 50  0001 C CNN
	1    8650 1650
	1    0    0    -1  
$EndComp
Connection ~ 8650 1500
$Comp
L Device:C C?
U 1 1 5EAF866A
P 9550 1650
F 0 "C?" H 9665 1696 50  0000 L CNN
F 1 "C" H 9665 1605 50  0000 L CNN
F 2 "" H 9588 1500 50  0001 C CNN
F 3 "~" H 9550 1650 50  0001 C CNN
	1    9550 1650
	1    0    0    -1  
$EndComp
Connection ~ 9550 1500
$Comp
L power:GND #PWR?
U 1 1 5EAF8D5B
P 8650 1800
F 0 "#PWR?" H 8650 1550 50  0001 C CNN
F 1 "GND" H 8655 1627 50  0000 C CNN
F 2 "" H 8650 1800 50  0001 C CNN
F 3 "" H 8650 1800 50  0001 C CNN
	1    8650 1800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5EAF90F4
P 9550 1800
F 0 "#PWR?" H 9550 1550 50  0001 C CNN
F 1 "GND" H 9555 1627 50  0000 C CNN
F 2 "" H 9550 1800 50  0001 C CNN
F 3 "" H 9550 1800 50  0001 C CNN
	1    9550 1800
	1    0    0    -1  
$EndComp
Text GLabel 8250 1500 0    50   Output ~ 0
ENC_A
Text GLabel 9950 1500 2    50   Output ~ 0
ENC_B
Wire Wire Line
	9950 1500 9550 1500
Wire Wire Line
	8250 1500 8650 1500
$Comp
L Device:C C?
U 1 1 5EB0C1B0
P 6100 1400
F 0 "C?" H 6215 1446 50  0000 L CNN
F 1 "C" H 6215 1355 50  0000 L CNN
F 2 "" H 6138 1250 50  0001 C CNN
F 3 "~" H 6100 1400 50  0001 C CNN
	1    6100 1400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5EB0C1B6
P 6100 1650
F 0 "#PWR?" H 6100 1400 50  0001 C CNN
F 1 "GND" H 6105 1477 50  0000 C CNN
F 2 "" H 6100 1650 50  0001 C CNN
F 3 "" H 6100 1650 50  0001 C CNN
	1    6100 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	6100 1550 6100 1650
Wire Wire Line
	6100 1150 6100 1250
$Comp
L power:+5V #PWR?
U 1 1 5EB0CBA6
P 6100 1150
F 0 "#PWR?" H 6100 1000 50  0001 C CNN
F 1 "+5V" H 6115 1323 50  0000 C CNN
F 2 "" H 6100 1150 50  0001 C CNN
F 3 "" H 6100 1150 50  0001 C CNN
	1    6100 1150
	1    0    0    -1  
$EndComp
$EndSCHEMATC
