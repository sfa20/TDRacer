#include "engine.h"
#include "maths.h"
#include "system_physics.h"
#include "system_renderer.h"
#include "system_resources.h"
#include <SFML/Graphics.hpp>
#include <future>
#include <iostream>
#include <stdexcept>
#include "../TDRacer/game.h"
#include "LevelSystem.h"
#include "../TDRacer/components/cmp_sprite.h"

using namespace sf;
using namespace std;
Scene* Engine::_activeScene = nullptr;
std::string Engine::_gameName;

static bool loading = false;
static float loadingspinner = 0.f;
static float loadingTime;
static RenderWindow* _window;
static Event* _event;

void Loading_update(float dt, const Scene* const scn) {
	//  cout << "Eng: Loading Screen\n";
	if (scn->isLoaded()) {
		cout << "Eng: Exiting Loading Screen\n";
		loading = false;
	}
	else {
		loadingspinner += 220.0f * dt;
		loadingTime += dt;
	}
}
void Loading_render() {
	// cout << "Eng: Loading Screen Render\n";
	static CircleShape octagon(80, 8);
	octagon.setOrigin(80, 80);
	octagon.setRotation(loadingspinner);
	octagon.setPosition(Vcast<float>(Engine::getWindowSize()) * .5f);
	octagon.setFillColor(Color(255, 255, 255, min(255.f, 40.f*loadingTime)));
	static Text t("Loading", *Resources::get<sf::Font>("RobotoMono-Regular.ttf"));
	t.setFillColor(Color(255, 255, 255, min(255.f, 40.f*loadingTime)));
	t.setPosition(Vcast<float>(Engine::getWindowSize()) * Vector2f(0.4f, 0.3f));
	Renderer::queue(&t);
	Renderer::queue(&octagon);
}

float frametimes[256] = {};
uint8_t ftc = 0;

void Engine::Update() {
	static sf::Clock clock;
	float dt = clock.restart().asSeconds();
	{
		frametimes[++ftc] = dt;
		static string avg = _gameName + " FPS:";
		if (ftc % 60 == 0) {
			double davg = 0;
			for (const auto t : frametimes) {
				davg += t;
			}
			davg = 1.0 / (davg / 255.0);
			_window->setTitle(avg + toStrDecPt(2, davg));
		}
	}

	if (loading) {
		Loading_update(dt, _activeScene);
	}
	else if (_activeScene != nullptr) {
		Physics::update(dt);
		_activeScene->Update(dt);
	}
}

void Engine::Render(RenderWindow& window) {
	if (loading) {
		Loading_render();
	}
	else if (_activeScene != nullptr) {
		_activeScene->Render();
	}

	Renderer::render();
}

void Engine::Start(unsigned int width, unsigned int height, const std::string& gameName, Scene* scn, bool isFullscreen) {

	auto screenType = isFullscreen ? sf::Style::Fullscreen : sf::Style::Resize;

	RenderWindow window(VideoMode(width, height), gameName, screenType);
	Event events;
	_gameName = gameName;
	_window = &window;
	_event = &events;
	Renderer::initialise(window);
	Physics::initialise();
	ChangeScene(scn);
	while (window.isOpen()) {
		while (window.pollEvent(events)) {
			if (events.type == Event::Closed) {
				window.close();
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
		}

		window.clear();
		Update();
		Render(window);
		window.display();
	}

	if (_activeScene != nullptr) {
		_activeScene->UnLoad();
		_activeScene = nullptr;
	}

	window.close();
	Physics::shutdown();
	// Render::shutdown();
}

std::shared_ptr<Entity> Scene::makeEntity() {
	auto e = make_shared<Entity>(this);
	ents.list.push_back(e);
	return std::move(e);
}

void Engine::setVsync(bool b) { _window->setVerticalSyncEnabled(b); }

void Engine::ChangeScene(Scene* s) {
	cout << "Eng: changing scene: " << s << endl;
	auto old = _activeScene;
	_activeScene = s;

	if (old != nullptr) {
		old->UnLoad(); // todo: Unload Async
	}

	if (!s->isLoaded()) {
		cout << "Eng: Entering Loading Screen\n";
		loadingTime = 0;
		_activeScene->LoadAsync();
		loading = true;
	}
}

void Scene::Update(const double& dt) { ents.update(dt); }

void Scene::Render() { ents.render(); }

bool Scene::isLoaded() const {
	{
		std::lock_guard<std::mutex> lck(_loaded_mtx);
		// Are we already loading asynchronously?
		if (_loaded_future.valid() // yes
			&&                     // Has it finished?
			_loaded_future.wait_for(chrono::seconds(0)) ==
			future_status::ready) {
			// Yes
			try
			{
				_loaded_future.get();
				_loaded = true;
			}
			catch (const std::exception&)
			{

			}

		}
		return _loaded;
	}
}

void Scene::setLoaded(bool b) {
	{
		std::lock_guard<std::mutex> lck(_loaded_mtx);
		_loaded = b;
	}
}

void Scene::UnLoad() {
	ents.list.clear();
	setLoaded(false);
}

void Scene::LoadAsync() { _loaded_future = std::async(&Scene::Load, this); }

//added
//void Scene::CheckScreenRes() {
//	if (nWidth == 1920 && nHeight == 1080) {
//		scale = { 0.400f, 0.400f };
//		size = 50.f;
//	}
//	else if (nWidth == 1280 && nHeight == 720) {
//		scale = { 0.395f, 0.395f };
//		size = 34.f;
//	}
//	else if (nWidth == 1024 && nHeight == 600) {
//		scale = { 0.300f, 0.300f };
//		size = 50.f;
//	}
//}

void Scene::MapSetup() {
	auto startTilesLeft = ls::findTiles(ls::STARTLEFT);
	for each (auto t in startTilesLeft) {
		static shared_ptr<Entity> start;
		start = makeEntity();
		//add a new sprite component, set texture and scale
		auto c = start->addComponent<SpriteComponent>();
		c->getSprite().setTexture(*Resources::get<Texture>("Straights/startLine_vertical_noBorder_right.png"));
		c->getSprite().setScale(scale);

		//get tile position - vector 2f
		auto p = ls::getTilePosition(t);
		start->setPosition(p);
	}

	auto startTilesRight = ls::findTiles(ls::STARTRIGHT);
	for each (auto t in startTilesRight) {
		static shared_ptr<Entity> start;
		start = makeEntity();
		//add a new sprite component, set texture and scale
		auto c = start->addComponent<SpriteComponent>();
		c->getSprite().setTexture(*Resources::get<Texture>("Straights/startLine_vertical_noBorder_left.png"));
		c->getSprite().setScale(scale);

		//get tile position - vector 2f
		auto p = ls::getTilePosition(t);
		start->setPosition(p);
	}

	auto startTiles = ls::findTiles(ls::START);
	for each (auto t in startTiles) {
		static shared_ptr<Entity> start;
		start = makeEntity();
		//add a new sprite component, set texture and scale
		auto c = start->addComponent<SpriteComponent>();
		c->getSprite().setTexture(*Resources::get<Texture>("Straights/startLine_vertical_noBorder.png"));
		c->getSprite().setScale(scale);

		//get tile position - vector 2f
		auto p = ls::getTilePosition(t);
		start->setPosition(p);
	}

	//Get position of grass tiles and set sprites to each position
	auto grassTiles = ls::findTiles(ls::GRASS);
	for each (auto t in grassTiles)
	{
		static shared_ptr<Entity> grass;
		grass = makeEntity();
		//Add a new sprite component set texture and scale
		auto t3 = grass->addComponent<SpriteComponent>();
		t3->getSprite().setTexture(*Resources::get<Texture>("grass.png"));
		t3->getSprite().setScale(scale);

		//get tile position - vector2f
		auto g = ls::getTilePosition(t);
		grass->setPosition(g);

	}


	auto wallTiles = ls::findTiles(ls::WALL);
	for each (auto t in wallTiles)
	{
		static shared_ptr<Entity> wall;
		wall = makeEntity();
		//Add a new sprite component set texture and scale
		auto t3 = wall->addComponent<SpriteComponent>();
		t3->getSprite().setTexture(*Resources::get<Texture>("grass.png"));
		t3->getSprite().setScale(scale);

		//get tile position - vector2f
		auto g = ls::getTilePosition(t);
		wall->setPosition(g);

	}


	//Get position of TopTrack tiles and set sprites to each postition
	auto peakTiles = ls::findTiles(ls::TOP);
	for each (auto t in peakTiles)
	{
		static shared_ptr<Entity> peak;
		peak = makeEntity();
		//Add a new sprite component set texture and scale
		auto t2 = peak->addComponent<SpriteComponent>();
		t2->getSprite().setTexture(*Resources::get<Texture>("Straights/straight_horizontal_noBorder_bottom.png"));
		t2->getSprite().setScale(scale);

		//get tile position - vector2f
		auto g = ls::getTilePosition(t);
		peak->setPosition(g);

	}

	//Get position of BottomTrack tiles and set sprites to each postition
	auto bottomTiles = ls::findTiles(ls::BOTTOM);
	for each (auto t in bottomTiles)
	{
		static shared_ptr<Entity> bottom;
		bottom = makeEntity();

		//Add a new sprite component set texture and scale
		auto t2 = bottom->addComponent<SpriteComponent>();
		t2->getSprite().setTexture(*Resources::get<Texture>("Straights/straight_horizontal_noBorder_top.png"));
		t2->getSprite().setScale(scale);

		//get tile position - vector2f
		auto g = ls::getTilePosition(t);
		bottom->setPosition(g);

	}

	//Get position of RightTrack tiles and set sprites to each postition
	auto rightTiles = ls::findTiles(ls::RIGHT);
	for each (auto t in rightTiles)
	{
		static shared_ptr<Entity> right;
		right = makeEntity();

		//Add a new sprite component set texture and scale
		auto t2 = right->addComponent<SpriteComponent>();
		t2->getSprite().setTexture(*Resources::get<Texture>("Straights/straight_vertical_noBorder_left.png"));
		t2->getSprite().setScale(scale);

		//get tile position - vector2f
		auto g = ls::getTilePosition(t);
		right->setPosition(g);
	}

	//Get position of LeftTrack tiles and set sprites to each postition
	auto leftTiles = ls::findTiles(ls::LEFT);
	for each (auto t in leftTiles)
	{
		static shared_ptr<Entity> left;
		left = makeEntity();
		//Add a new sprite component set texture and scale
		auto t2 = left->addComponent<SpriteComponent>();
		t2->getSprite().setTexture(*Resources::get<Texture>("Straights/straight_vertical_noBorder_right.png"));
		t2->getSprite().setScale(scale);

		//get tile position - vector2f
		auto g = ls::getTilePosition(t);
		left->setPosition(g);

	}

	//Get position of track tiles and set sprites to each postition
	auto trackTiles = ls::findTiles(ls::TRACK);
	for each (auto t in trackTiles)
	{
		static shared_ptr<Entity> track;
		track = makeEntity();
		//Add a new sprite component set texture and scale
		auto t2 = track->addComponent<SpriteComponent>();
		t2->getSprite().setTexture(*Resources::get<Texture>("Straights/straight_noBorder.png"));
		t2->getSprite().setScale(scale);

		//get tile position - vector2f
		auto g = ls::getTilePosition(t);
		track->setPosition(g);

	}

	//Get position of Corner tiles and set sprites to each postition
	auto corner1Tiles = ls::findTiles(ls::CORNER1);
	for each (auto t in corner1Tiles)
	{
		static shared_ptr<Entity> corn1;
		corn1 = makeEntity();

		auto t1 = corn1->addComponent<SpriteComponent>();
		t1->getSprite().setTexture(*Resources::get<Texture>("grass.png"));
		t1->getSprite().setScale(scale);
		//Add a new sprite component set texture and scale
		auto t2 = corn1->addComponent<SpriteComponent>();
		t2->getSprite().setTexture(*Resources::get<Texture>("Corners/90DegreeTopRight.png"));
		t2->getSprite().setScale(scale);


		//get tile position - vector2f
		auto g = ls::getTilePosition(t);
		corn1->setPosition(g);

	}

	//Get position of track tiles and set sprites to each postition
	auto corner2Tiles = ls::findTiles(ls::CORNER2);
	for each (auto t in corner2Tiles)
	{
		static shared_ptr<Entity> corn2;
		corn2 = makeEntity();
		auto t1 = corn2->addComponent<SpriteComponent>();
		t1->getSprite().setTexture(*Resources::get<Texture>("grass.png"));
		t1->getSprite().setScale(scale);
		//Add a new sprite component set texture and scale
		auto t2 = corn2->addComponent<SpriteComponent>();
		t2->getSprite().setTexture(*Resources::get<Texture>("Corners/90DegreeTopLeft.png"));
		t2->getSprite().setScale(scale);

		//get tile position - vector2f
		auto g = ls::getTilePosition(t);
		corn2->setPosition(g);

	}

	//Get position of track tiles and set sprites to each postition
	auto corner3Tiles = ls::findTiles(ls::CORNER3);
	for each (auto t in corner3Tiles)
	{
		static shared_ptr<Entity> corn3;
		corn3 = makeEntity();
		auto t1 = corn3->addComponent<SpriteComponent>();
		t1->getSprite().setTexture(*Resources::get<Texture>("grass.png"));
		t1->getSprite().setScale(scale);
		//Add a new sprite component set texture and scale
		auto t2 = corn3->addComponent<SpriteComponent>();
		t2->getSprite().setTexture(*Resources::get<Texture>("Corners/90DegreeBottomLeft.png"));
		t2->getSprite().setScale(scale);

		//get tile position - vector2f
		auto g = ls::getTilePosition(t);
		corn3->setPosition(g);

	}

	//Get position of track tiles and set sprites to each postition
	auto corner4Tiles = ls::findTiles(ls::CORNER4);
	for each (auto t in corner4Tiles)
	{
		static shared_ptr<Entity> corn4;
		corn4 = makeEntity();
		auto t1 = corn4->addComponent<SpriteComponent>();
		t1->getSprite().setTexture(*Resources::get<Texture>("grass.png"));
		t1->getSprite().setScale(scale);
		//Add a new sprite component set texture and scale
		auto t2 = corn4->addComponent<SpriteComponent>();
		t2->getSprite().setTexture(*Resources::get<Texture>("Corners/90DegreeBottomRight.png"));
		t2->getSprite().setScale(scale);


		//get tile position - vector2f
		auto g = ls::getTilePosition(t);
		corn4->setPosition(g);

	}

}

sf::Vector2u Engine::getWindowSize() { return _window->getSize(); }

sf::RenderWindow& Engine::GetWindow() { return *_window; }

sf::Event& Engine::GetEvent() { return *_event; }

namespace timing {
	// Return time since Epoc
	long long now() {
		return std::chrono::high_resolution_clock::now()
			.time_since_epoch()
			.count();
	}
	// Return time since last() was last called.
	long long last() {
		auto n = now();
		static auto then = now();
		auto dt = n - then;
		then = n;
		return dt;
	}
} // namespace timing

Scene::~Scene() { UnLoad(); }