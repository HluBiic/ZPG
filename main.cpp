//Include GLEW...tested static linked lib should work (dynamic link didnt work)
#define GLEW_STATIC
#include <GL/glew.h>
#define GLFW_INCLUDE_NONE

//Include GLFW
#include <GLFW/glfw3.h>

//Include GLM...tested lib should work
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

//Include the standard C++ headers
#include <stdlib.h>
#include <stdio.h>

float rotDir = 50.f; // TASK 2

// Prints GLFW errors to stderr
static void error_callback(int error, const char* description) { fputs(description, stderr); }
// Closes app when ESC pressed + prints info about key pressed
// TASK 2: after pressing R the direcion is changed
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);

    if (key == GLFW_KEY_R && action == GLFW_PRESS) {
        rotDir = rotDir * -1;
    }
}
// Prints info when window gains/looses focus
static void window_focus_callback(GLFWwindow* window, int focused) { printf("window_focus_callback \n"); }
// Prints info when window minimized/maximized
static void window_iconify_callback(GLFWwindow* window, int iconified) { printf("window_iconify_callback \n"); }
// Prints info when window resizewd + its new size
static void window_size_callback(GLFWwindow* window, int width, int height) {
    printf("resize %d, %d \n", width, height);
    glViewport(0, 0, width, height);
}
// Prints info when window registers mouse movements
static void cursor_callback(GLFWwindow* window, double x, double y) { printf("cursor_callback \n"); }
// Prints info when window registers mouse click + which button was clicked
static void button_callback(GLFWwindow* window, int button, int action, int mode) {
    if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
}


//GLM test
// Projection matrix : 45� Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
/*
glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.01f, 100.0f);

// Camera matrix
glm::mat4 View = glm::lookAt(
    glm::vec3(10, 10, 10), // Camera is at (4,3,-3), in World Space
    glm::vec3(0, 0, 0), // and looks at the origin
    glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
);
// Model matrix : an identity matrix (model will be at the origin)
glm::mat4 Model = glm::mat4(1.0f)
*/



int main(void) {
    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);

    if (!glfwInit()) // Initialize GLFW lib 
        exit(EXIT_FAILURE);
    window = glfwCreateWindow(640, 480, "ZPG", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enables V-sync

    // Registers all the callbacks
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_callback);
    glfwSetMouseButtonCallback(window, button_callback);
    glfwSetWindowFocusCallback(window, window_focus_callback);
    glfwSetWindowIconifyCallback(window, window_iconify_callback);
    glfwSetWindowSizeCallback(window, window_size_callback);

    // Initial setup of size, buffer size, viewport
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    float ratio = width / (float)height;
    glViewport(0, 0, width, height);

    // [0,0] in the center; [1,1] top right corner; [-1,-1] bottom left corner
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);



    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT); // Clears the screen

        glMatrixMode(GL_MODELVIEW); 
        glLoadIdentity();
        //glRotatef((float)glfwGetTime() * 50.f, 0.f, 0.f, 1.f);//angle, x, y, z axis rotation as direction vector
        
        // TASK 3: rotation along all 3 of the axes but with different speeds
        //glRotatef((float)glfwGetTime() * 50.f, 3.f, 1.0f, 0.5f);//angle, x, y, z axis rotation
        
        // TASK 4: rotation along one of the vertices
        // TASK 2: rotation changes after pressing the R kkey
        glTranslatef(-0.4f, 0.4f, 0.f); // move [0,0] to the edge of the red vertex
        glRotatef((float)glfwGetTime() * rotDir, 0.f, 0.f, 1.f);
        glTranslatef(0.4f, -0.4f, 0.0f); // move [0,0] back to center

        // TASK 1: 1st way via TRIANGLES (2 triangles)
        /*glBegin(GL_TRIANGLES);
        // 1st triangle of the Rectangle
        glColor3f(1.f, 0.f, 0.f); //set color
        glVertex3f(-0.6f, -0.4f, 0.f); // set vertex
        glColor3f(1.f, 1.f, 0.f);
        glVertex3f(0.6f, -0.4f, 0.f);
        glColor3f(0.f, 1.f, 0.f);
        glVertex3f(-0.6f, 0.4f, 0.f);

        // 2nd triangle of the Rectangle
        glColor3f(0.f, 0.f, 1.f);
        glVertex3f(0.6f, 0.4f, 0.f);
        glColor3f(0.f, 1.f, 0.f);
        glVertex3f(-0.6f, 0.4f, 0.f);
        glColor3f(1.f, 1.f, 0.f);
        glVertex3f(0.6f, -0.4f, 0.f);*/

        // TASK 1: 2nd way via POLYGON and not 2 triangles
        glBegin(GL_POLYGON);
        glColor3f(1.f, 0.f, 0.f); //red
        glVertex3f(-0.4f, 0.4f, 0.f);
        glColor3f(0.f, 1.f, 0.f); //green
        glVertex3f(-0.4f, -0.4f, 0.f);
        glColor3f(0.f, 0.f, 1.f); //blue
        glVertex3f(0.4f, -0.4f, 0.f);
        glColor3f(1.f, 1.f, 0.f); //yellow
        glVertex3f(0.4f, 0.4f, 0.f);


        glEnd();
        glfwSwapBuffers(window); // swap buffer...double buffering for rendering

        glfwPollEvents(); // For procesing any pending input events (nmouse, keyboard, window)
    }
    glfwDestroyWindow(window); // Destroy wind. before exiting program
    glfwTerminate();
    exit(EXIT_SUCCESS);
}



/*
TASKS from exercise 01:
1. DONE - Vytvořte z aktuálního trojúhelníku čtverec, jehož čtvrtý vrchol bude žlutý.
2. DONE - Upravte aplikaci tak, aby se při stisku klávesy změnil plynulý směr rotace.
3. DONE - Změňte si osu rotace.
4. DONE - Zkuste rotovat kolem obecného bodu (např. kolem jednoho z rohů čtverce).
5. DONE - Zprovozněte si knihovny GLM a GLEW, budeme je potřebovat příští týden.
6. DONE - Používejte verzovací systém, můžete použít gitlab.vsb.cz.
7. DONE - Zopakujte si debugování (procházení, krokování, vypisování proměnných atd.) zdrojového kódu.
*/