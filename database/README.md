# Database

A definição do banco define uma árvore hierárquica para os diferentes tipos de bloqueios. Um objeto possui um vetor de <unique_ptr> para os seus filhos, enquanto os filhos possuem ponteiros simples para o pai. 

Quando uma transação T fizer uma requisição de lock para um objeto X, o objeto propagará o bloqueio (com tipos diferentes) para o seu pai e o seu filho, repassando a informação da transação. Sempre que houver o bloqueio (caso seja possível) adicionaremos o tipo do bloqueio e o ponteiro ao elemento responsável pelo bloqueio na transação.

