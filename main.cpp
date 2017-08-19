#include "Main.h"

void APIENTRY debugcallback( GLenum source, GLenum typ,
        GLuint id_, GLenum severity, GLsizei length,
        const GLchar* message, const void* obj){
	cout << message << "\n";
	if (source != GL_DEBUG_SOURCE_SHADER_COMPILER && severity == GL_DEBUG_SEVERITY_HIGH)
		throw runtime_error("Encountered very bad GL error. Stopping.");
}

int main(int argc, char* argv[]){
	cout << "STARTING\n";

	//Resets the Random Seed
	srand(time(NULL));

    //Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);
    
    //Bring Up A Window At (20,20) With Size 800x800
	SDL_Window* win = SDL_CreateWindow(
		"ETGG",
		300, 20,
		1200, 900,
		SDL_WINDOW_OPENGL);
    
	if (!win)
		throw runtime_error("Could not create window");

    //Request GL Context For The Window
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GLContext rc = SDL_GL_CreateContext(win);
	if (!rc)
		throw runtime_error("Cannot create GL context");

	glClearColor(0.2f, 0.4f, 0.6f, 1.0f);
	glEnable(GL_DEPTH_TEST); 
           
    //Define GL Debug Messages
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//Initialize The Shaders
	Program* screenProgram = new Program("/home/tdriggs/Code/CLionWorkspace/ETGG2802/screenvs.txt", "/home/tdriggs/Code/CLionWorkspace/ETGG2802/screenfs.txt");
	Program * shadowProgram = new Program("/home/tdriggs/Code/CLionWorkspace/ETGG2802/shadowvs.txt", "/home/tdriggs/Code/CLionWorkspace/ETGG2802/shadowfs.txt");
	Program * pProgram = new Program("/home/tdriggs/Code/CLionWorkspace/ETGG2802/shadow2vs.txt", "/home/tdriggs/Code/CLionWorkspace/ETGG2802/shadow2fs.txt");
	Camera * shadowCam = new Camera(vec3(0, 0, 0));
	vector<Framebuffer2D *> shadowBuffers = { new Framebuffer2D(2048, 2048, 1, GL_RGBA, GL_FLOAT),
											  new Framebuffer2D(2048, 2048, 1, GL_RGBA, GL_FLOAT),
											  new Framebuffer2D(2048, 2048, 1, GL_RGBA, GL_FLOAT),
											  new Framebuffer2D(2048, 2048, 1, GL_RGBA, GL_FLOAT),
											  new Framebuffer2D(2048, 2048, 1, GL_RGBA, GL_FLOAT) };

	int MAX_LIGHTS = 5;
	vector <vec3> positions =vector <vec3> (MAX_LIGHTS);
	vector <vec4> colors = vector <vec4> (MAX_LIGHTS);
	vector <mat4> viewMatrixs = vector <mat4> (MAX_LIGHTS);
	vector <mat4> projMatrixs = vector <mat4> (MAX_LIGHTS);
	vector <vec3> hithyons = vector <vec3> (MAX_LIGHTS);
	vector <Texture*> sbuffers = vector <Texture*> (MAX_LIGHTS);

	SquareMesh * shadowMesh = NULL;

	//Draw the Loading Screen
	SquareMesh * loadingScreen = new SquareMesh(new ImageTexture("/home/tdriggs/Code/CLionWorkspace/ETGG2802/Resources/loadScreen.png"));
	SquareMesh * gameOverScreen = new SquareMesh(new ImageTexture("/home/tdriggs/Code/CLionWorkspace/ETGG2802/Resources/gameOverScreen.png"));
	SquareMesh * victoryScreen = new SquareMesh(new ImageTexture("/home/tdriggs/Code/CLionWorkspace/ETGG2802/Resources/victoryScreen.png"));

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	screenProgram->use();
	loadingScreen->draw(screenProgram);
	SDL_GL_SwapWindow(win);	
	
	//Set Inupt And Timing Variables
	SDL_SetRelativeMouseMode(SDL_TRUE);
    set<int> keys;
    int last = SDL_GetTicks();
    SDL_Event ev;

	float frame = 0;

	bool victory = false;
	bool gameOver = false;
    while(!gameOver && !victory){
		//Update Time Variables
		int now = SDL_GetTicks();
		float elapsed = (float)(now - last) / 1000;
		last = now;

		double dx = 0;
		double dy = 0;
        //Handle All Events In the Event Queue
        while(SDL_PollEvent(&ev)){
            if(ev.type == SDL_QUIT){
				exit(0);
            } else if(ev.type == SDL_KEYDOWN){
                int k = ev.key.keysym.sym;
                keys.insert(k);
                if(k == SDLK_q){
					exit(0);
                }
				if (k == SDLK_v) {
					Player::getInstance()->toggleSolid();
				}
				if (k == SDLK_c) {
					Player::getInstance()->toggleCameraMode();
				}
				if (k == SDLK_LSHIFT)
				{
					Player::getInstance()->toggleRunning();
				}
            } else if(ev.type == SDL_KEYUP){
                int k = ev.key.keysym.sym;
                keys.erase(k);
            } else if(ev.type == SDL_MOUSEBUTTONDOWN){
				Player::getInstance()->attack();
            } else if(ev.type == SDL_MOUSEMOTION){
                dx += (double)ev.motion.xrel;
				dy -= (double)ev.motion.yrel;
            }
        }
        
        //Handle Key Presses
        if(keys.find(SDLK_w) != keys.end())
            Player::getInstance()->walk(elapsed);
		if (keys.find(SDLK_s) != keys.end())
			Player::getInstance()->walk(-elapsed);
        if(keys.find(SDLK_a) != keys.end())
			Player::getInstance()->strafe(-elapsed);
        if(keys.find(SDLK_d) != keys.end())
			Player::getInstance()->strafe(elapsed);
		if (keys.find(SDLK_i) != keys.end())
			Player::getInstance()->position.y += elapsed * 10;
		if (keys.find(SDLK_k) != keys.end())
			Player::getInstance()->position.y -= elapsed * 10;

		if (keys.find(SDLK_UP) != keys.end())
			dy += 1;
		if (keys.find(SDLK_DOWN) != keys.end())
			dy -= 1;
		if (keys.find(SDLK_LEFT) != keys.end())
			dx -= 1;
		if (keys.find(SDLK_RIGHT) != keys.end())
			dx += 1;

		//Update Variables
		Player::getInstance()->rotate(dx, dy);
		Player::getInstance()->update(elapsed);
		World::getInstance()->update(elapsed);

		if (Player::getInstance()->isDead)
		{
			gameOver = true;
		}
		if (World::getInstance()->isBossDead())
		{
			victory = true;
		}

		//Hit Detection
		Player::getInstance()->detectCollision(World::getInstance()->getCurrentRoom());
		for (Character* enemy : World::getInstance()->getActiveEnemies())
			Player::getInstance()->detectCollision(enemy);
		for (Teleporter* teleporter : World::getInstance()->getActiveTeleporters())
			Player::getInstance()->detectCollision(teleporter);
		for (int i = 0; i < World::getInstance()->getActiveEnemies().size(); ++i) {
			for (int j = i + 1; j < World::getInstance()->getActiveEnemies().size(); ++j) {
				World::getInstance()->getActiveEnemies().at(i)->detectCollision(World::getInstance()->getActiveEnemies().at(j));
			}
		}
		for (Character* enemy : World::getInstance()->getActiveEnemies())
			enemy->detectCollision(World::getInstance()->getCurrentRoom());

		//Target Update
		vector<Collidable*> possibleCollidables = vector<Collidable*>();
		for (Character* enemy : World::getInstance()->getActiveEnemies())
			possibleCollidables.push_back(enemy);
		Player::getInstance()->getTarget(possibleCollidables);

		Player::getInstance()->updateCameraPosition();

		// Shadow First Pass
		for(int i = 0; i < MAX_LIGHTS; i++)
		{
			shadowCam->look_at(World::getInstance()->getCurrentRoom()->lights[i],
				World::getInstance()->getCurrentRoom()->lightDirections[i],
				World::getInstance()->getCurrentRoom()->lightUps[i]);
			shadowCam->yon = 100;
			shadowCam->fov_h = 45;
			shadowCam->fov_v = 45;
			shadowProgram->use();
			shadowProgram->setUniform("hitheryon", vec3(shadowCam->hither, shadowCam->yon, shadowCam->yon - shadowCam->hither));
			shadowBuffers[i]->bind();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			shadowCam->draw(shadowProgram);
			World::getInstance()->draw(shadowProgram);
			Player::getInstance()->draw(shadowProgram);
			shadowBuffers[i]->unbind();

			positions[i] = shadowCam->position;
			colors[i] = vec4(1, 1, 1, 1);
			hithyons[i] = vec3(shadowCam->hither, shadowCam->yon, shadowCam->yon - shadowCam->hither);
			viewMatrixs[i] = shadowCam->calc_viewMatrix();
			projMatrixs[i] = shadowCam->calc_projMatrix();
            sbuffers[i] = new ImageTexture(*(reinterpret_cast<ImageTexture *>(shadowBuffers[i]->texture)));
		}
		

		// Draw the Shadow Buffer to the Screen
		/*shadowMesh = new SquareMesh(new ImageTexture(*(reinterpret_cast<ImageTexture *>(sbuffers[0]))));
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		screenProgram->use();
		shadowMesh->draw(screenProgram);*/

		// Shadow Second Pass
		pProgram->use();
		pProgram->setUniform("lightPos[0]", positions);
		pProgram->setUniform("lightColor[0]", colors);
		pProgram->setUniform("shadowbuffer1", sbuffers[0]);
		pProgram->setUniform("shadowbuffer2", sbuffers[1]);
		pProgram->setUniform("shadowbuffer3", sbuffers[2]);
		pProgram->setUniform("shadowbuffer4", sbuffers[3]);
		pProgram->setUniform("shadowbuffer5", sbuffers[4]);
		pProgram->setUniform("light_hitheryon[0]", hithyons);
		pProgram->setUniform("light_viewMatrix[0]", viewMatrixs);
		pProgram->setUniform("light_projMatrix[0]", projMatrixs);
		
		// Clear The Back Buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Set Uniforms And Draw To The Back Buffer
		pProgram->use();
		Player::getInstance()->drawCamera(pProgram);
		World::getInstance()->draw(pProgram);
		Player::getInstance()->draw(pProgram);
		
		//Flip The Buffers
        SDL_GL_SwapWindow(win);
    }

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	screenProgram->use();

	if(gameOver)
		gameOverScreen->draw(screenProgram);
	else if (victory)
		victoryScreen->draw(screenProgram);

	SDL_GL_SwapWindow(win);
	SDL_Delay(5000);

	exit(0);
}
