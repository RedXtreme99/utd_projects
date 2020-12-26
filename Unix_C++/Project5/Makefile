CXX = g++
CPPFLAGS = -I/home/011/b/ba/bae170000/include
CXXFLAGS = -Wall -std=c++11
LDFLAGS = -L/home/011/b/ba/bae170000/lib -static
LDLIBS = -lrudeconfig

PROJECTNAME = Project5DirectMonitor

OBJS = cmdlineparser.o rudeconfig.o signalhandler.o popen.o inotifyuse.o program5.o
SRCS = $(OBJS:.o=.cc)
EXEC = program5

$(EXEC):$(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS)

clean:
	rm -f $(OBJS) *.d *~

%.d:%.cc
	@echo Updating .d Dependency File
	@set -e; rm -f $@; \
	$(CXX) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

Makfile: $(SRCS:.cc=.d)

backup: clean
	@mkdir -p ~/backups; chmod 700 ~/backups
	@$(eval CURDINAME := $(shell basename `pwd`))
	@$(eval MKBKUPNAME := ~/backups/$(PROJECTNAME)-$(shell date + '%Y.%m.%d-%H:%M:%S').tar.gz)
	@echo
	@echo Writing Backup file to: $(MKBKUPNAME)
	@echo
	@-tar zcfv $(MKBKUPNAME) ../$(CURDIRNAME)
	@chmod 600 ($(MKBKUPNAME)
	@echo
	@echo Done!

-include $(SRCS:.cc=.d)
