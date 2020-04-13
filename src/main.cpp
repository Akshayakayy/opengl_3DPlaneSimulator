#include "main.h"
#include "timer.h"
#include "ball.h"
#include "plane.h"
#include "scene.h"
#include "bomb.h"
#include "land.h"
#include "checkpoint.h"
#include "arrow.h"
#include "cannon.h"
#include "attack.h"
#include "hoop.h"
#include "volcano.h"
#include "fuel.h"
#include "parachute.h"
#include "coin.h"
#include "dashboard.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/
int timevar = 0;
float score = 1;
float fuelvar = 100;
float health = 100;

Ball ball1;
Ball ball2;
Arrow arrow;
//Bomb bomb;
Plane plane;

vector <Bomb> bombs;
vector <Bomb> missiles;
vector <Attack> attacks;
vector <Parachute> parachutes;
vector <Coin> coins;
vector <Hoop> hoops;
vector <Fuel> fuels;
vector <Cannon> cannons;

Altitude alt;

Land lands[150];
Volcano volcanos[20];

int enemycount = 0;
Checkpoint checkpoint;

Ocean ocean;

char title[100];
float altitude = plane.position.y;

float screen_zoom = -990, screen_center_x = 0, screen_center_y = 0;

Timer t60(1.0 / 60);

float camx = 0;
float camy = 4;
float camz = -5;

float upx = 0;
float upy = 1;
float upz = 0;

float tarx = 0;
float tary = 0;
float tarz = 0;

/* Render the scene with openGL */
/* Edit this function according to your assignment */
bool collision_plane_coin(Plane plane, Coin coin) {
    if (plane.position.x + 2 > coin.position.x && plane.position.x - 2 < coin.position.x){
      if (plane.position.y + 1.5 > coin.position.y && plane.position.y - 1.5 < coin.position.y){
        if (plane.position.z + 0.6 > coin.position.z && plane.position.z - 5 < coin.position.z){
          score += coin.points;
          printf("%f\n",score );
          return 1;
        }
      }
    }
    return 0;
}

bool collision_plane_hoop(Plane plane, Hoop hoop) {
  if (plane.position.x + 5 > hoop.position.x && plane.position.x - 5 < hoop.position.x){
    if (plane.position.y + 5 > hoop.position.y && plane.position.y -5 < hoop.position.y){
      if (abs(plane.position.z -hoop.position.z )< 1){
        score += 100;
        printf("%f\n",score );
        return 1;
      }
    }
  }
  return 0;
}

bool collision_plane_volcano(Plane plane, Volcano volcano) {
  if (plane.position.x + 8 > volcano.position.x && plane.position.x - 8 < volcano.position.x){
    if (plane.position.y < volcano.position.y + 22){
      if (plane.position.z + 8 > volcano.position.z && plane.position.z - 8 < volcano.position.z){
        return 1;
      }
    }
  }
  return 0;
}

bool collision_plane_fuel(Plane plane, Fuel fuel) {
  if (plane.position.x + 2 > fuel.position.x-2.5 && plane.position.x - 2 < fuel.position.x-2.5){
    if (plane.position.y < fuel.position.y + 10){
      if (plane.position.z + 0.6 > fuel.position.z-2.5 && plane.position.z - 5 < fuel.position.z-2.5){
        if(fuel.type == 0){
        if (fuelvar<=90){
          fuelvar += 10;
        }
        else{
          fuelvar = 100;
        }}
        else{
          if (health <= 90){
            health += 10;
          }
          else{
            health = 100;
          }
        }
        return 1;
      }
    }
  }
  return 0;
}

bool collision_bomb_enemy(Bomb bomb, Cannon cannon) {
  if (bomb.position.x + 4 > cannon.position.x && bomb.position.x - 4 < cannon.position.x){
    if (bomb.position.y + 2 > cannon.position.y && bomb.position.y - 2 < cannon.position.y){
      if (bomb.position.z + 4 >cannon.position.z && bomb.position.z - 4 < cannon.position.z){
        score += 200;
        printf("%f\n",score );
        return 1;
      }
    }
  }
  return 0;
}

bool collision_missile_enemy(Bomb bomb, Cannon cannon) {
  if (bomb.position.x + 4 > cannon.position.x && bomb.position.x - 4 < cannon.position.x){
    if (bomb.position.y + 2 > cannon.position.y && bomb.position.y - 2 < cannon.position.y){
      if (bomb.position.z + 4 > cannon.position.z && bomb.position.z - 4 < cannon.position.z){
        score += 200;
        printf("%f\n",score );
        return 1;
      }
    }
  }
  return 0;
}

bool collision_bomb_parachute(Bomb bomb, Parachute parachute) {
  if (bomb.position.x + 3 > parachute.position.x && bomb.position.x - 3 < parachute.position.x){
    if (bomb.position.y + 3 > parachute.position.y && bomb.position.y - 3 < parachute.position.y){
      if (bomb.position.z + 3 > parachute.position.z && bomb.position.z - 3 < parachute.position.z){
        score += 150;
        printf("%f\n",score );
        return 1;
      }
    }
  }
  return 0;
}

bool collision_missile_parachute(Bomb bomb, Parachute parachute) {
  if (bomb.position.x + 3 > parachute.position.x && bomb.position.x - 3 < parachute.position.x){
    if (bomb.position.y + 3 > parachute.position.y && bomb.position.y - 3 < parachute.position.y){
      if (bomb.position.z + 3 > parachute.position.z && bomb.position.z - 3 < parachute.position.z){
        score += 150;
        printf("%f\n",score );
        return 1;
      }
    }
  }
  return 0;
}

void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye ( camx, camy, camz );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (tarx, tary, tarz);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (upx, upy, upz);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    ocean.draw(VP);

    for(int i=0;i<150;i++) lands[i].draw(VP);
    for(int i=0;i<20;i++) volcanos[i].draw(VP);
    for(int i=0;i<50;i++) fuels[i].draw(VP);

    checkpoint.draw(VP);
    for(int i = 0; i<cannons.size();i++){
      cannons[i].draw(VP);
    }

    for(int i = 0; i<parachutes.size();i++){
      parachutes[i].draw(VP);
    }

    for(int i=0;i<attacks.size();i++){
      attacks[i].draw(VP);
    }
    for(int i = 0; i<bombs.size();i++){
      bombs[i].draw(VP);
    }
    for(int i = 0; i<missiles.size();i++){
      missiles[i].draw(VP);
    }
    for(int i=0;i<200;i++){
      coins[i].draw(VP);
    }

    arrow.draw(VP);

    for(int i = 0; i<5;i++){
      hoops[i].draw(VP);
    }

    plane.draw(VP);
    //alt.draw(VP);
}

char view = 'a';
float speed = 1;

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    int a = glfwGetKey(window, GLFW_KEY_A);
    int s = glfwGetKey(window, GLFW_KEY_S);
    int d = glfwGetKey(window, GLFW_KEY_D);
    int f = glfwGetKey(window, GLFW_KEY_F);
    int b = glfwGetKey(window, GLFW_KEY_B);
    int m = glfwGetKey(window, GLFW_KEY_M);

    if (a) {
      view = 'a';
    }
    else if (s) {
      view = 's';
    }
    else if (d) {
      view = 'd';
    }
    else if (f) {
      view = 'f';
    }

    if (space && speed < 15){
      speed += 0.2;
    }
    else{
      speed = 1;
    }

    if (right){
      plane.rotation += 0.5;
      plane.rotationy += 0.5;
      plane.rotationy += 0.5;
      // printf("1. %f %f %f\n", camx+6.5*sin(plane.rotationy*M_PI/180.0f), camy, camz+6.5*cos(plane.rotationy*M_PI/180.0f));
      // printf("2. %f %f %f\n", camx, camy, camz);

      if(view != 'd'){
        upx -= 0.0001;
      }
      //plane.rotationy
    }
    else if (left){
      plane.rotation -= 0.5;
      plane.rotationy -= 0.5;

      if(view != 'd'){
        upx += 0.0001;
      }

    }
    else if (plane.rotation < 0){
      plane.rotation += 0.3;
      if(view != 'd'){
        upx -= 0.0001;
      }
    }
    else if (plane.rotation > 0){
      plane.rotation -=0.3;
      if(view != 'd'){
        upx += 0.0001;
      }
    }

    if (up){
      plane.rotationx -= 0.096;
      if(view != 'd'){
        camy -= 0.01;
      }
      plane.position.y += 0.2;
    }
    else if (down){
      plane.rotationx += 0.096;
      if(view != 'd'){
        camy += 0.01;
      }
      plane.position.y -= 0.2;
    }
    else if (plane.rotationx < 20){
      plane.rotationx += 0.096;
      if(view != 'd'){
        camy += 0.01;
      }
    }
    else if (plane.rotationx > 20){
      plane.rotationx -= 0.096;
      if(view != 'd'){
        camy -= 0.01;
      }
    }
    if (b && timevar%10==0) {
      Bomb new_bomb = Bomb(plane.position.x, plane.position.y-0.5, plane.position.z, plane.rotationy, plane.rotationx, COLOR_GREY);
      bombs.push_back(new_bomb);
    }
    if (m && timevar%10==0) {
      Bomb new_missile = Bomb(plane.position.x, plane.position.y-0.5, plane.position.z, plane.rotationy, plane.rotationx, COLOR_DGREY);
      missiles.push_back(new_missile);
    }
}


void tick_elements() {
    if(timevar%50 == 0){
      score += 1;
    }

    if(timevar%100 == 0){
      fuelvar -= 1;
    }

    altitude = plane.position.y;

    timevar += 1;
    if (timevar > 1000){
      timevar = 0;
    }
    plane.position.x += 0.02*speed*-sin(plane.rotationy*M_PI/180.0f);
    plane.position.z += 0.02*speed*cos(plane.rotationy*M_PI/180.0f);
    //("3. %f %f %f\n", plane.position.x, plane.position.y, plane.position.z);

    if (view == 'a') {
        camx = plane.position.x + 7*sin(plane.rotationy*M_PI/180.0f);
        camy = plane.position.y + 8;
        camz = plane.position.z - 7*cos(plane.rotationy*M_PI/180.0f);

        tarz = plane.position.z + 1*cos(plane.rotationy*M_PI/180.0f);
        tary = plane.position.y + 4;
        tarx = plane.position.x - 1*sin(plane.rotationy*M_PI/180.0f);
    }
    else if (view == 's') {
        camx = plane.position.x + 3;
        camy = plane.position.y + 9.5;
        camz = plane.position.z - 3.5;

        tarz = plane.position.z;
        tary = plane.position.y + 4;
        tarx = plane.position.x;
    }
    else if (view == 'd') {
        camx = plane.position.x+ 1*sin(plane.rotationy*M_PI/180.0f);
        camy = plane.position.y + 20;
        camz = plane.position.z- 1*cos(plane.rotationy*M_PI/180.0f);

        tarz = plane.position.z + 0.1+ 1*cos(plane.rotationy*M_PI/180.0f);
        tary = plane.position.y;
        tarx = plane.position.x- 1*sin(plane.rotationy*M_PI/180.0f);
    }
    else if (view == 'f') {
        camx = plane.position.x+ 1*sin(plane.rotationy*M_PI/180.0f);
        camy = plane.position.y - 0.5;
        camz = plane.position.z- 1*cos(plane.rotationy*M_PI/180.0f);

        tarz = plane.position.z + 1*cos(plane.rotationy*M_PI/180.0f);
        tary = plane.position.y - 2;
        tarx = plane.position.x- 1*sin(plane.rotationy*M_PI/180.0f);
    }

    for(int i=0;i<bombs.size();i++){
      bombs[i].position.x += 0.2*-sin(bombs[i].rotationy*M_PI/180.0f);
      bombs[i].position.z += 0.2*cos(bombs[i].rotationy*M_PI/180.0f);
      bombs[i].position.y -= 0.2*cos(bombs[i].rotation*M_PI/180.0f);
    }

    for(int i=0;i<bombs.size();i++){
      if((bombs[i].position.z-plane.position.z)*(bombs[i].position.z-plane.position.z)+(bombs[i].position.x-plane.position.x)*(bombs[i].position.x-plane.position.x) > 625){
          bombs.erase(bombs.begin() + i);
      }
    }

    for(int i=0;i<missiles.size();i++){
      missiles[i].position.y -= 1.1;
    }

    for(int i=0;i<missiles.size();i++){
      if(missiles[i].position.y < -50){
          missiles.erase(missiles.begin() + i);
      }
    }

    if((checkpoint.position.x-plane.position.x)*(checkpoint.position.x-plane.position.x)+(checkpoint.position.z-plane.position.z)*(checkpoint.position.z-plane.position.z)>6400){
      arrow.position.x = (plane.position.x + checkpoint.position.x)/2;
      arrow.position.z = (plane.position.z + checkpoint.position.z)/2;
      arrow.position.y = plane.position.y;

    }
    else{
      arrow.position.x = checkpoint.position.x;
      arrow.position.z = checkpoint.position.z;
      arrow.position.y = plane.position.y;
    }

    if((checkpoint.position.x-plane.position.x)*(checkpoint.position.x-plane.position.x)+(checkpoint.position.z-plane.position.z)*(checkpoint.position.z-plane.position.z)<2500){
      if(timevar%400 == 0){
        for(int i=0;i<5;i++){
          Attack new_attack = Attack(cannons[i].position.x, cannons[i].position.y, cannons[i].position.z, plane, COLOR_GREY);
          attacks.push_back(new_attack);
        }
      }
    }
    for(int i=0;i<attacks.size();i++){
      attacks[i].position.y += 0.05;
    }

    for(int i=0; i<200; i++) coins[i].tick();

    for(int i=0;i<parachutes.size();i++){
      parachutes[i].position.y -= 0.1;
      if(parachutes[i].position.y < -51){
        parachutes.erase(parachutes.begin() + i);
        float a = plane.position.x+rand()%60-30;
        float b = plane.position.z+rand()%60-30;
        float c = plane.position.z+rand()%40+30;
        Parachute new_parachute = Parachute(a, c , b);
        parachutes.push_back(new_parachute);
      }
    }

    for(int i=0;i<20;i++){
      if(collision_plane_volcano(plane, volcanos[i])){
        quit(window);
      }

    }

    for(int i=0;i<coins.size();i++){
      if(collision_plane_coin(plane, coins[i])){
        coins.erase(coins.begin() + i);
      }
    }

    for(int i=0;i<hoops.size();i++){
      if(collision_plane_hoop(plane, hoops[i])){
        hoops.erase(hoops.begin() + i);
        float a = plane.position.x+rand()%100-50;
        float b = plane.position.z+rand()%100-50;
        float c = rand()%50-20;
        Hoop new_hoop = Hoop(a, c , b, COLOR_GREEN);
        hoops.push_back(new_hoop);
      }
    }

    for(int i=0;i<50;i++){
      if(collision_plane_fuel(plane, fuels[i])){
        printf("%f",fuelvar);
        fuels.erase(fuels.begin() + i);
      }
    }

    for(int i=0;i<bombs.size();i++){
      for(int j=0;j<cannons.size();j++){
        if(collision_bomb_enemy(bombs[i], cannons[j])){
          cannons.erase(cannons.begin() + j);
          bombs.erase(bombs.begin() + i);
          enemycount += 1;
          break;
        }
      }
    }

    for(int i=0;i<missiles.size();i++){
      for(int j=0;j<cannons.size();j++){
        if(collision_missile_enemy(missiles[i], cannons[j])){
          cannons.erase(cannons.begin() + j);
          missiles.erase(missiles.begin() + i);
          enemycount += 1;
          break;
        }
      }
    }


    if(enemycount == 2){
      enemycount = 0;

      checkpoint.position.x = plane.position.x+(rand()%3+6)*20;
      checkpoint.position.y = -49.5;
      checkpoint.position.z = plane.position.z+(rand()%3+6)*20;

      arrow.position.x = checkpoint.position.x;
      arrow.position.y = plane.position.y+5;
      arrow.position.z = checkpoint.position.z;

      for(int i=0;i<2;i++)
      {
          float a = checkpoint.position.x+rand()%40-20;
          float b = checkpoint.position.z+rand()%40-20;
          Cannon new_cannon = Cannon(a, -47, b);
          cannons.push_back(new_cannon);
      }
    }

    for(int i=0;i<bombs.size();i++){
      for(int j=0;j<parachutes.size();j++){
        if(collision_bomb_parachute(bombs[i], parachutes[j])){
          parachutes.erase(parachutes.begin() + j);
          bombs.erase(bombs.begin() + i);
          break;
        }
      }
    }

    for(int i=0;i<missiles.size();i++){
      for(int j=0;j<parachutes.size();j++){
        if(collision_missile_parachute(missiles[i], parachutes[j])){
          parachutes.erase(parachutes.begin() + j);
          missiles.erase(missiles.begin() + i);
          break;
        }
      }
    }

    if(altitude < -48){
      quit(window);
    }
    if(health < 0){
      quit(window);
    }
    if(fuelvar < 0){
      quit(window);
    }

    sprintf(title, "ALTITUDE: %f; SCORE: %f; FUEL: %f", altitude+50,score, fuelvar);
    glfwSetWindowTitle(window, title);

}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    ball1       = Ball(0, 0, -2.5, COLOR_RED);
    ball2       = Ball(10, -30, 20, COLOR_RED);
    plane       = Plane(0, -4, 1.5, COLOR_BLACK);
    ocean       = Ocean(COLOR_BLUE);
    checkpoint  = Checkpoint(plane.position.x+rand()%200-100, -49.5, plane.position.z+rand()%200-100);
    arrow       = Arrow(checkpoint.position.x, plane.position.y+5, checkpoint.position.z, plane.rotationy, COLOR_GREY);
    alt         = Altitude(camx+1,camy-0.5,camz+2);

    for(int i=0;i<5;i++)
    {
      float a = plane.position.x+rand()%60-30;
      float b = plane.position.z+rand()%60-30;
      float c = plane.position.z+rand()%40+30;
      Parachute new_parachute = Parachute(a, c , b);
      parachutes.push_back(new_parachute);
    }

    for(int i=0;i<200;i++)
    {
      float a = ((float)rand()/(float)RAND_MAX - 0.5f) * 600;
      float b = ((float)rand()/(float)RAND_MAX - 0.5f) * 600;
      float c = plane.position.y+rand()%30-15;
      Coin new_coin = Coin(a, c , b);
      coins.push_back(new_coin);
    }

    for(int i=0;i<2;i++)
    {
        float a = checkpoint.position.x+rand()%40-20;
        float b = checkpoint.position.z+rand()%40-20;
        Cannon new_cannon = Cannon(a, -47, b);
        cannons.push_back(new_cannon);
    }

    for(int i=0;i<150;i++)
    {
        float a = ((float)rand()/(float)RAND_MAX - 0.5f) * 600;
        float b = ((float)rand()/(float)RAND_MAX - 0.5f) * 600;
        lands[i] = Land(a, -50 , b);
    }

    for(int i=0;i<20;i++)
    {
        float a = ((float)rand()/(float)RAND_MAX - 0.5f) * 600;
        float b = ((float)rand()/(float)RAND_MAX - 0.5f) * 600;
        volcanos[i] = Volcano(a, -50 , b);
    }

    for(int i=0;i<50;i++)
    {
        float a = ((float)rand()/(float)RAND_MAX - 0.5f) * 600;
        float b = ((float)rand()/(float)RAND_MAX - 0.5f) * 600;
        Fuel new_fuel = Fuel(a, -50 , b);
        fuels.push_back(new_fuel);
    }

    for(int i=0;i<5;i++)
    {
      float a = plane.position.x+rand()%100-50;
      float b = plane.position.z+rand()%100-50;
      float c = rand()%50-20;
      Hoop new_hoop = Hoop(a, c , b, COLOR_GREEN);
      hoops.push_back(new_hoop);
    }

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw complaneds
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}


void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    //Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
    Matrices.projection = glm::perspective(glm::radians(screen_zoom),(float)800/(float)1000,0.1f,100.0f);
}
