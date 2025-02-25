#include <Geode/modify/LevelSearchLayer.hpp>

using namespace geode::prelude;

class $modify(MyLevelSearchLayer, LevelSearchLayer) {
	static void onModify(auto& self) {
		if (Loader::get()->isModLoaded("devcmb.cleanermenu")) (void) self.setHookPriorityAfterPost("LevelSearchLayer::init", "devcmb.cleanermenu");
		else (void) self.setHookPriority("LevelSearchLayer::init", -3001);
	}
	void moveStuff() {
		geode::Mod* cleanerMenu = Loader::get()->getLoadedMod("devcmb.cleanermenu");
		const bool isTitlesHidden = cleanerMenu || Mod::get()->getSettingValue<bool>("hide-titles");

		CCSize winSize = CCDirector::get()->getWinSize();

		CCNode* levelSearchBg = this->getChildByID("level-search-bg");
		if (!levelSearchBg) return;
		CCNode* levelSearchBarBg = this->getChildByID("level-search-bar-bg");
		if (!levelSearchBarBg) return;
		CCNode* searchBar = this->getChildByID("search-bar");
		if (!searchBar) return;

		CCNode* quickSearchTitle = this->getChildByID("quick-search-title");
		if (!quickSearchTitle) return;
		CCNode* quickSearchBG = this->getChildByID("quick-search-bg");
		if (!quickSearchBG) return;
		CCNode* quickSearchMenu = this->getChildByID("quick-search-menu");
		if (!quickSearchMenu) return;

		CCNode* filtersTitle = this->getChildByID("filters-title");
		if (!filtersTitle) return;
		CCNode* difficultyFiltersBg = this->getChildByID("difficulty-filters-bg");
		if (!difficultyFiltersBg) return;
		CCNode* difficultyFilterMenu = this->getChildByID("difficulty-filter-menu");
		if (!difficultyFilterMenu) return;

		CCNode* lengthFiltersBg = this->getChildByID("length-filters-bg");
		if (!lengthFiltersBg) return;
		CCNode* lengthFilterMenu = this->getChildByID("length-filter-menu");
		if (!lengthFilterMenu) return;

		if (isTitlesHidden) {
			quickSearchTitle->setVisible(false);
			filtersTitle->setVisible(false);
		}

		if (!isTitlesHidden) quickSearchTitle->setPositionY(winSize.height - 20.0f);
		quickSearchBG->setPositionY(isTitlesHidden ? winSize.height - 75.0f : quickSearchTitle->getPositionY() - 69.5f);
		quickSearchMenu->setPositionY(quickSearchBG->getPositionY() - 28.0f);

        const float dfbgPos = difficultyFiltersBg->getPositionY();

		if (!isTitlesHidden) filtersTitle->setPositionY(quickSearchBG->getPositionY() - 68.0f);
		difficultyFiltersBg->setPositionY(isTitlesHidden ? quickSearchBG->getPositionY() - 91.0f : filtersTitle->getPositionY() - 37.0f);
		
		const float filterMenuPosY = difficultyFilterMenu->getPositionY() + (difficultyFiltersBg->getPositionY() - dfbgPos);
		
		difficultyFilterMenu->setPositionY(filterMenuPosY);

		lengthFiltersBg->setPositionY(difficultyFiltersBg->getPositionY() - 51.0f);
		lengthFilterMenu->setPositionY(filterMenuPosY);

		levelSearchBg->setPositionY(30.0f);
		const float levelSearchBGPosY = levelSearchBg->getPositionY();
		static_cast<CCScale9Sprite*>(levelSearchBg)->setColor(ccColor3B{0, 36, 91});
		levelSearchBarBg->setPositionY(levelSearchBGPosY);
		searchBar->setPositionY(levelSearchBGPosY);
		
		CCNode* searchButtonMenu = this->getChildByID("search-button-menu");
		if (!searchButtonMenu) return;
		// just... no. why??
		/*
		searchButtonMenu->setLayout(
			RowLayout::create()
        		->setAxisAlignment(AxisAlignment::End)
				->setGap(7.0f)
		);
		searchButtonMenu->setContentWidth(levelSearchBg->getContentWidth() - 11.0f);
		searchButtonMenu->updateLayout();
		*/
		if (cleanerMenu && !cleanerMenu->getSettingValue<bool>("revertSearchPageChanges")) {
			levelSearchBg->setPositionY(levelSearchBGPosY + 15.0f);
			searchButtonMenu->setPositionY(searchButtonMenu->getPositionY() - 229.0f);
			levelSearchBarBg->setPositionY(levelSearchBarBg->getPositionY() + 30.f);
			searchBar->setPositionY(levelSearchBGPosY + 30.f);
		} else searchButtonMenu->setPositionY(searchButtonMenu->getPositionY() - 260.0f);

		if (!Loader::get()->isModLoaded("alphalaneous.pages_api") || !this->getChildByID("quick-search-menu-navigation-menu")) return;
		Loader::get()->queueInMainThread([this, quickSearchMenu, quickSearchBG] {
			quickSearchMenu->setPositionY(quickSearchBG->getPositionY());
		});
	}
	bool init(int p0) {
		if (!LevelSearchLayer::init(p0)) return false;

		MyLevelSearchLayer::moveStuff();

		return true;
	}
};
