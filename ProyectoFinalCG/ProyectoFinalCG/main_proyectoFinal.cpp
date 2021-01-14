/*---------------------------------------------------------*/
/* ----------------   Proyecto Final -----------------------*/
/*-----------------    2021-1   ---------------------------*/
/*-------- Alumnos: Monroy Velázquez Alejandra Sarahí 
						Cruz Zavala Miguel Angel	-------*/
#include <Windows.h>

#include <glad/glad.h>
#include <glfw3.h>	//main
#include <stdlib.h>		
#include <glm/glm.hpp>	//camera y model
#include <glm/gtc/matrix_transform.hpp>	//camera y model
#include <glm/gtc/type_ptr.hpp>
#include<time.h>

//Para incluir audio
#include <mmsystem.h>


#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>	//Texture

#define SDL_MAIN_HANDLED
#include <SDL/SDL.h>

#include <shader_m.h>
#include <camera.h>
#include <modelAnim.h>
#include <model.h>
#include <Skybox.h>
#include <iostream>

//#pragma comment(lib, "winmm.lib")

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void my_input(GLFWwindow *window);
void my_input(GLFWwindow* window, int key, int scancode, int action, int mods);
void animate(void);
void animacionKeyFrames();

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 50.0f, 500.0f));
float MovementSpeed = 0.1f;
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
const int FPS = 60;
const int LOOP_TIME = 1000 / FPS; // = 16 milisec // 1000 millisec == 1 sec
double	deltaTime = 0.0f,
		lastFrame = 0.0f;

//Lighting
glm::vec3 lightPosition(0.0f, 4.0f, -10.0f);
glm::vec3 lightDirection(0.0f, -1.0f, -1.0f);


//Variables animación pelota
float	movPelota_x = 0.0f,
		movPelota_z = 0.0f;

bool	animacion_pelota = false,
		recorrido1_pelota = true,
		recorrido2_pelota = false,
		recorrido3_pelota = false,
		recorrido4_pelota = false;

//Variables animación escoba
float	movEscoba_x = 0.0f,
		movEscoba_z = 0.0f,
		giroEscoba = 0.0f;

bool	animacion_escoba = false,
		recorrido1_escoba = true,
		recorrido2_escoba = false,
		izquierda_escoba = true,
		derecha_escoba = false;

//Variables animación colibri
float	velocidad_colibri = 1.0f,
		refGiroColibri_x = 0.0f,
		refGiroColibri_z = 0.0f,
		giroColibri = 0.0f,
		subeBajaColibri = 0.0f,
		variacionSubeBaja = 0.0f,
		movColibri_x = 0.0f;

bool	animacion_colibri = false,
		subiendo = true,
		bajando = false,
		recorrido1_colibri = true,
		recorrido2_colibri = false,
		recorrido3_colibri = false,
		recorrido4_colibri = false,
		recorrido5_colibri = false,
		recorrido6_colibri = false,
		recorrido7_colibri = false;

//Variables animación virus
float	movVirus_x = 0.0f,
		movVirus_y = 0.0f,
		rotarVirus = 0.0f;

bool	animacion_virus = false;

//Techo
float	escalaTecho = 5.0f;

//Keyframes (Manipulación y dibujo)
float	posX = 0.0f,
		posY = 0.0f,
		posZ = 0.0f,
		rotX = 0.0f,
		rotZ = 0.0f;
float	incX = 0.0f,
		incY = 0.0f,
		incZ = 0.0f,
		rotInc = 0.0f,
		rotZInc = 0.0f;

#define MAX_FRAMES 13
int i_max_steps = 60;
int i_curr_steps = 0;
typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float posX;		//Variable para PosicionX
	float posY;		//Variable para PosicionY
	float posZ;		//Variable para PosicionZ
	float rotX;
	float rotZ;

}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 0;			//introducir datos
bool play = false;
int playIndex = 0;

void saveFrame(void)
{
	//printf("frameindex %d\n", FrameIndex);
	std::cout << "Frame Index = " << FrameIndex << std::endl;

	KeyFrame[FrameIndex].posX = posX;
	KeyFrame[FrameIndex].posY = posY;
	KeyFrame[FrameIndex].posZ = posZ;

	KeyFrame[FrameIndex].rotX = rotX;
	KeyFrame[FrameIndex].rotZ = rotZ;

	FrameIndex++;
}

void animacionKeyFrames(void)
{
	//Frame 0
	KeyFrame[0].posX = 0;
	KeyFrame[0].posY = 0;
	KeyFrame[0].posZ = 0;
	KeyFrame[0].rotX = 0;
	KeyFrame[0].rotZ = 0;
	//Frame 1
	KeyFrame[1].posX = 0;
	KeyFrame[1].posY = 2;
	KeyFrame[1].posZ = -3;
	KeyFrame[1].rotX = -96;
	KeyFrame[1].rotZ = -25;
	//Frame 2
	KeyFrame[2].posX = -3;
	KeyFrame[2].posY = 2;
	KeyFrame[2].posZ = -1;
	KeyFrame[2].rotX = -96;
	KeyFrame[2].rotZ = 30;
	//Frame 3
	KeyFrame[3].posX = 5;
	KeyFrame[3].posY = 2;
	KeyFrame[3].posZ = -8;
	KeyFrame[3].rotX = -96;
	KeyFrame[3].rotZ = 30;
	//Frame 4
	KeyFrame[4].posX = -3;
	KeyFrame[4].posY = 2;
	KeyFrame[4].posZ = -6;
	KeyFrame[4].rotX = -96;
	KeyFrame[4].rotZ = 30;
	//Frame 5
	KeyFrame[5].posX = 5;
	KeyFrame[5].posY = 2;
	KeyFrame[5].posZ = -13;
	KeyFrame[5].rotX = -96;
	KeyFrame[5].rotZ = 30;
	//Frame 6
	KeyFrame[6].posX = -6;
	KeyFrame[6].posY = 2;
	KeyFrame[6].posZ = -1;
	KeyFrame[6].rotX = -96;
	KeyFrame[6].rotZ = -29;
	//Frame 7
	KeyFrame[7].posX = 1;
	KeyFrame[7].posY = 2;
	KeyFrame[7].posZ = -8;
	KeyFrame[7].rotX = -96;
	KeyFrame[7].rotZ = -21;
	//Frame 8
	KeyFrame[8].posX = -6;
	KeyFrame[8].posY = 2;
	KeyFrame[8].posZ = -4;
	KeyFrame[8].rotX = -96;
	KeyFrame[8].rotZ = -32;
	//Frame 9
	KeyFrame[9].posX = -1;
	KeyFrame[9].posY = 2;
	KeyFrame[9].posZ = -13;
	KeyFrame[9].rotX = -96;
	KeyFrame[9].rotZ = -20;
	//Frame 10
	KeyFrame[10].posX = -6;
	KeyFrame[10].posY = 2;
	KeyFrame[10].posZ = -9;
	KeyFrame[10].rotX = -96;
	KeyFrame[10].rotZ = -32;
	//Frame 11
	KeyFrame[11].posX = -3;
	KeyFrame[11].posY = 2;
	KeyFrame[11].posZ = -1;
	KeyFrame[11].rotX = -96;
	KeyFrame[11].rotZ = 4;

	FrameIndex = 13;
}

void resetElements(void)
{
	posX = KeyFrame[0].posX;
	posY = KeyFrame[0].posY;
	posZ = KeyFrame[0].posZ;

	rotX = KeyFrame[0].rotX;
	rotZ = KeyFrame[0].rotZ;
}

void interpolation(void)
{
	incX = (KeyFrame[playIndex + 1].posX - KeyFrame[playIndex].posX) / i_max_steps;
	incY = (KeyFrame[playIndex + 1].posY - KeyFrame[playIndex].posY) / i_max_steps;
	incZ = (KeyFrame[playIndex + 1].posZ - KeyFrame[playIndex].posZ) / i_max_steps;

	rotInc = (KeyFrame[playIndex + 1].rotX - KeyFrame[playIndex].rotX) / i_max_steps;
	rotZInc = (KeyFrame[playIndex + 1].rotZ - KeyFrame[playIndex].rotZ) / i_max_steps;

}


void animate(void)
{
	if (play)
	{
		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			if (playIndex > FrameIndex - 2)	//end of total animation?
			{
				std::cout << "Animation ended" << std::endl;
				//printf("termina anim\n");
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
								  //Interpolation
				interpolation();
			}
		}
		else
		{
			//Draw animation
			posX += incX;
			posY += incY;
			posZ += incZ;

			rotX += rotInc;
			rotZ += rotZInc;

			i_curr_steps++;
		}
	}

	//Pelota
	if (animacion_pelota)
	{
		if (recorrido1_pelota)
		{
			movPelota_x += 0.2f;
			movPelota_z += 0.25f;
			if (movPelota_x >= 40 && movPelota_z >= 50)
			{
				recorrido1_pelota = false;
				recorrido2_pelota = true;
			}
		}
		if (recorrido2_pelota)
		{
			movPelota_x += 0.25f;
			movPelota_z -= 0.25f;
			if (movPelota_x >= 110 && movPelota_z <= -20)
			{
				recorrido2_pelota = false;
				recorrido3_pelota = true;
			}
		}
		if (recorrido3_pelota)
		{
			movPelota_x -= 0.34375f;
			movPelota_z -= 0.25f;
			if (movPelota_x <= 55 && movPelota_z <= -60)
			{
				recorrido3_pelota = false;
				recorrido4_pelota = true;
			}
		}
		if (recorrido4_pelota)
		{
			movPelota_x -= 0.22915;
			movPelota_z += 0.25f;
			if (movPelota_x <= 0 && movPelota_z >= 0)
			{
				recorrido4_pelota = false;
				recorrido1_pelota = true;
			}
		}
	}

	//Escoba
	if (animacion_escoba)
	{
		if (izquierda_escoba) {
			giroEscoba -= 0.5;
			if (giroEscoba < -15) {
				izquierda_escoba = false;
				derecha_escoba = true;
			}
		}
		if (derecha_escoba) {
			giroEscoba += 0.5;
			if (giroEscoba > 15) {
				izquierda_escoba = true;
				derecha_escoba = false;
			}
		}
		if(recorrido1_escoba){
			movEscoba_z -= 0.1;
			if (movEscoba_z < -8) {
				recorrido1_escoba = false;
				recorrido2_escoba = true;
			}

		}
		if (recorrido2_escoba) {
			movEscoba_z += 0.1;
			if (movEscoba_z > 8) {
				recorrido2_escoba = false;
				recorrido1_escoba = true;
			}

		}
	}

	//Colibri
	if (animacion_colibri)
	{
		//Sube y baja
		if (movColibri_x < 800) {
			variacionSubeBaja = (movColibri_x / 90);
		}
		else {
			variacionSubeBaja = (movColibri_x / 110);
		}

		if (subiendo) {
			subeBajaColibri += 0.01;
			if (subeBajaColibri >= 10 - variacionSubeBaja) {
				subiendo = false;
				bajando = true;
			}
		}
		if (bajando) {
			subeBajaColibri -= 0.01;
			if (subeBajaColibri <= -10 + variacionSubeBaja) {
				subiendo = true;
				bajando = false;
			}
		}

		//Recorrido
		if (recorrido1_colibri)
		{
			movColibri_x += velocidad_colibri;
			if (movColibri_x >= 135)
			{
				recorrido1_colibri = false;
				recorrido2_colibri = true;
				giroColibri = 90;
				refGiroColibri_z = 340;
				refGiroColibri_x = -30;
			}
		}
		if (recorrido2_colibri)
		{
			movColibri_x += velocidad_colibri;
			if (movColibri_x >= 135 + 415)
			{
				recorrido2_colibri = false;
				recorrido3_colibri = true;
				giroColibri = 180;
				refGiroColibri_z = -45;
				refGiroColibri_x = 715;
			}
		}
		if (recorrido3_colibri)
		{
			movColibri_x += velocidad_colibri;
			if (movColibri_x >= 550 + 170)
			{
				recorrido3_colibri = false;
				recorrido4_colibri = true;
				giroColibri = 270;
				refGiroColibri_z = -965;
				refGiroColibri_x = 160;
			}
		}
		if (recorrido4_colibri)
		{
			movColibri_x += velocidad_colibri;
			if (movColibri_x >= 885)
			{
				recorrido4_colibri = false;
				recorrido5_colibri = true;
				giroColibri = 0;
				refGiroColibri_z = -245;
				refGiroColibri_x = -925;
			}
		}
		if (recorrido5_colibri)
		{
			movColibri_x += velocidad_colibri;
			if (movColibri_x >= 1055)
			{
				recorrido5_colibri = false;
				recorrido6_colibri = true;
				giroColibri = 270;
				refGiroColibri_z = -1130;
				refGiroColibri_x = 335;
			}
		}
		if (recorrido6_colibri)
		{
			movColibri_x += velocidad_colibri;
			if (movColibri_x >= 1295)
			{
				recorrido6_colibri = false;
				recorrido7_colibri = true;
				giroColibri = 180;
				refGiroColibri_z = 365;
				refGiroColibri_x = 1465;
			}
		}
		if (recorrido7_colibri)
		{
			movColibri_x += velocidad_colibri;
			if (movColibri_x >= 1425)
			{
				recorrido7_colibri = false;
				recorrido1_colibri = true;
				giroColibri = 0;
				refGiroColibri_z = 0;
				refGiroColibri_x = 0;
				movColibri_x = 0;
			}
		}
	}

	//Virus
	if (animacion_virus)
	{
		movVirus_x += 0.125f;
		movVirus_y += 0.25f;
		rotarVirus -= 0.5f;
		if (movVirus_x >= 10 && movVirus_y >= 80)
		{

			movVirus_x = 0.0;
			movVirus_y = 0.0f;
			rotarVirus = 0.0f;
		}
	}
}

void sonido() {

	sndPlaySound("resources/music/NymanoGreenTea.wav", SND_ASYNC);
}

void sonido();

int main()
{
	// glfw: initialize and configure
	glfwInit();

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Practica 12", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, my_input);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// build and compile shaders
	// -------------------------
	Shader staticShader("Shaders/shader_Lights.vs", "Shaders/shader_Lights.fs");
	Shader skyboxShader("Shaders/skybox.vs", "Shaders/skybox.fs");
	Shader animShader("Shaders/anim.vs", "Shaders/anim.fs");

	vector<std::string> faces
	{
		"resources/skybox/posx.jpg",
		"resources/skybox/negx.jpg",
		"resources/skybox/posy.jpg",
		"resources/skybox/negy.jpg",
		"resources/skybox/posz.jpg",
		"resources/skybox/negz.jpg"
	};

	Skybox skybox = Skybox(faces);

	// Shader configuration
	// --------------------
	skyboxShader.use();
	skyboxShader.setInt("skybox", 0);

	// load models
	
	//--------------------------------Escenario-------------------------------------------//
	Model suelo("resources/objects/Suelo/Suelo.obj");
	Model muros("resources/objects/Muros/Muros.obj");
	Model techo("resources/objects/Techo/Techo.obj");
	Model ventanas("resources/objects/Ventanas/Ventanas.obj");
	Model puertas("resources/objects/Puertas/Puertas.obj");
	Model puertaPrincipal("resources/objects/Puertas/Puerta_Principal.obj");
	Model marcoPuertaPrincipal("resources/objects/Puertas/Marco_Puerta_Principal.obj");
	
	//--------------------------------Carro-------------------------------------------//
	Model carro("resources/objects/lambo/carroceria.obj");
	Model llanta("resources/objects/lambo/Wheel.obj");
	
	//--------------------------------Alberca----------------------------------------------//
	Model alberca("resources/objects/Alberca/Alberca.obj");
	Model escaleras("resources/objects/Alberca/Escaleras.obj");
	Model agua("resources/objects/Alberca/agua.obj");

	//--------------------------------Cocina/Comedor---------------------------------------//
	Model cocina("resources/objects/Cocina/Cocina.obj");
	Model comedor("resources/objects/Comedor/Comedor.obj");
	
	//--------------------------------Lavanderia-------------------------------------------//
	Model lavanderia("resources/objects/Lavanderia/Lavanderia.obj");

	//--------------------------------Sala------------------------------------------------//
	Model planta("resources/objects/Planta/Planta.obj");
	Model mueblesSala("resources/objects/MueblesSala/MueblesSala.obj");
	Model sillonesSala("resources/objects/SillonesSala/SillonesSala.obj");
	Model tele("resources/objects/Tele/Tele.obj");

	//---------------------------------Baños----------------------------------------------//
	Model vater("resources/objects/Vater/vater.obj");
	Model shower("resources/objects/Ducha/ducha.obj");
	Model lavabo1("resources/objects/Lavabo1/Lavabo1.obj");
	Model lavabo11("resources/objects/Lavabo1.1/Lavabo1.1.obj");
	Model lavabo2("resources/objects/Lavabo2/Lavabo2.obj");
	Model lavabo3("resources/objects/Lavabo3/Lavabo3.obj");

	//--------------------------------Recamaras------------------------------------------//
	Model sillon("resources/objects/Sillones/Sillones.obj");
	Model mesaNoche("resources/objects/MesasNoche/MesasNoche.obj");
	Model closet("resources/objects/Closets/Closets.obj");
	Model cama1("resources/objects/CamaPrincipal/CamaPrincipal.obj");
	Model cama2("resources/objects/Cama2/Cama2.obj");
	Model cama3("resources/objects/Cama3/Cama3.obj");

	//-------------------------------Animaciones-----------------------------------------//
	Model virus("resources/objects/Covid/Covid.obj");
	Model colibri("resources/objects/Colibri/Colibri.obj");
	Model escoba("resources/objects/Escoba/Escoba.obj");
	Model pelota("resources/objects/Pelota/Pelota.obj");
	Model plancha("resources/objects/Plancha/Plancha.obj");


	//Inicialización de KeyFrames
	for (int i = 0; i < MAX_FRAMES; i++)
	{
		KeyFrame[i].posX = 0;
		KeyFrame[i].posY = 0;
		KeyFrame[i].posZ = 0;
		KeyFrame[i].rotX = 0;
		KeyFrame[i].rotZ = 0;
	}

	// draw in wireframe
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		skyboxShader.setInt("skybox", 0);
		
		// per-frame time logic
		// --------------------
		lastFrame = SDL_GetTicks();

		// input
		// -----
		//my_input(window);
		animate();

		// render
		// ------
		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// don't forget to enable shader before setting uniforms
		staticShader.use();
		//Setup Advanced Lights
		staticShader.setVec3("viewPos", camera.Position);
		staticShader.setVec3("dirLight.direction", lightDirection);
		staticShader.setVec3("dirLight.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
		staticShader.setVec3("dirLight.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
		staticShader.setVec3("dirLight.specular", glm::vec3(0.0f, 0.0f, 0.0f));

		staticShader.setVec3("pointLight[0].position", lightPosition);
		staticShader.setVec3("pointLight[0].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[0].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[0].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[0].constant", 0.8f);
		staticShader.setFloat("pointLight[0].linear", 0.009f);
		staticShader.setFloat("pointLight[0].quadratic", 0.032f);

		staticShader.setVec3("pointLight[1].position", glm::vec3(0.0, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[1].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[1].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[1].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[1].constant", 1.0f);
		staticShader.setFloat("pointLight[1].linear", 0.009f);
		staticShader.setFloat("pointLight[1].quadratic", 0.032f);

		staticShader.setFloat("material_shininess", 32.0f);

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 tmp = glm::mat4(1.0f);
		
		// view/projection transformations
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
		glm::mat4 view = camera.GetViewMatrix();
		staticShader.setMat4("projection", projection);
		staticShader.setMat4("view", view);

		//// Light
		glm::vec3 lightColor = glm::vec3(1.0f);
		glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
		glm::vec3 ambientColor = diffuseColor * glm::vec3(0.75f);

		// -------------------------------------------------------------------------------------------------------------------------
		// Escenario
		// -------------------------------------------------------------------------------------------------------------------------
		staticShader.use();
		staticShader.setMat4("projection", projection);
		staticShader.setMat4("view", view);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		staticShader.setMat4("model", model);
		suelo.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(escalaTecho, escalaTecho, escalaTecho));
		staticShader.setMat4("model", model);
		techo.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		staticShader.setMat4("model", model);
		ventanas.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		staticShader.setMat4("model", model);
		puertas.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		staticShader.setMat4("model", model);
		puertaPrincipal.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		staticShader.setMat4("model", model);
		marcoPuertaPrincipal.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		staticShader.setMat4("model", model);
		muros.Draw(staticShader);

		// -------------------------------------------------------------------------------------------------------------------------
		// Carro
		// -------------------------------------------------------------------------------------------------------------------------
		model = glm::mat4(1.0f);
		tmp= model = glm::translate(model, glm::vec3(-90.0f, 0.0f, 200.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		staticShader.setMat4("model", model);
		carro.Draw(staticShader);

		model = glm::translate(tmp, glm::vec3(17.0f, 6.5f, 25.4f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		staticShader.setMat4("model", model);
		llanta.Draw(staticShader);	//Izq delantera

		model = glm::translate(tmp, glm::vec3(-17.0f, 6.5f, 25.4f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		llanta.Draw(staticShader);	//Der delantera

		model = glm::translate(tmp, glm::vec3(-17.0f, 6.5f, -27.4f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		llanta.Draw(staticShader);	//Der trasera

		model = glm::translate(tmp, glm::vec3(17.0f, 6.5f, -27.4f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		staticShader.setMat4("model", model);
		llanta.Draw(staticShader);	//Izq trase

		// -------------------------------------------------------------------------------------------------------------------------
		// Alberca
		// -------------------------------------------------------------------------------------------------------------------------
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		staticShader.setMat4("model", model);
		alberca.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		staticShader.setMat4("model", model);
		escaleras.Draw(staticShader);


		// -------------------------------------------------------------------------------------------------------------------------
		// Cocina/Comedor
		// -------------------------------------------------------------------------------------------------------------------------
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		staticShader.setMat4("model", model);
		comedor.Draw(staticShader); 
		
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		staticShader.setMat4("model", model);
		cocina.Draw(staticShader);

		// -------------------------------------------------------------------------------------------------------------------------
		// Lavanderia
		// -------------------------------------------------------------------------------------------------------------------------
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		staticShader.setMat4("model", model);
		lavanderia.Draw(staticShader);

		// -------------------------------------------------------------------------------------------------------------------------
		// Sala
		// -------------------------------------------------------------------------------------------------------------------------
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		staticShader.setMat4("model", model);
		planta.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		staticShader.setMat4("model", model);
		mueblesSala.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		staticShader.setMat4("model", model);
		sillonesSala.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		staticShader.setMat4("model", model);
		tele.Draw(staticShader);

		// -------------------------------------------------------------------------------------------------------------------------
		// Baños
		// -------------------------------------------------------------------------------------------------------------------------
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		staticShader.setMat4("model", model);
		vater.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		staticShader.setMat4("model", model);
		shower.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		staticShader.setMat4("model", model);
		lavabo1.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		staticShader.setMat4("model", model);
		lavabo11.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		staticShader.setMat4("model", model);
		lavabo2.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		staticShader.setMat4("model", model);
		lavabo3.Draw(staticShader);

		// -------------------------------------------------------------------------------------------------------------------------
		// Recamaras
		// -------------------------------------------------------------------------------------------------------------------------
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		staticShader.setMat4("model", model);
		sillon.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		staticShader.setMat4("model", model);
		mesaNoche.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		staticShader.setMat4("model", model);
		closet.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		staticShader.setMat4("model", model);
		cama1.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		staticShader.setMat4("model", model);
		cama2.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		staticShader.setMat4("model", model);
		cama3.Draw(staticShader);

		// -------------------------------------------------------------------------------------------------------------------------
		// Animaciones
		// -------------------------------------------------------------------------------------------------------------------------
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(movVirus_x, movVirus_y, 80.0f));
		model = glm::rotate(model, glm::radians(rotarVirus), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		staticShader.setMat4("model", model);
		virus.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(refGiroColibri_x, 0.0f, refGiroColibri_z));
		model = glm::rotate(model, glm::radians(giroColibri), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(subeBajaColibri), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(movColibri_x, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		staticShader.setMat4("model", model);
		colibri.Draw(staticShader);


		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f + movPelota_x, 0.0f, 0.0f + movPelota_z));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		staticShader.setMat4("model", model);
		pelota.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -48));
		model = glm::rotate(model, glm::radians(giroEscoba), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, 0.5f, 48 + movEscoba_z));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		staticShader.setMat4("model", model);
		escoba.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(132 + posX, 22 + posY, 104 + posZ));
		model = glm::rotate(model, glm::radians(0 + rotX), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(0 + rotZ), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		staticShader.setMat4("model", model);
		plancha.Draw(staticShader);

		// -------------------------------------------------------------------------------------------------------------------------
		// Caja Transparente para Alberca
		// -------------------------------------------------------------------------------------------------------------------------
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		staticShader.setMat4("model", model);
		agua.Draw(staticShader);

		glEnable(GL_BLEND);
		// -------------------------------------------------------------------------------------------------------------------------
		// Termina Escenario
		// -------------------------------------------------------------------------------------------------------------------------

		//-------------------------------------------------------------------------------------
		// draw skybox as last
		// -------------------
		skyboxShader.use();
		skybox.Draw(skyboxShader, view, projection, camera);

		// Limitar el framerate a 60
		deltaTime = SDL_GetTicks() - lastFrame; // time for full 1 loop
		//std::cout <<"frame time = " << frameTime << " milli sec"<< std::endl;
		if (deltaTime < LOOP_TIME)
		{
			SDL_Delay((int)(LOOP_TIME - deltaTime));
		}

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	skybox.Terminate();

	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void my_input(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, (float)deltaTime);
	//To Configure Model

	//Animacion Pelota
	if (key == GLFW_KEY_KP_7 && action == GLFW_PRESS) {
		animacion_pelota = !animacion_pelota;
	}

	//Animacion Escoba
	if (key == GLFW_KEY_KP_8 && action == GLFW_PRESS) {
		animacion_escoba = !animacion_escoba;
	}

	//Animacion Colibri
	if (key == GLFW_KEY_KP_9 && action == GLFW_PRESS) {
		animacion_colibri = !animacion_colibri;
	}

	//Animacion Virus
	if (key == GLFW_KEY_KP_4 && action == GLFW_PRESS) {
		animacion_virus = !animacion_virus;
	}

	//Ocultar Techo
	if (key == GLFW_KEY_T && action == GLFW_PRESS) {
		if (escalaTecho == 5.0f)
			escalaTecho = 0.0f;
		else
			escalaTecho = 5.0f;
	}
		

	//To play KeyFrame animation 
	if (key == GLFW_KEY_KP_5 && action == GLFW_PRESS)
	{
		animacionKeyFrames();
		if (play == false && (FrameIndex > 1))
		{
			std::cout << "Play animation" << std::endl;
			resetElements();
			//First Interpolation				
			interpolation();

			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play = false;
			std::cout << "Not enough Key Frames" << std::endl;
		}
	}

	//To Save a KeyFrame
	if (key == GLFW_KEY_L && action == GLFW_PRESS)
	{
		if (FrameIndex < MAX_FRAMES)
		{
			saveFrame();
		}
	}
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
		sonido();
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
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

	camera.ProcessMouseMovement(xoffset, yoffset);
}
// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}