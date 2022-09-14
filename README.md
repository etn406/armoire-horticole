# ![icon](/images/icon.png) Armoire horticole

## Présentation

J'ai chez moi une petite collection de plantes (tropicales pour la plupart) et en hiver il y a peu de lumière et il fait parfois un peu froid (aérer l'appartement peu provoquer des courants d'air froid, auxquels les plantes sont sensibles).

J'ai donc aménagé une armoire vitrée pour garder les plantes les plus fragiles et les semis à l'abri, leur fournir de la lumière et de la chaleur, et -tant qu'à faire- avoir un suivi de la température et l'humidité à l'intérieur de l'armoire.

Le code présent dans ce dépôt est destiné à être installé sur un microcontrôleur ESP8266-12E.

## Matériel

### Électronique
- microcontrôleur ESP8266-12E
- capteurs de température et d'humidité DHT22
- module de 4 relais pour la commande des lumières 
- écran OLED 128x64 px
- bouton poussoir
- alimentation 5 V - 1 A (5W)

### Éclairage

- rubans LED horticole blanches 12 V consommant ±8.5 W/mètre de la marque YujiLED (2.5 m au total découpés en portions de 50 cm, puissance consommée ±22 W)
- alimentation 12 V - 5 A (60 W).

## Fonctionnalités

- Récupération de l'humidité et de la température de 3 capteurs (1 par étagère).
- Affichage de l'humidité et de la température moyenne sur un mini-écran.
- Allumage et extinction des 3 lumières (1 par étagère) et du tapis chauffant.
- Suivi de l'humidité et de la température, allumage et extinction des lumières et du tapis chauffant, etc.
- Connexion au WiFi réglable et automatique au démarrage.
- API HTTP pour récupérer les valeurs actuelles (C° et %) et contrôler l'allumage des lumières.

## Schéma

![illustration](/images/illustration.png)

## API HTTP

### Lire les valeurs des capteurs

```
GET /get-sensors-values
```

Retourne un array JSON contenant un objet par capteur. Chaque objet a 3 propriétés: `id` (identifiant numérique du capteur), `humidity` (en `%`) et `temperature` (en `°C`).

Exemple d'objet représentant un capteur:
```json
{
  "id": 0,
  "humidity": 70,
  "temperature": 23.5
}
```

### Lire les valeurs des relais
```
GET /get-relays-values
```

Retourne un array JSON contenant un objet par relais, plus un principal `main` (fictif, il permet de couper l'ensemble des relais si il est `false`). Chaque objet a 2 propriétés: `name` (le nom du relais) et `valeur` (booléen indiquant si le relais est actif ou non).

Exemple d'objet représentant un relais:
```json
{
  "name": "relay-2",
  "value": false
}
```

### Modifier la valeur d'un relais

```
GET /set-relay?name=<nom>&value=<true|false>
```

Modifier un relais identifié par son nom. Le retour de cette requête est le même que `/get-relays-values`.
