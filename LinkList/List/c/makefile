BINDIR:=./bin
SRCDIR:=./src
HEADDIR:=./include
CC:=clang
CFLAGS:=-g -std=c99 -o
SOURCE:=$(wildcard $(SRCDIR)/*.c)
OBJS:=$(addsuffix .o,$(addprefix $(BINDIR),$(basename $(subst $(SRCDIR),,$(SOURCE)))))
all:$(OBJS)
	$(CC) $(CFLAGS) $(BINDIR)/main $(OBJS) -I $(HEADDIR)
$(OBJS):$(BINDIR)/%.o:$(SRCDIR)/%.c
	$(CC) -c $(CFLAGS) $@ $< -I $(HEADDIR)
.PHONY:clean
clean:
	$(RM) $(BINDIR)/main $(OBJS)
