BINDIR:=./bin
SRCDIR:=./src
HEADDIR:=./include
SOURCE:=$(wildcard $(SRCDIR)/*.cpp)
CC:=clang++
CFLAGS:=-g -std=c++11 -o 
OBJS:=$(addsuffix .o,$(addprefix $(BINDIR),$(basename $(subst $(SRCDIR),,$(SOURCE)))))
all:$(OBJS)
	$(CC) $(CFLAGS) $(BINDIR)/main $(OBJS) -I $(HEADDIR)
$(OBJS):$(BINDIR)/%.o:$(SRCDIR)/%.cpp
	$(CC) -c $(CFLAGS) $@ $< -I $(HEADDIR)
.PHONY:clean
clean:
	$(RM) $(BINDIR)/main $(OBJS)

