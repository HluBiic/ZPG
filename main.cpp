#include "App.h"
/**
* @brief This is the aplication entry point. It creates the App class
* instance and initializes OpenGL, creates shaders / models and runs
* the main rendering loop.
* 
* @author HLU0035
*/


int main(void) {
    App* a = App::getInstance();

    a->initialization();

    a->createScenes();

    //int f;
    //glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &f);
    //printf("Texture units: %d", f);

    a->run();
}