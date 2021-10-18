fluent(libero(X)):-blocco(X).
fluent(sul_tavolo(X)):-blocco(X).
fluent(mano_vuota).
fluent(afferrato(X)):-blocco(X).
fluent(afferrato(X)):-blocco(X).
fluent(libero(Y)):-blocco(Y).
fluent(sopra(X, Y)):-blocco(X), blocco(Y).
fluent(libero(X)):-blocco(X).
fluent(mano_vuota).
fluent(libero(X)):-blocco(X).
fluent(afferrato(X)):-blocco(X).
fluent(libero(X)):-blocco(X).
fluent(sul_tavolo(X)):-blocco(X).
fluent(mano_vuota).
fluent(afferrato(X)):-blocco(X).
fluent(sopra(X, Y)):-blocco(X), blocco(Y).
fluent(libero(Y)):-blocco(Y).
fluent(libero(X)):-blocco(X).
fluent(mano_vuota).
action(prendi(X)):-blocco(X).
fluent(libero(X)):-blocco(X).
fluent(sul_tavolo(X)):-blocco(X).
fluent(mano_vuota).
action(appoggia(X)):-blocco(X).
fluent(afferrato(X)):-blocco(X).
action(impila(X, Y)):-blocco(X), blocco(Y).
fluent(afferrato(X)):-blocco(X).
fluent(libero(Y)):-blocco(Y).
action(prendi_da_pila(X, Y)):-blocco(X), blocco(Y).
fluent(sopra(X, Y)):-blocco(X), blocco(Y).
fluent(libero(X)):-blocco(X).
fluent(mano_vuota).
action(prendi(X)):-blocco(X).
fluent(libero(X)):-blocco(X).
action(appoggia(X)):-blocco(X).
fluent(afferrato(X)):-blocco(X).
fluent(libero(X)):-blocco(X).
fluent(sul_tavolo(X)):-blocco(X).
fluent(mano_vuota).
action(prendi_da_pila(X, Y)):-blocco(X), blocco(Y).
fluent(afferrato(X)):-blocco(X).
fluent(sopra(X, Y)):-blocco(X), blocco(Y).
fluent(libero(Y)):-blocco(Y).
fluent(libero(X)):-blocco(X).
fluent(mano_vuota).
