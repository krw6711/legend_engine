# Legend Engine

message to you!
>I am really happy to announce that our ambitous project is on his way to be production ready very soon!
>I guess I need more 2 weeks till I can ship a real working game
>
>So I am inviting you to join me the journy, if you are interested or want to share with your skills, the project is community driven and free for all, we believe on opensource 
>
>The current project that I am working on is a Game Engine based on C and SDL3, follows the data driven approche so it will be easy to do development on it!
>
>It might not be perfect, I am a solo working developer, but trying my best, because I love what I am doing :D
>
>Our Game Engine, which called: The Legend Engine 2D, I may change its name later if you want :). this will provide ability to make a 2D RPG Game with Tile Map style same as old Nintendo's Library like Pokemon, Final Fantasy, Zelda and so on, with a Turn Based fighting
>
>the coming game might be just a mix of memes I know! it will be just a prof of concept and demo for the game engine, real work comes after that, but I am sure you all would love Bouha and his sister and may enjoy the juorny in Zifta great lands!
>
>if you are interested in learning, paticipate in the project or try the game you can join our discord server!
>
>best wishes,
>Empty Bucket Studio Team Lead.

### Join our discord server! https://discord.gg/gXJZXGCbX

to run this use
```sh
git clone https://github.com/libsdl-org/SDL.git vendored/SDL
cmake -S . -B build && cmake --build build && gdb ./build/Debug/main
```

or you can remove gdb, I use it for debugging, and catch the segfaults, when you run with gdb, type run in its console to start, exit to leave, also print (var name)

you need stuff like gcc, make, cmake, idk, figure out by yourself
if you are using windows, do not tell me why it is not working, or how to get the whatever
idc, idk, just blame yourself that you are using windows!

installation? `sudo cmake --install build --prefix /usr/local`

learn more:
https://github.com/libsdl-org/SDL/blob/main/INSTALL.md

for windows users: https://github.com/libsdl-org/SDL/blob/main/docs/README-windows.md who still using windows in 2026? lol


yeah I did rm -rf .git by mistake :))))))


## resources
- map srpitesheet: https://opengameart.org/content/lots-of-free-2d-tiles-and-sprites-by-hyptosis


this is some ai slop about commits lol

---

### Commit Types

| Type | Use Case | Example |
| --- | --- | --- |
| **`feat`** | Adding a new feature | `feat(auth): add Google OAuth login` |
| **`fix`** | Fixing a bug | `fix(cart): resolve double-click checkout error` |
| **`docs`** | Documentation changes only | `docs(readme): update installation steps` |
| **`style`** | Formatting, missing semi-colons (no code logic change) | `style(lint): apply Prettier formatting` |
| **`refactor`** | Code change that neither fixes a bug nor adds a feature | `refactor(user): simplify permission check logic` |
| **`test`** | Adding or updating tests | `test(api): add unit tests for payment endpoint` |
| **`chore`** | Updating build tasks, package dependencies, etc. | `chore(deps): upgrade React to v19` |

---

### Good vs. Bad Examples

* ❌ `fixed stuff` *(vague, no context)*
* ❌ `Fixed bug in user login process.` *(past tense, unnecessary period)*
* ❌ `added a new feature to allow users to export data to CSV format` *(too long)*
* ✅ `fix(auth): prevent crash on empty password submission`
* ✅ `feat(export): allow users to export reports as CSV`

---