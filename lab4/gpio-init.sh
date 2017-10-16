#!/bin/bash

gpiopath='/sys/class/gpio'
echo 13 > $gpiopath/unexport 2>/dev/null
echo 10 > $gpiopath/unexport 2>/dev/null
echo 11 > $gpiopath/unexport 2>/dev/null
echo 12 > $gpiopath/unexport 2>/dev/null
echo 0 > $gpiopath/unexport 2>/dev/null
echo 13 > $gpiopath/export
echo 10 > $gpiopath/export
echo 11 > $gpiopath/export
echo 12 > $gpiopath/export
echo 0 > $gpiopath/export
echo out > $gpiopath/gpio13/direction
echo out > $gpiopath/gpio10/direction
echo out > $gpiopath/gpio11/direction
echo out > $gpiopath/gpio12/direction
echo out > $gpiopath/gpio0/direction
