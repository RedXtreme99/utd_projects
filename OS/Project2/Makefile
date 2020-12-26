PROJPATH = $(PWD)

JCC = javac
JFLAGS = -g 

SRCS = Proc1.java Proc2.java Proc3.java Proc4.java
EXEC = Proc1.class Proc2.class Proc3.class Proc4.class

all : $(EXEC)

Proc1.class : Proc1.java
	$(JCC) $(JFLAGS) Proc1.java

Proc2.class : Proc2.java
	$(JCC) $(JFLAGS) Proc2.java

Proc3.class : Proc3.java
	$(JCC) $(JFLAGS) Proc3.java

Proc4.class : Proc4.java
	$(JCC) $(JFLAGS) Proc4.java

clean : 
	rm -f *.class
