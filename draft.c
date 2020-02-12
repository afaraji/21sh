

/*

*****************************************************************
**********                shell grammar                 *********
*****************************************************************

<letter> ::= a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z|
	     A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z

<digit> ::= 0|1|2|3|4|5|6|7|8|9

<number> ::= <digit> | <number> <digit>

<word> ::= <letter> | <word> <letter> | <word> '_'

<word_list> ::= <word> |  <word_list> <word>

<assignment_word> ::= <word> '=' <word>

<redirection> ::=  '>' <word> |  '<' <word> |  <number> '>' <word>
		|  <number> '<' <word> |  '>>' <word>
		|  <number> '>>' <word> |  '<<' <word>
		|  <number> '<<' <word> |  '<&' <number>
		|  <number> '<&' <number> |  '>&' <number>
		|  <number> '>&' <number> |  '<&' <word>
		|  <number> '<&' <word> |  '>&' <word>
		|  <number> '>&' <word> |  '<<-' <word>
		| <number> '<<-' <word> |  '>&' '-'
		|  <number> '>&' '-' |  '<&' '-'
		|  <number> '<&' '-' |  '&>' <word>
		|  <number> '<>' <word> |  '<>' <word>
		|  '>|' <word> |  <number> '>|' <word>

<simple_command_element> ::= <word> | <assignment_word>
			<redirection>

<redirection_list> ::= <redirection> | <redirection_list> <redirection>

<simple_command> ::=  <simple_command_element> | <simple_command> <simple_command_element>

<command> ::=  <simple_command> | <shell_command> | <shell_command> <redirection_list>

<shell_command> ::=  <for_command> | <case_command>
		  | while <compound_list> do <compound_list> done
		  | until <compound_list> do <compound_list> done
		  | <select_command> | <if_command> | <subshell>
		  | <group_command> | <function_def>

<for_command> ::=  for <word> <newline_list> do <compound_list> done
	    |  for <word> <newline_list> '{' <compound_list> '}'
	    |  for <word> ';' <newline_list> do <compound_list> done
	    |  for <word> ';' <newline_list> '{' <compound_list> '}'
	    |  for <word> <newline_list> in <word_list> <list_terminator>
		   <newline_list> do <compound_list> done
	    |  for <word> <newline_list> in <word_list> <list_terminator>
		   <newline_list> '{' <compound_list> '}'

<select_command> ::=  select <word> <newline_list> do <list> done
		   |  select <word> <newline_list> '{' <list> '}'
		   |  select <word> ';' <newline_list> do <list> done
		   |  select <word> ';' <newline_list> '{' list '}'
		   |  select <word> <newline_list> in <word_list>
			   <list_terminator> <newline_list> do <list> done
		   |  select <word> <newline_list> in <word_list>
			   <list_terminator> <newline_list> '{' <list> '}'

<case_command> ::=  case <word> <newline_list> in <newline_list> esac
		 |  case <word> <newline_list> in <case_clause_sequence>
			 <newline_list> esac
		 |  case <word> <newline_list> in <case_clause> esac

<function_def> ::=  <word> '(' ')' <newline_list> <group_command>
		 |  function <word> '(' ')' <newline_list> <group_command>
		 |  function <word> <newline_list> <group_command>

<subshell> ::=  '(' <compound_list> ')'

<if_command> ::= if <compound_list> then <compound_list> fi
	  | if <compound_list> then <compound_list> else <compound_list> fi
	  | if <compound_list> then <compound_list> <elif_clause> fi

<group_command> ::=  '{' <list> '}'

<elif_clause> ::= elif <compound_list> then <compound_list>
	   | elif <compound_list> then <compound_list> else <compound_list>
	   | elif <compound_list> then <compound_list> <elif_clause>

<case_clause> ::=  <pattern_list>
		|  <case_clause_sequence> <pattern_list>

<pattern_list> ::=  <newline_list> <pattern> ')' <compound_list>
		 |  <newline_list> <pattern> ')' <newline_list>
		 |  <newline_list> '(' <pattern> ')' <compound_list>
		 |  <newline_list> '(' <pattern> ')' <newline_list>

<case_clause_sequence> ::=  <pattern_list> ';;'
			 |  <case_clause_sequence> <pattern_list> ';;'

<pattern> ::=  <word> | <pattern> '|' <word>


<list> ::=   <newline_list> <list0>

<compound_list> ::=  <list>
		  |  <newline_list> <list1>

<list0> ::=   <list1> '\n' <newline_list>
	   |  <list1> '&' <newline_list>
	   |  <list1> ';' <newline_list>

<list1> ::=   <list1> '&&' <newline_list> <list1>
	   |  <list1> '||' <newline_list> <list1>
	   |  <list1> '&' <newline_list> <list1>
	   |  <list1> ';' <newline_list> <list1>
	   |  <list1> '\n' <newline_list> <list1>
	   |  <pipeline_command>

<list_terminator> ::= '\n'
		   |  ';'

<newline_list> ::=
		  |  <newline_list> '\n'

<simple_list> ::=  <simple_list1>
		|  <simple_list1> '&'
		|  <simple_list1> ';'

<simple_list1> ::=  <simple_list1> '&&' <newline_list> <simple_list1>
		 |  <simple_list1> '||' <newline_list> <simple_list1>
		 |  <simple_list1> '&' <simple_list1>
		 |  <simple_list1> ';' <simple_list1>
		 |  <pipeline_command>

<pipeline_command> ::= <pipeline>
		    |  '!' <pipeline>
		    |  <timespec> <pipeline>
		    |  <timespec> '!' <pipeline>
		    |  '!' <timespec> <pipeline>

<pipeline> ::=
	  <pipeline> '|' <newline_list> <pipeline>
       |  <command>

<time_opt> ::= '-p'

<timespec> ::=  time
	     |  time <time_opt>

.XE "BNF (Backus-Naur Form)"
.XE "bash" "syntax, BNF form of"
// src: https://my.safaribooksonline.com/book/operating-systems-and-server-administration/unix/1565923472/syntax/lbs.appd.div.3

*/

/*

*****************************************************************
**********                shell grammar                 *********
*****************************************************************

<number> ::= <digit> | <number> <digit>

<word> ::= <letter> | <word> <letter> | <word> '_'

<word_list> ::= <word> |  <word_list> <word>

<assignment_word> ::= <word> '=' <word>

<redirection> ::=  '>' <word> |  '<' <word> |  <number> '>' <word>
		|  <number> '<' <word> |  '>>' <word>
		|  <number> '>>' <word> |  '<<' <word>
		|  <number> '<<' <word> |  '<&' <number>
		|  <number> '<&' <number> |  '>&' <number>
		|  <number> '>&' <number> |  '<&' <word>
		|  <number> '<&' <word> |  '>&' <word>
		|  <number> '>&' <word> |  '<<-' <word>
		| <number> '<<-' <word> |  '>&' '-'
		|  <number> '>&' '-' |  '<&' '-'
		|  <number> '<&' '-' |  '&>' <word>
		|  <number> '<>' <word> |  '<>' <word>
		|  '>|' <word> |  <number> '>|' <word>

<simple_command_element> ::= <word> | <assignment_word> | <redirection>

<redirection_list> ::= <redirection> | <redirection_list> <redirection>

<simple_command> ::=  <simple_command_element> | <simple_command> <simple_command_element>

<command> ::=  <simple_command> | <shell_command> | <shell_command> <redirection_list>

<list> ::=   <newline_list> <list0>

<list0> ::=   <list1> '\n' <newline_list>
	   |  <list1> '&' <newline_list>
	   |  <list1> ';' <newline_list>

<list1> ::=   <list1> '&&' <newline_list> <list1>
	   |  <list1> '||' <newline_list> <list1>
	   |  <list1> '&' <newline_list> <list1>
	   |  <list1> ';' <newline_list> <list1>
	   |  <list1> '\n' <newline_list> <list1>
	   |  <pipeline_command>

<list_terminator> ::= '\n'
		   |  ';'

<newline_list> ::=
		  |  <newline_list> '\n'

<simple_list> ::=  <simple_list1>
		|  <simple_list1> '&'
		|  <simple_list1> ';'

<simple_list1> ::=  <simple_list1> '&&' <newline_list> <simple_list1>
		 |  <simple_list1> '||' <newline_list> <simple_list1>
		 |  <simple_list1> '&' <simple_list1>
		 |  <simple_list1> ';' <simple_list1>
		 |  <pipeline_command>

<pipeline_command> ::= <pipeline>
		    |  '!' <pipeline>
		    |  <timespec> <pipeline>
		    |  <timespec> '!' <pipeline>
		    |  '!' <timespec> <pipeline>

<pipeline> ::=
	  <pipeline> '|' <newline_list> <pipeline>
       |  <command>

<time_opt> ::= '-p'

<timespec> ::=  time
	     |  time <time_opt>

.XE "BNF (Backus-Naur Form)"
.XE "bash" "syntax, BNF form of"
// src: https://my.safaribooksonline.com/book/operating-systems-and-server-administration/unix/1565923472/syntax/lbs.appd.div.3

*/

// https://www.geeksforgeeks.org/tree-traversals-inorder-preorder-and-postorder/
// https://www.geeksforgeeks.org/recursive-descent-parser/
// https://theswissbay.ch/pdf/Gentoomen%20Library/Programming/Bash/O%27Reilly%20bash%20CookBook.pdf
// http://man7.org/linux/man-pages/man1/bash.1.html



<redirection> ::=  '>' <word> |  '<' <word> |  <number> '>' <word>	|  <number> '<' <word>
				| '>>' <word>	|  <number> '>>' <word> |  '<<' <word> |  <number> '<<' <word>
				| '<&' <number> | <number> '<&' <number> | '>&' <number> | <number> '>&' <number> | '<&' <word> | <number> '<&' <word> | '>&' <word> | <number> '>&' <word> | '&>' <word>
				| '<<-' <word> | <number> '<<-' <word>
				| '>&' '-' |  <number> '>&' '-' |  '<&' '-' | <number> '<&' '-'
				| <number> '<>' <word> | '<>' <word>	| '>|' <word> | <number> '>|' <word>



>&2 2>
<&4