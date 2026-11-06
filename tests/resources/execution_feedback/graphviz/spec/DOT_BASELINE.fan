# Automatically generated from 'spec/DOT.g4'.
#
# DOT
<graph> ::= (<STRICT> <WS>)? (<GRAPH> | <DIGRAPH>) (<WS> <id_>)? '{' <stmt_list> '}'
<stmt_list> ::= (<stmt> ((';' | <WS>) <stmt>)*)? (';' | <WS>)?
<stmt> ::= <node_stmt> | <edge_stmt> | <attr_stmt> | <id_> '=' <id_> | <subgraph>
<attr_stmt> ::= (<GRAPH> | <NODE> | <EDGE>) <attr_list>
<attr_list> ::= ('[' <a_list>? ']')+
<a_list> ::= <id_> ('=' <id_>)? ((<WS> | ';' | ',') <id_> ('=' <id_>)?)* (';' | ',')?
<edge_stmt> ::= (<node_id> | <subgraph>) <edgeRHS> <attr_list>?
<edgeRHS> ::= (<edgeop> (<node_id> | <subgraph>))+
<edgeop> ::= '->' | '--'
<node_stmt> ::= <node_id> <attr_list>?
<node_id> ::= <id_> <port>?
<port> ::= ':' <id_> (':' <id_>)?
<subgraph> ::= (<SUBGRAPH> (<WS> <id_>)?)? '{' <stmt_list> '}'
<id_> ::= <ID> | <STRING> | <HTML_STRING> | <NUMBER>
<STRICT> ::= 'strict'
<GRAPH> ::= 'graph'
<DIGRAPH> ::= 'digraph'
<NODE> ::= 'node'
<EDGE> ::= 'edge'
<SUBGRAPH> ::= 'subgraph'
<NUMBER> ::= '-'? ('.' <DIGIT>+ | <DIGIT>+ ('.' <DIGIT>*)?)
<DIGIT> ::= r'[0-9]'
<STRING> ::= '"' <Char>* '"'
<Char> ::= r'[^"\\]' | <ESC>
<ESC> ::= '\\' r'.'
<ID> ::= <LETTER> (<LETTER> | <DIGIT>)*
<LETTER> ::= r'[a-z_]'
<HTML_STRING> ::= '<' (<TAG> | r'[^<>]')* '>'
<TAG> ::= '<' r'.'* '>'  # NOTE: was '*?'
<COMMENT> ::= '/*' r'.'* '*/'  # NOTE: was '*?'; was '-> skip'
<LINE_COMMENT> ::= '//' r'.'* '\r'? '\n'  # NOTE: was '*?'; was '-> skip'
<PREPROC> ::= '#' r'[^\r\n]'*  # NOTE: was '-> skip'
<WS> ::= r'[ \t\n\r]'+  # NOTE: was '-> skip'

