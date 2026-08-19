module lexer

enum Token {
	plus
	minus
	star
	slash
	equal
	greather
	less
	exclamation
	interrogation
	comma
	dot
	semicolon

	open_brackets
	close_brackets
	open_paren
	close_paren
	open_curly
	close_curly

	literal
	id

	// keywords
	fun
	if
	else
	switch
	case
	import
	from
	as
	for
	continue
	pass
	break
	struct
	return
}

fn read_file(filepath string) string {
	return filepath.to_lower()
}
