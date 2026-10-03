#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

class $modify(MyPauseLayer, PauseLayer) {
    bool init() {
        if (!PauseLayer::init()) return false;

        auto bottomMenu = this->getChildByID("bottom-menu");
        if (!bottomMenu) {
            bottomMenu = this->getChildByID("center-button-menu");
        }

        if (bottomMenu) {
            auto optionsBtn = bottomMenu->getChildByID("options-button");
            if (!optionsBtn) {
                optionsBtn = bottomMenu->getChildByID("settings-button");
            }

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
                auto optionsPos = optionsBtn->getPosition();
                instantBtn->setPosition({ optionsPos.x - 40.0f, optionsPos.y });
                bottomMenu->addChild(instantBtn);
            } else {
                bottomMenu->addChild(instantBtn);
                bottomMenu->updateLayout();
            }
        }

        return true;
    }

    void onInstantRestart(CCObject* sender) {
        this->onResume(sender);

        if (auto playLayer = PlayLayer::get()) {
            playLayer->resetLevel();
        }
    }
};

// Hook PlayLayer for 2.2081 instant respawn handling
class $modify(MyPlayLayer, PlayLayer) {
    void delayedResetLevel() {
        // Skips the post-death delay timer on 2.2081 completely
        PlayLayer::resetLevel();
    }
};
