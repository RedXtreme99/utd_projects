PROJPATH = /home/osc/Project1

OBJS = main.o
SRCS = $(OBJS:.o=.c)
LDLIBS = 
EXEC = program1

CXX = gcc
CXXFLAGS = -c -Wall
CPPFLAGS = -I$(PROJPATH)
LDFLAGS = 

$(EXEC):$(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS)

clean: 
	rm -f $(OBJS) $(EXEC) .*.swp \
	$(PROJPATH)/dir1/FileE $(PROJPATH)/dir1/FileF $(PROJPATH)/dir1/FileG \
	$(PROJPATH)/dir2/FileA $(PROJPATH)/dir2/FileC $(PROJPATH)/dir2/FileD
