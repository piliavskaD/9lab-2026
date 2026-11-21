#pragma once
#include "GildedRose.h"

class ItemUpdater {
public:
    virtual void update(Item& item) const = 0;
    virtual ~ItemUpdater() = default;
};