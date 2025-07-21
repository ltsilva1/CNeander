# CNeander
**CNeander** é um simulador do computador hipotético de 8-bits NEANDER, projetado para fins didáticos. Desenvolvido inteiramente em C e operado via linha de comandos, permite carregar e executar programas em Assembly da arquitetura de maneira eficiente.

## Características:
+ **Arquivos de memória de 16-bit, CPU de 8-bit:** Os ficheiros de memória (`.mem`) são lidos como uma sequência de inteiros de 16-bits. No entanto, o acumulador, os dados e todas as operações aritméticas e lógicas são estritamente de 8-bits, respeitando as limitações do processador.
+ **Validação de Assinatura:** O simulador valida uma "assinatura" esperada no início de cada arquivo `.mem` para garantir que está carregando um arquivo compatível.
+ **Binariamente compatível com os outros simuladores:** Por respeitar a mesma estrutura de ficheiros de entrada e saída, seus arquivos de memória podem ser carregados em outros simuladores compatíveis com o conjunto de instruções do NEANDER.

## Passos para compilação
1. Clone o repositório e navegue para a pasta do projeto.
2. Crie uma pasta para a build e execute o CMake:

   ```bash
     mkdir build
     cd build
     cmake ..
   ```
3. Compile o projeto:

   ```bash
     make
   ```
Isto irá gerar um executável chamado **cneander** na pasta build.

## Execução
Para executar o simulador, passe o caminho para um arquivo de memória como argumento na linha de comandos.

  ```bash
     ./cneander /caminho/para/seu/programa.mem
   ```
O simulador irá carregar o arquivo, executar o programa e exportar o resultado para um binário de memória chamado ```out.mem``` e para um arquivo texto chamado ```out.mem.txt```.

## Referências e créditos:
Esse simulador é baseado no trabalho original de Raul Fernando Weber e Taisy Silva Weber, responsáveis pela elaboração e desenvolvimento do computador hipotético NEANDER.

O conjunto de instruções do NEANDER e outras características do projeto podem ser consultadas na wiki oficial da UFRGS:
+ https://www.inf.ufrgs.br/arq/wiki/doku.php?id=neander
### Fonte bibliográfica:
WEBER, R. F. **Fundamentos de arquitetura de computadores.** 4. ed. Porto Alegre: Bookman, 2012. 424 p. (Série Livros Didáticos Informática UFRGS, v. 8). 
