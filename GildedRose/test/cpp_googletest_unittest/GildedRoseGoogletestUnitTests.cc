#include <gtest/gtest.h>
#include "GildedRose.h"

// Назви спеціальних товарів (мають збігатися з тими, що в GildedRose.cc)
const std::string BRIE = "Aged Brie";
const std::string SULFURAS = "Sulfuras, Hand of Ragnaros";
const std::string BACKSTAGE = "Backstage passes to a TAFKAL80ETC concert";

// Допоміжна функція: оновлює один товар на один день і повертає його
Item updateOne(const std::string& name, int sellIn, int quality) {
    std::vector<Item> items = { Item(name, sellIn, quality) };
    GildedRose app(items);
    app.updateQuality();
    return items[0];
}

// ===== Звичайний товар =====
TEST(GildedRoseTest, NormalItemLosesOneQualityPerDay) {
    Item r = updateOne("foo", 5, 10);
    EXPECT_EQ(4, r.sellIn);
    EXPECT_EQ(9, r.quality);                 // -1
}

TEST(GildedRoseTest, NormalItemDegradesTwiceAsFastAfterSellDate) {
    Item r = updateOne("foo", 0, 10);
    EXPECT_EQ(-1, r.sellIn);
    EXPECT_EQ(8, r.quality);                 // -2
}

TEST(GildedRoseTest, QualityIsNeverNegative) {
    EXPECT_EQ(0, updateOne("foo", 5, 0).quality);
    EXPECT_EQ(0, updateOne("foo", 0, 1).quality);
}

// ===== Aged Brie =====
TEST(GildedRoseTest, BrieIncreasesInQuality) {
    EXPECT_EQ(11, updateOne(BRIE, 5, 10).quality);   // +1
}

TEST(GildedRoseTest, BrieIncreasesTwiceAsFastAfterSellDate) {
    EXPECT_EQ(12, updateOne(BRIE, 0, 10).quality);   // +2
}

TEST(GildedRoseTest, BrieQualityNeverExceeds50) {
    EXPECT_EQ(50, updateOne(BRIE, 5, 50).quality);
    EXPECT_EQ(50, updateOne(BRIE, 0, 49).quality);
}

// ===== Sulfuras =====
TEST(GildedRoseTest, SulfurasNeverChanges) {
    Item r = updateOne(SULFURAS, 5, 80);
    EXPECT_EQ(5, r.sellIn);                  // термін не змінюється
    EXPECT_EQ(80, r.quality);                // якість не змінюється
}

TEST(GildedRoseTest, SulfurasUnchangedAtZeroSellIn) {
    Item r = updateOne(SULFURAS, 0, 80);
    EXPECT_EQ(0, r.sellIn);
    EXPECT_EQ(80, r.quality);
}

// ===== Backstage passes =====
TEST(GildedRoseTest, BackstageIncreasesByOneWhenMoreThan10Days) {
    EXPECT_EQ(11, updateOne(BACKSTAGE, 11, 10).quality);  // +1
}

TEST(GildedRoseTest, BackstageIncreasesByTwoWhen10DaysOrLess) {
    EXPECT_EQ(12, updateOne(BACKSTAGE, 10, 10).quality);  // +2
    EXPECT_EQ(12, updateOne(BACKSTAGE, 6, 10).quality);   // +2
}

TEST(GildedRoseTest, BackstageIncreasesByThreeWhen5DaysOrLess) {
    EXPECT_EQ(13, updateOne(BACKSTAGE, 5, 10).quality);   // +3
    EXPECT_EQ(13, updateOne(BACKSTAGE, 1, 10).quality);   // +3
}

TEST(GildedRoseTest, BackstageDropsToZeroAfterConcert) {
    EXPECT_EQ(0, updateOne(BACKSTAGE, 0, 10).quality);
}

TEST(GildedRoseTest, BackstageQualityNeverExceeds50) {
    EXPECT_EQ(50, updateOne(BACKSTAGE, 5, 49).quality);
}

const std::string CONJURED = "Conjured Mana Cake";

TEST(GildedRoseTest, ConjuredDegradesTwiceAsFastAsNormal) {
    Item r = updateOne(CONJURED, 5, 10);
    EXPECT_EQ(4, r.sellIn);
    EXPECT_EQ(8, r.quality);                 
}

TEST(GildedRoseTest, ConjuredDegradesFourPerDayAfterSellDate) {
    Item r = updateOne(CONJURED, 0, 10);
    EXPECT_EQ(-1, r.sellIn);
    EXPECT_EQ(6, r.quality);                 
}

TEST(GildedRoseTest, ConjuredQualityIsNeverNegative) {
    EXPECT_EQ(0, updateOne(CONJURED, 5, 1).quality);
    EXPECT_EQ(0, updateOne(CONJURED, 0, 3).quality);
    EXPECT_EQ(0, updateOne(CONJURED, 5, 0).quality);
}