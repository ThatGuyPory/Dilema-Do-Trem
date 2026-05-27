#include "raylib.h"   // Importa a biblioteca Raylib, essencial para criar a janela, renderizar gráficos e capturar teclado.
#include <stdlib.h>   // Importa a biblioteca padrão, usada aqui para a função rand() que gera escolhas aleatórias.

int main(void) {      // Início da função principal, onde o jogo começa a ser executado.
    
    // Inicializa a janela do jogo com largura (800), altura (450) e o título que aparecerá na barra superior.
    InitWindow(800, 450, "O Dilema do Trem - Raylib"); 
    
    SetTargetFPS(60); // Crava o jogo em 60 quadros por segundo (FPS), garantindo que ele rode na mesma velocidade em qualquer computador.

    int tempo_limite = 5;         // Define o tempo que o jogador tem para tomar a decisão (5 segundos).
    int escolha = -1;             // Guarda a decisão do jogador. Começa em -1 (nenhuma decisão). Usaremos 0 para "tempo esgotado".
    bool jogo_finalizado = false; // Variável de estado (verdadeiro/falso) para saber se a fase de escolha já acabou.
    
    double tempo_inicio = GetTime(); // Captura o tempo exato (em segundos) em que o jogo começou usando a função da Raylib.

    // O "Game Loop": este laço de repetição roda continuamente, 60 vezes por segundo, até o jogador fechar a janela.
    while (!WindowShouldClose()) { 
        
        // --- LÓGICA DE ATUALIZAÇÃO (O que acontece por trás dos panos) ---
        
        // Calcula quanto tempo se passou subtraindo o tempo atual contínuo do tempo em que o jogo abriu.
        double tempo_passado = GetTime() - tempo_inicio; 
        
        // Calcula quanto tempo sobra para o jogador, convertendo o resultado para número inteiro.
        int tempo_restante = tempo_limite - (int)tempo_passado; 

        if (!jogo_finalizado) { // Verifica se o jogo AINDA NÃO acabou para continuar processando cliques ou cronômetro.
            
            if (tempo_restante <= 0) { // Se o relógio zerar (ou ficar negativo)...
                escolha = 0;           // Define a escolha como 0 (nossa marcação para quando o tempo esgota).
                jogo_finalizado = true; // Altera o estado do jogo para finalizado, travando novas escolhas.
            } 
            else if (IsKeyPressed(KEY_ONE)) { // A Raylib verifica se o jogador apertou a tecla '1' neste exato frame...
                escolha = 1;                  // Registra a escolha como Trilho 1.
                jogo_finalizado = true;       // Encerra a fase de decisão.
            } 
            else if (IsKeyPressed(KEY_TWO)) { // Verifica se o jogador apertou a tecla '2'...
                escolha = 2;                  // Registra a escolha como Trilho 2.
                jogo_finalizado = true;       // Encerra a fase de decisão.
            }
        }

        // --- LÓGICA DE DESENHO (O que o jogador realmente vê na tela) ---
        
        BeginDrawing(); // Avisa a placa de vídeo que vamos começar a desenhar as coisas neste quadro.
        
        ClearBackground(RAYWHITE); // Pinta a tela inteira de branco, limpando os desenhos do quadro do milissegundo anterior.

        // Desenha o título do jogo na posição X=250, Y=20, com tamanho de fonte 30 e cor cinza escuro.
        DrawText("--- O DILEMA DO TREM ---", 250, 20, 30, DARKGRAY); 

        if (!jogo_finalizado) { // Se o jogador ainda estiver no momento de decidir, desenha as instruções:
            DrawText("O trem perdeu os freios e esta em alta velocidade!", 50, 80, 20, BLACK); // História.
            DrawText("Trilho 1: Pessoas BOAS estao amarradas.", 50, 130, 20, BLUE);           // Opção 1 (Azul).
            DrawText("Trilho 2: Pessoas RUINS estao amarradas.", 50, 170, 20, RED);             // Opção 2 (Vermelho).
            
            // TextFormat formata texto dinâmico (igual o printf). O resultado do cronômetro é desenhado em roxo.
            DrawText(TextFormat("Tempo restante: %d segundos", tempo_restante), 50, 230, 25, PURPLE); 
            DrawText("Aperte '1' ou '2' no teclado!", 50, 280, 20, DARKGRAY); // Comando para o jogador.
        } 
        else { // Se o jogo já acabou (por tempo ou porque o jogador escolheu), desenhamos a tela de desfecho:
            
            if (escolha == 0) { // Se a escolha é 0, o tempo acabou.
                DrawText("TEMPO ESGOTADO! Voce hesitou demais...", 50, 80, 25, RED); // Aviso de lentidão.
                
                int escolha_trem = (rand() % 2) + 1; // Sorteia 1 ou 2 para simular o "piloto automático" do trem.
                DrawText(TextFormat("O trem mudou sozinho para o Trilho %d.", escolha_trem), 50, 130, 20, BLACK); // Avisa o trilho sorteado.
                
                if (escolha_trem == 1) DrawText("Pessoas boas foram atingidas. Tragedia...", 50, 180, 20, BLUE); // Texto se o trem foi pro 1.
                else DrawText("Pessoas ruins atingidas. O mundo esta mais seguro...", 50, 180, 20, RED); // Texto se o trem foi pro 2.
            } 
            else if (escolha == 1) { // Se o jogador escolheu ativamente o Trilho 1.
                DrawText("RESULTADO: Voce direcionou para o Trilho 1.", 50, 80, 25, BLACK); 
                DrawText("As pessoas boas foram atingidas. Uma tragedia terrivel ocorreu.", 50, 130, 20, BLUE); 
            } 
            else if (escolha == 2) { // Se o jogador escolheu ativamente o Trilho 2.
                DrawText("RESULTADO: Voce direcionou para o Trilho 2.", 50, 80, 25, BLACK); 
                DrawText("As pessoas ruins foram atingidas. Um dilema moral pesado...", 50, 130, 20, RED); 
            }
            
            DrawText("Pressione ESC para fechar o jogo.", 50, 350, 20, DARKGRAY); // Informa como sair.
        }

        EndDrawing(); // Finaliza a montagem desta tela e envia para o seu monitor.
    }                 // Volta lá para cima no 'while' para começar o ciclo tudo de novo (60x por segundo).

    CloseWindow();    // O jogador apertou ESC ou fechou a aba. Essa linha destrói a janela e libera a memória do PC.
    
    return 0;         // Retorna 0 para o sistema operacional, informando que rodou e fechou com sucesso.
}                     // Fim do arquivo de código.
