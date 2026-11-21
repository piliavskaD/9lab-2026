#include "GildedRose.h"
#include "Updaters.h"

using namespace std;

GildedRose::GildedRose(vector<Item>& items) : items(items)
{
}

void GildedRose::updateQuality()
{
    for (Item& item : items)
    {
        updaterFor(item.name).update(item);
    }
}