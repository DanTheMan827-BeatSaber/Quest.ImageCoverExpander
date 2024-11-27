#include "AutoHooks.hpp"
#include "Helpers/logTransform.hpp"
#include "Helpers/shiftTransform.hpp"
#include "Helpers/getModIds.hpp"
#include "config.hpp"

// GlobalNamespace
#include "GlobalNamespace/StandardLevelDetailViewController.hpp"

// UnityEngine
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/Vector2.hpp"
#include "UnityEngine/Vector3.hpp"
#include "UnityEngine/Color.hpp"

// HMUI
#include "HMUI/ImageView.hpp"
#include <cmath>

#define MOD_ENABLED getModConfig().Active.GetValue()

namespace Hooks {
    using namespace GlobalNamespace;
    using namespace UnityEngine;
    using namespace HMUI;
    using namespace Helpers;

    static std::unordered_map<std::string, float> modExtraWidths = {
        {"", 2},
        {"PlaylistManager", 9},
        {"Replay", 7}
    };

    MAKE_AUTO_HOOK_MATCH(m_DidActivate,
                    &GlobalNamespace::StandardLevelDetailViewController::DidActivate,
                    void,
                    GlobalNamespace::StandardLevelDetailViewController* self,
                    bool firstActivation,
                    bool addedToHeirarchy,
                    bool screenSystemEnabling) {

        m_DidActivate(self, firstActivation, addedToHeirarchy, screenSystemEnabling);

        if (!firstActivation) {
            Logger.info("Not first activation, skipping.");

            return;
        }

        if(MOD_ENABLED) {
            static float_t extraWidth = []() {
                auto width = modExtraWidths[""];

                for (auto mod : modloader::get_loaded()) {
                    auto modExtraWidth = modExtraWidths.find(mod.info.id);

                    if (modExtraWidth != modExtraWidths.end() && modExtraWidths[mod.info.id] > width) {
                        width = modExtraWidths[mod.info.id];
                    }
                }

                return width;
            }();

            static float_t xShift = [](){
                auto const modIds = getModIds();
                if (std::find_if(modIds.begin(), modIds.end(), [](const char* modId) { return std::strcmp(modId, "PlaylistManager") == 0; }) != modIds.end())  {
                    return 0.0f;
                }

                return extraWidth / 2.0f;
            }();

            Logger.info("ImageCoverExpander Found Value Set As False, expanding Image");
            auto* imageCoverTransform = self->get_transform()->Find("LevelDetail/LevelBarBig/SongArtwork")->GetComponent<RectTransform*>();

            logTransform(imageCoverTransform);

            // Shift the song title left to fill where the artwork was.
            for (auto name : {
                "LevelDetail/LevelBarBig/SingleLineTextContainer",
                "LevelDetail/LevelBarBig/SongArtwork",
                "LevelDetail/LevelBarBig/MultipleLineTextContainer"
            }) {
                auto transform = self->get_transform()->Find(name)->GetComponent<RectTransform*>();

                if (transform) {
                    logTransform(transform);
                    shiftTransform(transform, Vector3(-14 + xShift, 0, 0));
                }
            }

            // Shift the various elements right to center them.
            for (auto name : {
                "LevelDetail/ActionButtons",
                "LevelDetail/BeatmapCharacteristic",
                "LevelDetail/BeatmapDifficulty",
                "LevelDetail/BeatmapParamsPanel",
                "LevelDetail/LoadingControl",
                "LevelDetail/ModifierSelection"
            }) {
                auto transform = self->get_transform()->Find(name)->GetComponent<RectTransform*>();

                if (transform) {
                    logTransform(transform);
                    shiftTransform(transform, Vector3(xShift, 0, 0));
                }
            }

            imageCoverTransform->set_sizeDelta(Vector2(68.5 + extraWidth, 58.0));
            imageCoverTransform->set_localPosition(Vector3(-34.4, -56, 0));
            imageCoverTransform->SetAsFirstSibling();

            auto* imageView = imageCoverTransform->GetComponent<ImageView*>();

            imageView->set_color(Color(0.5, 0.5, 0.5, 1));
            imageView->set_preserveAspect(false);
            imageView->_skew = 0.0f;

            logTransform(imageCoverTransform);
            // imageView->__Refresh();
        } else {
            Logger.info("ImageCoverExpander Found Value Set As True, not expanding");
        }
    }
}
