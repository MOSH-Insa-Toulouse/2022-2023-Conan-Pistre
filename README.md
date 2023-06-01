# 2022-2023-Conan-Pistre

![fake-it-till-u-make-it (1)](https://github.com/MOSH-Insa-Toulouse/2022-2023-Conan-Pistre/assets/124299449/4b47f089-a819-40a5-b6be-58dee72a209d)
[![forthebadge](https://forthebadge.com/images/badges/powered-by-black-magic.svg)](https://forthebadge.com)
[![forthebadge](https://forthebadge.com/images/badges/it-works-why.svg)](https://forthebadge.com)
[![forthebadge](https://forthebadge.com/images/badges/its-not-a-lie-if-you-believe-it.svg)](https://forthebadge.com)



Ce projet s'inscrit dans l'UF "*Du capteur au banc de Test*". Il consiste en l'élaboration d'un capteur de déformation/Jauge de contrainte à base de graphite.
**Design**, **Conception**, **Test** et **Codage** de notre Capteur et de son circuit sont détaillés ci-dessous.

## Descriptif du Projet

Notre projet se sépare en deux axes précis:
 - Le développement d'une partie *Professionnelle* permettant depuis une application et un affichage OLED d'obtenir les valeurs de résistance de notre capteur
 - Le développement d'une partie *Fun* permettant une application pratique du capteur pour jouer au Dino Game de google.

![Social_dino-with-hat](https://github.com/MOSH-Insa-Toulouse/2022-2023-Conan-Pistre/assets/124299449/8fbb687d-eef3-498b-a7d9-f39a7269cd0d) 

## Sommaire

* [Tests et Mesures LTSpice : circuit amplificateur Transimpédance à deux étages](#PremiereSection)
* [Fabrication du Shield](#DeuxiemeSection)
  * [Composants designés : Symboles & empreintes](#DeuxiemeSection1)
  * [Schématique](#DeuxiemeSection2)
  * [Placement des composants](#DeuxiemeSection3)
  * [Réalisation du PCB](#DeuxiemeSection4)
  * [Perçage et soudure](#DeuxiemeSection5)
* [Code Arduino](#TroisiemeSection)
  * [Lecture de la valeur de la Résistance](#TroisiemeSection1)
  * [Gestion du BlueTooth](#TroisiemeSection2)
  * [Gestion de l'affichage OLED](#TroisiemeSection3)
* [Application Smartphone APK](#QuatriemeSection)
* [Banc de test](#CinquiemeSection)
* [Datasheet](#SixiemeSection)

## Tests et Mesures LTSpice : circuit amplificateur Transimpédance à deux étages <a id="PremiereSection"></a>

Le Schéma du circuit `ci-dessous` représente le circuit choisi pour optimiser les capacités de notre capteur. En effet ce dernier possédant une résistance élevée, il ne délivrera qu'un courant faible qu'il nous faut amplifier pour obtenir des résultats exploitables par notre programme Arduino.

**Schéma électrique Optimisé**
![Schéma électrique optimisé](https://github.com/MOSH-Insa-Toulouse/2022-2023-Conan-Pistre/assets/124299449/073e9e18-b402-41fa-b7d9-c79b0854c814)

Ce circuit possède 3 filtres ayant chacun leur utilité :
 - `en rouge` le filtre passe bas passif permet donc filtrer les perturbations et les excès de bruit en courant sur la forme du signal d'entrée, il possède une fréquence de coupure aux alentour de 16Hz.
 - `en vert` le filtre passe haut actif permet de supprimer la composante parasite de 50Hz qui vient perturber le signal, il possède une fréqence de 1,6Hz.
 - `en violet` le filtre passe bas passif permet limiter le bruit lors du traitement du signal, il possède une fréquence de 1,6kHz.

Passons maintenant à la simulation de notre circuit afin d'en évaluer l'optimisation :

**Vérification du la tension de sortie du montage avec un courant d'entrée égal à 100nA**
![Test 100nA](https://github.com/MOSH-Insa-Toulouse/2022-2023-Conan-Pistre/assets/124299449/8a9fe258-257a-4ad1-936e-59e497afc3d3)

Comme constaté `ci-dessus` notre circuit permet bien un gain de 100dB ce qui permet une nette augmentation du signal de sortie par rapport au signal d'entrée.

## Fabrication du Shield <a id="DeuxiemeSection"></a>

Pour fabriquer notre PCB nous avons du le designer sur KICAD 7.0. Nous avons ajouté au circuit précédent un écran OLED, un encodeur rotatoire ainsi qu'un module Bluetooth afin d'exploiter les résultats de notre capteur.

### Composants designés : Symboles & empreintes <a id="DeuxiemeSection1"></a>

* Ecran OLED 
<img src="https://github.com/MOSH-Insa-Toulouse/2022-2023-Conan-Pistre/assets/124299449/690b7c5a-9b07-4123-ac01-b100b4dfdc0d" height="200">
<img src="https://github.com/MOSH-Insa-Toulouse/2022-2023-Conan-Pistre/assets/124299449/f26ef03b-f065-4206-ad9c-2aa820cba9b1" height="200"> 

* Module Bluetooth

<img src="https://github.com/MOSH-Insa-Toulouse/2022-2023-Conan-Pistre/assets/124299449/bbe3be88-456b-42c5-8b16-e3fc5adad2b9" height="200"> 
<img src="https://github.com/MOSH-Insa-Toulouse/2022-2023-Conan-Pistre/assets/124299449/011ea964-ad66-4075-81ba-17ab6f6eb55f" height="200"> 

* Amplificateur LT1050 

<img src="https://github.com/MOSH-Insa-Toulouse/2022-2023-Conan-Pistre/assets/124299449/cc63cc12-8514-423d-81bc-4b205ba3ffc6" height="200">
<img src="https://github.com/MOSH-Insa-Toulouse/2022-2023-Conan-Pistre/assets/124299449/5e5588c3-af64-495a-bda7-1309f1d21f31" height="200"> 

* Capteur Graphite 

<img src="https://github.com/MOSH-Insa-Toulouse/2022-2023-Conan-Pistre/assets/124299449/83842c6e-6c81-4218-8b72-2c11436dbcd0" height="200"> 
<img src="https://github.com/MOSH-Insa-Toulouse/2022-2023-Conan-Pistre/assets/124299449/bceab15a-b39f-4515-b251-cb0adb5ebefb" height="200"> 

* Encodeur Rotatoire

<img src="https://github.com/MOSH-Insa-Toulouse/2022-2023-Conan-Pistre/assets/124299449/23737520-2d90-4ebc-99b0-1eca3a8b345d" height="200"> 
<img src="https://github.com/MOSH-Insa-Toulouse/2022-2023-Conan-Pistre/assets/124299449/b3102eea-f775-4d99-bc2c-7c0313cecd2a" height="200"> 


### Schématique <a id="DeuxiemeSection2"></a>

Une fois les symboles et empreintes créés, nous avons réalisé le schéma de notre shield. En haut à gauche sont représentées les broches de la carte Arduino. Au milieu est représenté le cicuit comprenant notre capteur et l'amplificateur transimpédance et juste au-dessus se trouvent l'écran OLED, le module bluetooth et l'encodeur rotatoire.

![schématique](https://github.com/MOSH-Insa-Toulouse/2022-2023-Conan-Pistre/assets/124299449/ab0e1c07-749f-45b6-93e3-46a6f9240166)

### Placement des composants <a id="DeuxiemeSection3"></a>

![schématique](https://github.com/MOSH-Insa-Toulouse/2022-2023-Conan-Pistre/assets/124299449/a4e3f035-550c-4e20-b8b6-485168f39ef5)

### Réalisation du PCB <a id="DeuxiemeSection4"></a>

Le PCB a été réalisé avec l'aide de Cathy. Notre PCB a été fabriqué à partir d'une plaque d'Epoxy recouverte d'une fine couche de cuivre (≃ 60μm). Nous avons imprimé sur du papier calque la modélisation de notre PCB réalisée sur KICAD pour ensuite insoler notre plaquette aux UV avec le calque par-dessus pendant quelques minutes. À l'aide d'un révélateur, nous avons retiré la partie de la résine non insolée. La plaquette d'Epoxy est ensuite placée dans un bain de perchlorure de fer pour la gravure, cette opération dure en moyenne 7-9min. Le cuivre non protégé par la résine est ainsi retiré de la plaquette ce qui nous permet d'obtenir notre PCB correspondant à notre KICAD. Enfin, un rincage à l'acétone est réalisé sur la plaquette pour éliminer les dernières traces de résine.

### Perçage et soudure <a id="DeuxiemeSection5"></a>

Nous avons ensuite percé notre PCB aux emplacements où les différents composants seront insérés à l'aide d'une perceuse électrique. Le diamètre des trous dépend des différents composants à placer :

⌀ 0.8mm : AOP LTC1050, résistances et capacités
⌀ 1.0mm : Broches de connexion de la carte Arduino Uno et headers des différents modules (OLED, bluetooth, encodeur rotatoire)

## Code Arduino <a id="TroisiemeSection"></a>
### Lecture de la valeur de la Résistance <a id="TroisiemeSection1"></a>
### Gestion du BlueTooth <a id="TroisiemeSection2"></a>
### Gestion de l'affichage OLED <a id="TroisiemeSection3"></a>
## Application Smartphone APK <a id="QuatriemeSection"></a>
## Banc de test <a id="CinquiemeSection"></a>

Pour réaliser notre phase de test, nous avons utilisé le banc de test réalisé lors des années précédentes : 7 demi-cercles en plastique, dont les diamètres varient de 2cm à 5cm. Le test alors réalisé est plutôt simple : nous mesurons différentes valeurs de résistance en courbant notre capteur sur le banc de test. Nous utilisons 3 capteurs préparés à l'aide de 3 types de crayons différents à dureté variable : un HB, un 1B et un 4B.

<img width="252" alt="116738001-2dc50b00-a9f2-11eb-9315-dd29a9fe3ac9" src="https://github.com/MOSH-Insa-Toulouse/2022-2023-Conan-Pistre/assets/124299449/7a3ebfc8-85bd-400f-bcd3-adbc765b7827">

![Graph_tension](https://github.com/MOSH-Insa-Toulouse/2022-2023-Conan-Pistre/assets/124299449/2402a950-201b-4466-ad51-b090aa73c80d)

![Graph_Compression](https://github.com/MOSH-Insa-Toulouse/2022-2023-Conan-Pistre/assets/124299449/44c78554-b431-439e-996d-8f155e0b93ed)

Les résultats obtenus semblent cohérents. En effet, une mine 4B dépose plus de graphite qu'une mine 1B elle même plus généreuse qu'une mine HB. Le dépôt de graphite plus important entraine une résistance globale plus faible. Nos capteurs ont bien une résistance variable selon leur déformation comme attendus d'une jauge de contrainte. Petit bémol cependant à constater : l'espérance de vie du capteur est très faible, après la série de tests il n'est déjà quasi plus utilisable. Cela réduit bien evidemment ses chances d'utilisation à grande échelle.

## Datasheet <a id="SixiemeSection"></a> 
