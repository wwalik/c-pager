#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define LINE_BUFFER_SIZE 80

int
main(int argc, char *argv[])
{

	if (argc != 2)
	{
		printf("Usage: <c file>\n");
		exit(EXIT_FAILURE);
	}

	FILE *fp = fopen(argv[1], "r");
	if (fp == NULL)
	{
		perror(argv[0]);
		exit(EXIT_FAILURE);
	}
	initscr();
	noecho();
	cbreak();

	int row, col;
	getmaxyx(stdscr, row, col);

	char s[LINE_BUFFER_SIZE];
	int line_count = 1;
	while (fgets(s, LINE_BUFFER_SIZE, fp) != NULL)
	{
		int x, y;
		getyx(stdscr, y, x);
		if (y == row-1)
		{
			printw("Press <any key>");
			getch();
			move(0, 0);
			clear();
		}
		// print line number
		attron(A_BOLD);
		printw("%2d: ", line_count);
		attroff(A_BOLD);


		// Copy string into a buffer for tokenizing
		char tokenized_s[sizeof(s)]; // TODO
		strcpy(tokenized_s, s);

		// Stores the last character of the previous token, this allows printing of delimiters
		char *last_tok_end = s;
		const char *delim = " \t\n;";
		for (char *tok = strtok(tokenized_s, delim);
				tok != NULL;
				tok = strtok(NULL, delim))
		{
			const size_t tok_len = strlen(tok);
			// The offset of the token in the tokenized_s
			const size_t tok_offset = (tok-tokenized_s);
			// How many delimiter characters seperated this token and the previous
			const size_t delim_length = tok_offset - (last_tok_end - s);

			if (strcmp(tok, "int") == 0)
			{
				attron(A_BLINK);
			}
			addnstr(last_tok_end, tok_len+delim_length);
			attroff(A_BLINK);

			// Update for next token
			last_tok_end = s + /* offset to end of token */(tok_offset+tok_len);
		}
		
		// the \n was removed by tokenizing so add it back
		addstr("\n"); 
		line_count++;
	}
	getch();

	fclose(fp);
	endwin();
	exit(EXIT_SUCCESS);
}
