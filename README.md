# LED-Matrix-Control

## Raspberry Pi Wiring
<img src="./img/1.png" width=800>
<img src="./img/2.png" width=800>

```
R1=14       G1=15
B1=23       GND
R2=24       G2=25
B2=8        GND
A=7         B=16
C=4         D=<No Connect>
CLK=22      LAT=9
OE=6
```

## Use
```sh
~/Hi-Class/Cpp $ ./run.sh
```

## Customize Pin Number
```sh
~/Hi-Class/Cpp/src $ nano hardware-mapping.cc

line 217~236
Change Pin Number
```

## Reference
[rpi-rgb-led-matrix](https://github.com/hzeller/rpi-rgb-led-matrix)