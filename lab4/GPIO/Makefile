ServoSpeed: ServoSpeed.o GPIO.o
	g++ ServoSpeed.o GPIO.o -o ServoSpeed

ServoSpeed.o: ServoSpeed.cc GPIO.h
	g++ -c ServoSpeed.cc

GPIO.o: GPIO.cc GPIO.h
	g++ -c GPIO.cc

clean:
	rm *.o ServoSpeed
