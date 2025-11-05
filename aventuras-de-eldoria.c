#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char nome[50];
    int vida;
    int vida_maxima;
    int ataque;
    int defesa;
    int nivel;
    int experiencia;
    int ouro;
    int pocoes;
} Jogador;

typedef struct {
    char nome[50];
    int vida;
    int ataque;
    int defesa;
    int exp_reward;
    int ouro_reward;
} Inimigo;

void limparTela();
void pausar();
void exibirTitulo();
void exibirMenu();
void iniciarNovoJogo(Jogador *jogador);
void exibirStatus(Jogador *jogador);
void explorar(Jogador *jogador);
void combate(Jogador *jogador, Inimigo *inimigo);
void usarPocao(Jogador *jogador);
void subirNivel(Jogador *jogador);
void loja(Jogador *jogador);
void salvarJogo(Jogador *jogador);
int carregarJogo(Jogador *jogador);
Inimigo criarInimigo(int nivel_jogador);

int main() {
    srand(time(NULL));
    
    Jogador jogador;
    int opcao;
    int jogo_carregado = 0;
    
    while(1) {
        exibirTitulo();
        exibirMenu();
        
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();
        
        switch(opcao) {
            case 1:
                iniciarNovoJogo(&jogador);
                jogo_carregado = 1;
                break;
                
            case 2:
                if(carregarJogo(&jogador)) {
                    printf("\nJogo carregado com sucesso!\n");
                    jogo_carregado = 1;
                    pausar();
                } else {
                    printf("\nNenhum jogo salvo encontrado!\n");
                    pausar();
                }
                break;
                
            case 3:
                if(!jogo_carregado) {
                    printf("\nVoce precisa iniciar ou carregar um jogo primeiro!\n");
                    pausar();
                    break;
                }
                
                int continuar = 1;
                while(continuar) {
                    limparTela();
                    exibirStatus(&jogador);
                    
                    printf("\n=== MENU DE ACOES ===\n");
                    printf("1. Explorar (encontrar inimigos)\n");
                    printf("2. Usar Pocao de Vida\n");
                    printf("3. Visitar Loja\n");
                    printf("4. Salvar Jogo\n");
                    printf("5. Voltar ao Menu Principal\n");
                    printf("\nEscolha: ");
                    
                    int acao;
                    scanf("%d", &acao);
                    getchar();
                    
                    switch(acao) {
                        case 1:
                            explorar(&jogador);
                            break;
                        case 2:
                            usarPocao(&jogador);
                            pausar();
                            break;
                        case 3:
                            loja(&jogador);
                            break;
                        case 4:
                            salvarJogo(&jogador);
                            pausar();
                            break;
                        case 5:
                            continuar = 0;
                            break;
                        default:
                            printf("\nOpcao invalida!\n");
                            pausar();
                    }
                    
                    if(jogador.vida <= 0) {
                        printf("\nGAME OVER! Voce foi derrotado!\n");
                        printf("Seu progresso foi perdido...\n");
                        jogo_carregado = 0;
                        pausar();
                        break;
                    }
                }
                break;
                
            case 4:
                printf("\nObrigado por jogar! Ate a proxima aventura!\n");
                return 0;
                
            default:
                printf("\nOpcao invalida!\n");
                pausar();
        }
    }
    
    return 0;
}

void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pausar() {
    printf("\nPressione ENTER para continuar...");
    getchar();
}

void exibirTitulo() {
    limparTela();
    printf("========================================\n");
    printf("     AVENTURAS DE ELDORIA\n");
    printf("     RPG de Aventura em Turnos\n");
    printf("========================================\n");
}

void exibirMenu() {
    printf("\n=== MENU PRINCIPAL ===\n");
    printf("1. Novo Jogo\n");
    printf("2. Carregar Jogo\n");
    printf("3. Jogar\n");
    printf("4. Sair\n\n");
}

void iniciarNovoJogo(Jogador *jogador) {
    limparTela();
    printf("=== CRIAR PERSONAGEM ===\n\n");
    
    printf("Digite o nome do seu heroi: ");
    fgets(jogador->nome, 50, stdin);
    jogador->nome[strcspn(jogador->nome, "\n")] = 0;
    
    jogador->vida = 100;
    jogador->vida_maxima = 100;
    jogador->ataque = 15;
    jogador->defesa = 10;
    jogador->nivel = 1;
    jogador->experiencia = 0;
    jogador->ouro = 50;
    jogador->pocoes = 3;
    
    printf("\nPersonagem criado com sucesso!\n");
    printf("Bem-vindo ao mundo de Eldoria, %s!\n", jogador->nome);
    pausar();
}

void exibirStatus(Jogador *jogador) {
    printf("\n========================================\n");
    printf(" Heroi: %s\n", jogador->nome);
    printf(" Nivel: %d | Exp: %d\n", jogador->nivel, jogador->experiencia);
    printf(" Vida: %d/%d | Ouro: %d\n", 
           jogador->vida, jogador->vida_maxima, jogador->ouro);
    printf(" Ataque: %d | Defesa: %d\n", 
           jogador->ataque, jogador->defesa);
    printf(" Pocoes: %d\n", jogador->pocoes);
    printf("========================================\n");
}

Inimigo criarInimigo(int nivel_jogador) {
    Inimigo inimigo;
    
    char *nomes[] = {
        "Goblin", "Lobo Selvagem", "Esqueleto", "Orc",
        "Bandido", "Aranha Gigante", "Zumbi", "Troll"
    };
    
    int indice = rand() % 8;
    strcpy(inimigo.nome, nomes[indice]);
    
    inimigo.vida = 30 + (nivel_jogador * 10);
    inimigo.ataque = 8 + (nivel_jogador * 3);
    inimigo.defesa = 5 + (nivel_jogador * 2);
    inimigo.exp_reward = 20 + (nivel_jogador * 5);
    inimigo.ouro_reward = 10 + (nivel_jogador * 5);
    
    return inimigo;
}

void explorar(Jogador *jogador) {
    limparTela();
    printf("\nVoce explora os arredores...\n");
    pausar();
    
    Inimigo inimigo = criarInimigo(jogador->nivel);
    
    printf("\nUm %s apareceu!\n", inimigo.nome);
    pausar();
    
    combate(jogador, &inimigo);
}

void combate(Jogador *jogador, Inimigo *inimigo) {
    printf("\n=== COMBATE INICIADO ===\n");
    
    while(jogador->vida > 0 && inimigo->vida > 0) {
        limparTela();
        printf("\n=== COMBATE ===\n");
        printf("\n%s\n", jogador->nome);
        printf("Vida: %d/%d\n", jogador->vida, jogador->vida_maxima);
        
        printf("\nVS\n");
        
        printf("\n%s\n", inimigo->nome);
        printf("Vida: %d\n", inimigo->vida);
        
        printf("\n1. Atacar\n");
        printf("2. Usar Pocao\n");
        printf("3. Tentar Fugir\n");
        printf("\nEscolha: ");
        
        int acao;
        scanf("%d", &acao);
        getchar();
        
        if(acao == 1) {
            int dano = jogador->ataque - inimigo->defesa;
            if(dano < 1) dano = 1;
            
            inimigo->vida -= dano;
            printf("\nVoce causou %d de dano!\n", dano);
            
            if(inimigo->vida <= 0) {
                printf("\nVoce derrotou o %s!\n", inimigo->nome);
                jogador->experiencia += inimigo->exp_reward;
                jogador->ouro += inimigo->ouro_reward;
                printf("+ %d EXP | + %d Ouro\n", 
                       inimigo->exp_reward, inimigo->ouro_reward);
                
                if(jogador->experiencia >= jogador->nivel * 100) {
                    subirNivel(jogador);
                }
                
                pausar();
                return;
            }
            
        } else if(acao == 2) {
            usarPocao(jogador);
            
        } else if(acao == 3) {
            int chance = rand() % 100;
            if(chance < 50) {
                printf("\nVoce conseguiu fugir!\n");
                pausar();
                return;
            } else {
                printf("\nNao conseguiu fugir!\n");
            }
        }
        
        if(inimigo->vida > 0) {
            int dano_inimigo = inimigo->ataque - jogador->defesa;
            if(dano_inimigo < 1) dano_inimigo = 1;
            
            jogador->vida -= dano_inimigo;
            printf("O %s causou %d de dano!\n", inimigo->nome, dano_inimigo);
            pausar();
        }
    }
}

void usarPocao(Jogador *jogador) {
    if(jogador->pocoes <= 0) {
        printf("\nVoce nao tem pocoes!\n");
        return;
    }
    
    if(jogador->vida >= jogador->vida_maxima) {
        printf("\nSua vida ja esta cheia!\n");
        return;
    }
    
    int cura = 40;
    jogador->vida += cura;
    if(jogador->vida > jogador->vida_maxima) {
        jogador->vida = jogador->vida_maxima;
    }
    
    jogador->pocoes--;
    printf("\nVoce usou uma pocao e recuperou %d de vida!\n", cura);
}

void subirNivel(Jogador *jogador) {
    jogador->nivel++;
    jogador->vida_maxima += 20;
    jogador->vida = jogador->vida_maxima;
    jogador->ataque += 5;
    jogador->defesa += 3;
    jogador->experiencia = 0;
    
    printf("\nLEVEL UP!\n");
    printf("Voce alcancou o nivel %d!\n", jogador->nivel);
    printf("+ 20 Vida Maxima\n");
    printf("+ 5 Ataque\n");
    printf("+ 3 Defesa\n");
    printf("Vida totalmente restaurada!\n");
    pausar();
}

void loja(Jogador *jogador) {
    limparTela();
    printf("\n=== LOJA DO MERCADOR ===\n");
    printf("\nBem-vindo, %s!\n", jogador->nome);
    printf("Seu ouro: %d\n", jogador->ouro);
    
    printf("\n1. Pocao de Vida (+40 HP) - 25 Ouro\n");
    printf("2. Aumentar Ataque (+3) - 50 Ouro\n");
    printf("3. Aumentar Defesa (+2) - 50 Ouro\n");
    printf("4. Sair\n");
    printf("\nEscolha: ");
    
    int opcao;
    scanf("%d", &opcao);
    getchar();
    
    switch(opcao) {
        case 1:
            if(jogador->ouro >= 25) {
                jogador->ouro -= 25;
                jogador->pocoes++;
                printf("\nVoce comprou uma Pocao de Vida!\n");
            } else {
                printf("\nOuro insuficiente!\n");
            }
            break;
            
        case 2:
            if(jogador->ouro >= 50) {
                jogador->ouro -= 50;
                jogador->ataque += 3;
                printf("\nSeu ataque aumentou!\n");
            } else {
                printf("\nOuro insuficiente!\n");
            }
            break;
            
        case 3:
            if(jogador->ouro >= 50) {
                jogador->ouro -= 50;
                jogador->defesa += 2;
                printf("\nSua defesa aumentou!\n");
            } else {
                printf("\nOuro insuficiente!\n");
            }
            break;
    }
    
    pausar();
}

void salvarJogo(Jogador *jogador) {
    FILE *arquivo = fopen("savegame.dat", "wb");
    
    if(arquivo == NULL) {
        printf("\nErro ao salvar o jogo!\n");
        return;
    }
    
    fwrite(jogador, sizeof(Jogador), 1, arquivo);
    fclose(arquivo);
    
    printf("\nJogo salvo com sucesso!\n");
}

int carregarJogo(Jogador *jogador) {
    FILE *arquivo = fopen("savegame.dat", "rb");
    
    if(arquivo == NULL) {
        return 0;
    }
    
    fread(jogador, sizeof(Jogador), 1, arquivo);
    fclose(arquivo);
    
    return 1;
}
