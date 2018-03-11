% used to generate a list of the given length
gen_list(1,L):- L = [1].
gen_list(N,L):-
    M is N - 1,
    gen_list(M,K),
    append([N],K,L).

% immutable recursive implementation
do_sum_im([],N):- N = 0.
do_sum_im([X|Xs],N):-
    do_sum_im(Xs,M),
    N is X + M.

% main implementation using recursion
do_sum_m_r_int([]).
do_sum_m_r_int([X|Xs]):-
    do_sum_m_r_int(Xs),
    b_getval(k, Y),
    T is X + Y,
    b_setval(k, T).
do_sum_m_r(X,N):-
    b_setval(k,0),
    do_sum_m_r_int(X),
    b_getval(k,N).

% secondary implementation using backtracking
% only included to show benchmarks (not included in graphs)
do_sum_m_b_next([], Y, Ys):-
    Y = [],
    Ys = [].
do_sum_m_b_next([X|Xs], Y, Ys):-
    Y is X,
    Ys = Xs.
do_sum_m_b(X,N):-
    nb_setval(k,0),
    nb_setval(l,X),
    repeat,
    nb_getval(l,L),
    do_sum_m_b_next(L, Y, Ys),
    nb_setval(l,Ys),
    nb_getval(k,K),
    ( Y = [] ->
        true,
        !
      ; T is Y + K,
        nb_setval(k,T),
        fail
    ),
    b_getval(k,N).

% performs all the benchmarks using the given list length
% takes in a boolean value to decide whether to run the mutable benchmarks or not
% (this is due to the fact that for 1,000,000 items, the mutable versions stop working)
bench(N,M):-
    write("====== benching with list of "),
    write(N),
    writeln(" items ======"),
    gen_list(N,L),
    writeln("---===--- benchmarking immutable ---===---"),
    time(do_sum_im(L,N1)),
    writeln("---===--- benchmarking mutable recursion ---===---"),
    time(do_sum_m_r(L,N2)),
    ( M ->
        writeln("---===--- benchmarking mutable backtracking ---===---"),
        time(do_sum_m_b(L,N3))
      ; true
    ),
    writeln("---===--- benchmarking complete ---===---"),
    writeln("").

% entry point for benchmarks
bench:-
    bench(10000,true), % 10,000 items
    bench(100000,true), % 100,000 items
    bench(1000000,false). % 1,000,000 items

?- bench.
?- halt.
