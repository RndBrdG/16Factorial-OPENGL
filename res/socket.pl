%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%                 Sockets                   %%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

:-use_module(library(sockets)).
:-use_module(library(lists)).
:-use_module(library(random)).

port(60070).

% launch me in sockets mode
server:-
	port(Port),
	socket_server_open(Port, Socket),
	socket_server_accept(Socket, _Client, Stream, [type(text)]),
	write('Accepted connection'), nl,
	serverLoop(Stream),
	socket_server_close(Socket).

% wait for commands
serverLoop(Stream) :-
	repeat,
	read(Stream, ClientMsg),
	write('Received: '), write(ClientMsg), nl,
	parse_input(ClientMsg, MyReply),
	format(Stream, '~q.~n', [MyReply]),
	write('Wrote: '), write(MyReply), nl,
	flush_output(Stream),
	(ClientMsg == quit; ClientMsg == end_of_file), !.

parse_input(comando(Arg1, Arg2), Answer) :-
	comando(Arg1, Arg2, Answer).
parse_input(verificarJogadaValida(TabuleiroJogo, Linha, Coluna, PadraoRodado), Answer):-
	(jogadaValidaCima(TabuleiroJogo, Linha, Coluna, PadraoRodado), jogadaValidaDir(TabuleiroJogo, Linha, Coluna, PadraoRodado), jogadaValidaBaixo(TabuleiroJogo, Linha, Coluna, PadraoRodado), jogadaValidaEsq(TabuleiroJogo, Linha, Coluna, PadraoRodado)
		->Answer is 1
		; Answer is 2
		).
parse_input(verificarFimJogo(Tabuleiro, TabuleiroPadrao), Answer) :-
	imprimirPadroes(TabuleiroPadrao),nl,
	verificarFimJogo(Tabuleiro, TabuleiroPadrao, FimJogo),
	(FimJogo =:= 0
		-> Answer is 1
		; Answer is 2
	).

parse_input(quit, ok-bye) :- !.
		
comando(Arg1, Arg2, Answer) :-
	write(Arg1), nl, write(Arg2), nl,
	Answer is Arg1+Arg2.


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%                 JOGO                      %%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

verificarJogadaValida(Tabuleiro, Linha, Coluna, Peca):-
	((jogadaValidaCima(Tabuleiro, Linha, Coluna, Peca), jogadaValidaDir(Tabuleiro, Linha, Coluna, Peca), jogadaValidaBaixo(Tabuleiro, Linha, Coluna, Peca), jogadaValidaEsq(Tabuleiro, Linha, Coluna, Peca));
	(rodarPadrao(Peca, PecaRodada1, 1), jogadaValidaCima(Tabuleiro, Linha, Coluna, PecaRodada1), jogadaValidaDir(Tabuleiro, Linha, Coluna, PecaRodada1), jogadaValidaBaixo(Tabuleiro, Linha, Coluna, PecaRodada1), jogadaValidaEsq(Tabuleiro, Linha, Coluna, PecaRodada1));
	(rodarPadrao(PecaRodada1, PecaRodada2, 1), jogadaValidaCima(Tabuleiro, Linha, Coluna, PecaRodada2), jogadaValidaDir(Tabuleiro, Linha, Coluna, PecaRodada2), jogadaValidaBaixo(Tabuleiro, Linha, Coluna, PecaRodada2), jogadaValidaEsq(Tabuleiro, Linha, Coluna, PecaRodada2));
	(rodarPadrao(PecaRodada2, PecaRodada3, 1), jogadaValidaCima(Tabuleiro, Linha, Coluna, PecaRodada3), jogadaValidaDir(Tabuleiro, Linha, Coluna, PecaRodada3), jogadaValidaBaixo(Tabuleiro, Linha, Coluna, PecaRodada3), jogadaValidaEsq(Tabuleiro, Linha, Coluna, PecaRodada3))).

jogadaValidaCima(Tabuleiro, Linha, Coluna, Padrao):-
	nth0(0, Padrao, ParteSupPeca),
	OutraLinha is Linha - 1,
	(OutraLinha >= 0 ->
		nth0(OutraLinha, Tabuleiro, OutraLinhaComPadroes),
		nth0(Coluna, OutraLinhaComPadroes, OutraPeca),
		nth0(2, OutraPeca, ParteInfOutraPeca),
		(compare(=, ParteInfOutraPeca, ParteSupPeca); compare(=, ParteInfOutraPeca, [' ', ' ', ' ']));
		true
	).

jogadaValidaBaixo(Tabuleiro, Linha, Coluna, Padrao):-
	nth0(2, Padrao, ParteInfPeca),
	OutraLinha is Linha + 1,
	(OutraLinha =< 3 ->
		nth0(OutraLinha, Tabuleiro, OutraLinhaComPadroes),
		nth0(Coluna, OutraLinhaComPadroes, OutraPeca),
		nth0(0, OutraPeca, ParteSupOutraPeca),
		(compare(=, ParteSupOutraPeca, ParteInfPeca); compare(=, ParteSupOutraPeca, [' ', ' ', ' ']));
		true
	).
	
jogadaValidaEsq(Tabuleiro, Linha, Coluna, Padrao):-
	nth0(0, Padrao, ParteSupPeca),
	nth0(1, Padrao, ParteCentrPeca),
	nth0(2, Padrao, ParteInfPeca),
	nth0(0, ParteSupPeca, SupEsqPeca),
	nth0(0, ParteCentrPeca, CentrEsqPeca),
	nth0(0, ParteInfPeca, InfEsqPeca),
	OutraColuna is Coluna - 1,
	(OutraColuna >= 0 ->
		nth0(Linha, Tabuleiro, LinhaComPadroes),
		nth0(OutraColuna, LinhaComPadroes, OutraPeca),
		nth0(0, OutraPeca, ParteSupOutraPeca),
		nth0(1, OutraPeca, ParteCentrOutraPeca),
		nth0(2, OutraPeca, ParteInfOutraPeca),
		nth0(2, ParteSupOutraPeca, SupDirOutraPeca),
		nth0(2, ParteCentrOutraPeca, CentrDirOutraPeca),
		nth0(2, ParteInfOutraPeca, InfDirOutraPeca),
		(compare(=, [SupDirOutraPeca, CentrDirOutraPeca, InfDirOutraPeca], [SupEsqPeca, CentrEsqPeca, InfEsqPeca]); compare(=, [SupDirOutraPeca, CentrDirOutraPeca, InfDirOutraPeca], [' ', ' ', ' ']));
		true
	).
jogadaValidaDir(Tabuleiro, Linha, Coluna, Padrao):-
	nth0(0, Padrao, ParteSupPeca),
	nth0(1, Padrao, ParteCentrPeca),
	nth0(2, Padrao, ParteInfPeca),
	nth0(2, ParteSupPeca, SupDirPeca),
	nth0(2, ParteCentrPeca, CentrDirPeca),
	nth0(2, ParteInfPeca, InfDirPeca),
	OutraColuna is Coluna + 1,
	(OutraColuna =< 3 ->
		nth0(Linha, Tabuleiro, LinhaComPadroes),
		nth0(OutraColuna, LinhaComPadroes, OutraPeca),
		nth0(0, OutraPeca, ParteSupOutraPeca),
		nth0(1, OutraPeca, ParteCentrOutraPeca),
		nth0(2, OutraPeca, ParteInfOutraPeca),
		nth0(0, ParteSupOutraPeca, SupEsqOutraPeca),
		nth0(0, ParteCentrOutraPeca, CentrEsqOutraPeca),
		nth0(0, ParteInfOutraPeca, InfEsqOutraPeca),
		(compare(=, [SupEsqOutraPeca, CentrEsqOutraPeca, InfEsqOutraPeca], [SupDirPeca, CentrDirPeca, InfDirPeca]); compare(=, [SupEsqOutraPeca, CentrEsqOutraPeca, InfEsqOutraPeca], [' ', ' ', ' ']));
		true
	).

verificarFimJogo(Tabuleiro, TabuleiroPadrao, FimJogo):-
	length(TabuleiroPadrao, Tam),
	( Tam =:= 0
		-> FimJogo is 0
	; (\+verificarExistenciaJogadaValida(Tabuleiro, 0, 0, TabuleiroPadrao, 0)
		-> FimJogo is 0
		; FimJogo is 1
	  )
	).

verificarExistenciaJogadaValida(_,_,_,_,1):- !.
verificarExistenciaJogadaValida(_, _, _, [], _):- fail.
verificarExistenciaJogadaValida(Tabuleiro, 4, 0, [Cabeca|Resto], 0):-
	verificarExistenciaJogadaValida(Tabuleiro, 0, 0, Resto, 0).
verificarExistenciaJogadaValida(Tabuleiro,Linha,Coluna,[Cabeca|Resto], 0):-
	nth0(Linha, Tabuleiro, LinhaComPecas),
	nth0(Coluna, LinhaComPecas, PosicaoAVerificar),
	(\+compare(=, [[' ', ' ', ' '], [' ', ' ', ' '], [' ', ' ', ' ']], PosicaoAVerificar) 
		->  
			(Coluna =:= 3 
					-> Linha1 is Linha+1, Coluna1 is 0
					; Linha1 is Linha, Coluna1 is Coluna+1
			),
			verificarExistenciaJogadaValida(Tabuleiro, Linha1, Coluna1, [Cabeca|Resto], 0);

		(verificarJogadaValida(Tabuleiro, Linha, Coluna, Cabeca)
			->  verificarExistenciaJogadaValida(Tabuleiro, Linha, Coluna, [Cabeca|Resto], 1)
			;	(Coluna =:= 3
					-> Linha1 is Linha+1, Coluna1 is 0
					; Linha1 is Linha, Coluna1 is Coluna+1
				),
					verificarExistenciaJogadaValida(Tabuleiro, Linha1, Coluna1, [Cabeca|Resto], 0)
		)
	).
	
verificarJogadaValida(Tabuleiro, Linha, Coluna, Peca):-
	((jogadaValidaCima(Tabuleiro, Linha, Coluna, Peca), jogadaValidaDir(Tabuleiro, Linha, Coluna, Peca), jogadaValidaBaixo(Tabuleiro, Linha, Coluna, Peca), jogadaValidaEsq(Tabuleiro, Linha, Coluna, Peca));
	(rodarPadrao(Peca, PecaRodada1, 1), jogadaValidaCima(Tabuleiro, Linha, Coluna, PecaRodada1), jogadaValidaDir(Tabuleiro, Linha, Coluna, PecaRodada1), jogadaValidaBaixo(Tabuleiro, Linha, Coluna, PecaRodada1), jogadaValidaEsq(Tabuleiro, Linha, Coluna, PecaRodada1));
	(rodarPadrao(PecaRodada1, PecaRodada2, 1), jogadaValidaCima(Tabuleiro, Linha, Coluna, PecaRodada2), jogadaValidaDir(Tabuleiro, Linha, Coluna, PecaRodada2), jogadaValidaBaixo(Tabuleiro, Linha, Coluna, PecaRodada2), jogadaValidaEsq(Tabuleiro, Linha, Coluna, PecaRodada2));
	(rodarPadrao(PecaRodada2, PecaRodada3, 1), jogadaValidaCima(Tabuleiro, Linha, Coluna, PecaRodada3), jogadaValidaDir(Tabuleiro, Linha, Coluna, PecaRodada3), jogadaValidaBaixo(Tabuleiro, Linha, Coluna, PecaRodada3), jogadaValidaEsq(Tabuleiro, Linha, Coluna, PecaRodada3))).

rodarPadrao(Peca, Peca, 0):- !.
rodarPadrao([[A1, B1, C1], [A2, B2, C2], [A3, B3, C3]], PecaRodada, Rotacoes):-
	Rotacoes1 is (Rotacoes-1) mod 4,
	rodarPadrao([[A3, A2, A1], [B3, B2, B1], [C3, C2, C1]], PecaRodada, Rotacoes1).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% FUNÇÕES DE IMPRIMIR TABULEIRO E PADROES  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

imprimirTabuleiro([]):- 
	write('#########################################'),
	!.
imprimirTabuleiro([H|T]):-
	write('#########################################'), nl,
	imprimirLinha(H),
	imprimirTabuleiro(T).

imprimirLinha(Linha):-
	write('| '),
	imprimirLinhaPeca(Linha,0), nl, write('| '),
	imprimirLinha2Peca(Linha,0), nl, write('| '),
	imprimirLinha3Peca(Linha,0), nl.

imprimirLinhaPeca(_,4):- !.
imprimirLinhaPeca([[Linha|R]|T],Numero):-
	N1 is Numero + 1,
	nth0(0,Linha,LinhaPeca),
	nth0(1,Linha,LinhaPeca1),
	nth0(2,Linha,LinhaPeca2),
	write(LinhaPeca),
	write('  '),
	write(LinhaPeca1),
	write('  '),
	write(LinhaPeca2),
	write(' | '),
	%write(Linha),nl,write(R), nl, write(T), nl,
	imprimirLinhaPeca(T,N1).

imprimirLinha2Peca(_,4):- !.
imprimirLinha2Peca([[Linha|[R|X]]|T],Numero):-
	N1 is Numero + 1,
	nth0(0,R,LinhaPeca),
	nth0(1,R,LinhaPeca1),
	nth0(2,R,LinhaPeca2),
	write(LinhaPeca),
	write('  '),
	write(LinhaPeca1),
	write('  '),
	write(LinhaPeca2),
	write(' | '),
	imprimirLinha2Peca(T,N1).

imprimirLinha3Peca(_,4):- !.
imprimirLinha3Peca([[Linha|[R|[X|Lixo]]]|T],Numero):-
	N1 is Numero + 1,
	nth0(0,X,LinhaPeca),
	nth0(1,X,LinhaPeca1),
	nth0(2,X,LinhaPeca2),
	write(LinhaPeca),
	write('  '),
	write(LinhaPeca1),
	write('  '),
	write(LinhaPeca2),
	write(' | '),
	imprimirLinha3Peca(T,N1).

imprimirPadroes(Padrao):-
	write('| '),
	imprimirPadroesLinha1(Padrao), nl, write('| '),
	imprimirPadroesLinha2(Padrao), nl, write('| '),
	imprimirPadroesLinha3(Padrao).

imprimirPadroesLinha1([]):- !.
imprimirPadroesLinha1([[Cabeca|Resto]|T]):-
	nth0(0,Cabeca,Indice1),
	nth0(1,Cabeca,Indice2),
	nth0(2,Cabeca,Indice3),
	write(Indice1),write(' '),
	write(Indice2),write(' '),
	write(Indice3),write(' '),
	write('| '),
	imprimirPadroesLinha1(T).

imprimirPadroesLinha2([]):- !.
imprimirPadroesLinha2([[Cabeca|[CabecaResto|Resto]]|T]):-
	nth0(0,CabecaResto,Indice1),
	nth0(1,CabecaResto,Indice2),
	nth0(2,CabecaResto,Indice3),
	write(Indice1),write(' '),
	write(Indice2),write(' '),
	write(Indice3),write(' '),
	write('| '),
	imprimirPadroesLinha2(T).

imprimirPadroesLinha3([]):- !.
imprimirPadroesLinha3([[Cabeca|[CabecaResto|[Resto|Vazio]]]|T]):-
	nth0(0,Resto,Indice1),
	nth0(1,Resto,Indice2),
	nth0(2,Resto,Indice3),
	write(Indice1),write(' '),
	write(Indice2),write(' '),
	write(Indice3),write(' '),
	write('| '),
	imprimirPadroesLinha3(T).

