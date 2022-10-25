#include "game.h"
#include <iostream>

std::string nodeName = "RootNode";
bool scale = false;
game::game()
{
	leftStaticModel = nullptr;
	rightStaticModel = nullptr;
	frontStaticModel = nullptr;
	centerStaticModel = nullptr;
	mobileModel = nullptr;

	conteiner2 = nullptr;
	floor = nullptr;

	for (int i = 0; i < AMOUNT_POINT_LIGHTS; i++)
	{
		pointLight[i] = nullptr;
		pointLightBox[i] = nullptr;
	}

	directionalLight = nullptr;
	spotLight = nullptr;
	spotLightBox = nullptr;
	
	cubePearl = nullptr;
	cubeEmerald = nullptr;

	actualCam = nullptr;

	colors[0] = glm::vec4(0, 0, 0, 0);
	colors[1] = glm::vec4(1, 0, 0, 1);
	colors[2] = glm::vec4(0, 1, 0, 1);
	colors[3] = glm::vec4(0, 0, 1, 1);
	colors[4] = glm::vec4(1, 1, 0, 1);
	colors[5] = glm::vec4(0, 1, 1, 1);
	colors[6] = glm::vec4(1, 0, 1, 1);
	colors[7] = glm::vec4(1, 1, 1, 1);
	nextColor = colors[4];
	rotationSpeed = 2;
	timeBetweenChanges = 1;
	t = 0;
	currentColorIndex = 5;

	bpsManager = nullptr;
}

game::~game()
{

}

void game::draw()
{
	bpsManager->flagAllTrackEntities();

	if (drawPlanes)
	{
		bpsManager->drawPlanes();
	}
	
	//tileMap->draw();
	floor->draw();
	conteiner2->draw();

	for (int i = 0; i < AMOUNT_POINT_LIGHTS; i++)
	{
		pointLight[i]->draw();
		pointLightBox[i]->draw();
	}

	spotLight->draw();
	spotLightBox->draw();
	directionalLight->draw();

	mobileModel->draw();
	leftStaticModel->draw();
	rightStaticModel->draw();
	frontStaticModel->draw();
	centerStaticModel->draw();
}

void game::update()
{
	engine::OcclusionCulling::Update();

	if (isKeyPressed(ENGINE_KEY_0))
	{
		selectedEntity = pointLight[0];
		nodeName = "RootNode";
	}
	else if (isKeyPressed(ENGINE_KEY_1))
	{
		selectedEntity = pointLight[1];
		nodeName = "pCube2";
	}
	else if (isKeyPressed(ENGINE_KEY_2))
	{
		selectedEntity = pointLight[2];
		nodeName = "group1";
	}
	else if (isKeyPressed(ENGINE_KEY_3))
	{
		selectedEntity = pointLight[3];
		nodeName = "pCylinder1";
	}


	if (isKeyPressed(ENGINE_KEY_8))
	{
		drawPlanes = true;
	}
	else if (isKeyPressed(ENGINE_KEY_9))
	{
		drawPlanes = false;
	}
	
	glm::vec3 rotation = glm::vec3(0, 0, 0);
	glm::vec3 movement = glm::vec3(0, 0, 0);
	glm::vec3 front = glm::vec3(0, 0, -1);
	glm::vec3 up = glm::vec3(0, 1, 0);
	
	float movementSpeed = 0.05f;
	float rotationSpeed = 1.f;
	
	front.y = 0;
	
	if (isKeyPressed(ENGINE_KEY_UP))
	{
		movement += front * movementSpeed;
	}
	else if (isKeyPressed(ENGINE_KEY_DOWN))
	{
		movement -= front * movementSpeed;
	}
	
	if (isKeyPressed(ENGINE_KEY_LEFT))
	{
		movement -= glm::vec3(1, 0, 0) * movementSpeed;
	}
	else if (isKeyPressed(ENGINE_KEY_RIGHT))
	{
		movement += glm::vec3(1, 0, 0) * movementSpeed;
	}
	
	if (isKeyPressed(ENGINE_KEY_Q))
	{
		movement += up * movementSpeed;
	}
	else if (isKeyPressed(ENGINE_KEY_E))
	{
		movement -= up * movementSpeed;
	}
	
	if (isKeyPressed(ENGINE_KEY_I))
	{
		rotation.y -= engine::time::getDeltaTime() * rotationSpeed;
	}
	else if (isKeyPressed(ENGINE_KEY_O))
	{
		rotation.y += engine::time::getDeltaTime() * rotationSpeed;
	}
	
	if (isKeyPressed(ENGINE_KEY_K))
	{
		rotation.x -= engine::time::getDeltaTime() * rotationSpeed;
	}
	else if (isKeyPressed(ENGINE_KEY_L))
	{
		rotation.x += engine::time::getDeltaTime() * rotationSpeed;
	}
	
	if (isKeyPressed(ENGINE_KEY_R))
	{
		managingDirectionalLight = true;
		pointLight[0]->setColor(glm::vec4(0, 0, 0, 1));
	}
	else if (isKeyPressed(ENGINE_KEY_T))
	{
		managingDirectionalLight = false;
		pointLight[0]->setColor(glm::vec4(1, 0, 0, 1));
	}

	if (isKeyPressed(ENGINE_KEY_Z))
	{
		scale = true;
	}
	else if (isKeyPressed(ENGINE_KEY_X))
	{
		scale = false;
	}
	
	entityPos += movement;
	
	if (managingDirectionalLight)
	{
		engine::node* child = mobileModel->getChildWithName(nodeName);

		if (child != NULL)
		{
			std::cout << "childFound" << std::endl;

			if (scale)
			{
				child->setScale(child->getScale() + rotation);
			}
			else
			{
				child->setRot(child->getRot() + rotation);;
			}

			child->setPos(entityPos);
		}
	}
	else
	{
		if (scale)
		{
			mobileModel->setScale(mobileModel->getScale() + rotation);
		}
		else
		{
			mobileModel->setRot(mobileModel->getRot() + rotation);
		}

		mobileModel->setPos(entityPos);
	}
	
	mobileModel->setTransformations();
	leftStaticModel->setTransformations();
	rightStaticModel->setTransformations();
	frontStaticModel->setTransformations();
	centerStaticModel->setTransformations();

	for (int i = 0; i < AMOUNT_POINT_LIGHTS; i++)
	{
		pointLightBox[i]->setPos(pointLight[i]->getPos());
	}

	spotLightBox->setPos(spotLight->getPos());

	//camera movement
	float cameraMovementAmount = engine::time::getDeltaTime() * cameraSpeed;
	
	if (isKeyPressed(ENGINE_KEY_W))
	{
		actualCam->moveCamera(cameraMovementAmount, engine::MOVEMENT_DIRECTION::FRONT);
	}
	else if (isKeyPressed(ENGINE_KEY_S))
	{
		actualCam->moveCamera(cameraMovementAmount, engine::MOVEMENT_DIRECTION::BACK);
	}
	
	if (isKeyPressed(ENGINE_KEY_D))
	{
		actualCam->moveCamera(cameraMovementAmount, engine::MOVEMENT_DIRECTION::RIGHT);
	}
	else if (isKeyPressed(ENGINE_KEY_A))
	{
		actualCam->moveCamera(cameraMovementAmount, engine::MOVEMENT_DIRECTION::LEFT);
	}
	
	actualCam->rotateCamera(getMouseOffset());
	
	if (actualCam == thirdPersonCam)
	{
		thirdPersonCam->updateTargetPos(conteiner2->getPos());
	}
}

void game::init()
{
	scene = engine::modelImporter::chargeBaseNodeInfo((string)"../res/assets/j/scenefachera.fbx");

	mobileModel = scene->GetBaseNode()->getChildWithName("mobile");
	mobileModel->setRenderer(currentRenderer);
	leftStaticModel = scene->GetBaseNode()->getChildWithName("left");
	leftStaticModel->setRenderer(currentRenderer);
	rightStaticModel = scene->GetBaseNode()->getChildWithName("right");
	rightStaticModel->setRenderer(currentRenderer);
	frontStaticModel = scene->GetBaseNode()->getChildWithName("foward");
	frontStaticModel->setRenderer(currentRenderer);
	centerStaticModel = scene->GetBaseNode()->getChildWithName("center");
	centerStaticModel->setRenderer(currentRenderer);

	entityPos = mobileModel->getPos();

	glm::vec3 camPos = { 0, 8, 10 };
	glm::vec3 camView = { 0, -0.5f, 0.8f};
	glm::vec3 camUp = { 0, 1, 0 };
	firstPersonCam = new engine::firstPersonCamera(currentRenderer, camPos, camView, camUp, engine::PROJECTION::PERSPECTIVE);
	thirdPersonCam = new engine::thirdPersonCamera(currentRenderer, camPos, camView, camUp, engine::PROJECTION::PERSPECTIVE);
	actualCam = firstPersonCam;

	engine::OcclusionCulling::Init(firstPersonCam);

	conteiner2 = new engine::sprite(currentRenderer, "../res/assets/textures/container2.png", "../res/assets/textures/container2_specular.png", true, engine::MATERIAL::PEARL);
	conteiner2->setPos(glm::vec3(0, 1, 3));
	conteiner2->setScale(glm::vec3(2, 2, 2));
	conteiner2->setRot(glm::vec3(glm::radians(-90.0f), 0, 0));

	for (int i = 0; i < AMOUNT_POINT_LIGHTS; i++)
	{
		pointLight[i] = new engine::pointLight(currentRenderer);
		pointLight[i]->setColor(glm::vec4(1, 1, 1, 1));
		pointLight[i]->setPos(glm::vec3(-4 + 2 * i, 1, -3));
		
		pointLightBox[i] = new engine::shape(currentRenderer,engine::SHAPE::CUBE, engine::MATERIAL::PEARL);
		pointLightBox[i]->setScale(glm::vec3(0.5f, 0.5f, 0.5f));
		pointLightBox[i]->setPos(glm::vec3(-4 + 2 * i, 1, -3));
		
		switch (i)
		{
		case 0:
			pointLight[0]->setColor(glm::vec4(1, 0, 0, 1));
			break;
		case 1:
			pointLight[1]->setColor(glm::vec4(0, 1, 0, 1));
			break;
		case 2:
			pointLight[2]->setColor(glm::vec4(0, 0, 1, 1));
			break;
		case 3:
			pointLight[3]->setColor(glm::vec4(1, 1, 1, 1));
			break;
		default:
			break;
		}

	}
	
	directionalLight = new engine::directionalLight(currentRenderer);

	spotLight = new engine::spotLight(currentRenderer);
	spotLight->setPos({ 0,5,3 });
	spotLightBox = new engine::shape(currentRenderer, engine::SHAPE::CUBE, engine::MATERIAL::PEARL);
	spotLightBox->setScale(glm::vec3(0.5f, 0.5f, 0.5f));
	spotLightBox->setPos({ 0,5,3 });
	
	selectedEntity = spotLight;
	
	floor = new engine::sprite(currentRenderer, "../res/assets/textures/papa.png", "../res/assets/textures/papa.png", true, engine::MATERIAL::YELLOW_RUBBER);
	floor->setScale(glm::vec3(10, 10, 1));
	floor->setRot(glm::vec3(glm::radians(-90.0f), 0, 0));
	floor->setPos(glm::vec3(0,0,0));

	bpsManager = new engine::BSPManager();
	bpsManager->setCameraEntityForCheck(actualCam);
	bpsManager->addEnityToTrackList(mobileModel);
	bpsManager->addEnityToTrackList(leftStaticModel);
	bpsManager->addEnityToTrackList(rightStaticModel);
	bpsManager->addEnityToTrackList(frontStaticModel);
	bpsManager->addEnityToTrackList(centerStaticModel);
	bpsManager->addPlanesToTrackList(scene->GetBSPPlanes());
	bpsManager->setRendererForPlanes(currentRenderer);
}

void game::deInit()
{
	delete firstPersonCam;
	delete thirdPersonCam;

	conteiner2->deinit();
	delete conteiner2;

	floor->deinit();
	delete floor;

	for (int i = 0; i < AMOUNT_POINT_LIGHTS; i++)
	{
		delete pointLight[i];
		delete pointLightBox[i];
	}

	delete directionalLight;

	delete spotLight;
	delete spotLightBox;

	delete bpsManager;

	delete leftStaticModel;
	delete rightStaticModel;
	delete frontStaticModel;
	delete centerStaticModel;
	delete mobileModel;

	delete scene;
}