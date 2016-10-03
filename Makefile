CC = g++

CFLAGS = -Wall -std=c++11 -g

VPATH = \
          inc/prism \
          inc/prism/h \
          src/prism

INC = \
         -I inc \
         -I external

OBJS = \
          main.o \
          Bitvector.o \
          Char.o \
          Circle.o \
          Fraction.o \
          Mathf.o \
          Matrix4.o \
          Point.o \
          Pointf.o \
          Quaternion.o \
          Rect.o \
          SharedData.o \
          Size.o \
          String.o \
          Time.o \
          Vector2.o \
          Vector3.o \
          Vector4.o

HEADERS =\
         inc/prism/Allocator\
         inc/prism/Array \
         inc/prism/Bitvector\
         inc/prism/Circle \
         inc/prism/Char \
         inc/prism/Deque \
         inc/prism/Fraction \
         inc/prism/iterator \
         inc/prism/List \
         inc/prism/LogAllocator \
         inc/prism/Mathf\
         inc/prism/memory \
         inc/prism/OutOfBoundsException \
         inc/prism/Pair \
         inc/prism/Point \
         inc/prism/Pointf\
         inc/prism/Queue \
         inc/prism/Rect \
         inc/prism/SharedPointer \
         inc/prism/Size \
         inc/prism/Stack \
         inc/prism/String \
         inc/prism/Time \
         inc/prism/utilities \
         inc/prism/Vector

SOURCES = \
         main.cpp \
         Bitvector.cpp \
         Char.cpp \
         Circle.cpp \
         Fraction.cpp \
         Mathf.cpp \
         Matrix4.cpp \
         Point.cpp \
         Pointf.cpp \
         Quaternion.cpp \
         Rect.cpp \
         SharedData.cpp \
         Size.cpp \
         String.cpp \
         Time.cpp \
         Vector2.cpp \
         Vector3.cpp \
         Vector4.cpp

EXE = prism

default : $(EXE)

library : $(OBJS)
	g++ -dynamiclib -o libprism.so $(OBJS) -headerpad_max_install_names

documentation :
	doxygen Doxyfile

valgrind :
	valgrind --leak-check=full ./$(EXE)

#include $(SOURCES:.c=.d)

#%.d: %.c
#	@set -e; rm -f $@; \
	$(CC) -M $(CFLAGS) $< > $@.$$$$; \
	sed ’s,\($*\)\.o[ :]*,\1.o $@ : ,g’ < $@.$$$$ > $@; \
	rm -f $@.$$$$

$(EXE) : $(OBJS)
	@echo Building target: $@
	$(CC) -o $(EXE) $(OBJS)
	@echo Finished building target: $@
	@echo ''

main.o : main.cpp $(HEADERS)
	@echo Building file: main.cpp
	$(CC) $(CFLAGS) $(INC) -c main.cpp
	@echo Finished building file: main.cpp
	@echo ''

Bitvector.o : Bitvector.cpp Bitvector.h algorithms.h OutOfBoundsException.h UnequalSizeException.h OverflowException.h Char.h
	@echo Building file: src/prism/Bitvector.cpp
	$(CC) $(CFLAGS) $(INC) -c src/prism/Bitvector.cpp
	@echo Finished building file: src/prism/Bitvector.cpp
	@echo ''

Char.o : Char.cpp Char.h
	@echo Building file: src/prism/Char.cpp
	$(CC) $(CFLAGS) $(INC) -c src/prism/Char.cpp
	@echo Finished building file: src/prism/Char.cpp
	@echo ''

Circle.o : Circle.cpp Circle.h Pointf.h Mathf.h algorithms.h
	@echo Building file: src/prism/Circle.cpp
	$(CC) $(CFLAGS) $(INC) -c src/prism/Circle.cpp
	@echo Finished building file: src/prism/Circle.cpp
	@echo ''

Fraction.o : Fraction.cpp Fraction.h algorithms.h
	@echo Building file: src/prism/Fraction.cpp
	$(CC) $(CFLAGS) $(INC) -c src/prism/Fraction.cpp
	@echo Finished building file: src/prism/Fraction.cpp
	@echo ''

Mathf.o : Mathf.cpp Mathf.h
	@echo Building file: src/prism/Mathf.cpp
	$(CC) $(CFLAGS) $(INC) -c src/prism/Mathf.cpp
	@echo Finished building file: src/prism/Mathf.cpp
	@echo ''

Matrix4.o : Matrix4.cpp Matrix4.h Vector3.h Vector4.h Point.h Mathf.h
	@echo Building file: src/prism/Matrix4.cpp
	$(CC) $(CFLAGS) $(INC) -c src/prism/Matrix4.cpp
	@echo Finished building file: src/prism/Matrix4.cpp
	@echo ''

Point.o : Point.cpp Point.h
	@echo Building file: src/prism/Point.cpp
	$(CC) $(CFLAGS) $(INC) -c src/prism/Point.cpp
	@echo Finished building file: src/prism/Point.cpp
	@echo ''

Pointf.o : Pointf.cpp Pointf.h Point.h
	@echo Building file: src/prism/Pointf.cpp
	$(CC) $(CFLAGS) $(INC) -c src/prism/Pointf.cpp
	@echo Finished building file: src/prism/Pointf.cpp
	@echo ''

Quaternion.o : Quaternion.cpp Quaternion.h Vector3.h Vector4.h Matrix4.h Mathf.h
	@echo Building file: src/prism/Quaternion.cpp
	$(CC) $(CFLAGS) $(INC) -c src/prism/Quaternion.cpp
	@echo Finished building file: src/prism/Quaternion.cpp
	@echo ''

Rect.o : Rect.cpp Rect.h Size.h Point.h algorithms.h
	@echo Building file: src/prism/Rect.cpp
	$(CC) $(CFLAGS) $(INC) -c src/prism/Rect.cpp
	@echo Finished building file: src/prism/Rect.cpp
	@echo ''

SharedData.o : SharedData.cpp SharedData.h
	@echo Building file: src/prism/SharedData.cpp
	$(CC) $(CFLAGS) $(INC) -c src/prism/SharedData.cpp
	@echo Finished building file: src/prism/SharedData.cpp
	@echo ''

Size.o : Size.cpp Size.h
	@echo Building file: src/prism/Size.cpp
	$(CC) $(CFLAGS) $(INC) -c src/prism/Size.cpp
	@echo Finished building file: src/prism/Size.cpp
	@echo ''

String.o : String.cpp String.h Char.h algorithms.h OutOfBoundsException.h iterator.h List.h
	@echo Building file: src/prism/String.cpp
	$(CC) $(CFLAGS) $(INC) -c src/prism/String.cpp
	@echo Finished building file: src/prism/String.cpp
	@echo ''

Time.o : Time.cpp Time.h
	@echo Building file: src/prism/Time.cpp
	$(CC) $(CFLAGS) $(INC) -c src/prism/Time.cpp
	@echo Finished building file: src/prism/Time.cpp
	@echo ''

Vector2.o : Vector2.cpp Vector2.h Vector3.h Vector4.h Point.h
	@echo Building file: src/prism/Vector2.cpp
	$(CC) $(CFLAGS) $(INC) -c src/prism/Vector2.cpp
	@echo Finished building file: src/prism/Vector2.cpp
	@echo ''

Vector3.o : Vector3.cpp Vector3.h Vector2.h Vector4.h Point.h
	@echo Building file: src/prism/Vector3.cpp
	$(CC) $(CFLAGS) $(INC) -c src/prism/Vector3.cpp
	@echo Finished building file: src/prism/Vector3.cpp
	@echo ''

Vector4.o : Vector4.cpp Vector4.h Vector2.h Vector3.h Point.h
	@echo Building file: src/prism/Vector4.cpp
	$(CC) $(CFLAGS) $(INC) -c src/prism/Vector4.cpp
	@echo Finished building file: src/prism/Vector4.cpp
	@echo ''

clean :
	rm -rf $(OBJS) $(EXE) libprism.so
