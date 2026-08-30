# UNDERCONSTRUCTION
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