# Escalonador

O escalonador espera receber uma lista de operações. Cada operação possui:

1. ID da transação (int)
2. Operação a ser realizada (enum / int)
3. Objeto alvo (ponteiro para um objeto)

Sempre que uma operação for tentar ser escalonada, verificaremos os tipos de bloqueio necessários no vetor do objeto apontado. Se o bloqueio for concedido, além de colocar ele como "TRUE", também adicionaremos o ponteiro do booleano a um vetor na transação correspondente (junto do tipo do bloqueio). O ponteiro servirá para termos como acessar um elemento de um bloqueio via uma transação. 

Se um commit chegar, precisaremos converter os bloqueios de escrita em certify lock, isso será feito usando o vetor na transação correspondente.

Se um abort tiver que ser realizado, precisaremos liberar todos os bloqueios da transação abortada, isso também será feito usando o vetor na transação.

Quando uma transação espera, outras transações ainda podem ser escalonadas, para isso serve o grafo de espera!

