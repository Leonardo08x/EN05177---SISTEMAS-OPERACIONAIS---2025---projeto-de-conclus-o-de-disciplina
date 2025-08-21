# Visão Geral do Projeto: Jogo da Forca com Threads e Semáforos

Este projeto é uma implementação do clássico jogo da forca, desenvolvido para a disciplina de Sistemas Operacionais da FACOMP/ICEN/UFPA. O objetivo principal é demonstrar o uso de threads e semáforos para gerenciar o fluxo do jogo, garantindo a sincronização e a comunicação entre diferentes partes do código.

## Integrantes do Grupo

    ALESSANDRO REALI LOPES SILVA

    JHONATA BEZERRA FIGUEIREDO

    LEONARDO CUNHA DA ROCHA

    MATHEUS DE SOUSA DINIZ

## Estrutura do Código

### O projeto é dividido em três arquivos principais, cada um com uma responsabilidade específica:

1. `__main.c__`: O módulo principal que inicializa o jogo. Ele é responsável por:

* Criar e inicializar os semáforos (sem_word, sem_input, sem_check), que controlam a ordem de execução das threads.

* Criar três threads (`t_word, t_input, t_check`), cada uma executando uma função vital do jogo.

* Esperar o término das threads e destruir os semáforos, garantindo a liberação adequada dos recursos.

2. `__main-voids.c__`: Este arquivo contém as principais funções do jogo, executadas por cada uma das threads:

* `choose_word()`: Permite que o jogador insira a palavra secreta e inicializa o display do jogo.

* `input_letter()`: Gerencia a entrada de letras pelo jogador, esperando a permissão do semáforo antes de solicitar a letra.

* `check_letter()`: Verifica se a letra inserida está correta, atualiza o estado do jogo (ex: attempts_left) e checa as condições de vitória ou derrota.

3. `__utils__`: Uma pasta que armazena arquivos com funções e variáveis auxiliares, separando-as do fluxo principal da lógica.

* `util-variables.c`: Armazena variáveis globais essenciais para o jogo, como os semáforos, o número de tentativas e a palavra secreta.

* `util-desenha-forca.c`: Contém a função responsável por imprimir o desenho da forca no console, de acordo com o número de tentativas restantes.

### Como as Threads e Semáforos Funcionam

O projeto utiliza um modelo de produtor-consumidor para a comunicação entre as threads, orquestrado pelos semáforos:

* `__sem_word__`: Inicia com valor 1, permitindo que a thread choose_word comece. Após a escolha da palavra, ela libera a thread de input_letter.

* `__sem_input__`: Inicia bloqueado (valor 0). A thread input_letter só pode prosseguir quando o semáforo é liberado, seja pela thread de escolha da palavra ou pela thread de checagem.

* `__sem_check__`: Inicia bloqueado (valor 0). A thread check_letter só pode prosseguir quando uma letra é inserida e o semáforo é liberado pela thread de entrada.

Essa abordagem garante que as ações ocorram em uma sequência lógica: primeiro, a escolha da palavra; depois, a inserção e checagem de letras em um ciclo contínuo até o fim do jogo.

