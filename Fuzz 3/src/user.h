#ifndef _USER_H_INCLUDED_
#define _USER_H_INCLUDED_


#define BUFFER_SIZE 30
#define STANDARD_BUFFER_LENGTH 16

#define DEFS_ARRAY_ENTRY(field, op)\
	{#field, &(op->field)}

#define DEFS_ARRAY(op) \
{\
	DEFS_ARRAY_ENTRY(comment_begin, op),\
	DEFS_ARRAY_ENTRY(comment_end, op),\
	DEFS_ARRAY_ENTRY(document_begin, op),\
	DEFS_ARRAY_ENTRY(document_end, op),\
	DEFS_ARRAY_ENTRY(header_begin, op),\
	DEFS_ARRAY_ENTRY(header_end, op),\
	DEFS_ARRAY_ENTRY(document_title_begin, op),\
	DEFS_ARRAY_ENTRY(document_title_end, op),\
	DEFS_ARRAY_ENTRY(document_keywords_begin, op),\
	DEFS_ARRAY_ENTRY(document_keywords_end, op),\
	DEFS_ARRAY_ENTRY(document_author_begin, op),\
	DEFS_ARRAY_ENTRY(document_author_end, op),\
	DEFS_ARRAY_ENTRY(document_changedate_begin, op),\
	DEFS_ARRAY_ENTRY(document_changedate_end, op),\
	DEFS_ARRAY_ENTRY(body_begin, op),\
	DEFS_ARRAY_ENTRY(body_end, op),\
	DEFS_ARRAY_ENTRY(word_begin, op),\
	DEFS_ARRAY_ENTRY(word_end, op),\
	DEFS_ARRAY_ENTRY(paragraph_begin, op),\
	DEFS_ARRAY_ENTRY(paragraph_end, op),\
	DEFS_ARRAY_ENTRY(center_begin, op),\
	DEFS_ARRAY_ENTRY(center_end, op),\
	DEFS_ARRAY_ENTRY(align_left_begin, op),\
	DEFS_ARRAY_ENTRY(align_left_end, op),\
	DEFS_ARRAY_ENTRY(align_right_begin, op),\
	DEFS_ARRAY_ENTRY(align_right_end, op),\
	DEFS_ARRAY_ENTRY(justify_begin, op),\
	DEFS_ARRAY_ENTRY(justify_end, op),\
	DEFS_ARRAY_ENTRY(forced_space, op),\
	DEFS_ARRAY_ENTRY(line_break, op),\
	DEFS_ARRAY_ENTRY(page_break, op),\
	DEFS_ARRAY_ENTRY(hyperlink_begin, op),\
	DEFS_ARRAY_ENTRY(hyperlink_end, op),\
	DEFS_ARRAY_ENTRY(imagelink_begin, op),\
	DEFS_ARRAY_ENTRY(imagelink_end, op),\
	DEFS_ARRAY_ENTRY(table_begin, op),\
	DEFS_ARRAY_ENTRY(table_end, op),\
	DEFS_ARRAY_ENTRY(table_row_begin, op),\
	DEFS_ARRAY_ENTRY(table_row_end, op),\
	DEFS_ARRAY_ENTRY(table_cell_begin, op),\
	DEFS_ARRAY_ENTRY(table_cell_end, op),\
	DEFS_ARRAY_ENTRY(font_begin, op),\
	DEFS_ARRAY_ENTRY(font_end, op),\
	DEFS_ARRAY_ENTRY(fontsize_begin, op),\
	DEFS_ARRAY_ENTRY(fontsize_end, op),\
	DEFS_ARRAY_ENTRY(fontsize8_begin, op),\
	DEFS_ARRAY_ENTRY(fontsize8_end, op),\
	DEFS_ARRAY_ENTRY(fontsize10_begin, op),\
	DEFS_ARRAY_ENTRY(fontsize10_end, op),\
	DEFS_ARRAY_ENTRY(fontsize12_begin, op),\
	DEFS_ARRAY_ENTRY(fontsize12_end, op),\
	DEFS_ARRAY_ENTRY(fontsize14_begin, op),\
	DEFS_ARRAY_ENTRY(fontsize14_end, op),\
	DEFS_ARRAY_ENTRY(fontsize18_begin, op),\
	DEFS_ARRAY_ENTRY(fontsize18_end, op),\
	DEFS_ARRAY_ENTRY(fontsize24_begin, op),\
	DEFS_ARRAY_ENTRY(fontsize24_end, op),\
	DEFS_ARRAY_ENTRY(fontsize36_begin, op),\
	DEFS_ARRAY_ENTRY(fontsize36_end, op),\
	DEFS_ARRAY_ENTRY(fontsize48_begin, op),\
	DEFS_ARRAY_ENTRY(fontsize48_end, op),\
	DEFS_ARRAY_ENTRY(smaller_begin, op),\
	DEFS_ARRAY_ENTRY(smaller_end, op),\
	DEFS_ARRAY_ENTRY(bigger_begin, op),\
	DEFS_ARRAY_ENTRY(bigger_end, op),\
	DEFS_ARRAY_ENTRY(foreground_begin, op),\
	DEFS_ARRAY_ENTRY(foreground_end, op),\
	DEFS_ARRAY_ENTRY(background_begin, op),\
	DEFS_ARRAY_ENTRY(background_end, op),\
	DEFS_ARRAY_ENTRY(bold_begin, op),\
	DEFS_ARRAY_ENTRY(bold_end, op),\
	DEFS_ARRAY_ENTRY(italic_begin, op),\
	DEFS_ARRAY_ENTRY(italic_end, op),\
	DEFS_ARRAY_ENTRY(underline_begin, op),\
	DEFS_ARRAY_ENTRY(underline_end, op),\
	DEFS_ARRAY_ENTRY(dbl_underline_begin, op),\
	DEFS_ARRAY_ENTRY(dbl_underline_end, op),\
	DEFS_ARRAY_ENTRY(superscript_begin, op),\
	DEFS_ARRAY_ENTRY(superscript_end, op),\
	DEFS_ARRAY_ENTRY(subscript_begin, op),\
	DEFS_ARRAY_ENTRY(subscript_end, op),\
	DEFS_ARRAY_ENTRY(strikethru_begin, op),\
	DEFS_ARRAY_ENTRY(strikethru_end, op),\
	DEFS_ARRAY_ENTRY(dbl_strikethru_begin, op),\
	DEFS_ARRAY_ENTRY(dbl_strikethru_end, op),\
	DEFS_ARRAY_ENTRY(emboss_begin, op),\
	DEFS_ARRAY_ENTRY(emboss_end, op),\
	DEFS_ARRAY_ENTRY(engrave_begin, op),\
	DEFS_ARRAY_ENTRY(engrave_end, op),\
	DEFS_ARRAY_ENTRY(shadow_begin, op),\
	DEFS_ARRAY_ENTRY(shadow_end, op),\
	DEFS_ARRAY_ENTRY(outline_begin, op),\
	DEFS_ARRAY_ENTRY(outline_end, op),\
	DEFS_ARRAY_ENTRY(all_caps_begin, op),\
	DEFS_ARRAY_ENTRY(all_caps_end, op),\
	DEFS_ARRAY_ENTRY(small_caps_begin, op),\
	DEFS_ARRAY_ENTRY(small_caps_end, op),\
	DEFS_ARRAY_ENTRY(pointlist_begin, op),\
	DEFS_ARRAY_ENTRY(pointlist_end, op),\
	DEFS_ARRAY_ENTRY(pointlist_item_begin, op),\
	DEFS_ARRAY_ENTRY(pointlist_item_end, op),\
	DEFS_ARRAY_ENTRY(numericlist_begin, op),\
	DEFS_ARRAY_ENTRY(numericlist_end, op),\
	DEFS_ARRAY_ENTRY(numericlist_item_begin, op),\
	DEFS_ARRAY_ENTRY(numericlist_item_end, op),\
	DEFS_ARRAY_ENTRY(expand_begin, op),\
	DEFS_ARRAY_ENTRY(expand_end, op),\
	DEFS_ARRAY_ENTRY(toc_entry_begin, op),\
	DEFS_ARRAY_ENTRY(toc_entry_end, op),\
	DEFS_ARRAY_ENTRY(index_entry_begin, op),\
	DEFS_ARRAY_ENTRY(index_entry_end, op),\
	DEFS_ARRAY_ENTRY(chars.right_quote, op),\
	DEFS_ARRAY_ENTRY(chars.left_quote, op),\
	DEFS_ARRAY_ENTRY(chars.right_dbl_quote, op),\
	DEFS_ARRAY_ENTRY(chars.left_dbl_quote, op),\
	DEFS_ARRAY_ENTRY(chars.right_quote, op),\
	DEFS_ARRAY_ENTRY(chars.left_quote, op),\
	DEFS_ARRAY_ENTRY(chars.right_dbl_quote, op),\
	DEFS_ARRAY_ENTRY(chars.left_dbl_quote, op),\
	DEFS_ARRAY_ENTRY(chars.endash, op),\
	DEFS_ARRAY_ENTRY(chars.emdash, op),\
	DEFS_ARRAY_ENTRY(chars.bullet, op),\
	DEFS_ARRAY_ENTRY(chars.lessthan, op),\
	DEFS_ARRAY_ENTRY(chars.greaterthan, op),\
	DEFS_ARRAY_ENTRY(chars.amp, op),\
	DEFS_ARRAY_ENTRY(chars.copyright, op),\
	DEFS_ARRAY_ENTRY(chars.trademark, op),\
	DEFS_ARRAY_ENTRY(chars.nonbreaking_space, op),\
	DEFS_ARRAY_ENTRY(unisymbol_print, op),\
	DEFS_ARRAY_ENTRY(utf8_encoding, op),\
	DEFS_ARRAY_ENTRY(fonttable_begin, op),\
	DEFS_ARRAY_ENTRY(fonttable_end, op),\
	DEFS_ARRAY_ENTRY(fonttable_fontnr, op),\
	DEFS_ARRAY_ENTRY(fonttable_fontname, op),\
	{0, 0} \
}

#ifndef _USER


extern zFvIyYuWC *user_init(zFvIyYuWC *, char *tags_file_path);


#define _USER
#endif

#endif
