/*******************************************************************************************
*
*   raylib FINAL PONG - Basic Game Structure
*    Developed by Daniel Gómez (Koocachookies)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
********************************************************************************************/

#include "raylib.h"
#include <stdlib.h>
#include <time.h>

typedef enum GameScreen { LOGO, TITLE, CONTROLS, GAMEPLAY, ENDING } GameScreen;

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 450;
    char windowTitle[30] = "Final Pong by Koo";
    
    GameScreen screen = LOGO;
	
	srand(time(NULL));
    
    // TODO: Define required variables here..........................(0.5p)
	
			//Logo Screen Variables
			
	Color logoColor = BROWN;
	logoColor.a = 0;
	
		//Title Screen Variables
	
	Color titleColor1 = RAYWHITE;
	Color titleColor2 = RAYWHITE;
	
	int fPosY = -80;
	int iPosY = -80;
	int n1PosY = -80;
	int aPosY = -80;
	int lPosY = -80;
	
	int pPosY = -80;
	int oPosY = -80;
	int n2PosY = -80;
	int gPosY = -80;
	
    // NOTE: Here there are some useful variables (should be initialized)
		//Gameplay Screen Variables
		
    int playerWidth = 20;
    int playerHeight = 60;
    int playerPosX = 30;
    int playerPosY = screenHeight / 2 - playerHeight / 2 + 20;
    int playerSpeedY = 4;
    
    int enemyWidth = 20;
    int enemyHeight = 60;
    int enemyPosX = screenWidth - 30 - enemyWidth;
    int enemyPosY =  screenHeight / 2 - enemyHeight / 2 + 20;
    int enemySpeedY = 4;
    
    float ballPosX = screenWidth / 2;
    float ballPosY = screenHeight / 2 + 20;
    float ballRadius = 10;
    float ballSpeedX = 0;
    float ballSpeedY = 0;
	int moveBall = 0;
	int goal = 0;
    
    int playerLife = 5;
    int enemyLife = 5;
	int playerBarHeight = 300;
	int enemyBarHeight = 300;
    
    int secondsCounter = 99;
    
    int framesCounter = 0;            // General purpose frames counter
    
    int gameResult = -1;        // 0 - Lose, 1 - Win, -1 - Draw
	int playResult = 0;
	int playMusic = 0;
	
	
	 // Pause saving variables
	 
	int pause = 0;
	int playerSpeedYP = 0;
	int enemySpeedYP = 0;
	int ballSpeedXP = 0;
	int ballSpeedYP = 0;
	int framesCounterP = 0;
    
    InitWindow(screenWidth, screenHeight, windowTitle);
    InitAudioDevice();
	
	Sound select = LoadSound("resources/select.wav");
	Sound start = LoadSound("resources/start.wav");
	Sound pauseon = LoadSound("resources/pauseon.wav");
	Sound pauseoff = LoadSound("resources/pauseoff.wav");
	Sound wall = LoadSound("resources/wall.wav");
	Sound kick = LoadSound("resources/kick.wav");
	Sound goalPlayer = LoadSound("resources/goalplayer.wav");
	Sound goalEnemy = LoadSound("resources/goalenemy.wav");
	Sound win = LoadSound("resources/win.wav");
	Sound lose = LoadSound("resources/lose.wav");
	Sound draw = LoadSound("resources/draw.wav");
	Sound titleMusic = LoadSound("resources/title.wav");
	Sound controlsMusic = LoadSound("resources/controls.wav");
	Sound gameplayMusic = LoadSound("resources/gameplay.wav");
	Sound resultMusic = LoadSound("resources/result.wav");
    
    // NOTE: If using textures, declare Texture2D variables here (after InitWindow)
	
	Texture2D logo = LoadTexture("resources/logo.png");
	Texture2D fondotitulo = LoadTexture("resources/fondotitulo.png");
	
    // NOTE: If using SpriteFonts, declare SpriteFont variables here (after InitWindow)
    
    SetTargetFPS(60);
	
    //--------------------------------------------------------------------------------------
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        switch(screen) 
        {
            case LOGO: 
            {
                // Update LOGO screen data here!
				// TODO: Logo fadeIn and fadeOut logic...............(0.5p)
				framesCounter++;
				
				if ((logoColor.a < 254) && (framesCounter > 60) && (framesCounter < 200)) logoColor.a += 2;
				else if ((logoColor.a > 0) && (framesCounter > 270)) logoColor.a -= 2;
				
				if (framesCounter > 400)
				{
					screen = TITLE;
					framesCounter = 0;
				}
                
            } break;
            case TITLE: 
            {
                // Update TITLE screen data here!
                
                // TODO: Title animation logic.......................(0.5p)
				framesCounter++;

				if (!playMusic)
				{
					PlaySound(titleMusic);
					playMusic = !playMusic;
				}
				
					//Title falls down
				if ((framesCounter > 10) && (fPosY < 100)) fPosY += 5;
				if ((framesCounter > 20) && (iPosY < 100)) iPosY += 5;
				if ((framesCounter > 30) && (n1PosY < 100)) n1PosY += 5;				
				if ((framesCounter > 40) && (aPosY < 100)) aPosY += 5;
				if ((framesCounter > 50) && (lPosY < 100)) lPosY += 5;

				if ((framesCounter > 60) && (pPosY < 100)) pPosY += 5;
				if ((framesCounter > 70) && (oPosY < 100)) oPosY += 5;
				if ((framesCounter > 80) && (n2PosY < 100)) n2PosY += 5;
				if ((framesCounter > 90) && (gPosY < 100)) gPosY += 5;
				
					//Title changes its color
				if (framesCounter  == 150)
				{
					titleColor1 = DARKBROWN;
					titleColor2 = DARKBROWN;
				}
				if (framesCounter == 155)
				{
					titleColor1 = BROWN;
					titleColor2 = BROWN;
				}
				
					//Title effect
					
				if (framesCounter > 180)
				{
					if ((framesCounter/15)%2)
					{
						titleColor1 = BROWN;
						titleColor2 = DARKBROWN;
					}
					else
					{
						titleColor1 = DARKBROWN;
						titleColor2 = BROWN;
					}
				}

                // TODO: "PRESS ENTER" logic.........................(0.5p)
                if (IsKeyPressed(KEY_ENTER))
				{
					screen = CONTROLS;
					framesCounter = 0;
					PlaySound(select);
					StopSound(titleMusic);
					playMusic = !playMusic;
				}
            } break;
			case CONTROLS: 
            {
                // Update CONTROLS screen data here!

				framesCounter++;
				
				if (!playMusic)
				{
					PlaySound(controlsMusic);
					playMusic = !playMusic;
				}
				
				if (IsKeyPressed(KEY_ENTER))
				{
					PlaySound(select);
					screen = GAMEPLAY;
					framesCounter = 0;
					StopSound(controlsMusic);
					playMusic = !playMusic;
				}
				else if (framesCounter > 390)
				{
					screen = GAMEPLAY;
					framesCounter = 0;
					StopSound(controlsMusic);
					playMusic = !playMusic;
				}
                
            } break;
            case GAMEPLAY:
            { 
                // Update GAMEPLAY screen data here!
				
				if (!playMusic)
				{
					PlaySound(gameplayMusic);
					playMusic = !playMusic;
				}

                // TODO: Ball movement logic.........................(0.2p)
				
				if ((IsKeyPressed(KEY_SPACE)) && (!moveBall))
				{
					while (ballSpeedX == 0) ballSpeedX = (-1 + rand() % 3) * 5;
					while (ballSpeedY == 0) ballSpeedY = (-1 + rand() % 3) * 5;
					moveBall = 1;
					goal = 0;
					PlaySound(start);
				}
				else
				{
					ballPosX += ballSpeedX;
					ballPosY += ballSpeedY;
				}
                
                // TODO: Player movement logic.......................(0.2p)
				
				if ((IsKeyDown(KEY_UP)) && (playerPosY >= 90)) playerPosY-= playerSpeedY;
				if ((IsKeyDown(KEY_DOWN)) && (playerPosY + playerHeight <= screenHeight - 30)) playerPosY += playerSpeedY;
                
                // TODO: Enemy movement logic (IA)...................(1p)
				
				if ((moveBall) && (ballPosX > 4 * screenWidth / 7))
				{
					if ((ballPosY < enemyPosY + enemyHeight / 2) && (enemyPosY >= 90) && (ballSpeedX > 0)) enemyPosY -= enemySpeedY;
					if ((ballPosY > enemyPosY + enemyHeight / 2) && (enemyPosY + enemyHeight <= screenHeight - 30) && (ballSpeedX > 0)) enemyPosY += enemySpeedY;
				}
				
                // TODO: Collision detection (ball-player) logic.....(0.5p)
				
				if ((ballPosX - ballRadius <= playerPosX + playerWidth) && (ballPosY + ballRadius >= playerPosY) && (ballPosY - ballRadius <= playerPosY + playerHeight))
				{
					ballSpeedX *= -1.1;
					PlaySound(kick);
				}
                
                // TODO: Collision detection (ball-enemy) logic......(0.5p)
				
				if ((ballPosX + ballRadius >= enemyPosX) && (ballPosY + ballRadius >= enemyPosY) && (ballPosY - ballRadius <= enemyPosY + enemyHeight))
				{
					ballSpeedX *= -1.1;
					PlaySound(kick);
				}
				
                // TODO: Collision detection (ball-limits) logic.....(1p)
				
				if ((ballPosY - ballRadius <= 85) || (ballPosY + ballRadius >= screenHeight - 25))
				{
					ballSpeedY *= -1;
					PlaySound(wall);
				}
				
				if (ballPosX - ballRadius <= 25) 
				{
					playerLife--;
					moveBall = 0;
					goal = 1;
					PlaySound(goalEnemy);
				}
				
				if (ballPosX + ballRadius >= screenWidth - 25)
				{
					enemyLife--;
					moveBall = 0;
					goal = 1;
					PlaySound(goalPlayer);
				}
				
                // TODO: Life bars decrease logic....................(1p)
				
				playerBarHeight = playerLife * 60;
				enemyBarHeight = enemyLife * 60;

                // TODO: Time counter logic..........................(0.2p)
				
				if ((moveBall) && (!pause))
				{
					framesCounter++;
					if (!(framesCounter % 60)) secondsCounter--;
				}

				// Reset in case of a goal
				
				if(!moveBall)
				{
					playerPosY = screenHeight / 2 - playerHeight / 2 + 20;
					enemyPosY = screenHeight / 2 - enemyHeight / 2 + 20;
					ballPosX = screenWidth / 2;
					ballPosY = screenHeight / 2 + 20;
					ballSpeedX = 0;
					ballSpeedY = 0;
				}
				
                // TODO: Game ending logic...........................(0.2p)
				
				if ((secondsCounter <= 0) || (playerLife == 0) || (enemyLife == 0))
				{
					if (playerLife > enemyLife) gameResult = 1;
					else if (playerLife < enemyLife) gameResult = 0;
					else gameResult = -1;
					
					StopSound(gameplayMusic);
					playMusic = !playMusic;
					playResult = !playResult;
					
					screen = ENDING;
					framesCounter = 0;
                }
                // TODO: Pause button logic..........................(0.2p)
				
				if (IsKeyPressed ('P') && (moveBall))
				{
					if (!pause)
					{
						playerSpeedYP = playerSpeedY;
						enemySpeedYP = enemySpeedY;
						ballSpeedXP = ballSpeedX;
						ballSpeedYP = ballSpeedY;
						framesCounterP = framesCounter;
						
						playerSpeedY = 0;
						enemySpeedY = 0;
						ballSpeedX = 0;
						ballSpeedY = 0;
						framesCounter = 0;
						
						PlaySound(pauseon);
						PauseSound(gameplayMusic);
					}
					else
					{
						playerSpeedY = playerSpeedYP;
						enemySpeedY = enemySpeedYP;
						ballSpeedX = ballSpeedXP;
						ballSpeedY = ballSpeedYP;
						framesCounter = framesCounter;
						
						PlaySound(pauseoff);
						PlaySound(gameplayMusic);
					}
					
					pause = !pause;
				}
                
            } break;
            case ENDING: 
            {
                // Update END screen data here!
				
				framesCounter++;
				
				if (!playMusic)
				{
					PlaySound(resultMusic);
					playMusic = !playMusic;
				}
                
                // TODO: Replay / Exit game logic....................(0.5p)
				
				if (playResult)
				{
					playResult = !playResult;
					
					if (gameResult == 1) PlaySound(win);
					else if (gameResult == 0) PlaySound(lose);
					else PlaySound(draw);
				}
				
				if (IsKeyPressed(KEY_ENTER))
				{
					playerPosY = screenHeight / 2 - playerHeight / 2 + 20;
					enemyPosY = screenHeight / 2 - enemyHeight / 2 + 20;
					ballPosX = screenWidth / 2;
					ballPosY = screenHeight / 2 + 20;
					ballSpeedX = 0;
					ballSpeedY = 0;
					playerLife= 5;
					enemyLife = 5;
					secondsCounter = 99;
					framesCounter = 0;
					screen = GAMEPLAY;
					moveBall = 0;
					PlaySound(select);
					
					StopSound(resultMusic);
					playMusic = !playMusic;
					
				}
                
            } break;
            default: break;
        }
        //----------------------------------------------------------------------------------
        
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        
            ClearBackground(BEIGE);
            
            switch(screen) 
            {
                case LOGO: 
                {
                    // Draw LOGO screen here!
                    
                    // TODO: Draw Logo...............................(0.2p)
					
					DrawTexture(logo, 170, 180, logoColor);
					DrawText("presents", 175, 230, 20, logoColor);
                    
                } break;
                case TITLE: 
                {
                    // Draw TITLE screen here!
					
					//ClearBackground(BEIGE);
					
					DrawTexture(fondotitulo, 0, 0, BEIGE);
                    
                    // TODO: Draw Title..............................(0.2p)
					DrawText("F", 160, fPosY, 80, titleColor1);
					DrawText("I", 215, iPosY, 80, titleColor2);
					DrawText("N", 250, n1PosY, 80, titleColor1);
					DrawText("A", 305, aPosY, 80, titleColor2);
					DrawText("L", 360, lPosY, 80, titleColor1);
					DrawText("P", 440, pPosY, 80, titleColor2);
					DrawText("O", 495, oPosY, 80, titleColor1);
					DrawText("N", 550, n2PosY, 80, titleColor2);
					DrawText("G", 605, gPosY, 80, titleColor1);
					
                    // TODO: Draw "PRESS ENTER" message..............(0.2p)

					if ((framesCounter > 180) && ((framesCounter/30)%2)) DrawText("PRESS ENTER", 300, 300, 30, DARKBROWN);
                    
                } break;
				case CONTROLS: 
				{
                    // Draw CONTROLS screen here!

					ClearBackground(DARKBROWN);
					
					DrawText("CONTROLS", screenWidth / 2 - 200, screenHeight / 2 - 60, 40, BROWN);
					DrawText("ARROW UP / DOWN - Player Movement", screenWidth / 2 - 200, screenHeight / 2 - 20, 20, BROWN);
					DrawText("P - Pause Game", screenWidth / 2 - 200, screenHeight / 2 + 10, 20, BROWN);
					DrawText("ESC - Exit Game", screenWidth / 2 - 200, screenHeight / 2 + 40, 20, BROWN);
					
					
				} break;
                case GAMEPLAY:
                { 
                    // Draw GAMEPLAY screen here!
					
					ClearBackground(BEIGE);
					
					// Draw "battlefield"
					
					DrawRectangle(20, 80, screenWidth - 40, screenHeight - 100, BROWN);
					DrawRectangle(25, 85, screenWidth - 50, screenHeight - 110, BEIGE);
					DrawRectangle(screenWidth / 2 - 2, 85, 4, screenHeight - 110, BROWN);
					
					// Draw ball
                    
					DrawCircle(ballPosX,ballPosY,ballRadius, DARKBROWN);
					
                    // TODO: Draw player and enemy...................(0.2p)
					
					DrawRectangle(playerPosX, playerPosY, playerWidth, playerHeight, DARKBROWN);
					DrawRectangle(enemyPosX, enemyPosY, enemyWidth, enemyHeight, DARKBROWN);
                    
                    // TODO: Draw player and enemy life bars.........(0.5p)
					
					DrawRectangle(screenWidth / 2 - 30 - playerBarHeight, 30, playerBarHeight, 20, DARKBROWN);
					DrawRectangle(screenWidth / 2 + 30, 30, enemyBarHeight, 20, DARKBROWN);
					
					// Draw Goal Message
					
					if (goal) DrawText("GOAL", screenWidth / 2 - MeasureText("GOAL", 60) / 2, screenHeight / 2 - 60, 60, DARKBROWN);
					
					// Draw Press Space Message
					
					if (!moveBall) DrawText("PRESS SPACE BAR TO START", screenWidth / 2 - MeasureText("PRESS SPACE BAR TO START", 20) / 2, screenHeight / 2 + 60, 20, DARKBROWN);
                    
                    // TODO: Draw time counter.......................(0.5p)
					
					if (secondsCounter > 9) DrawText(FormatText("%i", secondsCounter), screenWidth/2 - 22, 20, 40, BROWN);
					else DrawText(FormatText("0%i", secondsCounter), screenWidth/2 - 22, 20, 40, BROWN);
                    
                    // TODO: Draw pause message when required........(0.5p)
					
					if (pause) DrawText("PAUSE", screenWidth / 2 - MeasureText("PAUSE", 60) / 2, screenHeight / 2 - 60, 60, DARKBROWN);
                    
                } break;
                case ENDING: 
                {
                    // Draw END screen here!
					
					ClearBackground(DARKBROWN);
                    
					// TODO: Draw ending message (win or loose)......(0.2p)
					
					if (secondsCounter <= 0)
					{
						DrawText("TIME UP!", screenWidth / 2 - MeasureText("TIME UP!", 60) / 2, screenHeight / 2 - 40, 60, BROWN);
						if (gameResult == 0) DrawText("AND YOU COULDN'T BEAT YOUR ENEMY", screenWidth / 2 - MeasureText("AND YOU COULDN'T BEAT YOUR ENEMY", 20) / 2, screenHeight / 2 + 40, 20, BROWN);
						else if (gameResult == 1) DrawText("ANYWAY... YOU WON!", screenWidth / 2 - MeasureText("ANYWAY... YOU WON!", 20) / 2, screenHeight / 2 + 40, 20, BROWN);
						else DrawText("BOTH OF YOU ARE EQUALLY GREAT (OR BOTH OF YOU EQUALLY SUCK)", screenWidth / 2 - MeasureText("BOTH OF YOU ARE EQUALLY GREAT (OR BOTH OF YOU EQUALLY SUCK)", 20) / 2, screenHeight / 2 + 40, 20, BROWN);
					}
                    else
					{
						if (gameResult == 0)
						{
							DrawText("YOU LOSE!", screenWidth / 2 - MeasureText("YOU LOSE!", 60) / 2, screenHeight / 2 - 50, 60, BROWN);
							DrawText("YOU WERE HUMILIATED BY YOU ENEMY", screenWidth / 2 - MeasureText("YOU WERE HUMILIATED BY YOU ENEMY", 20) / 2, screenHeight / 2 + 40, 20, BROWN);
						}
						else if (gameResult == 1)
						{
							DrawText("YOU WIN!", screenWidth / 2 - MeasureText("YOU WIN!", 60) / 2, screenHeight / 2 - 40, 60, BROWN);
							DrawText("YOU DESTROYED YOUR ENEMY'S REPUTATION", screenWidth / 2 - MeasureText("YOU DESTROYED YOUR ENEMY'S REPUTATION", 20) / 2, screenHeight / 2 + 40, 20, BROWN);
						}
						else //impossible
						{
							DrawText("DRAW!", screenWidth / 2 - MeasureText("DRAW!", 60) / 2, screenHeight / 2 - 30, 60, BROWN);
							DrawText("BUT NONE OF YOU COULD ERASE HIS OPPONENT", screenWidth / 2 - MeasureText("BUT NONE OF YOU COULD ERASE HIS OPPONENT", 20) / 2, screenHeight / 2 + 40, 20, BROWN);
						}
					}
					
					DrawText("Press Enter To Play Again :D or Escape To Exit the Game :(", screenWidth / 2 - MeasureText("Press Enter To Play Again :D or Escape To Exit the Game :(", 10) / 2, screenHeight / 2 + 80, 10, BROWN);
					
                } break;
                default: break;
            }
        
            //DrawFPS(10, 10);
        
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    
    // NOTE: Unload any Texture2D or SpriteFont loaded here
	
	UnloadSound(wall);
	UnloadSound(kick);
	UnloadSound(goalPlayer);
	UnloadSound(goalEnemy);
	UnloadSound(win);
	UnloadSound(lose);
	UnloadSound(draw);
	UnloadSound(select);
	UnloadSound(start);
	UnloadSound(pauseon);
	UnloadSound(pauseoff);
	UnloadSound(titleMusic);
	UnloadSound(controlsMusic);
	UnloadSound(gameplayMusic);
	UnloadSound(resultMusic);
	
	UnloadTexture(logo);
	UnloadTexture(fondotitulo);
    
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    
    return 0;
}