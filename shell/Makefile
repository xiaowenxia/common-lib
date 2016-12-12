CROSS_PREFIX	?= 

CC	= $(CROSS_PREFIX)gcc
CXX	= $(CROSS_PREFIX)g++
LD	= $(CROSS_PREFIX)ld
AR	= $(CROSS_PREFIX)ar

NAME        = shell
LIBNAME		= lib$(NAME)
LIB_A       = $(LIBNAME).a
LIB_SO      = $(LIBNAME).so
LIB_TEST    = $(NAME)_test.c

TARGET      := $(LIB_A)
TARGET      += $(LIB_SO)
TARGET      += $(NAME)_test

OBJ_LIB     = $(LIBNAME).o
OBJ_TEST    = $(NAME)_test.o

OBJS        = $(OBJ_LIB) $(OBJ_TEST)

###############################################################################
# cflags and ldflags
###############################################################################
CFLAGS	:= -g -Wall -Werror -fPIC
CFLAGS	+= $($(ARCH)_CFLAGS)

LDFLAGS	:= $($(ARCH)_LDFLAGS)
LDFLAGS	+= -pthread

###############################################################################
# target
###############################################################################
.PHONY : all clean

all: $(TARGET)

$(LIBNAME).o:$(NAME).c
	$(CC) -c $(CFLAGS) $< -o $@

$(NAME)_test.o: $(NAME)_test.c
	$(CC) -c $(CFLAGS) $< -o $@

$(LIB_A): $(OBJ_LIB)
	$(AR) rcs $@ $^

$(LIB_SO): $(OBJ_LIB)
	$(LD) -o $@ $^ -shared

$(NAME)_test: $(OBJ_TEST)
	$(CC) -o $@ $^ $(LIB_A) $(LDFLAGS)

clean:
	-rm -f $(OBJS)
	-rm -f $(TARGET)