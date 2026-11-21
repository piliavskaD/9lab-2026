#pragma once
#include <algorithm>
#include <string>
#include "ItemUpdater.h"

const std::string BRIE_NAME = "Aged Brie";
const std::string SULFURAS_NAME = "Sulfuras, Hand of Ragnaros";
const std::string BACKSTAGE_NAME = "Backstage passes to a TAFKAL80ETC concert";
const std::string CONJURED_NAME = "Conjured Mana Cake";   

const int MAX_QUALITY = 50;

inline void increaseQuality(Item& item, int amount) {
    if (item.quality < MAX_QUALITY) {
        item.quality = std::min(MAX_QUALITY, item.quality + amount);
    }
}

class NormalUpdater : public ItemUpdater {
public:
    void update(Item& item) const override {
        item.sellIn--;
        int decrease = (item.sellIn < 0) ? 2 : 1;
        item.quality = std::max(0, item.quality - decrease);
    }
};

// Aged Brie: якість росте, після терміну вдвічі швидше
class AgedBrieUpdater : public ItemUpdater {
public:
    void update(Item& item) const override {
        item.sellIn--;
        increaseQuality(item, (item.sellIn < 0) ? 2 : 1);
    }
};

class SulfurasUpdater : public ItemUpdater {
public:
    void update(Item&) const override {}
};

class BackstageUpdater : public ItemUpdater {
public:
    void update(Item& item) const override {
        int bonus = 1;
        if (item.sellIn < 11) bonus = 2;
        if (item.sellIn < 6)  bonus = 3;
        increaseQuality(item, bonus);

        item.sellIn--;
        if (item.sellIn < 0) {
            item.quality = 0;
        }
    }
};

class ConjuredUpdater : public ItemUpdater {
public:
    void update(Item& item) const override {
        item.sellIn--;
        int decrease = (item.sellIn < 0) ? 4 : 2;
        item.quality = std::max(0, item.quality - decrease);
    }
};

inline const ItemUpdater& updaterFor(const std::string& name) {
    static const NormalUpdater    normal;
    static const AgedBrieUpdater  brie;
    static const SulfurasUpdater  sulfuras;
    static const BackstageUpdater backstage;
    static const ConjuredUpdater  conjured;            

    if (name == BRIE_NAME)      return brie;
    if (name == SULFURAS_NAME)  return sulfuras;
    if (name == BACKSTAGE_NAME) return backstage;
    if (name == CONJURED_NAME)  return conjured;       
    return normal;
}