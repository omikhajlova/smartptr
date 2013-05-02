objects = main.o

CC = g++
CXX = g++

main: $(objects) tholder.h checking_policy.h delete_policy.h smartptr.h ref_counted.h

.PHONY: clean
clean:
	rm main $(objects)

