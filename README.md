![image](https://user-images.githubusercontent.com/82617401/208313402-82c10a61-bc17-4bc6-9d18-220db3a44ea2.png)
### Compiling
- ```git clone https://github.com/basedSkeleton/my-tile.git```
- ```cd my-tile```
- ```mkdir build && cd build```
- ```cmake ..```
- ```make```
### Installation
- Download/Copy ```libmy-tile.so``` to ```~/.minecraft-pi/mods/```

### Editing block properties
- Navigate to line 35.<br/>
```(*Tile)(my_tile, 129, 175, *Material_stone);```<br/>
- You'll see the values ```129``` and ```175```. These correspond to the ID and Texture of the block. 
- If you want to change the ID, make sure it's not already used <br/>https://wiki.mcpirevival.tk/wiki/Minecraft:_Pi_Edition_Complete_Block_List
- If you want to change the texture, then, open the ```terrain.png``` file and count up from 0 for each block texture until you reach the one you want.
- If you want to change the name of the block, navigate to line 53.<br/>```(*Tile_setDescriptionId)(my_tile, "my_tile");```
- The second argument, ```"my_tile"``` is the identifier for the language string. So, if it's set to "grass" instead, the game will search the language file for ```tile.grass.name```.

### Credits
- TheBrokenRail
- Bigjango13
