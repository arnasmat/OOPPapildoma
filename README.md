# OOP Papildoma užduotis

Kaip asociatyvų atminties konteinerį pasirinkau naudoti savo implementuotą RB Medį su truputį modifikacijos. </br>

# Klasė RBTreeMap 

Randama rbtreemap.h </br>
## Klasės vieši metodai:
- insert(key) - Į konteinerį įterpia elementą. Jeigu toks elementas jau egzistuoja, padidina jo pair (šiuo atveju
naudojama kiekiui skaičiuoti) vienetu.
- remove(key) - Pašalina elementą iš konteinerio arba pamažina jo kiekį jeigu yra įterpti keli tokie patys elementai
- search(key) - Ieško konteinerį, gražina Node struktūros elementą (apie ją žemiau)
- navigate_tree() - Išvardina visus konteinerio elementus bei jų kiekį: Elementas, kiekis, spalva

### Node struktūros elementai:
- T key
- int pair - elementų kiekis
- bool red - ar šis Node [RB medyje yra raudonas](https://en.wikipedia.org/wiki/Red%E2%80%93black_tree). 
- Node* parent - šio Node tėvas/protėvis
- Node* left - šiam Node iš kairės esantis elementas (mažesnis už jį)
- Node* right - šiam Node iš dešinės esantis elementas (didesnis už jį)

