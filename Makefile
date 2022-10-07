SHELL    = /bin/sh
CC       = g++
CPPFLAGS = -O2 -std=c++17 -Wall -Wextra
RM       = rm -f

Sources    = src/tvop.cc
Executable = tvop

.PHONY: clean

$(Executable): $(Sources)
	$(CC) $(CPPFLAGS) -o $(Executable) $(Sources)

clean:
	$(RM) $(Executable)
