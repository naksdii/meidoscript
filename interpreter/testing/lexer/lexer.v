module lexer

import os

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
	eof
}

fn lexer(file string) []Token {
	file_content := os.read_file(file) or {
		eprintln('Erro ao ler: $err')
		return [Token.eof]
	}

	mut tokens := []Token{len: 1, cap: 1000, init: Token.eof}

	return tokens
}

fn format(code string) string {
	i := 0
	mut code_runified := code.runes()
	for {
		if i >= code_runified.len {
			break
		}
		if code_runified[i] == ` ` && code_runified[i + 1] == ` ` {
			code_runified.delete(i)
		}
	}
	return code
}
