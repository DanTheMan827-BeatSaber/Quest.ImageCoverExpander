#pragma once

#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Vector2.hpp"
#include "UnityEngine/Vector3.hpp"

namespace Helpers {
    using namespace UnityEngine;

    inline void shiftTransform(RectTransform* transform, Vector3 shift) {
        auto currentPosition = transform->get_localPosition();
        transform->set_localPosition(Vector3(currentPosition.x + shift.x, currentPosition.y + shift.y, currentPosition.z + shift.z));
    }
}
