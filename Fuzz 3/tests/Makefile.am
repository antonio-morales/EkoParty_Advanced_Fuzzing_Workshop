# executable test scripts to perform
TESTS = test_html.sh test_latex.sh test_text.sh

# the data set for the tests
testdata = \
	accents.rtf \
	ascii_decimal.rtf \
	backslash.rtf \
	body.rtf \
	borders_shading.rtf \
	braces.rtf \
	character_formatting.rtf \
	chars.rtf \
	columns.rtf \
	cp1251-russian-alphabet.rtf \
	emfpict.rtf \
	EndNote.rtf \
	font_size.rtf \
	font_styles.rtf \
	Greek1.rtf \
	Greek2.rtf \
	left-double-quotes.rtf \
	lists.rtf \
	opensymbols.rtf \
	paragraph_formatting.rtf \
	pict.rtf \
	pictNotIgnored.rtf \
	quotes.rtf \
	symbol.rtf \
	text_color.rtf \
	text_formatting.rtf \
	Turkish.rtf \
	unicode4.rtf \
	unnested.rtf

# the result set for the html test
testresults_html = \
	accents.rtf.html \
	ascii_decimal.rtf.html \
        backslash.rtf.html \
	body.rtf.html \
        borders_shading.rtf.html \
        braces.rtf.html \
        character_formatting.rtf.html \
        chars.rtf.html \
        columns.rtf.html \
	cp1251-russian-alphabet.rtf.html \
	emfpict.rtf.html \
	EndNote.rtf.html \
        font_size.rtf.html \
        font_styles.rtf.html \
	Greek1.rtf.html \
	Greek2.rtf.html  \
	left-double-quotes.rtf.html \
        lists.rtf.html \
	opensymbols.rtf.html \
        paragraph_formatting.rtf.html \
	pict.rtf.html \
	pictNotIgnored.rtf.html \
	quotes.rtf.html \
        symbol.rtf.html \
        text_color.rtf.html \
        text_formatting.rtf.html \
	Turkish.rtf.html \
        unicode4.rtf.html \
	unnested.rtf.html

# the result set for the latex test
testresults_tex = \
	accents.rtf.tex \
	ascii_decimal.rtf.tex \
        backslash.rtf.tex \
	body.rtf.tex \
        borders_shading.rtf.tex \
        braces.rtf.tex \
        character_formatting.rtf.tex \
        chars.rtf.tex \
        columns.rtf.tex \
	cp1251-russian-alphabet.rtf.tex \
	emfpict.rtf.tex \
	EndNote.rtf.tex \
        font_size.rtf.tex \
        font_styles.rtf.tex \
	Greek1.rtf.tex \
	Greek2.rtf.tex  \
	left-double-quotes.rtf.tex \
        lists.rtf.tex \
	pictNotIgnored.rtf.tex \
	opensymbols.rtf.tex \
        paragraph_formatting.rtf.tex \
	pict.rtf.tex \
	quotes.rtf.tex \
        symbol.rtf.tex \
        text_color.rtf.tex \
        text_formatting.rtf.tex \
	Turkish.rtf.tex \
        unicode4.rtf.tex \
	unnested.rtf.tex

# the result set for the text test
testresults_text = \
	accents.rtf.text \
	ascii_decimal.rtf.text \
        backslash.rtf.text \
	body.rtf.text \
        borders_shading.rtf.text \
        braces.rtf.text \
        character_formatting.rtf.text \
        chars.rtf.text \
        columns.rtf.text \
	cp1251-russian-alphabet.rtf.text \
	emfpict.rtf.text \
	EndNote.rtf.text \
        font_size.rtf.text \
        font_styles.rtf.text \
	Greek1.rtf.text \
	Greek2.rtf.text  \
	left-double-quotes.rtf.text \
        lists.rtf.text \
	opensymbols.rtf.text \
        paragraph_formatting.rtf.text \
	pict.rtf.text \
	pictNotIgnored.rtf.text \
	quotes.rtf.text \
        symbol.rtf.text \
        text_color.rtf.text \
        text_formatting.rtf.text \
	Turkish.rtf.text \
        unicode4.rtf.text \
	unnested.rtf.text


# need to wipe out test results on make clean
CLEANFILES = $(testresults_html) $(testresults_tex) $(testresults_text) pict0*.*

# add the test scripts and the test data to the distributed files
EXTRA_DIST = $(TESTS) $(testdata)

TESTS_ENVIRONMENT = UNRTF=$(top_builddir)/src/unrtf UNRTF_SEARCH_PATH=$(top_builddir)/outputs/

# ensure that the distributed scripts are executable before distribution.
# Could be necessary if checking out CVS.
dist-hook:
	cd $(distdir); for i in $(TESTS); do chmod +x $$i; done
