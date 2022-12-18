#include <stdlib.h>

#include <libreborn/libreborn.h>
#include <symbols/minecraft.h>
#include <mods/misc/misc.h>

#include "my-tile.h"

typedef unsigned char uchar;

// My Tile VTable
static unsigned char *get_my_tile_vtable() {
    static unsigned char *vtable = NULL;
    if (vtable == NULL) {
        // Init
        vtable = (unsigned char *) malloc(TILE_VTABLE_SIZE);
        ALLOC_CHECK(vtable);
        // Copy Old VTable
        memcpy((void *) vtable, (void *) Tile_vtable, TILE_VTABLE_SIZE);
    }
    return vtable;
}
__attribute__((destructor)) static void free_my_tile_vtable() {
    free(get_my_tile_vtable());
}

// Add My Tile
unsigned char *my_tile = NULL;
static void Tile_initTiles_injection(__attribute__((unused)) uchar *null) {
    // Allocate
    my_tile = (unsigned char *) ::operator new(TILE_SIZE);
    ALLOC_CHECK(my_tile);

    // Construct
    (*Tile)(my_tile, 129, 175, *Material_stone);

    // Set VTable
    *(unsigned char **) my_tile = get_my_tile_vtable();
    unsigned char *my_tile_vtable = *(unsigned char **) my_tile;

    // Get Functions
    Tile_setDestroyTime_t Tile_setDestroyTime = *(Tile_setDestroyTime_t *) (my_tile_vtable + Tile_setDestroyTime_vtable_offset);
    Tile_setExplodeable_t Tile_setExplodeable = *(Tile_setExplodeable_t *) (my_tile_vtable + Tile_setExplodeable_vtable_offset);
    Tile_setSoundType_t Tile_setSoundType = *(Tile_setSoundType_t *) (my_tile_vtable + Tile_setSoundType_vtable_offset);
    Tile_setDescriptionId_t Tile_setDescriptionId = *(Tile_setDescriptionId_t *) (my_tile_vtable + Tile_setDescriptionId_vtable_offset);

    // Init
    (*Tile_init)(my_tile);
    (*Tile_setDestroyTime)(my_tile, 2.0f);
    (*Tile_setExplodeable)(my_tile, 10.0f);
    (*Tile_setSoundType)(my_tile, SOUND_STONE);
    *(int32_t *) (my_tile + Tile_category_property_offset) = 1;
    (*Tile_setDescriptionId)(my_tile, "my_tile");
}

static void Inventory_setupDefault_FillingContainer_addItem_call_injection(unsigned char *filling_container) {
    ItemInstance *my_tile_instance = new ItemInstance;
    ALLOC_CHECK(my_tile_instance);
    my_tile_instance->count = 255;
    my_tile_instance->auxiliary = 0;
    my_tile_instance->id = 129;
    (*FillingContainer_addItem)(filling_container, my_tile_instance);
}

// Init
__attribute__((constructor)) static void init() {
    misc_run_on_tiles_setup(Tile_initTiles_injection);
    misc_run_on_creative_inventory_setup(Inventory_setupDefault_FillingContainer_addItem_call_injection);
}
