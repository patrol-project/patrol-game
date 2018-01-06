# patrol-game
Patrol game C++/SDL project

# Documentation
# Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`enum `[`mouse_buttons`](#_input_handler_8h_1a7e5f61c59f658d9196d15f3b98f1e56e)            | Easier to use this enum than only numbers.Needed for SDL [InputHandler](#class_input_handler) methods.
`public int `[`main`](#_main_8cpp_1a700a0caa5b70a06d1064e576f9f3cf65)`(int argc,char * args)`            | SDL-required arguments for multi-platform.
`class `[`Game`](#class_game) | 
`class `[`GameObject`](#class_game_object) | Abstract base class with pure virtual functions to set a blueprint for all the game objects we are creating.
`class `[`GameState`](#class_game_state) | Abstract base class with pure virtual functions which serves as a blueprint for all [Game](#class_game) states.
`class `[`GameStateMachine`](#class_game_state_machine) | Responsible for controlling and managing all game states.
`class `[`InputHandler`](#class_input_handler) | Responsible for listening to input and it's handling. Singleton approach.
`class `[`LoaderParams`](#class_loader_params) | Instead of changing all [GameObject](#class_game_object) classes when a parameter changes we use [LoaderParams](#class_loader_params) so that we change the parameters here only. And it is easier to read and maintain.
`class `[`MenuButton`](#class_menu_button) | [Game](#class_game) object which is a button in the game.
`class `[`MenuState`](#class_menu_state) | In this state the menu is showed on the screen with corresponding game object on it.
`class `[`PauseState`](#class_pause_state) | This is the state when the game is paused with the ESCAPE key.
`class `[`Player`](#class_player) | 
`class `[`PlayState`](#class_play_state) | 
`class `[`SDLGameObject`](#class_s_d_l_game_object) | 
`class `[`TextureManager`](#class_texture_manager) | 
`class `[`Vector2D`](#class_vector2_d) | 

## Members

#### `enum `[`mouse_buttons`](#_input_handler_8h_1a7e5f61c59f658d9196d15f3b98f1e56e) 

Easier to use this enum than only numbers.Needed for SDL [InputHandler](#class_input_handler) methods.

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
LEFT            | 
MIDDLE            | 
RIGHT            | 

#### `public int `[`main`](#_main_8cpp_1a700a0caa5b70a06d1064e576f9f3cf65)`(int argc,char * args)` 

SDL-required arguments for multi-platform.

#### Parameters
* `argc` 

* `args` 

#### Returns
int

# class `Game` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public bool `[`init`](#class_game_1a63254562bdd2a3d7f53e071564066a38)`(const char * title,int xpos,int ypos,int width,int height,bool showWindow)` | [Game::init](#class_game_1a63254562bdd2a3d7f53e071564066a38) initializes SDL and [GameStateMachine](#class_game_state_machine) and prepares everything for starting the game.
`public void `[`handleInput`](#class_game_1aa5abc4e07a1f5abce24e473c5567300b)`()` | Listens for input and delegates the work to the [InputHandler](#class_input_handler) class.
`public bool `[`loadMedia`](#class_game_1af4b6b1d9f209d7b08b7c6c8556898ecb)`()` | Uses [TextureManager](#class_texture_manager) to load all the needed pictures for the game to start.
`public void `[`update`](#class_game_1a79df6376b332d63c9eca0dcee30305c3)`()` | Responsible for updating the game every frame. Delegates the work to the [GameStateMachine](#class_game_state_machine) class.
`public void `[`clean`](#class_game_1ad4f36a72a2d06696f7973788606f57fc)`()` | Destroys all the loaded images, closes the window and quits SDL.
`public void `[`quit`](#class_game_1a8272be134d16c277bb014ad6a22fc357)`()` | Stops the game loop.
`public void `[`render`](#class_game_1a15ddd769261d923827a3cdf41499c843)`()` | Responsible for drawing all the game objects to the screen. Delegates the work to [GameStateMachine](#class_game_state_machine) class.
`public bool `[`get_running`](#class_game_1a0100e360773a67a44fd38abdf7b8233b)`() const` | Returns the status of the game loop.
`public inline SDL_Renderer * `[`getRenderer`](#class_game_1a8048a134ab883974e0c4d0147d4ba473)`() const` | Returns the SDL renderer.
`public inline `[`GameStateMachine`](#class_game_state_machine)` * `[`getStateMachine`](#class_game_1a582a1d2d18d6a5ed53fc75e388c79bec)`() const` | Returns the current game state from [GameStateMachine](#class_game_state_machine).
`public  `[`Game`](#class_game_1a586a831ed5ff1283fcf1b96f4eff065c)`(`[`Game`](#class_game)` const &) = delete` | 
`public void `[`operator=`](#class_game_1aa4c0eacd8656e54ec4e94877c453e531)`(`[`Game`](#class_game)` const &) = delete` | 

## Members

#### `public bool `[`init`](#class_game_1a63254562bdd2a3d7f53e071564066a38)`(const char * title,int xpos,int ypos,int width,int height,bool showWindow)` 

[Game::init](#class_game_1a63254562bdd2a3d7f53e071564066a38) initializes SDL and [GameStateMachine](#class_game_state_machine) and prepares everything for starting the game.

#### Parameters
* `title` the title of the game window 

* `xpos` position on the X axis on screen 

* `ypos` position on the Y axis on screen 

* `width` width of the game window 

* `height` height of the game window 

* `showWindow` if we want to show the window when everything is ready 

#### Returns
true if all SDL specific systems are properly initialised 

#### Returns
false if any of the SDL systems failed to load properly

#### `public void `[`handleInput`](#class_game_1aa5abc4e07a1f5abce24e473c5567300b)`()` 

Listens for input and delegates the work to the [InputHandler](#class_input_handler) class.

#### `public bool `[`loadMedia`](#class_game_1af4b6b1d9f209d7b08b7c6c8556898ecb)`()` 

Uses [TextureManager](#class_texture_manager) to load all the needed pictures for the game to start.

#### Returns
true if everything loaded successfully 

#### Returns
false if some of the media couldn't load

#### `public void `[`update`](#class_game_1a79df6376b332d63c9eca0dcee30305c3)`()` 

Responsible for updating the game every frame. Delegates the work to the [GameStateMachine](#class_game_state_machine) class.

#### `public void `[`clean`](#class_game_1ad4f36a72a2d06696f7973788606f57fc)`()` 

Destroys all the loaded images, closes the window and quits SDL.

#### `public void `[`quit`](#class_game_1a8272be134d16c277bb014ad6a22fc357)`()` 

Stops the game loop.

#### `public void `[`render`](#class_game_1a15ddd769261d923827a3cdf41499c843)`()` 

Responsible for drawing all the game objects to the screen. Delegates the work to [GameStateMachine](#class_game_state_machine) class.

#### `public bool `[`get_running`](#class_game_1a0100e360773a67a44fd38abdf7b8233b)`() const` 

Returns the status of the game loop.

#### Returns
true if the game is running 

#### Returns
false if the game is stopped

#### `public inline SDL_Renderer * `[`getRenderer`](#class_game_1a8048a134ab883974e0c4d0147d4ba473)`() const` 

Returns the SDL renderer.

#### Returns
SDL_Renderer* getRenderer

#### `public inline `[`GameStateMachine`](#class_game_state_machine)` * `[`getStateMachine`](#class_game_1a582a1d2d18d6a5ed53fc75e388c79bec)`() const` 

Returns the current game state from [GameStateMachine](#class_game_state_machine).

#### Returns
GameStateMachine* getStateMachine

#### `public  `[`Game`](#class_game_1a586a831ed5ff1283fcf1b96f4eff065c)`(`[`Game`](#class_game)` const &) = delete` 

#### `public void `[`operator=`](#class_game_1aa4c0eacd8656e54ec4e94877c453e531)`(`[`Game`](#class_game)` const &) = delete` 

# class `GameObject` 

Abstract base class with pure virtual functions to set a blueprint for all the game objects we are creating.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public void `[`draw`](#class_game_object_1a59f11cba9071a39ba2f486a8364ed536)`()` | 
`public void `[`update`](#class_game_object_1ae83128d0e0efef691417779605ee037c)`()` | 
`public void `[`clean`](#class_game_object_1a8e8c897a0be1966cfb6488ce97206d60)`()` | 
`protected inline  `[`GameObject`](#class_game_object_1a90daf6c63db960904650c2fe8d6085cc)`(const `[`LoaderParams`](#class_loader_params)` * pParams)` | 
`protected inline virtual  `[`~GameObject`](#class_game_object_1a224d4f6d9dd75c8a6f9d022eaf586fd9)`()` | 

## Members

#### `public void `[`draw`](#class_game_object_1a59f11cba9071a39ba2f486a8364ed536)`()` 

#### `public void `[`update`](#class_game_object_1ae83128d0e0efef691417779605ee037c)`()` 

#### `public void `[`clean`](#class_game_object_1a8e8c897a0be1966cfb6488ce97206d60)`()` 

#### `protected inline  `[`GameObject`](#class_game_object_1a90daf6c63db960904650c2fe8d6085cc)`(const `[`LoaderParams`](#class_loader_params)` * pParams)` 

#### `protected inline virtual  `[`~GameObject`](#class_game_object_1a224d4f6d9dd75c8a6f9d022eaf586fd9)`()` 

# class `GameState` 

Abstract base class with pure virtual functions which serves as a blueprint for all [Game](#class_game) states.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public void `[`update`](#class_game_state_1ab2864bfa04f92f6966861a1f2883bda0)`()` | Updating game objects every frame.
`public void `[`render`](#class_game_state_1abb892a3560e8fbedb3e4526af5deed7b)`()` | Draws to the screen all the game object every frame.
`public bool `[`onEnter`](#class_game_state_1ad17154015d2de5e669067c34d2cfe5b3)`()` | Loads all needed stuff for the game state.
`public bool `[`onExit`](#class_game_state_1aed6186fd65fefb5460f89ceed82829a1)`()` | Free all resources and clean after it.
`public string `[`getStateID`](#class_game_state_1a30ed42b8138dca2a0fb97edcc68be3ea)`() const` | Every game state has it's own ID.

## Members

#### `public void `[`update`](#class_game_state_1ab2864bfa04f92f6966861a1f2883bda0)`()` 

Updating game objects every frame.

#### `public void `[`render`](#class_game_state_1abb892a3560e8fbedb3e4526af5deed7b)`()` 

Draws to the screen all the game object every frame.

#### `public bool `[`onEnter`](#class_game_state_1ad17154015d2de5e669067c34d2cfe5b3)`()` 

Loads all needed stuff for the game state.

#### Returns
true if everything is ok 

#### Returns
false if something fails

#### `public bool `[`onExit`](#class_game_state_1aed6186fd65fefb5460f89ceed82829a1)`()` 

Free all resources and clean after it.

#### Returns
true 

#### Returns
false

#### `public string `[`getStateID`](#class_game_state_1a30ed42b8138dca2a0fb97edcc68be3ea)`() const` 

Every game state has it's own ID.

#### Returns
string getStateID

# class `GameStateMachine` 

Responsible for controlling and managing all game states.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public void `[`pushState`](#class_game_state_machine_1aff2a05d4c45dafa7988c43deb385c0f7)`(`[`GameState`](#class_game_state)` * state)` | Adds the given state to the vector and runs it.
`public void `[`changeState`](#class_game_state_machine_1a1305926cd932c708a75a950f99b6dd1e)`(`[`GameState`](#class_game_state)` * state)` | Changes from current to the given state First call onExit() on the current state, then onEnter() on the given state and continues it's work with the new given state.
`public void `[`popState`](#class_game_state_machine_1a691905effed30b630c3971fb5bbfcc4f)`()` | Checks if there are states in the vector. If yes calls onExit() and removes it from the vector If no returns doing nothing.
`public void `[`update`](#class_game_state_machine_1a7a3be350727fff550f09cc0499398ece)`()` | Calls the update method on the current state.
`public void `[`render`](#class_game_state_machine_1abfad06d5c6aa2f7d96a18e405f6d56c5)`()` | Calls the render method on the current state.

## Members

#### `public void `[`pushState`](#class_game_state_machine_1aff2a05d4c45dafa7988c43deb385c0f7)`(`[`GameState`](#class_game_state)` * state)` 

Adds the given state to the vector and runs it.

#### Parameters
* `state` some game state

#### `public void `[`changeState`](#class_game_state_machine_1a1305926cd932c708a75a950f99b6dd1e)`(`[`GameState`](#class_game_state)` * state)` 

Changes from current to the given state First call onExit() on the current state, then onEnter() on the given state and continues it's work with the new given state.

#### Parameters
* `state` the state to which we will change

#### `public void `[`popState`](#class_game_state_machine_1a691905effed30b630c3971fb5bbfcc4f)`()` 

Checks if there are states in the vector. If yes calls onExit() and removes it from the vector If no returns doing nothing.

#### `public void `[`update`](#class_game_state_machine_1a7a3be350727fff550f09cc0499398ece)`()` 

Calls the update method on the current state.

#### `public void `[`render`](#class_game_state_machine_1abfad06d5c6aa2f7d96a18e405f6d56c5)`()` 

Calls the render method on the current state.

# class `InputHandler` 

Responsible for listening to input and it's handling. Singleton approach.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public void `[`update`](#class_input_handler_1a72ec3b0da1f1747064bf00fc9d180d48)`()` | Polls for events from SDL. Then using a switch-case based on the event decides which function to call next and what to do.
`public void `[`clean`](#class_input_handler_1a23b2e1fac565e5bcd5ea393795b7ac67)`()` | 
`public void `[`reset`](#class_input_handler_1a1e7028e9c3c69eaf9749a2b6cc8d5967)`()` | Sets all mouse button states to false.
`public bool `[`isKeyDown`](#class_input_handler_1ab60a988015ec0b4d983dc305062d5b95)`(SDL_Scancode key) const` | Given a SDL_Scancode(all of which can be found on SDL site documentation) checks if the given key is pressed or not.
`public bool `[`getMouseButtonState`](#class_input_handler_1a36651253a9aec2310ce2c06f647b9609)`(int buttonNumber) const` | Using the mouse_buttons enum we can check the state of every mouse button.
`public `[`Vector2D`](#class_vector2_d)` * `[`getMousePosition`](#class_input_handler_1ac80f65f61e0c17894adec36e86ce768d)`() const` | Returns the position of the mouse.

## Members

#### `public void `[`update`](#class_input_handler_1a72ec3b0da1f1747064bf00fc9d180d48)`()` 

Polls for events from SDL. Then using a switch-case based on the event decides which function to call next and what to do.

#### `public void `[`clean`](#class_input_handler_1a23b2e1fac565e5bcd5ea393795b7ac67)`()` 

#### `public void `[`reset`](#class_input_handler_1a1e7028e9c3c69eaf9749a2b6cc8d5967)`()` 

Sets all mouse button states to false.

#### `public bool `[`isKeyDown`](#class_input_handler_1ab60a988015ec0b4d983dc305062d5b95)`(SDL_Scancode key) const` 

Given a SDL_Scancode(all of which can be found on SDL site documentation) checks if the given key is pressed or not.

#### Parameters
* `key` code for a key on the keyboard 

#### Returns
true if the key is pressed 

#### Returns
false if the key is not pressed

#### `public bool `[`getMouseButtonState`](#class_input_handler_1a36651253a9aec2310ce2c06f647b9609)`(int buttonNumber) const` 

Using the mouse_buttons enum we can check the state of every mouse button.

#### Parameters
* `buttonNumber` 0,1,2 for left, middle, right 

#### Returns
true if pressed 

#### Returns
false if not pressed

#### `public `[`Vector2D`](#class_vector2_d)` * `[`getMousePosition`](#class_input_handler_1ac80f65f61e0c17894adec36e86ce768d)`() const` 

Returns the position of the mouse.

#### Returns
Vector2D* X and Y position of the mouse

# class `LoaderParams` 

Instead of changing all [GameObject](#class_game_object) classes when a parameter changes we use [LoaderParams](#class_loader_params) so that we change the parameters here only. And it is easier to read and maintain.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline  `[`LoaderParams`](#class_loader_params_1af949d7192e36f67bdee98d151b10983a)`(int x,int y,int width,int height,string textureID)` | #### Parameters
`public inline int `[`getX`](#class_loader_params_1ab1c4adbbcd0185c0622b85ed8b2df1a2)`() const` | Returns the x position on the screen.
`public inline int `[`getY`](#class_loader_params_1a5aaa4e06b2fa0faea3c5aea86b88f1a5)`() const` | Returns the y position on the screen.
`public inline int `[`getWidth`](#class_loader_params_1a82785ff84c5546cd8b86607c2fd363b1)`() const` | Return the width of the game object.
`public inline int `[`getHeight`](#class_loader_params_1abfa2dac38e1c7dbe1a426139a5337408)`() const` | Returns the height of the game object.
`public inline string `[`getTextureID`](#class_loader_params_1abc34be7aaebd1d27595ea3a3b14b1dee)`() const` | Returns the texture ID of the game object.

## Members

#### `public inline  `[`LoaderParams`](#class_loader_params_1af949d7192e36f67bdee98d151b10983a)`(int x,int y,int width,int height,string textureID)` 

#### Parameters
* `x` position on the screen corresponding to the X axis 

* `y` position on the screen corresponding to the Y axis 

* `width` width of the object 

* `height` height of the object 

* `textureID` the ID of the texture(picture) to

#### `public inline int `[`getX`](#class_loader_params_1ab1c4adbbcd0185c0622b85ed8b2df1a2)`() const` 

Returns the x position on the screen.

#### Returns
int getX

#### `public inline int `[`getY`](#class_loader_params_1a5aaa4e06b2fa0faea3c5aea86b88f1a5)`() const` 

Returns the y position on the screen.

#### Returns
int getY

#### `public inline int `[`getWidth`](#class_loader_params_1a82785ff84c5546cd8b86607c2fd363b1)`() const` 

Return the width of the game object.

#### Returns
int getWidth

#### `public inline int `[`getHeight`](#class_loader_params_1abfa2dac38e1c7dbe1a426139a5337408)`() const` 

Returns the height of the game object.

#### Returns
int getHeight

#### `public inline string `[`getTextureID`](#class_loader_params_1abc34be7aaebd1d27595ea3a3b14b1dee)`() const` 

Returns the texture ID of the game object.

#### Returns
string getTextureID

# class `MenuButton` 

```
class MenuButton
  : public SDLGameObject
```  

[Game](#class_game) object which is a button in the game.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`MenuButton`](#class_menu_button_1aa0f55f2084bb269c5ab3840637c97ccf)`(const `[`LoaderParams`](#class_loader_params)` * params,void(*)() callback)` | Constructor accepting two arguments.
`public virtual void `[`draw`](#class_menu_button_1a3e854949b52808f9d6092e149a116f5c)`()` | Draw the button to the screen.
`public virtual void `[`update`](#class_menu_button_1a86b038172871555da45606e20fa6bad7)`()` | Update button status if hovered or clicked.
`public virtual void `[`clean`](#class_menu_button_1a970fc154ec16a7c0c9ad7f3626199bba)`()` | Free resources.

## Members

#### `public  `[`MenuButton`](#class_menu_button_1aa0f55f2084bb269c5ab3840637c97ccf)`(const `[`LoaderParams`](#class_loader_params)` * params,void(*)() callback)` 

Constructor accepting two arguments.

#### Parameters
* `params` All needed parameters for initiliazing a game object 

* `callback` Function pointer to a function which will execute when the button is pressed

#### `public virtual void `[`draw`](#class_menu_button_1a3e854949b52808f9d6092e149a116f5c)`()` 

Draw the button to the screen.

#### `public virtual void `[`update`](#class_menu_button_1a86b038172871555da45606e20fa6bad7)`()` 

Update button status if hovered or clicked.

#### `public virtual void `[`clean`](#class_menu_button_1a970fc154ec16a7c0c9ad7f3626199bba)`()` 

Free resources.

# class `MenuState` 

```
class MenuState
  : public GameState
```  

In this state the menu is showed on the screen with corresponding game object on it.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public virtual void `[`update`](#class_menu_state_1ad13c9a5c3063ab3cc0bc058301f1ee3f)`()` | Updates the game objects which are in this state.
`public virtual void `[`render`](#class_menu_state_1ad7afca66ece4a1e7bad77828e4f39f3e)`()` | Draws all game object which are in this state.
`public virtual bool `[`onEnter`](#class_menu_state_1a56faf9f3d2bdae763b9de12b4cb7ff20)`()` | Loads all needed resources when entering this state.
`public virtual bool `[`onExit`](#class_menu_state_1a7ff1d1ca0d3c03592a737673647406ca)`()` | Cleans all resources which were loaded for this state.
`public inline virtual string `[`getStateID`](#class_menu_state_1aa7a908a3cdc86f31b5464de97d7ac8c8)`() const` | returns current states name

## Members

#### `public virtual void `[`update`](#class_menu_state_1ad13c9a5c3063ab3cc0bc058301f1ee3f)`()` 

Updates the game objects which are in this state.

#### `public virtual void `[`render`](#class_menu_state_1ad7afca66ece4a1e7bad77828e4f39f3e)`()` 

Draws all game object which are in this state.

#### `public virtual bool `[`onEnter`](#class_menu_state_1a56faf9f3d2bdae763b9de12b4cb7ff20)`()` 

Loads all needed resources when entering this state.

#### Returns
true if everything is loaded 

#### Returns
false if something failed to load

#### `public virtual bool `[`onExit`](#class_menu_state_1a7ff1d1ca0d3c03592a737673647406ca)`()` 

Cleans all resources which were loaded for this state.

#### Returns
true if everything is cleaned 

#### Returns
false if something failed to free resources

#### `public inline virtual string `[`getStateID`](#class_menu_state_1aa7a908a3cdc86f31b5464de97d7ac8c8)`() const` 

returns current states name

#### Returns
string getStateID

# class `PauseState` 

```
class PauseState
  : public GameState
```  

This is the state when the game is paused with the ESCAPE key.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public virtual void `[`update`](#class_pause_state_1ad061f453cc65fb276a45da4790c9f0dd)`()` | Updates the game objects which are in this state.
`public virtual void `[`render`](#class_pause_state_1a9f4e24345a737cd3e623697409cf5bf4)`()` | Draws all game object which are in this state.
`public virtual bool `[`onEnter`](#class_pause_state_1ae7a5c230fa869805040b7ca82215a4c0)`()` | Loads all needed resources when entering this state.
`public virtual bool `[`onExit`](#class_pause_state_1a5a5315c115ba23beb4c03137cca947a3)`()` | Cleans all resources which were loaded for this state.
`public inline virtual string `[`getStateID`](#class_pause_state_1a8bf8f11fd918f50ce6c6042b0bb3a08b)`() const` | returns current states name

## Members

#### `public virtual void `[`update`](#class_pause_state_1ad061f453cc65fb276a45da4790c9f0dd)`()` 

Updates the game objects which are in this state.

#### `public virtual void `[`render`](#class_pause_state_1a9f4e24345a737cd3e623697409cf5bf4)`()` 

Draws all game object which are in this state.

#### `public virtual bool `[`onEnter`](#class_pause_state_1ae7a5c230fa869805040b7ca82215a4c0)`()` 

Loads all needed resources when entering this state.

#### Returns
true if everything is loaded 

#### Returns
false if something failed to load

#### `public virtual bool `[`onExit`](#class_pause_state_1a5a5315c115ba23beb4c03137cca947a3)`()` 

Cleans all resources which were loaded for this state.

#### Returns
true if everything is cleaned 

#### Returns
false if something failed to free resources

#### `public inline virtual string `[`getStateID`](#class_pause_state_1a8bf8f11fd918f50ce6c6042b0bb3a08b)`() const` 

returns current states name

#### Returns
string getStateID

# class `Player` 

```
class Player
  : public SDLGameObject
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`Player`](#class_player_1ad247c148ef8c104bec6a22c194e0a8d5)`(const `[`LoaderParams`](#class_loader_params)` * pParams)` | 
`public virtual void `[`draw`](#class_player_1ac18c9d30d2997765321c62030a4b20b7)`()` | 
`public virtual void `[`update`](#class_player_1a82c3476f3e65a4e2ac6bcd040771bdd4)`()` | 
`public virtual void `[`clean`](#class_player_1a883c81df5be3b931ecfa6c8de08acfbd)`()` | 
`public void `[`handleInput`](#class_player_1a3c2e7e40fe2018229d44168bd484c182)`()` | 

## Members

#### `public  `[`Player`](#class_player_1ad247c148ef8c104bec6a22c194e0a8d5)`(const `[`LoaderParams`](#class_loader_params)` * pParams)` 

#### `public virtual void `[`draw`](#class_player_1ac18c9d30d2997765321c62030a4b20b7)`()` 

#### `public virtual void `[`update`](#class_player_1a82c3476f3e65a4e2ac6bcd040771bdd4)`()` 

#### `public virtual void `[`clean`](#class_player_1a883c81df5be3b931ecfa6c8de08acfbd)`()` 

#### `public void `[`handleInput`](#class_player_1a3c2e7e40fe2018229d44168bd484c182)`()` 

# class `PlayState` 

```
class PlayState
  : public GameState
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public virtual void `[`update`](#class_play_state_1a3beac23cba7b9541714ebd33ea77a913)`()` | Updating game objects every frame.
`public virtual void `[`render`](#class_play_state_1ad0b2654d0d822b853c6d06ee5c4a95c2)`()` | Draws to the screen all the game object every frame.
`public virtual bool `[`onEnter`](#class_play_state_1a412edf86cef5eaffdfd63d69af42c39b)`()` | Loads all needed stuff for the game state.
`public virtual bool `[`onExit`](#class_play_state_1aed7fef037f6e9c9fc4a02924e2fe7154)`()` | Free all resources and clean after it.
`public inline virtual string `[`getStateID`](#class_play_state_1a31ad0dc82c2038f09218102411bbfc62)`() const` | Every game state has it's own ID.

## Members

#### `public virtual void `[`update`](#class_play_state_1a3beac23cba7b9541714ebd33ea77a913)`()` 

Updating game objects every frame.

#### `public virtual void `[`render`](#class_play_state_1ad0b2654d0d822b853c6d06ee5c4a95c2)`()` 

Draws to the screen all the game object every frame.

#### `public virtual bool `[`onEnter`](#class_play_state_1a412edf86cef5eaffdfd63d69af42c39b)`()` 

Loads all needed stuff for the game state.

#### Returns
true if everything is ok 

#### Returns
false if something fails

#### `public virtual bool `[`onExit`](#class_play_state_1aed7fef037f6e9c9fc4a02924e2fe7154)`()` 

Free all resources and clean after it.

#### Returns
true 

#### Returns
false

#### `public inline virtual string `[`getStateID`](#class_play_state_1a31ad0dc82c2038f09218102411bbfc62)`() const` 

Every game state has it's own ID.

#### Returns
string getStateID

# class `SDLGameObject` 

```
class SDLGameObject
  : public GameObject
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`SDLGameObject`](#class_s_d_l_game_object_1a21c807a03e8002aa2ca6239916586021)`(const `[`LoaderParams`](#class_loader_params)` * pParams)` | 
`public virtual void `[`draw`](#class_s_d_l_game_object_1ab703854bfb62a291ad23dc1f01d5190d)`()` | 
`public virtual void `[`update`](#class_s_d_l_game_object_1a9322e790f0515760f36b62ce35d4a090)`()` | 
`public virtual void `[`clean`](#class_s_d_l_game_object_1afa6c3cdc5dc42f1f67a14d5d140f20d3)`()` | 
`protected `[`Vector2D`](#class_vector2_d)` `[`position`](#class_s_d_l_game_object_1a6f9a5729fff7eb602523f5eb72e2cf96) | 
`protected `[`Vector2D`](#class_vector2_d)` `[`velocity`](#class_s_d_l_game_object_1a31bca8ce640d00909d9f2155a5c454f7) | 
`protected `[`Vector2D`](#class_vector2_d)` `[`acceleration`](#class_s_d_l_game_object_1ad52bc69122455b41a2b1b6b600e560c6) | 
`protected int `[`width`](#class_s_d_l_game_object_1afbc0aee47190300a36bb69d7936eb307) | 
`protected int `[`height`](#class_s_d_l_game_object_1aff33890e3aa92fa57f98d286b37e84b9) | 
`protected int `[`currentRow`](#class_s_d_l_game_object_1ae8ad8a9a77809ff4c1336db52b9382cd) | 
`protected int `[`currentFrame`](#class_s_d_l_game_object_1a262d4d0db5fb93e3034e22804624153f) | 
`protected string `[`textureID`](#class_s_d_l_game_object_1a5f8b439613f9da6361b4d9465144b788) | 

## Members

#### `public  `[`SDLGameObject`](#class_s_d_l_game_object_1a21c807a03e8002aa2ca6239916586021)`(const `[`LoaderParams`](#class_loader_params)` * pParams)` 

#### `public virtual void `[`draw`](#class_s_d_l_game_object_1ab703854bfb62a291ad23dc1f01d5190d)`()` 

#### `public virtual void `[`update`](#class_s_d_l_game_object_1a9322e790f0515760f36b62ce35d4a090)`()` 

#### `public virtual void `[`clean`](#class_s_d_l_game_object_1afa6c3cdc5dc42f1f67a14d5d140f20d3)`()` 

#### `protected `[`Vector2D`](#class_vector2_d)` `[`position`](#class_s_d_l_game_object_1a6f9a5729fff7eb602523f5eb72e2cf96) 

#### `protected `[`Vector2D`](#class_vector2_d)` `[`velocity`](#class_s_d_l_game_object_1a31bca8ce640d00909d9f2155a5c454f7) 

#### `protected `[`Vector2D`](#class_vector2_d)` `[`acceleration`](#class_s_d_l_game_object_1ad52bc69122455b41a2b1b6b600e560c6) 

#### `protected int `[`width`](#class_s_d_l_game_object_1afbc0aee47190300a36bb69d7936eb307) 

#### `protected int `[`height`](#class_s_d_l_game_object_1aff33890e3aa92fa57f98d286b37e84b9) 

#### `protected int `[`currentRow`](#class_s_d_l_game_object_1ae8ad8a9a77809ff4c1336db52b9382cd) 

#### `protected int `[`currentFrame`](#class_s_d_l_game_object_1a262d4d0db5fb93e3034e22804624153f) 

#### `protected string `[`textureID`](#class_s_d_l_game_object_1a5f8b439613f9da6361b4d9465144b788) 

# class `TextureManager` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public bool `[`load`](#class_texture_manager_1a328e8f9b727a36c1a2003ab668fe0a7e)`(string fileName,string id,SDL_Renderer * pRenderer)` | 
`public void `[`draw`](#class_texture_manager_1a3c2b92718d8d64e7f0897eef9e94b65b)`(string id,int x,int y,int width,int height,SDL_Renderer * pRenderer,SDL_RendererFlip flip)` | 
`public void `[`drawFrame`](#class_texture_manager_1a5b497311ac901dbf6eea3ee3834248ee)`(string id,int x,int y,int width,int height,int currentRow,int currentFrame,SDL_Renderer * pRenderer,SDL_RendererFlip flip)` | 
`public void `[`clearAllTexturesFromMap`](#class_texture_manager_1ac8879ddf15375637fa826477ca269c47)`()` | 
`public void `[`clearFromTextureMap`](#class_texture_manager_1a33efce47a656364f93866a560914cbfe)`(string id)` | 

## Members

#### `public bool `[`load`](#class_texture_manager_1a328e8f9b727a36c1a2003ab668fe0a7e)`(string fileName,string id,SDL_Renderer * pRenderer)` 

#### `public void `[`draw`](#class_texture_manager_1a3c2b92718d8d64e7f0897eef9e94b65b)`(string id,int x,int y,int width,int height,SDL_Renderer * pRenderer,SDL_RendererFlip flip)` 

#### `public void `[`drawFrame`](#class_texture_manager_1a5b497311ac901dbf6eea3ee3834248ee)`(string id,int x,int y,int width,int height,int currentRow,int currentFrame,SDL_Renderer * pRenderer,SDL_RendererFlip flip)` 

#### `public void `[`clearAllTexturesFromMap`](#class_texture_manager_1ac8879ddf15375637fa826477ca269c47)`()` 

#### `public void `[`clearFromTextureMap`](#class_texture_manager_1a33efce47a656364f93866a560914cbfe)`(string id)` 

# class `Vector2D` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline  `[`Vector2D`](#class_vector2_d_1a166ca1df158a260a7cbf3b57ff147a4a)`(float x,float y)` | 
`public inline float `[`getX`](#class_vector2_d_1a527601e47976bcfdac2520817bfee675)`()` | 
`public inline float `[`getY`](#class_vector2_d_1a5b797fb62a3c21ced0cc8e27afd62f8b)`()` | 
`public inline void `[`setX`](#class_vector2_d_1ac458bd997d2f0c6c7234cf1e8a7b73b8)`(float x)` | 
`public inline void `[`setY`](#class_vector2_d_1a9b47adcbdf2c10f3ba893285b5c34709)`(float y)` | 
`public inline float `[`length`](#class_vector2_d_1ae9c6666151cd09a233f35c13cdfd9049)`()` | 
`public inline `[`Vector2D`](#class_vector2_d)` `[`operator+`](#class_vector2_d_1aa98d8882a429397b69d246a996191a92)`(const `[`Vector2D`](#class_vector2_d)` & v2) const` | 
`public inline `[`Vector2D`](#class_vector2_d)` `[`operator*`](#class_vector2_d_1afe8ec16d5f9fa65bf22489c0e0102f33)`(float scalar)` | 
`public inline `[`Vector2D`](#class_vector2_d)` & `[`operator*=`](#class_vector2_d_1ac512b056ccd633ffd78c589ab835b980)`(float scalar)` | 
`public inline `[`Vector2D`](#class_vector2_d)` `[`operator-`](#class_vector2_d_1a251772bc24e826046ad093cbd08ae346)`(const `[`Vector2D`](#class_vector2_d)` & v2) const` | 
`public inline `[`Vector2D`](#class_vector2_d)` `[`operator/`](#class_vector2_d_1a8cd7cab406efc12492645757a88443dd)`(float scalar)` | 
`public inline `[`Vector2D`](#class_vector2_d)` & `[`operator/=`](#class_vector2_d_1a76e18d3294066c50ec2a29f0667358fb)`(float scalar)` | 
`public inline void `[`normalize`](#class_vector2_d_1a39a3335f33d7e9850b99e4498ba4d856)`()` | 

## Members

#### `public inline  `[`Vector2D`](#class_vector2_d_1a166ca1df158a260a7cbf3b57ff147a4a)`(float x,float y)` 

#### `public inline float `[`getX`](#class_vector2_d_1a527601e47976bcfdac2520817bfee675)`()` 

#### `public inline float `[`getY`](#class_vector2_d_1a5b797fb62a3c21ced0cc8e27afd62f8b)`()` 

#### `public inline void `[`setX`](#class_vector2_d_1ac458bd997d2f0c6c7234cf1e8a7b73b8)`(float x)` 

#### `public inline void `[`setY`](#class_vector2_d_1a9b47adcbdf2c10f3ba893285b5c34709)`(float y)` 

#### `public inline float `[`length`](#class_vector2_d_1ae9c6666151cd09a233f35c13cdfd9049)`()` 

#### `public inline `[`Vector2D`](#class_vector2_d)` `[`operator+`](#class_vector2_d_1aa98d8882a429397b69d246a996191a92)`(const `[`Vector2D`](#class_vector2_d)` & v2) const` 

#### `public inline `[`Vector2D`](#class_vector2_d)` `[`operator*`](#class_vector2_d_1afe8ec16d5f9fa65bf22489c0e0102f33)`(float scalar)` 

#### `public inline `[`Vector2D`](#class_vector2_d)` & `[`operator*=`](#class_vector2_d_1ac512b056ccd633ffd78c589ab835b980)`(float scalar)` 

#### `public inline `[`Vector2D`](#class_vector2_d)` `[`operator-`](#class_vector2_d_1a251772bc24e826046ad093cbd08ae346)`(const `[`Vector2D`](#class_vector2_d)` & v2) const` 

#### `public inline `[`Vector2D`](#class_vector2_d)` `[`operator/`](#class_vector2_d_1a8cd7cab406efc12492645757a88443dd)`(float scalar)` 

#### `public inline `[`Vector2D`](#class_vector2_d)` & `[`operator/=`](#class_vector2_d_1a76e18d3294066c50ec2a29f0667358fb)`(float scalar)` 

#### `public inline void `[`normalize`](#class_vector2_d_1a39a3335f33d7e9850b99e4498ba4d856)`()` 

Generated by [Moxygen](https://sourcey.com/moxygen)