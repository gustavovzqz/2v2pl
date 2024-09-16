# Parser

O parser espera receber as operações na gramática abaixo:


```
<op> ::= "w" | "r" | "u" | "c"
<cmt> ::= "c" 
<numb> := conjunto de numeros naturais
<obj> ::= conjunto de letras com parenteses em volta;

<action> ::= <op><numb><obj>
<commit> ::= <cmt><numb>

<tr> ::= <action> | <commit> | <tr> <tr>

```


Alguns exemplos:

1. $w1(x)w2(x)r1(z)r2(y)c1c2$
2. $r1(x)w1(x)r2(x)w2(x)c2$

Daqui, já extraímos que:

1. Temos duas transações (ou a quantidade de números diferentes)
2. Temos dois objetos, $x$ e $y$.

O objetivo do parser é criar uma lista de operações e inicializar o vetor de Transactions. 

```cpp 

struct Operation {
    char object;
    int transaction_id;
    OperationType operation_type;
}

``` 

