# Game Mechanics

## Game Battle Combat System
Content:
- [**EXP && LVL** Experince and Level](#exp-and-lvl)
- [**HP** Health Points](#hp)
- [**MP** Magic Points](#mp)
- [**SKL & PSN** Skills and Poisons](#skl--psn)
- [**ATK** Attack](#atk)
- [**DEF** Defence](#def)
- [**LCK** Luck](#lck)
- [**ACC** Accurcy](#acc)
- [**EVA** Evasion](#eva)
- [**SPD** Spead](#spd)

### EXP and LVL
**Experience Points and Level** 
- player starts with LVL 1 and EXP 0
- this increase by fights and based on the damage you made and the turns
- gained EXP formula for fights if at least enemy level is half of player level, or **Player's Level is less than 2**
- if enemy's level is less than the half of the player level
$$
	EXP = 
		\begin{cases} 
			 \frac{PlayerDamage \times EnimeLVL}{PlayerTurns \times 2}
				& \text{if } LVL_{\text{foe}} \geq \frac{1}{2}LVL_{\text{p}} \quad \text{or} \quad LVL_{\text{p}} < 2 
			\\ \frac{(PlayerDamage/2) \times EnimeLVL}{PlayerTurns \times playerLVL}
				 & \text{if } LVL_{foe} < \frac{1}{2} LVL_{p}
		\end{cases}
$$
**(int): mean ignoring any fractions**
- for example:
	- you have killed a crazy frog with deal damage 60 in 4 turns, even if the crazy frog have 50HP, and this Frog have LVL 3, your EXP will be
	$$
		EXP = (60 \times 3) / 4 \times 2  \simeq 22 
	$$
	- your level is 8 and you fight an enimy with level 2, you made 50 damage in 2 turns
	$$
		EXP = \frac{(50/2) \times 2}{2 \times 8} \simeq 3
	$$
- EXP needed for each LVL Formula, **baseLVL = 10**
$$
	EXP = \sum_{i=0}^{LVL} \times baseLVL = \frac{LVL\times(LVL+1)}{2} \times baseLVL
$$
- LVL Examples:
	- LVL 1 = 10 EXP
	- LVL 2 = 30 EXP
	- LVL 3 = 60 EXP
	- ...
	-  LVL 99 = 49500 EXP
- 

---
### HP
**Health Points**
player have **HP starts with 30, which is baseHP**
player's HP increase based on EXP and LVL and this based on fights
$$
	HP = BaseHP \times (\frac{LVL}{2} + 1) 
$$
player can also have more HP based on some Items, Gears, drinking posion, or amount of magical beans
$$
	HP = CurrentHP + ItemHP 
$$

---
### ATK
**Attack** 
- player starts with ATK 10
- each equipped item affect the ATK value
---
### DEF
**Defense**
- player starts with DEF 10
- each equipped item affect the Defense
---
### LCK
**Luck**
- Player starts with LCK 10
- Luck affect on each turn attack value, we pick a random number between 1 and LCK value to calculate
---
### ACC
**Accuracy**
- Player starts with ACC 5
- this affects if the attack will deal damage or will be missed, this is based on **[EVA](#EVA)**
---
### EVA
**Evasion**
- Player starts with EVA 5
- same as ACC, but EVA affects if you will dodge this attack or it will deal a damage for you
---
### SPD
**SPEED**
- Player starts with SPD 5
- this affect if the player will start or the enemy, and is there someone have to make a double attack?
- who have a greater SPD value will start have to start the attack
- if $SPD_{player} = \frac{1}{2} SDP_{enemy}$ the enemy will have to start the attack, same for Player.
---
### MP
**Magic Points**
- Player starts with 0 MP
- player gain MP beside EXP by fights and by using heals and item $\text{gained MP} = \frac{1}{2} \text{Gained EXP}$
- player starts with 30 MP limit and increase by the Level, the same algorithm of level calculation (Linear increasing)
---
### SKL & PSN
**Skills and Poisons**
- player learn skills and gain poisons by the time from the NPCs
[[Skills senarios.excalidraw]]

| Poison / Skill Type | Effect on Type    | Poison effect | Effect name |
| ------------------- | ----------------- | ------------- | ----------- |
| Fire                | Plant, Normal     | -HP           | Burning     |
| Plant               | Light             | +DF           | Tree        |
| Light               | Air               | -EVA          | Shock       |
| Air                 | Dust              | -DF           | Wind        |
| Dust                | Water, Normal     | -ACC          | Tornado     |
| Water               | Fire, Normal      | -SPD          | Ice         |
| Normal              | Plant, Light, Air | —             | —           |

- Skill is used one time and affect on MP points %%as well the LVL, if you have got down by one level by using skills, there is three senario: [[Skills senarios.excalidraw]]%%
- Poison add an affect that remains for for each turn
- you can get rid of Poisons by eating something heals you (Increase your HP)
---
### Calculate the attack damage on HP

TODO

---
### Calculate the defence mechanic and how it reduce the attack damage
TODO

---
### The Algorithm of the Enemy in playing
TODO

---
