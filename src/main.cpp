#include <MeusH/libs.h>
#include <string.h>
#include <stdlib.h>
#include <cmath>
#include <iostream>

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;

unsigned int VBO = 0;
unsigned int VArray = 0;

float angle = 0.0; 
float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame
//
// camera
Camera camera(glm::vec3(0.0f, -0.1f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

//Texture tex("Textures/wall.jpg", GL_TEXTURE_2D);


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

/*unsigned int*/void configScene(Shader prog){
    
    
    Vertex verticesTri[] = {
    -0.5f, -0.5f, -0.5f, 1.0f,1.0f,1.0f,1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f, 1.0f,1.0f,1.0f,1.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f, 1.0f,1.0f,1.0f,1.0f, 1.0f, 1.0f,
     0.5f,  0.5f, -0.5f, 1.0f,1.0f,1.0f,1.0f, 1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f, 1.0f,1.0f,1.0f,1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f,1.0f,1.0f,1.0f, 0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f, 1.0f,1.0f,1.0f,1.0f, 0.0f, 0.0f,
     0.5f, -0.5f,  0.5f, 1.0f,1.0f,1.0f,1.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 1.0f,1.0f,1.0f,1.0f, 1.0f, 1.0f,
     0.5f,  0.5f,  0.5f, 1.0f,1.0f,1.0f,1.0f, 1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f, 1.0f,1.0f,1.0f,1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, 1.0f,1.0f,1.0f,1.0f, 0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, 1.0f,1.0f,1.0f,1.0f, 1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, 1.0f,1.0f,1.0f,1.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f,1.0f,1.0f,1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f,1.0f,1.0f,1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, 1.0f,1.0f,1.0f,1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, 1.0f,1.0f,1.0f,1.0f, 1.0f, 0.0f,

     0.5f,  0.5f,  0.5f, 1.0f,1.0f,1.0f,1.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f, 1.0f,1.0f,1.0f,1.0f, 1.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 1.0f,1.0f,1.0f,1.0f, 0.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 1.0f,1.0f,1.0f,1.0f, 0.0f, 1.0f,
     0.5f, -0.5f,  0.5f, 1.0f,1.0f,1.0f,1.0f, 0.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 1.0f,1.0f,1.0f,1.0f, 1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f, 1.0f,1.0f,1.0f,1.0f, 0.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 1.0f,1.0f,1.0f,1.0f, 1.0f, 1.0f,
     0.5f, -0.5f,  0.5f, 1.0f,1.0f,1.0f,1.0f, 1.0f, 0.0f,
     0.5f, -0.5f,  0.5f, 1.0f,1.0f,1.0f,1.0f, 1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f, 1.0f,1.0f,1.0f,1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 1.0f,1.0f,1.0f,1.0f, 0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f, 1.0f,1.0f,1.0f,1.0f, 0.0f, 1.0f,
     0.5f,  0.5f, -0.5f, 1.0f,1.0f,1.0f,1.0f, 1.0f, 1.0f,
     0.5f,  0.5f,  0.5f, 1.0f,1.0f,1.0f,1.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 1.0f,1.0f,1.0f,1.0f, 1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, 1.0f,1.0f,1.0f,1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, 1.0f,1.0f,1.0f,1.0f, 0.0f, 1.0f
    };
    float coordTriangle[] = {
            // positions      //coordenadas
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
           
};
    int verticesInd[] = {
        0,1,2,
        3,4,5,
        6,7,8,
        9,10,11,
        12,13,14,
        15,16,17,
        18,19,20,
        21,22,23,
        24,25,26,
        27,28,29,
        30,31,32,
        33,34,35
    };
    /*
    //unsigned int vtxBuffer = 0;
    glGenBuffers(1, &VArray);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VArray);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(verticesInd), verticesInd, GL_STATIC_DRAW);

    //unsigned int VBO = 0;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesTri), verticesTri, GL_STATIC_DRAW);

    //auto position = prog.getAttrib("position");//glGetAttribLocation(prog.ID, "position");
    glVertexAttribPointer(0, 
                          3,
                          GL_FLOAT,
                          false, 
                          9*sizeof(float), 
                          (void*)0);
    glEnableVertexAttribArray(0);


    auto texCoord = prog.getAttrib("texCoord");//glGetAttribLocation(prog.ID, "color");
    glVertexAttribPointer(2, 
                          2,
                          GL_FLOAT,
                          false, 
                          9*sizeof(float), 
                          (void*)(7*sizeof(float)));
    glEnableVertexAttribArray(2);


    prog.use();
    prog.setInt("texture_1", 0);
    prog.setFloat("uPixelSize", 5.0f);
    prog.set2dVec("uTextureSize", (float)256, (float)256);
    */

    //tex.bind(GL_TEXTURE1, GL_TEXTURE_2D);
    //texture_0.bind(0,GL_TEXTURE_2D); 
    glViewport(0,0, SCR_WIDTH, SCR_HEIGHT);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC0_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //return VBO;
}


void draw(Shader prog, GLFWwindow* window){
   
}


int main()
{
    //iniciando a janela e opengl
    GLFWwindow* window = init(SCR_WIDTH, SCR_HEIGHT, "Jogo");
    if(window == NULL){
        std::cout << "erro iniciando a janela!\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }    
    //inicializacoes finalizadas

    Shader prog("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");  
    

    Texture textt("Textures/wall.jpg", GL_TEXTURE_2D);
    textt.bind(GL_TEXTURE0, GL_TEXTURE_2D); 

    //Inicia a mesh
    Vertex verticesTri[] = {
    -0.5f, -0.5f, -0.5f, 1.0f,1.0f,1.0f,1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f, 1.0f,1.0f,1.0f,1.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f, 1.0f,1.0f,1.0f,1.0f, 1.0f, 1.0f,
     0.5f,  0.5f, -0.5f, 1.0f,1.0f,1.0f,1.0f, 1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f, 1.0f,1.0f,1.0f,1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f,1.0f,1.0f,1.0f, 0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f, 1.0f,1.0f,1.0f,1.0f, 0.0f, 0.0f,
     0.5f, -0.5f,  0.5f, 1.0f,1.0f,1.0f,1.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 1.0f,1.0f,1.0f,1.0f, 1.0f, 1.0f,
     0.5f,  0.5f,  0.5f, 1.0f,1.0f,1.0f,1.0f, 1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f, 1.0f,1.0f,1.0f,1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, 1.0f,1.0f,1.0f,1.0f, 0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, 1.0f,1.0f,1.0f,1.0f, 1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, 1.0f,1.0f,1.0f,1.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f,1.0f,1.0f,1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f,1.0f,1.0f,1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, 1.0f,1.0f,1.0f,1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, 1.0f,1.0f,1.0f,1.0f, 1.0f, 0.0f,

     0.5f,  0.5f,  0.5f, 1.0f,1.0f,1.0f,1.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f, 1.0f,1.0f,1.0f,1.0f, 1.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 1.0f,1.0f,1.0f,1.0f, 0.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 1.0f,1.0f,1.0f,1.0f, 0.0f, 1.0f,
     0.5f, -0.5f,  0.5f, 1.0f,1.0f,1.0f,1.0f, 0.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 1.0f,1.0f,1.0f,1.0f, 1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f, 1.0f,1.0f,1.0f,1.0f, 0.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 1.0f,1.0f,1.0f,1.0f, 1.0f, 1.0f,
     0.5f, -0.5f,  0.5f, 1.0f,1.0f,1.0f,1.0f, 1.0f, 0.0f,
     0.5f, -0.5f,  0.5f, 1.0f,1.0f,1.0f,1.0f, 1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f, 1.0f,1.0f,1.0f,1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 1.0f,1.0f,1.0f,1.0f, 0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f, 1.0f,1.0f,1.0f,1.0f, 0.0f, 1.0f,
     0.5f,  0.5f, -0.5f, 1.0f,1.0f,1.0f,1.0f, 1.0f, 1.0f,
     0.5f,  0.5f,  0.5f, 1.0f,1.0f,1.0f,1.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 1.0f,1.0f,1.0f,1.0f, 1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, 1.0f,1.0f,1.0f,1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, 1.0f,1.0f,1.0f,1.0f, 0.0f, 1.0f
    };
    unsigned int verticesInd[] = {
        0,1,2,
        3,4,5,
        6,7,8,
        9,10,11,
        12,13,14,
        15,16,17,
        18,19,20,
        21,22,23,
        24,25,26,
        27,28,29,
        30,31,32,
        33,34,35
    };
    unsigned nrOfVertices = sizeof(verticesTri) / sizeof(Vertex);
    unsigned nrOfIndices = sizeof(verticesInd) / sizeof(unsigned int);

    Mesh teste(verticesTri, nrOfVertices, verticesInd, nrOfIndices);
    /////////////////
    configScene(prog);

    // render loop
    // -----------
    //draw
    while (!glfwWindowShouldClose(window))
    {
        //draw(prog, window);
        // -----
        prog.use();

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame; 

        //inputs
        processInput(window);

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        prog.setMat4("projection", projection);

            // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        prog.setMat4("view", view);
        
        //glUniform4f(vertexColorLoc, 0.0f, greenValue, 0.0f, 1.0f);
        // render
        // ------
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        teste.Render(&prog, 0);
        //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0);
        //glDrawArrays(GL_TRIANGLES, 0, 36);
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();

    }
    glDeleteBuffers(1, &VBO);
    textt.Apagar();
    teste.~Mesh();
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FRENTE, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(TRAS, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(ESQUERDA, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(DIREITA, deltaTime); 
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;
    //std::cout << yoffset << "\n";

    camera.ProcessMouseMovement(xoffset, yoffset/*0.0f*/);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
