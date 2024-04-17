LIB = -lm -lpigpio -lrt -lpthread -lc # library chosen for the implementation of PCA9685 
OBJS_O = MotorDriver.o main.o
CC = gcc

MotorProgram: $(OBJS_O)
	$(CC) $(OBJS_O) -o MotorProgram $(LIB)

clean:
	sudo rm -f *.o
	sudo rm -f MotorProgram
	sudo killall pigpiod

run: 
	sudo ./MotorProgram