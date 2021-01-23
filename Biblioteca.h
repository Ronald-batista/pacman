void IniciarNcurses();

void manual();

void MapaConfig(int *altura, int *largura);

char **ConstruirMapa(int *altura, int *largura);

void ConstruirObstaculos(char **mapa);

void Pastilhas (char **mapa);

void AdicionarPacman(char **mapa, int *PosLIN_Pac,int *PosCOL_Pac );

void MostrarMapa(char **mapa, int *altura, int *largura, int *pontos, int *vida );

void MoverPacman(char **mapa, int *pacman_Direcao, int *pacman_PosLIN, int *PosCOL_Pac, int *pontos, int *vida, int *Blinky_Status, int *Pinky_Status, int *Inky_Status, int *Clyde_Status);

void MudarDirecaoPacman(int *pacman_Direcao, int key);

void MoverBlinky(char **mapa, int *PosL_Blinky, int *PosC_Blinky,int *pacman_PosLIN, int *pacman_PosCOL);

void MoverPinky(char **mapa, int *PosL_Pinky, int *PosC_Pinky,int pacman_PosLIN, int pacman_PosCOL, int pacman_Direcao);

void MoverInky(char **mapa, int PosL_Blinky, int PosC_Blinky,int pacman_PosLIN, int pacman_PosCOL, int *PosL_Inky,  int *PosC_Inky);

void MoverClyde(char **mapa, int *PosL_Clyde, int *PosC_Clyde,int *pacman_PosLIN, int *pacman_PosCOL);

void Fugir(char **mapa, int *PosL_Fantasma, int *PosC_Fantasma, int *Fantasma_Status, char padrao);