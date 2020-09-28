dist_man1_MANS = unrtf.1

EXTRA_DIST = unrtf.1.in

unrtf.1: unrtf.1.in Makefile
	sed -e 's!@DATADIR@!${datarootdir}/unrtf!g' < ${srcdir}/unrtf.1.in > unrtf.1

clean-local:
	rm -f unrtf.1
