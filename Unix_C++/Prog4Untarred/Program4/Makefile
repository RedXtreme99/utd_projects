#
# Filename	Makefile
# Date		3/28/2019
# Author	Basil Elhindi
# Email		bae170000@utdallas.edu
# Course	CS 3377.502 Spring 2019
# Version 	1.0
# Copyright 2019, All Rights Reserved
#
# Description
#   Makefile to build project and remove extraneous files and produce a tarball for submission.

CC = gcc
CPPFLAGS = 
CFLAGS = -Werror
LDFLAGS = 
LEX = /bin/flex
LFLAGS = 
YACC = /bin/bison
YFLAGS = -dy

SRCS = $(OBJS:.o=.c)
EXEC = program4 
OBJS = parse.o scan.o prog4.o
PROJNAME = Project4Backup

PHONY: clean backup


$(EXEC): $(OBJS)
	$(CXX) -o $(EXEC) $(LDFLAGS) $(OBJS)
	ln -s ./$(EXEC) scanner
	ln -s ./$(EXEC) parser

clean:
	rm -f $(OBJS) *.d* *~ $(EXEC) y.tab.h scan.c parse.c scanner parser

%.d:%.c
	@echo Updating .d Dependency File
	@set -e; rm -f $@; \
	$(CXX) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*, \1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

Makefile: $(SRCS:.c=.d)

backup: clean
	@mkdir -p ~/backups; chmod 700 ~/backups
	@$(eval CURDIRNAME := $(shell basename `pwd`))
	@$(eval MKBKUPNAME := ~/backups/$(PROJNAME)-$(shell date + '%Y.%m.%d-%H:%M:%S').tar.gz)
	@echo
	@echo Writing Backup file to: $(MKBKUPNAME)
	@echo
	@-tar zcfv $(MKBKUPNAME) ../$(CURDIRNAME)
	@chmod 600 $(MKBKUPNAME)
	@echo
	@echo Done!

-include $(SRCS:.c=.d)
