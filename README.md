# CNeander
**CNeander** é um simulador do computador hipotético de 8-bits NEANDER, projetado para fins didáticos. Desenvolvido inteiramente em C e operado via linha de comandos, permite carregar e executar programas em Assembly da arquitetura de maneira mais eficiente.

## Características:
+ **Memória de 16-bit, CPU de 8-bit:** Os ficheiros de memória (`.mem`) são lidos como uma sequência de palavras de 16-bits. No entanto, o acumulador, os dados e todas as operações aritméticas e lógicas são estritamente de 8-bits, simulando as limitações do processador.
+ **Validação de Assinatura:** O simulador valida uma "assinatura" de 4 bytes no início de cada arquivo `.mem` para garantir que está carregando um arquivo compatível.

Por conta desses dois pontos, o simulador CNeander é **100% binariamente compatível** com os arquivos dos simuladores oficiais de NEANDER, com seus arquivos também podendo ser lidos outros simuladores.

## Referências:
Esse simulador é baseado no trabalho original de Raul Fernando Weber e Taisy Silva Weber na elaboração e desenvolvimento do computador hipotético NEANDER.
O conjunto de instruções e outras características do NEANDER podem ser consultados em https://www.inf.ufrgs.br/arq/wiki/doku.php?id=neander.
### Fonte bibliográfica:
WEBER, R. F. Fundamentos de arquitetura de computadores. 4. ed. Porto Alegre: Bookman, 2012. 424 p. (Série Livros Didáticos Informática UFRGS, v. 8). 
