objects = main.o

CC = g++
CXX = g++

main: $(objects) testobj.h tholder.h checking_policy.h delete_policy.h tintrusive.h ref_counted.h

.PHONY: clean
clean:
	rm main $(objects)

