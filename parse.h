/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 23:23:11 by afaraji           #+#    #+#             */
/*   Updated: 2020/01/14 23:23:26 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# include "21sh.h"

# define SPACE	-1			/* white space */
# define QUOTE	-2			/* '	*/
# define DQUOTE	-3			/* "	*/
# define SMCLN	-4			/* ;	*/
# define ANDLG	-5			/* &&	*/
# define ORLG	-6			/* ||	*/
# define PIP	-10			/* |	*/
# define BGJOB	-11			/* &	*/
# define ESCAPE	-12			/* \	*/
# define GRT	-20 		/* >	*/
# define GRTGRT	-21			/* >>	*/
# define SML	-22			/* <	*/
# define SMLSML	-23 		/* <<	*/
# define WORD	-42			/* word */

# define _OR(m,a,b,c,d,e) (m==a||m==b||m==c||m==d||m==e) ? 1 : 0

typedef union	u_token
{
	/* data */
} 				t_token;

 
typedef struct					s_list_token
{
	int							type;
	int							is_ok; // for ' and " closed or not
	char						*data;
	struct s_list_token			*next;
	struct s_list_token			*prec;
}                               t_list_token;

typedef struct					s_alias
{
	char						*key;
	char						*sub;
	struct s_alias				*next;
}                               t_alias;

struct SimpleCommand
{
        char ** _arguments;
};

// ***************************************

typedef struct				s_simple_cmd
{
	char					*cmd;
	char					**cmd_tab;
	struct s_simple_cmd		*next;
}							t_simple_cmd;

typedef struct				s_comp_cmd
{ 
	char					*outFile; 
	char					*inFile; 
	char					*errFile; 
	int						background;
	t_simple_cmd			*cmd_list;
	t_list_token			*tokens;
}							t_comp_cmd;

typedef struct				s_pipe_seq
{
	int						dependent;	// 0/1/2 (0 not dependt, 1 exec if $? == 0, 2 exec if $? != 0)
	t_comp_cmd				*left;
	struct s_pipe_seq		*right;
}							t_pipe_seq;

typedef struct			s_redirect
{
	int						in;
	int						out;
	char					*output;
	char					*input;
}							t_redirect;

// ***************************************

// struct Command { 
//         int _numberOfAvailableSimpleCommands; 
//         int _numberOfSimpleCommands; 
//         SimpleCommand ** _simpleCommands; 
//         char * _outFile; 
//         char * _inputFile; 
//         char * _errFile; 
//         int _background; 
//         void prompt(); 
//         void print(); 
//         void execute(); 
//         void clear(); 
//         Command(); 
//         void insertSimpleCommand( SimpleCommand * simpleCommand ); 
//         static Command _currentCommand; 
//         static SimpleCommand *_currentSimpleCommand; 
// }; 

/*
	https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html#tag_02_03
	https://en.wikipedia.org/wiki/Backus%E2%80%93Naur_form
	https://www.gnu.org/software/bash/manual/bash.html#Shell-Operation
	https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf
	https://git.kernel.org/pub/scm/utils/dash/dash.git/tree/src

	https://catonmat.net/ftp/bash-redirections-cheat-sheet.pdf
*/

#endif
