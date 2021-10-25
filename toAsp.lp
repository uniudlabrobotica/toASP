:- action(A), time(T), occurs(A,T), not executable(A,T).
action(noop).
action(pick(X, H, W)):-block(X), h(H), place(W).
action(put(X, H, W)):-block(X), h(H), place(W).
block(a;b;c;d).
causes(pick(X, H, W), gripped(X)):-block(X), h(H), place(W), block(X).
causes(pick(X, H, W), hight(W, H-1)):-block(X), h(H), place(W), place(W), h(H).
causes(pick(X, H, W), neg(free_gripper)):-block(X), h(H), place(W).
causes(pick(X, H, W), neg(hight(W, H))):-block(X), h(H), place(W), place(W), h(H).
causes(pick(X, H, W), neg(on(X, Y)), T):-time(T), block(X), h(H), place(W), block(X), block(Y), holds(on(X, Y),T), block(X), block(Y).
causes(pick(X, H, W), neg(top(X, W))):-block(X), h(H), place(W), block(X), place(W).
causes(pick(X, H, W), top(Y, W), T):-time(T), block(X), h(H), place(W), block(Y), place(W), holds(on(X, Y),T), block(X), block(Y).
causes(put(X, H, W), free_gripper):-block(X), h(H), place(W).
causes(put(X, H, W), hight(W, H)):-block(X), h(H), place(W), place(W), h(H).
causes(put(X, H, W), neg(gripped(X))):-block(X), h(H), place(W), block(X).
causes(put(X, H, W), neg(hight(W, H-1))):-block(X), h(H), place(W), place(W), h(H).
causes(put(X, H, W), neg(top(Y, W)), T):-time(T), block(X), h(H), place(W), block(Y), place(W), holds(top(Y, W),T), block(Y), place(W).
causes(put(X, H, W), on(X, Y), T):-time(T), block(X), h(H), place(W), block(X), block(Y), holds(top(Y, W),T), block(Y), place(W).
causes(put(X, H, W), top(X, W)):-block(X), h(H), place(W), block(X), place(W).
exec(pick(X, H, W), free_gripper):-block(X), h(H), place(W).
exec(pick(X, H, W), hight(W, H)):-block(X), h(H), place(W), place(W), h(H).
exec(pick(X, H, W), top(X, W)):-block(X), h(H), place(W), block(X), place(W).
exec(put(X, H, W), gripped(X)):-block(X), h(H), place(W), block(X).
exec(put(X, H, W), hight(W, H-1)):-block(X), h(H), place(W), place(W), h(H).
exec(put(X, H, W), neg(free_gripper)):-block(X), h(H), place(W).
executable(A,T):- action(A), time(T), T<10, not not_executable(A,T).
finally(on(a, c)).
finally(on(c, b)).
fluent(free_gripper).
fluent(gripped(X)):-block(X).
fluent(hight(W, H-1)):-place(W), h(H).
fluent(hight(W, H)):-place(W), h(H).
fluent(on(X, Y)):-block(X), block(Y).
fluent(top(X, W)):-block(X), place(W).
fluent(top(Y, W)):-block(Y), place(W).
goal(T) :- time(T), not not_ok(T).
h(1..3).
holds(F,1):-initially(F).
holds(F):- holds(F,10).
holds(F,T+1):-opposto(F,G), T<10, holds(F,T), not holds(G,T+1).
holds(F,T+1):- T<10, executable(A,T), occurs(A,T), causes(A,F).
holds(F,T+1):- T<10, executable(A,T), occurs(A,T), causes(A,F,T).
initially(free_gripper).
initially(hight(1, 2)).
initially(hight(2, 1)).
initially(hight(3, 0)).
initially(on(a, b)).
initially(top(a, 1)).
initially(top(c, 2)).
#maximize { T:occurs(noop,T) }.
not_executable(A,T):- time(T), exec(A,F), not holds(F,T).
:- not goal(10).
not_occurs(A,T):- action(A), action(B), time(T), occurs(B,T), A!=B.
not_ok(T) :- time(T), finally(F), not holds(F,T).
occurs(A,T):- action(A), time(T), not goal(T), not not_occurs(A,T).
opposto(F,neg(F)):- fluent(F).
opposto(neg(F),F):- fluent(F).
place(1..3).
#show occurs/2.
time(1..10).
