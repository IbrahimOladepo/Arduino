EESchema Schematic File Version 4
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
L COM-09032:COM-09032 U1
U 1 1 5F1DB2A4
P 4000 2210
F 0 "U1" H 3893 1343 50  0000 C CNN
F 1 "LEFT JOYSTICK" H 3893 1434 50  0000 C CNN
F 2 "COM-09032:XDCR_COM-09032" H 4000 2210 50  0001 L BNN
F 3 "N/A" H 4000 2210 50  0001 L BNN
F 4 "SparkFun Electronics" H 4000 2210 50  0001 L BNN "Field4"
F 5 "Manufacturer Recommendations" H 4000 2210 50  0001 L BNN "Field5"
F 6 "30.1mm" H 4000 2210 50  0001 L BNN "Field6"
	1    4000 2210
	-1   0    0    1   
$EndComp
$Comp
L COM-09032:COM-09032 U2
U 1 1 5F1DD198
P 5600 2210
F 0 "U2" H 5493 1343 50  0000 C CNN
F 1 "RIGHT JOYSTICK" H 5493 1434 50  0000 C CNN
F 2 "COM-09032:XDCR_COM-09032" H 5600 2210 50  0001 L BNN
F 3 "N/A" H 5600 2210 50  0001 L BNN
F 4 "SparkFun Electronics" H 5600 2210 50  0001 L BNN "Field4"
F 5 "Manufacturer Recommendations" H 5600 2210 50  0001 L BNN "Field5"
F 6 "30.1mm" H 5600 2210 50  0001 L BNN "Field6"
	1    5600 2210
	-1   0    0    1   
$EndComp
$Comp
L RF:NRF24L01_Breakout U3
U 1 1 5F1E5B97
P 4050 4520
F 0 "U3" H 4429 4474 50  0000 L CNN
F 1 "NRF24L01_Breakout" H 4429 4565 50  0000 L CNN
F 2 "RF_Module:nRF24L01_Breakout" H 4200 5120 50  0001 L CIN
F 3 "http://www.nordicsemi.com/eng/content/download/2730/34105/file/nRF24L01_Product_Specification_v2_0.pdf" H 4050 4420 50  0001 C CNN
	1    4050 4520
	-1   0    0    1   
$EndComp
$Comp
L MCU_Module:Arduino_Nano_v2.x A1
U 1 1 5F1EAF4A
P 6530 4650
F 0 "A1" H 6530 3561 50  0000 C CNN
F 1 "Arduino NANO v2.x" H 6530 3470 50  0000 C CNN
F 2 "Module:Arduino_Nano" H 6530 4650 50  0001 C CIN
F 3 "https://www.arduino.cc/en/uploads/Main/ArduinoNanoManual23.pdf" H 6530 4650 50  0001 C CNN
	1    6530 4650
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Female J1
U 1 1 5F1EE47F
P 6900 1940
F 0 "J1" H 6792 1615 50  0000 C CNN
F 1 "POWER" H 6792 1706 50  0000 C CNN
F 2 "Connector_PinHeader_1.00mm:PinHeader_1x02_P1.00mm_Vertical" H 6900 1940 50  0001 C CNN
F 3 "~" H 6900 1940 50  0001 C CNN
	1    6900 1940
	-1   0    0    1   
$EndComp
$Comp
L power:+BATT #PWR010
U 1 1 5F1EF0DA
P 7290 1720
F 0 "#PWR010" H 7290 1570 50  0001 C CNN
F 1 "+BATT" H 7305 1893 50  0000 C CNN
F 2 "" H 7290 1720 50  0001 C CNN
F 3 "" H 7290 1720 50  0001 C CNN
	1    7290 1720
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR011
U 1 1 5F1EF85D
P 7290 2070
F 0 "#PWR011" H 7290 1820 50  0001 C CNN
F 1 "GND" H 7295 1897 50  0000 C CNN
F 2 "" H 7290 2070 50  0001 C CNN
F 3 "" H 7290 2070 50  0001 C CNN
	1    7290 2070
	1    0    0    -1  
$EndComp
Wire Wire Line
	7290 1720 7290 1840
Wire Wire Line
	7290 1840 7100 1840
Wire Wire Line
	7100 1940 7290 1940
Wire Wire Line
	7290 1940 7290 2070
$Comp
L power:+5V #PWR09
U 1 1 5F1F174C
P 6730 3510
F 0 "#PWR09" H 6730 3360 50  0001 C CNN
F 1 "+5V" H 6745 3683 50  0000 C CNN
F 2 "" H 6730 3510 50  0001 C CNN
F 3 "" H 6730 3510 50  0001 C CNN
	1    6730 3510
	1    0    0    -1  
$EndComp
Wire Wire Line
	6730 3510 6730 3650
$Comp
L power:+5V #PWR03
U 1 1 5F1F2B8F
P 4670 1810
F 0 "#PWR03" H 4670 1660 50  0001 C CNN
F 1 "+5V" H 4685 1983 50  0000 C CNN
F 2 "" H 4670 1810 50  0001 C CNN
F 3 "" H 4670 1810 50  0001 C CNN
	1    4670 1810
	1    0    0    -1  
$EndComp
Wire Wire Line
	4500 1810 4670 1810
Wire Wire Line
	4500 2610 4670 2610
Connection ~ 4670 1810
Wire Wire Line
	4500 2210 4670 2210
Wire Wire Line
	4670 1810 4670 2210
Connection ~ 4670 2210
Wire Wire Line
	4670 2210 4670 2610
$Comp
L power:GND #PWR04
U 1 1 5F1F3F84
P 4800 2510
F 0 "#PWR04" H 4800 2260 50  0001 C CNN
F 1 "GND" H 4805 2337 50  0000 C CNN
F 2 "" H 4800 2510 50  0001 C CNN
F 3 "" H 4800 2510 50  0001 C CNN
	1    4800 2510
	1    0    0    -1  
$EndComp
Wire Wire Line
	4500 2510 4800 2510
Wire Wire Line
	4500 2110 4800 2110
Wire Wire Line
	4800 2110 4800 2510
Connection ~ 4800 2510
$Comp
L power:+5V #PWR05
U 1 1 5F1F53B4
P 6200 1810
F 0 "#PWR05" H 6200 1660 50  0001 C CNN
F 1 "+5V" H 6215 1983 50  0000 C CNN
F 2 "" H 6200 1810 50  0001 C CNN
F 3 "" H 6200 1810 50  0001 C CNN
	1    6200 1810
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR06
U 1 1 5F1F5F45
P 6300 2510
F 0 "#PWR06" H 6300 2260 50  0001 C CNN
F 1 "GND" H 6305 2337 50  0000 C CNN
F 2 "" H 6300 2510 50  0001 C CNN
F 3 "" H 6300 2510 50  0001 C CNN
	1    6300 2510
	1    0    0    -1  
$EndComp
Wire Wire Line
	6100 1810 6200 1810
Wire Wire Line
	6100 2210 6200 2210
Wire Wire Line
	6200 2210 6200 1810
Connection ~ 6200 1810
Wire Wire Line
	6100 2610 6200 2610
Wire Wire Line
	6200 2610 6200 2210
Connection ~ 6200 2210
Wire Wire Line
	6300 2510 6100 2510
Wire Wire Line
	6100 2110 6300 2110
Wire Wire Line
	6300 2110 6300 2510
Connection ~ 6300 2510
Wire Wire Line
	6100 1610 6300 1610
Wire Wire Line
	6300 1610 6300 2110
Connection ~ 6300 2110
Wire Wire Line
	4500 1610 4800 1610
Wire Wire Line
	4800 1610 4800 2110
Connection ~ 4800 2110
Text GLabel 4890 1910 2    50   Input ~ 0
BTNL
Text GLabel 6400 1910 2    50   Input ~ 0
BTNR
Text GLabel 5880 4350 0    50   Input ~ 0
BTNL
Text GLabel 5880 4250 0    50   Input ~ 0
BTNR
Wire Wire Line
	5880 4250 6030 4250
Wire Wire Line
	6030 4350 5880 4350
Wire Wire Line
	4890 1910 4500 1910
Wire Wire Line
	6400 1910 6100 1910
Text GLabel 4900 2710 2    50   Input ~ 0
LY
Text GLabel 4900 2310 2    50   Input ~ 0
LX
Wire Wire Line
	4900 2310 4500 2310
Wire Wire Line
	4500 2710 4900 2710
Text GLabel 6410 2310 2    50   Input ~ 0
RX
Text GLabel 6400 2710 2    50   Input ~ 0
RY
Wire Wire Line
	6100 2310 6410 2310
Wire Wire Line
	6400 2710 6100 2710
Text GLabel 7200 4850 2    50   Input ~ 0
RY
Text GLabel 7200 4950 2    50   Input ~ 0
RX
Wire Wire Line
	7030 4850 7200 4850
Wire Wire Line
	7200 4950 7030 4950
Text GLabel 7200 4650 2    50   Input ~ 0
LY
Text GLabel 7200 4750 2    50   Input ~ 0
LX
Wire Wire Line
	7200 4650 7030 4650
Wire Wire Line
	7030 4750 7200 4750
$Comp
L power:GND #PWR08
U 1 1 5F1FF945
P 6630 5710
F 0 "#PWR08" H 6630 5460 50  0001 C CNN
F 1 "GND" H 6635 5537 50  0000 C CNN
F 2 "" H 6630 5710 50  0001 C CNN
F 3 "" H 6630 5710 50  0001 C CNN
	1    6630 5710
	1    0    0    -1  
$EndComp
Wire Wire Line
	6630 5650 6630 5710
Wire Wire Line
	6530 5650 6530 5710
Wire Wire Line
	6530 5710 6630 5710
Connection ~ 6630 5710
$Comp
L power:+3.3V #PWR07
U 1 1 5F201433
P 6630 3510
F 0 "#PWR07" H 6630 3360 50  0001 C CNN
F 1 "+3.3V" H 6645 3683 50  0000 C CNN
F 2 "" H 6630 3510 50  0001 C CNN
F 3 "" H 6630 3510 50  0001 C CNN
	1    6630 3510
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR02
U 1 1 5F202168
P 4050 5210
F 0 "#PWR02" H 4050 5060 50  0001 C CNN
F 1 "+3.3V" H 4065 5383 50  0000 C CNN
F 2 "" H 4050 5210 50  0001 C CNN
F 3 "" H 4050 5210 50  0001 C CNN
	1    4050 5210
	-1   0    0    1   
$EndComp
Wire Wire Line
	4050 5120 4050 5210
Wire Wire Line
	6630 3510 6630 3650
$Comp
L power:GND #PWR01
U 1 1 5F204541
P 4050 3740
F 0 "#PWR01" H 4050 3490 50  0001 C CNN
F 1 "GND" H 4055 3567 50  0000 C CNN
F 2 "" H 4050 3740 50  0001 C CNN
F 3 "" H 4050 3740 50  0001 C CNN
	1    4050 3740
	-1   0    0    1   
$EndComp
Wire Wire Line
	4050 3740 4050 3920
Wire Wire Line
	4550 4720 5500 4720
Wire Wire Line
	5500 4720 5500 5250
Wire Wire Line
	5500 5250 6030 5250
Wire Wire Line
	5400 4820 4550 4820
Wire Wire Line
	6030 5150 5400 5150
Wire Wire Line
	5400 5150 5400 4820
Wire Wire Line
	4550 4620 5610 4620
Wire Wire Line
	5610 4620 5610 5350
Wire Wire Line
	5610 5350 6030 5350
Wire Wire Line
	4550 4520 5720 4520
Wire Wire Line
	5720 4520 5720 5050
Wire Wire Line
	5720 5050 6030 5050
Wire Wire Line
	4550 4320 5290 4320
Wire Wire Line
	5290 4320 5290 4950
Wire Wire Line
	5290 4950 6030 4950
$Comp
L power:+BATT #PWR0101
U 1 1 5F20F714
P 6430 3510
F 0 "#PWR0101" H 6430 3360 50  0001 C CNN
F 1 "+BATT" H 6445 3683 50  0000 C CNN
F 2 "" H 6430 3510 50  0001 C CNN
F 3 "" H 6430 3510 50  0001 C CNN
	1    6430 3510
	1    0    0    -1  
$EndComp
Wire Wire Line
	6430 3510 6430 3650
$EndSCHEMATC
