
#include "../../headers/minishell.h"


t_scanner scanner_value(t_char_itr char_itr)
{
	t_scanner scanner;
	t_token token;

	ft_memset(&token, 0, sizeof(t_token));
	scanner.char_itr = char_itr;
	scanner.next = token;
	return(scanner);
}

int scanner_has_next(const t_scanner *self)
{
	char c;
	c = char_itr_peek(&self->char_itr);
	//printf("Character peeked: %c (ASCII: %d)\n", c, c);
	//printf("scanner has next? R: %i\n", !(c == EOF || c == '\n' || c == '\0'));
	if (!(c == EOF || c == '\n' || c == '\0'))
	{
		return (!(c == EOF || c == '\n' || c == '\0'));
	}
	else
	{
		//printf("End token\n");
		end_token((t_scanner *)self);
		return (!(c == EOF || c == '\n' || c == '\0'));
	}
}

/* t_token scanner_peek(const t_scanner *self)
{
} */

t_token scanner_next(t_scanner *self)
{
	skip_whitespaces(&self->char_itr);
	//self->next = scanner_peek(self);
	if (scanner_has_next(self)) //ok this is if there is next, but what about the current? Next is the current!
	{
		self->next.lexeme.length = 0;
		self->next = scanner_peek(self);
	}
	else
	{
		//printf("Scanner next end token\n");
		self->next = end_token(self); // Does not have next, returns the END_TOKEN.
	}
	return (self->next);
}

t_token scanner_peek(t_scanner *self)
{
	char c;
	c = *self->char_itr.cursor;
	while(1)
	{
		if (c == EOF || c == '\n' || c == '\0')
			return (end_token(self));
		else if (c == '|')
			return (pipe_token(self));
		else if (c == '>')
			return (redir_out_token(self));
		else if (c == '<')
			return (redir_in_token(self));
		else if (c == '$')
			return (env_var_token(self));
		else if (c == '/')
			return (abs_path_token(self));
		else if (c == '.' && *(self->char_itr.cursor + 1) == '/')
			return (rel_path_token(self));
		else if (c == '-')
			return (option_token(self));
		else if (ft_isalnum(c))
			return (word_token(self));
		else
			return (tmp_unknown_token(self));
	}
}
 int check_start_uknown(const char *input)
 {
	if (ft_strchr(SYMBOLS, input[0]))
	{
		printf("Input character: %c\n", input[0]);
		printf("ft_strchr result: %s\n", ft_strchr(SYMBOLS, input[0]));
		return(1);
	}
	else
		return(0);
 }
