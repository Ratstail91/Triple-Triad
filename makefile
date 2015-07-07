#Windows 7:
#RM=del /y

#Windows 8.1:
#RM=del /S

OUTDIR=out
OUT=$(addprefix $(OUTDIR)/,tt)

all: $(OUTDIR)
	$(MAKE) -C src

$(OUTDIR):
	mkdir $(OUTDIR)

clean:
ifeq ($(OS),Windows_NT)
	$(RM) *.o *.a *.exe
else ifeq ($(shell uname), Linux)
	find . -type f -name '*.o' -exec rm -f -r -v {} \;
	find . -type f -name '*.a' -exec rm -f -r -v {} \;
	rm -f -v $(OUT)
endif

rebuild: clean all
