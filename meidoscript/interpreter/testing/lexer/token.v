module lexer

enum Token_Type {
	error
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
struct Token {
	Name: string,
	Type_of_Token: Token_Type,
	position_l: int,
	position_c: int,
	fn get_name(self Token) string {
		return self.Name
	}
	fn get_type(self Token) Token_Type {
		return self.Type_of_Token
	}
	fn get_position(self Token) (int, int) {
		return self.position_l, self.position_c
	}

}

fn read_file(filepath string) (string){
	file := filepath.to_lower()
	return file
}

fn lexer() []Token {
	file := if read_file(input) == 0 {return tokens := [Token{Name: 'file is empty', Type_of_token: error, position_l: 0, position_c: 0}]} else {read_file(input)}

	for
}
