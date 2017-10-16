MultiSpeed: MultiSpeed.o GPIO.o
	g++ MultiSpeed.o GPIO.o -o MultiSpeed

MultiSpeed.o: MultiSpeed.cc GPIO.h
	g++ -c MultiSpeed.cc

GPIO.o: GPIO.cc GPIO.h
	g++ -c GPIO.cc

clean:
	rm *.o MultiSpeed
