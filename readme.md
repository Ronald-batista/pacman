# Game baseado no Pacman classico desenvolvido em C

### O jogo foi desenvolvido para a disciplina CI1001 - Programação 1 - na UFPR.

## Tela de instruções
![Tela de instruções](https://uploaddeimagens.com.br/images/003/049/643/original/tela-instrucoes.PNG?1611418735)

## Tela de Jogo
![Tela do game](https://uploaddeimagens.com.br/images/003/049/644/full/tela-game.PNG?1611418786)


## Como compilar e executar?
  
#### _OBS: Para compilar é necessario ter o compilador GCC e a biblioteca ncurses_

### Instalar GCC no linux Debian/Ubuntu
#### sudo apt update
#### sudo apt install build-essential 

### Instalar biblioteca Ncurses no Debian/Ubuntu
#### sudo apt-get install libncurses5-dev libncursesw5-dev
  
### Compilar
#### gcc -o Pacman Pacman.c -lncurses
