CC = gcc
GD = gcc -ansi -pedantic-errors -Wall -Wextra -g

#pathes
INCLUDE_PATH = ~/git/dani-benjamin/ds/include/
LIB_PATH = ~/git/dani-benjamin/ds/lib/
BIN_PATH = ~/git/dani-benjamin/ds/test/

FILES_C = $(wildcard *.c)
SRCS := $(filter-out $(wildcard *_test.c), $(FILES_C))

#test
TESTFILES_C := $(wildcard *_test.c)
TESTFILES_O := $(TESTFILES:%.c=%.o)
OUTFILES := $(TESTFILES_C:%_test.c=%.out)

#all
HFILES := $(wildcard *.h)
OFILES := $(SRCS:%.c=%.o)

#libs
AFILES := $(wildcard *.a)

#release
OFILES_RELEASE := $(SRCS:%.c=%_release.o)
 

# ======== release ========
.PHONY : release
release : $(OFILES_RELEASE)

%_release.o: %.c %.h
	@echo "Creating object for release.."
	@${CC} -c -O -DNDEBUG $< -o $@
	@ar rcs libds_release.a $@

# ======================

# ======== test ======== 
.PHONY : test
test: all $(OUTFILES)

%.d : %.c
	@${CC} -MM $*.c > $@
-include $(FILES_C:.c=.d)

%.out : %_test.o
	@${GD} -o $@ $*_test.o libds.a -lm
	@ln -sf $(addprefix $(PWD)/,$(OUTFILES)) $(BIN_PATH)

# ======================

# ======== all ========
all : $(OFILES) libds.a
	@echo "all"

libds.a : $(OFILES)
	@ar rcs libds.a $?
	
# ======================

.PHONY : Include
Include : $(HFILES)
	@ln -sf $(addprefix $(PWD)/,$(HFILES)) $(INCLUDE_PATH)
	@echo "include was made"


.PHONY : libs
libs : $(AFILES)
	@ln -sf $(addprefix $(PWD)/,$(AFILES)) $(LIB_PATH) 
	@echo "libs was made"


.PHONY : clean
clean :
	rm -f *.a *.out *.d *.o $(INCLUDE_PATH)*.h $(LIB_PATH)*.a $(BIN_PATH)*.out0