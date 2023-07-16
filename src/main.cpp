#include <MeusH/libs.h>
#include <string.h>
#include <stdlib.h>
#include <cmath>
#include <iostream>


// settings
GLFWwindow* window;
unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;
//luz
float incremento = 0.01;
glm::vec3 lightPos = glm::vec3(-1, 5, 0);
//animacao chegada
float counter = 0;
//player pos
int playerX = 4;
int playerY = 7;
float pauseMove = 0.0;
bool shouldPause = false;
//
float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame
//
// camera
Camera camera(glm::vec3(1.5f, 12, 20), glm::vec3( 0.0169991f, 0.90824f, -0.418104f), glm::vec3(0.0f, 0.0f, -1.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
//mapa de colisao
std::vector<std::vector<int>> createMatrix(int size) {
    std::vector<std::vector<int>> matrix(size, std::vector<int>(size, 0));
    return matrix;
}
std::vector<std::vector<int>> mapaColisao = createMatrix(8);
void startarMapaColisao(){
      mapaColisao[0][0] = 2;
      mapaColisao[0][7] = 1;
      //linha 2
      mapaColisao[1][1] = 1;
      mapaColisao[1][2] = 1;
      mapaColisao[1][3] = 1;
      mapaColisao[1][4] = 1;
      mapaColisao[1][5] = 1;
      //linha 3
      mapaColisao[2][4] = 1;
      mapaColisao[2][5] = 1;
      mapaColisao[2][6] = 1;
      //linha 4
      mapaColisao[3][0] = 1;
      mapaColisao[3][1] = 1;
      mapaColisao[3][2] = 1;
      mapaColisao[3][3] = 1;
      //linha 5
      mapaColisao[4][3] = 1;
      mapaColisao[4][4] = 1;
      mapaColisao[4][6] = 1;
      mapaColisao[4][7] = 1;
      //linha 6
      mapaColisao[5][0] = 1;
      mapaColisao[5][1] = 1;
      //linha 7
      mapaColisao[6][3] = 1;
      mapaColisao[6][4] = 1;
      mapaColisao[6][5] = 1;
      mapaColisao[6][7] = 1;
      //linha 8
      mapaColisao[7][0] = 1;
      mapaColisao[7][1] = 1;
      mapaColisao[7][3] = 1;
      mapaColisao[7][7] = 1;
}
//enums
enum MODELO{
    PLAYER_MODEL,
    CHEGADA_MODEL,
    FLOOR_MODEL,
    WALL_MODEL
};
enum TEXTURA{
    PLAYER_TEX,
    WALL_TEX,
    FLOOR_TEX,
};
enum SHADER{
    SHADER_CORE,
    SHADER_AUX
};
//objetos do jogo
std::vector<Model*> modelos;
std::vector<Model*> paredes;
std::vector<Texture*> texturas;
std::vector<Shader*> shaders;


 GLFWwindow* init(unsigned int WIDTH, unsigned int HEIGHT, const char* name){
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, name, NULL, NULL);
    return window;   
 }


void initTexturas(){
    //player
    texturas.push_back(new Texture("Textures/shatrang.jpg", GL_TEXTURE_2D));
    //wall
    texturas.push_back(new Texture("Textures/wallMetal.jpg", GL_TEXTURE_2D));
    //floor
    texturas.push_back(new Texture("Textures/Chess_Board.jpg", GL_TEXTURE_2D));
}

void initShaders(){
    shaders.push_back(new Shader("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl"));
}

void initMap(){
    //floor
    std::vector<Mesh*> meshes;
    Quad tempQ = Quad();
    meshes.push_back(new Mesh(&tempQ));
    modelos.push_back(new Model(glm::vec3(0,0,0), texturas[FLOOR_TEX], meshes));
    modelos[2]->ScaleXZ(10);
    for(auto&i: meshes){
            delete i;
    }
    //paredes
    //criando as paredes
    //paredes da linha 1
    paredes.push_back(new Model(glm::vec3(1.3,2.0,1.3), texturas[WALL_TEX], "Objetos/parede.obj"));
    paredes[0]->Scale(1.20);
    paredes[0]->Mover(6.2, 0.1, -8.2);
    //paredes da linha 2
    paredes.push_back(new Model(glm::vec3(1.3,2.0,1.3), texturas[WALL_TEX], "Objetos/parede.obj"));
    paredes[1]->Scale(1.20);
    paredes[1]->ScaleVar(5,1,1);
    paredes[1]->Mover(-0.4, 0.1, -6.2);
    //paredes da linha 3
    paredes.push_back(new Model(glm::vec3(1.3,2.0,1.3), texturas[WALL_TEX], "Objetos/parede.obj"));
    paredes[2]->Scale(1.20);
    paredes[2]->Mover(2.2, 0.1, -4.2);
    paredes[2]->ScaleVar(3,1,1);
    //paredes da linha 4
    paredes.push_back(new Model(glm::vec3(1.3,2.0,1.3), texturas[WALL_TEX], "Objetos/parede.obj"));
    paredes[3]->Scale(1.20);
    paredes[3]->Mover(-5, 0.1, -2.2);
    paredes[3]->ScaleVar(4,1,1);
    //paredes da linha 5
        //primeira parede
        paredes.push_back(new Model(glm::vec3(1.3,2.0,1.3), texturas[WALL_TEX], "Objetos/parede.obj"));
        paredes[4]->Scale(1.20);
        paredes[4]->ScaleVar(2,1,1);
        paredes[4]->Mover(-0.5, 0.1, 0);
        //segunda parede
        paredes.push_back(new Model(glm::vec3(1.3,2.0,1.3), texturas[WALL_TEX], "Objetos/parede.obj"));
        paredes[5]->Scale(1.20);
        paredes[5]->ScaleVar(2,1,1);
        paredes[5]->Mover(2.5, 0.1, 0);
    //paredes da linha 6
    paredes.push_back(new Model(glm::vec3(1.3,2.0,1.3), texturas[WALL_TEX], "Objetos/parede.obj"));
    paredes[6]->Scale(1.20);
    paredes[6]->ScaleVar(2,1,1);
    paredes[6]->Mover(-3.7, 0.1, 2.2);
    //paredes da linha 7
        //primeira parede
        paredes.push_back(new Model(glm::vec3(1.3,2.0,1.3), texturas[WALL_TEX], "Objetos/parede.obj"));
        paredes[7]->Scale(1.20);
        paredes[7]->ScaleVar(3,1,1);
        paredes[7]->Mover(0.0, 0.1, 4.1);
        //segunda parede
        paredes.push_back(new Model(glm::vec3(1.3,2.0,1.3), texturas[WALL_TEX], "Objetos/parede.obj"));
        paredes[8]->Scale(1.20);
        paredes[8]->Mover(6.2, 0.1, 4.1);
    //paredes da linha 8
        //parede 1
        paredes.push_back(new Model(glm::vec3(1.3,2.0,1.3), texturas[WALL_TEX], "Objetos/parede.obj"));
        paredes[9]->Scale(1.20);
        paredes[9]->ScaleVar(2,1,1);
        paredes[9]->Mover(-3.7, 0.1, 6.2);
        //parede 2
        paredes.push_back(new Model(glm::vec3(1.3,2.0,1.3), texturas[WALL_TEX], "Objetos/parede.obj"));
        paredes[10]->Scale(1.20);
        paredes[10]->Mover(-2.2, 0.1, 6.2);
        //parede 3
        paredes.push_back(new Model(glm::vec3(1.3,2.0,1.3), texturas[WALL_TEX], "Objetos/parede.obj"));
        paredes[11]->Scale(1.20);
        paredes[11]->Mover(6.2, 0.1, 6.2);

}

void initModelos(){
    //player
    modelos.push_back(new Model(glm::vec3(1.3,1,1.3), texturas[PLAYER_TEX], "Objetos/PawnW.obj"));
    modelos[0]->Scale(1.20);
    modelos[0]->Mover(0, 0, 6.2);
    //chegada
    std::vector<Mesh*> meshes;
    Cube tempC = Cube();
    meshes.push_back(new Mesh(&tempC));
    modelos.push_back(new Model(glm::vec3(-8.4,2.5,-8.4), texturas[PLAYER_TEX], meshes));

    //paredes
    initMap();
    for(auto&i: meshes){
            delete i;
    }
    startarMapaColisao();
}

enum GAMESTATE{
    GAME,
    END
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window, GAMESTATE state);


int main()
{
    GAMESTATE state = GAME;
    //iniciando a janela e opengl
    window = init(SCR_WIDTH, SCR_HEIGHT, "Jogo");
    if(window == NULL){
        std::cout << "erro iniciando a janela!\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }    

    initTexturas();
    initShaders();
    initModelos();
    //inicializacoes finalizadas
    glViewport(0,0, SCR_WIDTH, SCR_HEIGHT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC0_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame; 
        if(state == GAME){
            if(shouldPause){
                pauseMove += deltaTime;
                if(pauseMove >= 0.2){
                    pauseMove = 0;
                    shouldPause = false;
                }
            }
            //inputs
            processInput(window, state);
            // pass projection matrix to shader (note that in this case it could change every frame)
            glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
            glm::mat4 view = camera.GetViewMatrix();
            for(auto&i: shaders){
                i->setMat4("projection", projection);
                i->setMat4("view", view);
                i->set3dVec("lightDirection", 1,1,0);
                i->set3dVec("lightColor", 1,1,1);
                i->set3dVec("lightpos", lightPos.x, lightPos.y, lightPos.z);
                i->set3dVec("campos", 5, 5, 5);
            }
            // render
            // ------
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            //Chegada
            shaders[SHADER_CORE]->setBool("chegada", true);
            modelos[CHEGADA_MODEL]->Rotate(deltaTime, 0, 1.f, 0);
            //modelos[CHEGADA_MODEL]->Mover(0, direcaoCubo, 0);
            modelos[CHEGADA_MODEL]->render(shaders[SHADER_CORE]);
            shaders[SHADER_CORE]->setBool("chegada", false);
            //Chao
            modelos[FLOOR_MODEL]->render(shaders[SHADER_CORE]);
            //Player
            modelos[PLAYER_MODEL]->render(shaders[SHADER_CORE]);

            for(auto&i: paredes){
                i->render(shaders[SHADER_CORE]);
            }
            counter += deltaTime;
            lightPos.x += incremento;
            if(counter >= 3.0f){
                incremento *=-1;
                counter = 0;
            }
            
            if(mapaColisao[playerY][playerX] == 2){
                state = END;
            }
            // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
            // -------------------------------------------------------------------------------
            glfwSwapBuffers(window);
            glfwPollEvents();
        }else{
            processInput(window, state);
            //glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }
    //textt.Apagar();
    for(auto&i: modelos){
        delete i;
    }
    for(auto&i: paredes){
        delete i;
    }
    for(auto&i: texturas){
        delete i;
    }
    for(auto&i: shaders){
        delete i;
    }
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window, GAMESTATE state)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
    if(state == GAME){
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
            if(playerY > 0){
                if(mapaColisao[playerY - 1][playerX] != 1){
                    if(!shouldPause){
                    playerY -= 1;
                    modelos[PLAYER_MODEL]->Mover(0,0,-2.2f);
                    camera.ProcessKeyboard(FRENTE, deltaTime);
                    shouldPause = true;
                    }
                }
            }
        
        }else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
            if(playerY < 7){
                if(mapaColisao[playerY + 1][playerX] != 1){
                    if(!shouldPause){
                    playerY += 1;
                    modelos[PLAYER_MODEL]->Mover(0,0,2.2f);
                    camera.ProcessKeyboard(TRAS, deltaTime);
                    shouldPause = true;
                    }
                }
            }
            
        }else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
            if(playerX > 0){
                if(mapaColisao[playerY][playerX-1] != 1){
                    if(!shouldPause){
                    playerX -= 1;
                    modelos[PLAYER_MODEL]->Mover(-2.2f,0,0);
                    camera.ProcessKeyboard(ESQUERDA, deltaTime);
                    shouldPause = true;
                    }
                }
            }
            
            
        }else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
            if(playerX < 7){
                if(mapaColisao[playerY][playerX+1] != 1){
                    if(!shouldPause){
                    playerX += 1;
                    modelos[PLAYER_MODEL]->Mover(2.2f,0,0);
                    camera.ProcessKeyboard(DIREITA, deltaTime); 
                    shouldPause = true;
                    }
                }
            }
        }
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
