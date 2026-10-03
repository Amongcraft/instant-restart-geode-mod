#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>
#include <Geode/modify/PlayerObject.hpp>

using namespace geode::prelude;

class $modify(MyPauseLayer, PauseLayer) {
    bool init() {
        if (!PauseLayer::init()) return false;

        // Target the bottom menu where Options, Practice Mode, and Retry buttons live
        auto bottomMenu = this->getChildByID("bottom-menu");
        if (!bottomMenu) {
            bottomMenu = this->getChildByID("center-button-menu");
        }

        if (bottomMenu) {
            // Find the options button ("options-button" or "settings-button")
            auto optionsBtn = bottomMenu->getChildByID("options-button");
            if (!optionsBtn) {
                optionsBtn = bottomMenu->getChildByID("settings-button");
            }

            // Create a custom icon using the restart sprite
            auto btnSprite = CCSprite::createWithSpriteFrameName("GJ_updateBtn_001.png");
            if (!btnSprite) {
                btnSprite = CCSprite::createWithSpriteFrameName("GJ_playBtn2_001.png");
            }
            btnSprite->setScale(0.65f);

            auto instantBtn = CCMenuItemSpriteExtra::create(
                btnSprite,
                this,
                menu_selector(MyPauseLayer::onInstantRestart)
            );
            instantBtn->setID("instant-restart-button"_spr);

            if (optionsBtn) {
                // Get the exact position of the options button and place our button right to its left (-40 units)
                auto optionsPos = optionsBtn->getPosition();
                instantBtn->setPosition({ optionsPos.x - 40.0f, optionsPos.y });
                bottomMenu->addChild(instantBtn);
            } else {
                // Fallback if options button ID isn't found by Node IDs
                bottomMenu->addChild(instantBtn);
                bottomMenu->updateLayout();
            }
        }

        return true;
    }

    void onInstantRestart(CCObject* sender) {
        // Resume game & reset level instantly
        this->onResume(sender);

        if (auto playLayer = PlayLayer::get()) {
            playLayer->resetLevel();
        }
    }
};

// Force near-zero respawn delay
class $modify(MyPlayerObject, PlayerObject) {
    void playerDestroyed(bool p0) {
        PlayerObject::playerDestroyed(p0);
        
        if (auto playLayer = PlayLayer::get()) {
            playLayer->m_levelSettings->m_respawnTime = 0.001f;
        }
    }
};
