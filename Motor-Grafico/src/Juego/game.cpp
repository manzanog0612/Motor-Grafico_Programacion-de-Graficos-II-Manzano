#include "game.h"
#include <iostream>
#include "Motor/modelImporter.h"

std::string nodeName = "RootNode";
bool scale = false;
game::game()
{
	leftStaticModel = nullptr;
	rightStaticModel = nullptr;
	frontStaticModel = nullptr;
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

	//archer = nullptr;
	//triangle = nullptr;
	actualCam = nullptr;
	//tileMap = nullptr;
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

	//planeLeft = nullptr;
	//planeCenter = nullptr;
	//planeRight = nullptr;
	//
	//planeL = nullptr;

	bpsManager = nullptr;

	//archerRunLeftAnimationID = 0;
	//archerRunRightAnimationID = 0;
	//archerRunUpAnimationID = 0;
	//archerRunUpLeftAnimationID = 0;
	//archerRunUpRightAnimationID = 0;
	//archerRunDownAnimationID = 0;
	//archerRunDownLeftAnimationID = 0;
	//archerRunDownRightAnimationID = 0;
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

	//planeLeft->draw();
	//planeCenter->draw();
	//planeRight->draw();
	//
	//testModel->draw();

	//triangle->draw();
	//archer->draw();
}

void game::update()
{
	engine::OcclusionCulling::Update();
	/*t += engine::time::getDeltaTime();

	if (isKeyPressed(ENGINE_KEY_W) && isKeyPressed(ENGINE_KEY_A))
	{
		glm::vec3 pos = archer->getPos();
		archer->setPos(pos.x - engine::time::getDeltaTime() * runSpeed / 2, pos.y + engine::time::getDeltaTime() * runSpeed / 2, pos.z);
		archer->playAnimation(archerRunUpLeftAnimationID);
	}
	else if (isKeyPressed(ENGINE_KEY_W) && isKeyPressed(ENGINE_KEY_D))
	{
		glm::vec3 pos = archer->getPos();
		archer->setPos(pos.x + engine::time::getDeltaTime() * runSpeed / 2, pos.y + engine::time::getDeltaTime() * runSpeed / 2, pos.z);
		archer->playAnimation(archerRunUpRightAnimationID);
	}
	else if (isKeyPressed(ENGINE_KEY_S) && isKeyPressed(ENGINE_KEY_A))
	{
		glm::vec3 pos = archer->getPos();
		archer->setPos(pos.x - engine::time::getDeltaTime() * runSpeed / 2, pos.y - engine::time::getDeltaTime() * runSpeed / 2, pos.z);
		archer->playAnimation(archerRunDownLeftAnimationID);
	}
	else if (isKeyPressed(ENGINE_KEY_S) && isKeyPressed(ENGINE_KEY_D))
	{
		glm::vec3 pos = archer->getPos();
		archer->setPos(pos.x + engine::time::getDeltaTime() * runSpeed / 2, pos.y - engine::time::getDeltaTime() * runSpeed / 2, pos.z);
		archer->playAnimation(archerRunDownRightAnimationID);
	}
	else if(isKeyPressed(ENGINE_KEY_A))
	{
		glm::vec3 pos = archer->getPos();
		archer->setPos(pos.x - engine::time::getDeltaTime() * runSpeed, pos.y, pos.z);
		archer->playAnimation(archerRunLeftAnimationID);
	}
	else if(isKeyPressed(ENGINE_KEY_D))
	{
		glm::vec3 pos = archer->getPos();
		archer->setPos(pos.x + engine::time::getDeltaTime() * runSpeed, pos.y, pos.z);
		archer->playAnimation(archerRunRightAnimationID);
	}
	else if (isKeyPressed(ENGINE_KEY_W))
	{
		glm::vec3 pos = archer->getPos();
		archer->setPos(pos.x, pos.y + engine::time::getDeltaTime() * runSpeed, pos.z);
		archer->playAnimation(archerRunUpAnimationID);
	}
	else if (isKeyPressed(ENGINE_KEY_S))
	{
		glm::vec3 pos = archer->getPos();
		archer->setPos(pos.x, pos.y - engine::time::getDeltaTime() * runSpeed, pos.z);
		archer->playAnimation(archerRunDownAnimationID);
	}
	else
	{
		archer->stopAllAnimations();
	}*/

	//box movement

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
	
	float movementSpeed = 0.01f;
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

	//cout << "x = " << entityPos.x << " y = " << entityPos.y << " z = " << entityPos.z << endl;
	
	//selectedEntity->setPos(entityPos);
	
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


	//spotLight->setDirection(actualCam->getFront());
	//if (isKeyDown(ENGINE_KEY_ENTER))
	//{
	//	if (cam->getCameraType() == engine::MOVEMENT_TYPE::FPS)
	//	{
	//		cam->setCameraType(engine::MOVEMENT_TYPE::THIRD_PERSON);
	//	}
	//	else
	//	{
	//		cam->setCameraType(engine::MOVEMENT_TYPE::FPS);
	//	}
	//}
		
	/* 
	
	PARA METER ROTACI�N DE CAMARA PROXIMAMENTE

	if (isKeyPressed(ENGINE_KEY_K))
	{
		glm::vec3 rotation = { 0, 0, engine::time::getDeltaTime() * cameraSpeed };
	}
	else if (isKeyPressed(ENGINE_KEY_L))
	{
		glm::vec3 rotation = { 0, 0, engine::time::getDeltaTime() * -cameraSpeed };
	}
	
	*/

	/*if (isKeyDown(ENGINE_KEY_ENTER))
	{
		if (hasCollider(archer)) removeCollider(archer);
		else addCollider(archer, false);
	}*/

	//updateCollisions(tileMap);
}

void game::init()
{
	static engine::Model* scene = engine::modelImporter::chargeBaseNodeInfo((string)"../res/assets/j/scenefachera.fbx");//scenefachera

	//testModel = engine::modelImporter::chargeBaseNodeInfo((string)"../res/assets/j/scenefachera.fbx");
	//testModel->setRenderer(currentRenderer);
	//testModel->setRot(glm::vec3(0, 0, 0));
	//testModel->setScale(glm::vec3(1, 1, 1));

	mobileModel = scene->GetBaseNode()->getChildWithName("mobile");
	mobileModel->setRenderer(currentRenderer);
	leftStaticModel = scene->GetBaseNode()->getChildWithName("left");
	leftStaticModel->setRenderer(currentRenderer);
	rightStaticModel = scene->GetBaseNode()->getChildWithName("right");
	rightStaticModel->setRenderer(currentRenderer);
	frontStaticModel = scene->GetBaseNode()->getChildWithName("foward");
	frontStaticModel->setRenderer(currentRenderer);

	glm::vec3 camPos = { 0, 5, -3 };
	glm::vec3 camView = { 0, 0, -1 };
	glm::vec3 camUp = { 0, 1, 0 };
	firstPersonCam = new engine::firstPersonCamera(currentRenderer, camPos, camView, camUp, engine::PROJECTION::PERSPECTIVE);
	thirdPersonCam = new engine::thirdPersonCamera(currentRenderer, camPos, camView, camUp, engine::PROJECTION::PERSPECTIVE);
	actualCam = firstPersonCam;

	engine::OcclusionCulling::Init(firstPersonCam);
	//currentRenderer->shaderPro.use();
	//glm::mat4 model = glm::mat4(1.0f);
	//model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
	//model = glm::scale4(model, glm::vec3(10.0f, 10.0f, 10.0f));	// it's a bit too big for our scene, so scale it down
	//currentRenderer->shaderPro.setMat4("model", model);

	//tileMap = new engine::tileMap(currentRenderer);

	/*if (tileMap->importTileMap("../res/assets/tilemapreal.tmx"))
	{
		std::cout << "tilemap loaded";
	}
	else
	{
		std::cout << "tilemap failed to load";
	}*/

	/*triangle = new engine::shape(currentRenderer, 3);
	triangle->setScale(3, 3, 3);
	triangle->setPos(-14, -10, 0);
	triangle->setColor(1, 1, 0, 1);

	triangle2 = new engine::shape(currentRenderer, 3);
	triangle2->setScale(3, 3, 3);
	triangle2->setPos(-17, -10, 0);
	triangle2->setColor(1, 1, 0, 1);

	triangle3 = new engine::shape(currentRenderer, 3);
	triangle3->setScale(3, 3, 3);
	triangle3->setPos(-15.5, -7, 0);
	triangle3->setColor(1, 1, 0, 1);

	quad = new engine::shape(currentRenderer, 4);
	quad->setScale(5, 5, 5);
	quad->setPos(15, -10, 0);
	quad->setColor(0, 1, 1, 1);

	imageCampus = new engine::sprite(currentRenderer, "../res/assets/textures/Image Campus.png", true);
	imageCampus->setScale(glm::vec3(30, 20, 10));
	imageCampus->setPos(glm::vec3(0, -9.f, -.1f));

	container = new engine::sprite(currentRenderer, "../res/assets/textures/container.jpg", true);
	container->setScale(glm::vec3(10, 10, 10));
	container->setPos(glm::vec3(-15, 0, 0));*/

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

	//entityPos = { 0,5,3 };
	
	floor = new engine::sprite(currentRenderer, "../res/assets/textures/papa.png", "../res/assets/textures/papa.png", true, engine::MATERIAL::YELLOW_RUBBER);
	floor->setScale(glm::vec3(10, 10, 1));
	floor->setRot(glm::vec3(glm::radians(-90.0f), 0, 0));
	floor->setPos(glm::vec3(0,0,0));

	//planeLeft = new engine::sprite(currentRenderer, "../res/assets/textures/papa.png", "../res/assets/textures/papa.png", true, engine::MATERIAL::YELLOW_RUBBER);
	//planeLeft->setScale(glm::vec3(3, 3, 1));
	//planeLeft->setRot(glm::vec3(0, glm::radians(-90.0f), 0));
	//planeLeft->setPos(glm::vec3(-3, 1.5f, -2));
	//planeL = new engine::plane(glm::vec3(1, 0, 0), planeLeft->getPos());
	//
	//planeCenter = new engine::sprite(currentRenderer, "../res/assets/textures/papa.png", "../res/assets/textures/papa.png", true, engine::MATERIAL::YELLOW_RUBBER);
	//planeCenter->setScale(glm::vec3(3, 3, 1));
	//planeCenter->setRot(glm::vec3(0, 0, 0));
	//planeCenter->setPos(glm::vec3(0, 1.5f, -5));
	//
	//planeRight = new engine::sprite(currentRenderer, "../res/assets/textures/papa.png", "../res/assets/textures/papa.png", true, engine::MATERIAL::YELLOW_RUBBER);
	//planeRight->setScale(glm::vec3(3, 3, 1));
	//planeRight->setRot(glm::vec3(0, glm::radians(90.0f), 0));
	//planeRight->setPos(glm::vec3(3, 1.5f, -2));

	bpsManager = new engine::BSPManager();
	bpsManager->setCameraEntityForCheck(actualCam);
	bpsManager->addEnityToTrackList(mobileModel);
	bpsManager->addEnityToTrackList(leftStaticModel);
	bpsManager->addEnityToTrackList(rightStaticModel);
	bpsManager->addEnityToTrackList(frontStaticModel);
	bpsManager->addPlanesToTrackList(scene->GetBSPPlanes());
	bpsManager->setRendererForPlanes(currentRenderer);
	

	/*archer = new engine::sprite(currentRenderer, "../res/assets/textures/Atlas Sprites/archerFullAtlas.png", false);
	
	engine::atlasCutConfig archerRunAtlasConfig;

	archerRunAtlasConfig.CutByCount(10, 7, 6, 5, 8);
	archerRunLeftAnimationID = archer->createAnimation(archerRunAtlasConfig);

	archerRunAtlasConfig.CutByCount(10, 7, 0, 0, 8);
	archerRunRightAnimationID = archer->createAnimation(archerRunAtlasConfig);

	archerRunAtlasConfig.CutByCount(10, 7, 8, 0, 8);
	archerRunUpAnimationID = archer->createAnimation(archerRunAtlasConfig);

	archerRunAtlasConfig.CutByCount(10, 7, 2, 3, 8);
	archerRunDownAnimationID = archer->createAnimation(archerRunAtlasConfig);

	archerRunAtlasConfig.CutByCount(10, 7, 4, 2, 8);
	archerRunUpLeftAnimationID = archer->createAnimation(archerRunAtlasConfig);
	
	archerRunAtlasConfig.CutByCount(10, 7, 8, 4, 8);
	archerRunDownLeftAnimationID = archer->createAnimation(archerRunAtlasConfig);
	
	archerRunAtlasConfig.CutByCount(10, 7, 6, 1, 8);
	archerRunUpRightAnimationID = archer->createAnimation(archerRunAtlasConfig);
	
	archerRunAtlasConfig.CutByCount(10, 7, 0, 4, 8);
	archerRunDownRightAnimationID = archer->createAnimation(archerRunAtlasConfig);

	archer->setAnimationFullTime(archerRunRightAnimationID, .5f);
	archer->setAnimationFullTime(archerRunLeftAnimationID, .5f);
	archer->setAnimationFullTime(archerRunUpAnimationID, .5f);
	archer->setAnimationFullTime(archerRunUpLeftAnimationID, .5f);
	archer->setAnimationFullTime(archerRunDownAnimationID, .5f);
	archer->setAnimationFullTime(archerRunUpRightAnimationID, .5f);
	archer->setAnimationFullTime(archerRunDownLeftAnimationID, .5f);
	archer->setAnimationFullTime(archerRunDownRightAnimationID, .5f);

	archer->setScale(32, 32, 1);
	archer->setPos(-80, 20, 0);*/

	//changeClearColor(glm::vec4(.25, .25, .5, 1));
	//addCollider(archer, false);
	//addCollider(awesomeface, false);
	//addCollider(triangle, false);
	//addCollider(triangle2, false);
	//addCollider(triangle3, false);
	//addCollider(quad, true);
	//addCollider(container, true);
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
	delete mobileModel;

	//archer->deinit();
	//delete archer;
	//delete triangle;
}