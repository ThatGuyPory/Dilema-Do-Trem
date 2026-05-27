#include "raylib.h"

typedef enum GameScreen {INICIO, GAMEPLAY} GameScreen;

    Vector2 tremPos = {0, 200};

    Rectangle tremHitbox = {120,420,220,200};

    // Definição de l1 e l2 (os alvos), posi.
    Vector2 l1Pos = { 1000, 250 };
    Vector2 l2Pos = { 1000, 475 };
    float alvosRaio = 40.0f;

    // Movimento inicial inativo, e alvos ativos.
    bool emMovimento = false;
    bool l1Ativo = true;
    bool l2Ativo = true;

int main() {
    // Tamanho da tela em pixels.
    InitWindow(1200, 900, "Dilema do Trem");
    // Imagem do trem, e do Nick
    Texture2D tremTexture = LoadTexture("François_o_trem-.png");
    Texture2D nickTexture = LoadTexture("Nick Stick Man Filho.png");
    SetTargetFPS(90);

    //Começa no "Menu" (INICIO).
    GameScreen currentScreen = INICIO;

    //Eventos que ocorrem enquanto o jogo está rodando.
    while (!WindowShouldClose()) {

    switch(currentScreen) {
    case INICIO: {

                // Pressionar Space para ir para a tela de Gameplay.
                if (IsKeyPressed(KEY_SPACE)) {
                    currentScreen = GAMEPLAY;
                }
        }   break;

    // Responsavel pelas funções do jogo em si.
    case GAMEPLAY:  {

        // Definindo a colisão de um retangulo(Rec), com um circulo(circle).
        bool colisaoL1 = CheckCollisionCircleRec(l1Pos, alvosRaio, tremHitbox);
        bool colisaoL2 = CheckCollisionCircleRec(l2Pos, alvosRaio, tremHitbox);

        // Ativa o movimento, e alinha(posiçao Y - altura do trem)
        // Se pressionar pra cima
        if (IsKeyPressed(KEY_UP)) {
            tremPos.y = 110;
            tremHitbox.y = 230;     // Alinha com o trilho 1
            emMovimento = true;
        }
        // Se pressionar pra baixo
        else if (IsKeyPressed(KEY_DOWN)) {
            tremPos.y = 330;
            tremHitbox.y = 510;     // Alinha com o trilho 2
            emMovimento = true;
        }

        // Velocidade quando em movimento
        if (emMovimento) {
            tremPos.x += 5;
            tremHitbox.x += 5;
        }

        // Reinicia se o Enter for pressionado
        if (IsKeyPressed(KEY_ENTER)) {
            emMovimento = false;
            l1Ativo = true;
            l2Ativo = true;
            tremPos.x = 0;
            tremPos.y = 200;

            tremHitbox.x = 120;
            tremHitbox.y = 420;;
        }

        // Desativa quando ocorre a colisão.
        if (l1Ativo && colisaoL1) {
            l1Ativo = false;
        }

        if (l2Ativo && colisaoL2) {
            l2Ativo = false;
        }

        } break;
    }

        // Responsável pelo que aparece na tela.
        BeginDrawing();
            ClearBackground(GRAY);

            switch(currentScreen){  
            
            case INICIO: {
            DrawText("MENU", 20, 20, 40, WHITE);
            DrawText("Pressione espaço para iniciar o jogo", 370, 320, 25, WHITE);
            } break;

            case GAMEPLAY:  {

            DrawText("Aperte CIMA ou BAIXO para mover o trem!", 400, 20, 20, WHITE);
            DrawText("Aperte Enter para reiniciar.", 470, 60, 20, WHITE);

            if (l1Ativo) DrawTextureEx(nickTexture,l1Pos,0.0f,0.15f,WHITE);
            if (l2Ativo) DrawTextureEx(nickTexture,l2Pos,0.5f,0.15f,WHITE);

            DrawTextureEx(tremTexture, tremPos, 0.0f, 0.9f, WHITE);
            } break;
            default: break;
            }

        EndDrawing();
    }


    CloseWindow();
    return 0;
}
