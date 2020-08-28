#pragma once
#include "GameObject.hpp"
#include "GameParamerts.hpp"
#include <cstdio>
#include <vector>
#include <memory>
#include "SupportingFunctions.hpp"
class GameEventBox {
	bool _locked;
	bool _ClickCatching;
	bool _blocksAdjustment;
	bool _placedInOrder;
	bool _swap;
	bool _newBlocksAdjustment;
	bool _deleteion;
	bool _combinationChecking = true;
	int _numOfClicks = 0;
	bool _showNewBlocks;
	bool _bomb;
	bool _minibomb;
	bool _bonusHandling;
public:
	GameEventBox() { Reset(); }

	void ActivateBomb() { _bomb = true; }
	bool IsBombActive() { return _bomb; }
	void DeactivateBomb() { _bomb = false; }

	void ActivateMiniBomb() { _minibomb = true; }
	bool IsMiniBombActive() { return _minibomb; }
	void DeactivateMiniBomb() { _minibomb = false; }

	bool ShowNewBlocks() { return _showNewBlocks; }
	void ConfirmShowingNewBlocks() { _showNewBlocks = true; }
	void CancelShowingNewBlocks() { _showNewBlocks = false; }

	bool ArePlacedInOrder(){ return _placedInOrder; }
	void ConfirmOrdering() { _placedInOrder = true; }
	void CancelOrdering() { _placedInOrder = false; }
	bool IsCombinationCheck() { return _combinationChecking; }
	void ConfirmCombinationChecking() { _combinationChecking = true; }
	void CancelCombinationChecking() { _combinationChecking = false; }

	bool IsLocked() { return _locked; }
	void Unlock() { _locked = false; }
	void Lock() { _locked = true; }

	void IncreaseNumOfClicks() { _numOfClicks++; }
	void DecreaseNumOfClicks() { _numOfClicks--; }
	int NumOfClicks() { return _numOfClicks; }
	void ResetClicks() { _numOfClicks = 0; }

	bool PerformCatching() { return _ClickCatching; }
	void ConfirmCatching() { _ClickCatching = true; }
	void CancelCatching() { _ClickCatching = false; }

	bool IsBlocksAdjustment(){ return _blocksAdjustment; }
	void ConfirmBlockAdjustment() { _blocksAdjustment = true; }
	void CancelBlockAdjustment() { _blocksAdjustment = _placedInOrder = false; }

	bool IsSwap() { return _swap; }
	void ConfirmSwap() { _swap = true; }
	void CancelSwap() { _swap = false; }

	bool IsNewBlocksAdjustment() { return _newBlocksAdjustment; }
	void ConfirmNewBlockAdjustment() { _newBlocksAdjustment = true; }
	void CancelNewBlockAdjustment() { _newBlocksAdjustment = false; }

	bool IsDeletion() { return _deleteion; }
	void ConfirmDeletion() { _deleteion = true; }
	void CancelSDeletion() { _deleteion = false; }

	void HandleBonuses() { _bonusHandling = true; }
	void StopHandlingBonuses() { _bonusHandling = false; }
	bool BonusHandlingActive() { return _bonusHandling; }

	void Reset() {_bonusHandling = _blocksAdjustment = _swap = _newBlocksAdjustment = _deleteion = _ClickCatching = _locked = _placedInOrder = _showNewBlocks = _bomb = _minibomb = false;}
};
class Game {
	sf::Vector2i InstantMousePosition;
	sf::Vector2i MousePos1;
	sf::Vector2i MousePos2;
	std::shared_ptr<GameObject> firstlyClickedBlock;
	std::vector<std::vector<std::vector<sf::Vector2i>>> combinationsTable;
	std::vector<std::vector<sf::Vector2i>> ordered;
	std::vector<std::vector<std::shared_ptr<GameObject>>> blocks;
	void DrawTable(sf::RenderWindow& Window);
	std::shared_ptr<GameEventBox> Box;
	std::shared_ptr<GameObject> FindElement(sf::Vector2i& indices);
	void ProcessMouseClicks();
	//bool _in_combination(int level, sf::Vector2i& position, std::vector<sf::Vector2i>& isVisiting, sf::Color col);
	void DetectCombinations();
	bool MarkCombinations();
	void Deletion();
	sf::Vector2i PressedBlockIndices();
	void ShowNewBlocks();
	void ProcessSwap();
	void PlaceInOrder();
	void Adjust();
	void AdjustNewBlocks();
	void ProcessBonuses();
	void InvokeBonus();
	bool IndicesAreValid(sf::Vector2i& indices) { return indices.x != -1 && indices.y != -1; };
public:
	Game();
	void Launch();
};