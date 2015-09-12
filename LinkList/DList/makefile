CC:=clang++
CFLAGS:=-g -std=c++11 -o
BINDIR:=./bin
SRCDIR:=./src
HEADDIR:=./include
SOURCE:=$(wildcard $(SRCDIR)/*.cpp)
OBJS:=$(addprefix $(BINDIR),$(addsuffix .o,$(basename $(subst $(SRCDIR),,$(SOURCE)))))
all:$(OBJS)
	$(CC) $(CFLAGS) $(BINDIR)/main $(OBJS) -I $(HEADDIR)
$(OBJS):$(BINDIR)/%.o:$(SRCDIR)/%.cpp
	$(CC) -c $(CFLAGS) $@ $< -I $(HEADDIR)
.PHONY:clean
clean:
	$(RM) -rf $(BINDIR)/main $(OBJS)
