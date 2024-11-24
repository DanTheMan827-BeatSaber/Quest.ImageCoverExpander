#pragma once

#include "bsml/shared/macros.hpp"
#include "HMUI/ViewController.hpp"
#include "custom-types/shared/macros.hpp"

DECLARE_CLASS_CODEGEN(ImageCoverExpander::UI, Settings, HMUI::ViewController,

    DECLARE_SIMPLE_DTOR();
    DECLARE_OVERRIDE_METHOD_MATCH(void, DidActivate, &HMUI::ViewController::DidActivate, bool firstActivation, bool addedToHierarchy, bool screenSystemDisabling);

    DECLARE_INSTANCE_METHOD(void, PostParse);
    DECLARE_INSTANCE_METHOD(void, UpdateSettings);

    //DECLARE_INSTANCE_FIELD(bool, enabledSetting);

    //DECLARE_INSTANCE_FIELD(UnityW<BSML::TextMeshPro>, imageCoverExpanderText);
    //DECLARE_INSTANCE_FIELD(UnityW<BSML::TextMeshPro>, versionText);

    //DECLARE_INSTANCE_FIELD(UnityW<BSML::TextMeshPro>, restartHintText);

    DECLARE_BSML_PROPERTY(bool, enabledValue);



)
