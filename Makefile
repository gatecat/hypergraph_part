all: hypergraph_test

SRC = $(wildcard *.cc)
OBJS = $(patsubst %.cc,%.o,$(SRC))

include $(SRC:.cc=.d)

LD = $(CXX)
CXXFLAGS += -Icore -I. -fPIC -Wall -MD -g -std=c++14 -O1
LDFLAGS ?=
LDLIBS := $(LDLIBS) -lstdc++ -lm

%.d : %.cc
	$(MAKEDEPEND)

%.o: %.cc
	$(CXX) -o $@ -c $(CPPFLAGS) $(CXXFLAGS) $<

hypergraph_test: $(OBJS)
	$(CXX) -o $@ $(LDFLAGS) $^ $(LDLIBS)

clean:
	rm $(OBJS) hypergraph_test
