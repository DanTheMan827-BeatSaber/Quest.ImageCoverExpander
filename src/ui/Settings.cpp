#include "HMUI/ViewController.hpp"
#include "HMUI/Touchable.hpp"
#include "Logger.hpp"
#include "config.hpp"

void ActivateSettings(HMUI::ViewController* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling){
    Logger.info("ActivateSettings: {}, {}, {}", firstActivation, addedToHierarchy, screenSystemEnabling);

    if (!firstActivation)
        return;

    self->get_gameObject()->AddComponent<HMUI::Touchable*>();
    auto vertical = BSML::Lite::CreateVerticalLayoutGroup(self);
    vertical->set_childControlHeight(false);
    vertical->set_childForceExpandHeight(false);
    vertical->set_spacing(1);

    BSML::Lite::AddHoverHint(AddConfigValueToggle(vertical, getModConfig().Active)->get_gameObject(),"Toggles whether the mod is active or not (restart required to take effect)");
}
