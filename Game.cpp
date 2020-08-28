#include "Game.hpp"
#include <stack>
#include <tuple>
static bool resolved(sf::Vector2i& pos) {
	return pos.x == -1 && pos.y == -1;
}
Game::Game() {
	Box = std::make_shared<GameEventBox>();
	ordered.resize(TABLE_WIDTH);
	sf::Vector2f position(INITIAL_X, INITIAL_Y);
	sf::Vector2f blockSize(BLOCK_SIDE, BLOCK_SIDE);
	sf::Vector2f delta(DELTA, DELTA);
	blocks.resize(TABLE_HEIGHT);
	combinationsTable.resize(TABLE_HEIGHT);
	for (int i = 0; i < TABLE_HEIGHT; i++)
		combinationsTable[i].resize(TABLE_WIDTH);
	for (int i = 0; i < TABLE_HEIGHT; i++) {
		for (int j = 0; j < TABLE_WIDTH; j++) {
			std::shared_ptr<GameObject> block;
			block = std::make_shared<GameObject>(blockSize, position, COLOR_MODES[rand() % 7], sf::Vector2i(i, j));
			blocks[i].push_back(block);
			position.x += delta.x;
		}
		position.x = INITIAL_X;
		position.y += delta.y;
	}
	for (int i = 0; i < TABLE_HEIGHT; i++)
		for (int j = 0; j < TABLE_WIDTH; j++)
			combinationsTable[i][j].push_back(blocks[i][j]->getTableIndices());
}
void Game::InvokeBonus() {
	int bonustype = rand() % 3;
	if (bonustype == 0)
		Box->ActivateBomb();
	else if (bonustype == 1)
		Box->ActivateMiniBomb();
}
void Game::Launch() {
	sf::RenderWindow Window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "GEMS");
	Window.setFramerateLimit(FRAME_RATE);
	while (Window.isOpen()) {
		sf::Event ev;
		while (Window.pollEvent(ev)) {
			if (ev.type == sf::Event::Closed)
				Window.close();
			else if (ev.type == sf::Event::MouseButtonPressed && ev.key.code == sf::Mouse::Left && Box->PerformCatching()) {
				Box->IncreaseNumOfClicks();
				InstantMousePosition = sf::Mouse::getPosition(Window);
				//printf("%i, %i ", InstantMousePosition.x, InstantMousePosition.y);
			}
		}
		Window.clear(BACKGROUND_COLOR);
		DrawTable(Window);
		Window.display();
		DetectCombinations();
		Deletion();
		Adjust();
		AdjustNewBlocks();
		ShowNewBlocks();
		ProcessBonuses();
		ProcessMouseClicks();
		ProcessSwap();
		Window.clear(BACKGROUND_COLOR);
		DrawTable(Window);
		Window.display();
	}
}
void Game::DrawTable(sf::RenderWindow& Window) {
	for (int i = 0; i < TABLE_HEIGHT; i++)
		for (int j = 0; j < TABLE_WIDTH; j++)
			if (blocks[i][j]->Opacity() > 0)
				blocks[i][j]->draw(Window);
}
void Game::PlaceInOrder() {
	for (int j = 0; j < TABLE_WIDTH; j++) {
		for (int i = TABLE_HEIGHT - 1; i >= 0; i--) {
			auto curBlock = FindElement(sf::Vector2i(i, j));
			if (curBlock->InCombination() == false)
				ordered[j].push_back(curBlock->getTableIndices());
		}
	}
}
void Game::Adjust() {
	if (Box->IsBlocksAdjustment() == false)
		return;
	if (Box->ArePlacedInOrder() == false) {
		PlaceInOrder();
		Box->ConfirmOrdering();
	}
	for (int j = 0; j < TABLE_WIDTH; j++)
		for (int i = 0; i < ordered[j].size(); i++) {
			if (resolved(ordered[j][i]))
				continue;
			auto block1 = FindElement(ordered[j][i]);//mousepos2
			sf::Vector2f InstantPos1(block1->getInstantPosition());
			sf::Vector2f RealPos1(INITIAL_X + BLOCK_SIDE * j, INITIAL_Y + BLOCK_SIDE * (TABLE_HEIGHT - 1 - i));
			if (InstantPos1.y - RealPos1.y != 0) {
				block1->setPosition(sf::Vector2f(InstantPos1.x, InstantPos1.y + VELOCITY));
			}
			else {
				ordered[j][i].x = ordered[j][i].y = -1;
				block1->setIndices(sf::Vector2i(TABLE_HEIGHT - 1 - i, j));
			}
		}
	for (int j = 0; j < TABLE_WIDTH; j++)
		for (int i = 0; i < ordered[j].size(); i++) {
			if (!resolved(ordered[j][i]))
				return;
		}
	for (int j = 0; j < TABLE_WIDTH; j++)
		ordered[j].clear();
	Box->CancelBlockAdjustment();
	Box->ConfirmNewBlockAdjustment();
}
void Game::Deletion() {
	if (Box->IsDeletion() == false)
		return;
	for (int i = 0; i < TABLE_HEIGHT; i++)
		for (int j = 0; j < TABLE_WIDTH; j++) {
			if (blocks[i][j]->InCombination()) {
				int op = blocks[i][j]->Opacity();
				if (op <= 0) {
					Box->CancelSDeletion();
					Box->ConfirmBlockAdjustment();
					return;
				}
				blocks[i][j]->ReduceOpacityBy(OPACITY_FALL);
			}
		}
}

void Game::DetectCombinations() {
	if (Box->IsCombinationCheck() == false)
		return;
	bool combinationsExist = MarkCombinations();
	Box->CancelCombinationChecking();
	if (combinationsExist)
		Box->ConfirmDeletion();
	else {
		Box->ConfirmCatching();
		Box->DeactivateBomb();
		Box->DeactivateMiniBomb();
	}
}
void Game::AdjustNewBlocks() {
	if (Box->IsNewBlocksAdjustment() == false)
		return;
	std::vector<std::vector<std::shared_ptr<GameObject>>> ClearBlocks(TABLE_WIDTH);
	for (int i = 0; i < TABLE_HEIGHT; i++)
		for (int j = 0; j < TABLE_WIDTH; j++) {
			if (blocks[i][j]->InCombination())
				ClearBlocks[blocks[i][j]->getTableIndices().y].push_back(blocks[i][j]);
		}
	for (int j = 0; j < TABLE_WIDTH; j++) {
		for (int i = 0; i < ClearBlocks[j].size(); i++) {
			ClearBlocks[j][i]->setIndices(sf::Vector2i(i, j));
			ClearBlocks[j][i]->SetColor(COLOR_MODES[rand() % 7]);
			ClearBlocks[j][i]->setPosition(sf::Vector2f(INITIAL_X + BLOCK_SIDE * j, INITIAL_Y + BLOCK_SIDE * i));
		}
	}
	for (int i = 0; i < TABLE_HEIGHT; i++)
		for (int j = 0; j < TABLE_WIDTH; j++)
			blocks[i][j]->DeleteFromCombination();
	Box->CancelNewBlockAdjustment();
	Box->ConfirmShowingNewBlocks();
}
void Game::ShowNewBlocks() {
	if (Box->ShowNewBlocks() == false)
		return;
	bool end = true;
	for (int i = 0; i < TABLE_HEIGHT; i++)
		for (int j = 0; j < TABLE_WIDTH; j++) {
			if (blocks[i][j]->Opacity() < 255) {
				blocks[i][j]->ReduceOpacityBy(-OPACITY_FALL);
				end = false;
			}
		}
	if (end) {
		Box->CancelShowingNewBlocks();
		Box->HandleBonuses();
	}
}
void Game::ProcessBonuses() {
	if (Box->BonusHandlingActive() == false)
		return;
	if (!Box->IsBombActive() && !Box->IsMiniBombActive()) {
		Box->StopHandlingBonuses();
		Box->ConfirmCombinationChecking();
		return;
	}
	if (Box->IsMiniBombActive()) {
		for (int i = 0; i < 2; i++) {
			auto block = FindElement(sf::Vector2i((TABLE_HEIGHT - 1) & rand(), (TABLE_WIDTH - 1) & rand()));
			block->SetColor(COLOR_MODES[rand() % 7]);
		}
	}
	else {
		for (int i = 0; i < 5; i++) {
			auto block = FindElement(sf::Vector2i((TABLE_HEIGHT - 1) & rand(), (TABLE_WIDTH - 1) & rand()));
			block->AddInCombination();
		}
	}
	Box->ConfirmCombinationChecking();
	Box->DeactivateBomb();
	Box->DeactivateMiniBomb();
}
/*bool Game::_in_combination(int level, sf::Vector2i& position, std::vector<sf::Vector2i>& isVisiting, sf::Color col) {
	if (support::IsIn(position, isVisiting) || support::IsOutOfBounds(position))
		return false;
	isVisiting.push_back(position);
	auto block = FindElement(position);
	if (block->GetColor() == col)
		level++;
	else
		return false;
	bool path1 = _in_combination(level, sf::Vector2i(position.x + 1, position.y), isVisiting, col);
	bool path2 = _in_combination(level, sf::Vector2i(position.x - 1, position.y), isVisiting, col);
	bool path3 = _in_combination(level, sf::Vector2i(position.x, position.y + 1), isVisiting, col);
	bool path4 = _in_combination(level, sf::Vector2i(position.x, position.y - 1), isVisiting, col);
	if ((level >= SUFFICIENT_ORDER_OF_COMBINATION) || (path1 || path2 || path3 || path4)) {
		block->AddInCombination();
		return true;
	}
	return false;
}*/
bool Game::MarkCombinations() {
	bool detected = false;
	std::shared_ptr<GameObject> currentElement;
	std::shared_ptr<GameObject> upper;
	std::shared_ptr<GameObject> lower;
	std::shared_ptr<GameObject> left;
	std::shared_ptr<GameObject> right;
	std::vector<sf::Vector2i> uni;
	for (int i = 0; i < TABLE_HEIGHT; i++)
		for (int j = 0; j < TABLE_WIDTH; j++) {
			currentElement = FindElement(sf::Vector2i(i, j));
			if (!support::IsOutOfBounds(sf::Vector2i(i + 1, j))) {
				upper = FindElement(sf::Vector2i(i + 1, j));
				if (upper->GetColor() == currentElement->GetColor()) {
					uni = support::FindUnion(combinationsTable[i][j], combinationsTable[i + 1][j]);
					combinationsTable[i][j].clear();
					combinationsTable[i + 1][j].clear();
					combinationsTable[i][j] = uni;
					combinationsTable[i + 1][j] = uni;
				}
			}
			if (!support::IsOutOfBounds(sf::Vector2i(i - 1, j))) {
				lower = FindElement(sf::Vector2i(i - 1, j));
				if (lower->GetColor() == currentElement->GetColor()) {
					uni = support::FindUnion(combinationsTable[i][j], combinationsTable[i - 1][j]);
					combinationsTable[i][j].clear();
					combinationsTable[i - 1][j].clear();
					combinationsTable[i][j] = uni;
					combinationsTable[i - 1][j] = uni;
				}
			}
			if (!support::IsOutOfBounds(sf::Vector2i(i, j - 1))) {
				left = FindElement(sf::Vector2i(i, j - 1));
				if (left->GetColor() == currentElement->GetColor()) {
					uni = support::FindUnion(combinationsTable[i][j], combinationsTable[i][j - 1]);
					combinationsTable[i][j].clear();
					combinationsTable[i][j - 1].clear();
					combinationsTable[i][j] = uni;
					combinationsTable[i][j - 1] = uni;
				}
			}
			if (!support::IsOutOfBounds(sf::Vector2i(i, j + 1))) {
				right = FindElement(sf::Vector2i(i, j + 1));
				if (right->GetColor() == currentElement->GetColor()) {
					uni = support::FindUnion(combinationsTable[i][j], combinationsTable[i][j + 1]);
					combinationsTable[i][j].clear();
					combinationsTable[i][j + 1].clear();
					combinationsTable[i][j] = uni;
					combinationsTable[i][j + 1] = uni;
				}
			}
		}
	for (int i = 0; i < TABLE_HEIGHT; i++)
		for (int j = 0; j < TABLE_WIDTH; j++) {
			if (combinationsTable[i][j].size() >= SUFFICIENT_ORDER_OF_COMBINATION) {
				detected = true;
				for (int k = 0; k < combinationsTable[i][j].size(); k++) {
					currentElement = FindElement(combinationsTable[i][j][k]);
					currentElement->AddInCombination();
				}
			}
		}
	for (int i = 0; i < TABLE_HEIGHT; i++)
		for (int j = 0; j < TABLE_WIDTH; j++) {
			combinationsTable[i][j].clear();
			combinationsTable[i][j].push_back(sf::Vector2i(i, j));
		}
	return detected;
}
std::shared_ptr<GameObject> Game::FindElement(sf::Vector2i& indices) {
	for (int i = 0; i < TABLE_HEIGHT; i++)
		for (int j = 0; j < TABLE_WIDTH; j++) {
			auto temp = blocks[i][j]->getTableIndices();
			if (temp.x == indices.x && temp.y == indices.y)
				return blocks[i][j];
		}
	return nullptr;
}
void Game::ProcessSwap() {
	if (Box->IsSwap() == false)
		return;
	auto block1 = FindElement(MousePos2);
	auto block2 = FindElement(MousePos1);
	sf::Vector2f InstantPos1(block1->getInstantPosition());
	sf::Vector2f InstantPos2(block2->getInstantPosition());
	sf::Vector2f RealPos1(INITIAL_X + BLOCK_SIDE * MousePos1.y, INITIAL_Y + BLOCK_SIDE * MousePos1.x);
	sf::Vector2f RealPos2(INITIAL_X + BLOCK_SIDE * MousePos2.y, INITIAL_Y + BLOCK_SIDE * MousePos2.x);
	if (InstantPos1.x - RealPos1.x != 0 || InstantPos1.y - RealPos1.y != 0) {
		if (MousePos1.x == MousePos2.x) {
			if (RealPos1.x > InstantPos1.x) {
				block1->setPosition(sf::Vector2f(InstantPos1.x + VELOCITY, InstantPos1.y));
				block2->setPosition(sf::Vector2f(InstantPos2.x - VELOCITY, InstantPos2.y));
			}
			else {
				block1->setPosition(sf::Vector2f(InstantPos1.x - VELOCITY, InstantPos1.y));
				block2->setPosition(sf::Vector2f(InstantPos2.x + VELOCITY, InstantPos2.y));
			}
		}
		else {
			if (RealPos1.y > InstantPos1.y) {
				block1->setPosition(sf::Vector2f(InstantPos1.x, InstantPos1.y + VELOCITY));
				block2->setPosition(sf::Vector2f(InstantPos2.x, InstantPos2.y - VELOCITY));
			}
			else {
				block1->setPosition(sf::Vector2f(InstantPos1.x, InstantPos1.y - VELOCITY));
				block2->setPosition(sf::Vector2f(InstantPos2.x, InstantPos2.y + VELOCITY));
			}
		}
	}
	else {
		auto temp = block1->getTableIndices();
		block1->setIndices(block2->getTableIndices());
		block2->setIndices(temp);
		Box->ResetClicks();
		Box->CancelSwap();
		Box->ConfirmCombinationChecking();
	}
}
void Game::ProcessMouseClicks() {
	if (Box->PerformCatching() == false)
		return;
	int num = Box->NumOfClicks();
	if (num == 0)
		return;
	if (num == 1 && Box->IsLocked())
		return;
	sf::Vector2i temp;
	temp = PressedBlockIndices();
	if (IndicesAreValid(temp) == false) {
		Box->DecreaseNumOfClicks();
		return;
	}
	if (num == 1) {
		MousePos1 = temp;
		Box->Lock();
	}
	else {
		MousePos2 = temp;
		if (MousePos1 == MousePos2)
			Box->ResetClicks();
		else if ((abs(MousePos1.x - MousePos2.x) > 1 || abs(MousePos1.y - MousePos2.y) > 1) || (abs(MousePos1.x - MousePos2.x) == 1 && abs(MousePos1.y - MousePos2.y) == 1))
			Box->DecreaseNumOfClicks();
		else {
			Box->CancelCatching();
			Box->ConfirmSwap();
		}
		Box->Unlock();
	}
}
sf::Vector2i Game::PressedBlockIndices() {
	for (int i = 0; i < TABLE_HEIGHT; i++)
		for (int j = 0; j < TABLE_WIDTH; j++) {
			sf::Vector2f pos = blocks[i][j]->getInstantPosition();
			if ((InstantMousePosition.x > pos.x && InstantMousePosition.x < (pos.x + BLOCK_SIDE)) && (InstantMousePosition.y > pos.y && InstantMousePosition.y < (pos.y + BLOCK_SIDE)))
				return blocks[i][j]->getTableIndices();
		}
	return sf::Vector2i(-1, -1);
}