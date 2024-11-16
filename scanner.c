
#include "./include/minishell.h"


/*
We need to initialize the first scanner structure with its
iterator located at the first token and the first token.
*/
t_scanner scanner_value(t_char_itr char_itr)
{
	t_scanner scanner;
	t_token token; // we really need to have the token in the t_scanner struct?

	//skip_whitespaces(&char_itr); //It's already done in scanner_next()
	ft_memset(&token, 0, sizeof(t_token));
	scanner.char_itr = char_itr;
	scanner.next = token; //Here I am assigning the token initialized with memset.
	token = scanner_next(&scanner); //Then I use scanner_next to produce the token.
	scanner.next = token; //Here I make sure that the token is saved in the scanner struct.
	print_token(scanner.next);
	return(scanner);
}

int scanner_has_next(const t_scanner *self)
{
	char c;
	c = char_itr_peek(&self->char_itr);
	printf("Character peeked: %c (ASCII: %d)\n", c, c);
	printf("scanner has next? R: %i\n", !(c == EOF || c == '\n' || c == '\0'));
	if (!(c == EOF || c == '\n' || c == '\0'))
		return (!(c == EOF || c == '\n' || c == '\0'));
	else
	{
		end_token((t_scanner *)self);
		return (!(c == EOF || c == '\n' || c == '\0'));
	}
}

/* t_token scanner_peek(const t_scanner *self)
{
} */

t_token scanner_next(t_scanner *self)
{
	/* t_token token;
	ft_memset(&token, 0, sizeof(t_token)); */

	skip_whitespaces(&self->char_itr);
	//self->next = scanner_peek(self);
	if (scanner_has_next(self)) //ok this is if there is next, but what about the current? Next is the current!
	{
		self->next = scanner_peek(self);
	}
	else
	{
		printf("Scanner next end token\n");
		self->next = end_token(self); // Does not have next, returns the END_TOKEN.
	}
/* 	while (*self->char_itr.cursor != '\0' && self->char_itr.cursor < self->char_itr.sentinel1)
	{
		if (*self->char_itr.cursor == '|')
			{
				//printf("I found a pipe!\n");
				self->next = new_token (PIPE, (char *)self->char_itr.cursor, 1);// <-------- WILL BE COMING FROM PEEK
				print_token(self->next);
				printf("Iterator advance, after printing token\n");
				self->char_next = char_itr_next(&self->char_itr); //we need to advance the iterator anyway... but the return is a char, what we should do... not sure if later we can use this char.
			}
	} */
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
		{
			printf("I see a pipe\n");
			return (pipe_token(self));
		}
		else if (c == '>')
			return (redir_out_token(self));
		else if (c == '<')
			return (redir_in_token(self));
		else if (ft_isalnum(c))
			return (word_token(self));
		else
			return (unknown_token(self));
	}
}








// This functions returns the tokens. Not sure...
/* void parse(t_scanner *scanner)
{
	t_token next = scanner_peek(scanner);
	if (next.type ==  )

} */
