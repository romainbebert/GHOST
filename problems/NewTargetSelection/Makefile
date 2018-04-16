EXEC=target

#CXX=clang++
CXX=g++

# Directories
SRCDIR=src
OBJDIR=obj
BINDIR=bin


# Compiler flags
CXXFIRSTFLAGS= -Ofast -DNDEBUG -W -Wall -Wextra -pedantic -Wno-sign-compare -Wno-unused-parameter
CXXFIRSTFLAGSDEBUG= -g -O0 -W -Wall -Wextra -pedantic -Wno-sign-compare -Wno-unused-parameter 

# Linker flags
LDFLAGS=-pthread -lghost

# Compiler
ifneq (,$(findstring clang,$(CXX)))
	CXXFLAGS= -std=c++1y  -stdlib=libc++ $(CXXFIRSTFLAGS)
	CXXFLAGSDEBUG= -std=c++1y  -stdlib=libc++ $(CXXFIRSTFLAGSDEBUG)
	LDFLAGS=-pthread -lghost -lc++ -lc++abi
else
	CXXFLAGS= -std=c++14 $(CXXFIRSTFLAGS)
	CXXFLAGSDEBUG= -std=c++14 $(CXXFIRSTFLAGSDEBUG)
endif

# Files
SOURCES=$(foreach sdir, $(SRCDIR), $(wildcard $(sdir)/*.cpp))
OBJECTS=$(patsubst %.cpp, $(OBJDIR)/%.o, $(notdir $(SOURCES)))

# For rm
SOURCESTILDE=$(foreach sdir, $(SRCDIR), $(wildcard $(sdir)/*.cpp~))

vpath %.cpp $(SRCDIR)

# Reminder, 'cause it is easy to forget makefile's fucked-up syntax...
# $@ is what triggered the rule, ie the target before :
# $^ is the whole dependencies list, ie everything after :
# $< is the first item in the dependencies list

# Rules
all: $(BINDIR)/$(EXEC)

debug: CXXFLAGS= $(CXXFLAGSDEBUG)
debug: $(BINDIR)/$(EXEC)

$(BINDIR)/$(EXEC): $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean 

clean:
	rm -fr core *~ $(EXEC) $(OBJECTS) $(SOURCESTILDE)
