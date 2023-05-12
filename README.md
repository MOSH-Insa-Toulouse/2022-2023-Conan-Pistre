# 2022-2023-Conan-Pistre

![fake-it-till-u-make-it (1)](https://github.com/MOSH-Insa-Toulouse/2022-2023-Conan-Pistre/assets/124299449/4b47f089-a819-40a5-b6be-58dee72a209d)
[![forthebadge](https://forthebadge.com/images/badges/powered-by-black-magic.svg)](https://forthebadge.com)
[![forthebadge](https://forthebadge.com/images/badges/powered-by-coffee.svg)](https://forthebadge.com)
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
* [Fabrication du shield](#DeuxiemeSection)
  * [Composants designés : empreintes](#DeuxiemeSection1)
  * [Schématique](#DeuxiemeSection2)
  * [Placement des composants](#DeuxiemeSection3)
  * [Visualisation 3D](#DeuxiemeSection4)
  * [Réalisation du PCB](#DeuxiemeSection5)
  * [Perçage et soudure](#DeuxiemeSection6)
* [Code Arduino](#TroisiemeSection)
  * [Lecture de la valeur de la Résistance](#TroisiemeSection1)
  * [Gestion du BlueTooth](#TroisiemeSection2)
  * [Gestion de l'affichage OLED](#TroisiemeSection3)
* [Application Smartphone APK](#QuatriemeSection)
* [Banc de test](#CinquiemeSection)
* [Datasheet](#SixiemeSection)

## Tests et Mesures LTSpice : circuit amplificateur Transimpédance à deux étages <a id="PremiereSection"></a>
## Fabrication du shield <a id="DeuxiemeSection"></a>
### Composants designés : empreintes <a id="DeuxiemeSection1"></a>
### Schématique <a id="DeuxiemeSection2"></a>
### Placement des composants <a id="DeuxiemeSection3"></a>
### Visualisation 3D <a id="DeuxiemeSection4"></a>
### Réalisation du PCB <a id="DeuxiemeSection5"></a>

Le PCB a été réalisé avec l'aide de Cathy. Notre PCB a été fabriqué à partir d'une plaque d'Epoxy recouverte d'une fine couche de cuivre (≃ 60μm). Nous avons imprimé sur du papier calque la modélisation de notre PCB réalisée sur KICAD pour ensuite insoler notre plaquette aux UV avec la silhouette par-dessus pendant quelques minutes. À l'aide d'un révélateur, nous avons retiré la partie de la résine non insolée. La plaquette d'Epoxy est ensuite placée dans un bain de perchlorure de fer pour la gravure, opération durant entre 7 et 9 minutes. Le cuivre non protégé par la résine est ainsi retiré de la plaquette ce qui nous permet d'obtenir le PCB avec les pistes souhaitées. Enfin, de l'acétone est appliquée sur la plaquette pour éliminer les dernières traces de résine.

### Perçage et soudure <a id="DeuxiemeSection6"></a>

Nous avons ensuite percé notre PCB aux emplacements où les différents composants seront insérés à l'aide d'une perceuse électrique. Le diamètre des trous dépend des différents composants à placer :

⌀ 0.8mm : AOP LTC1050, résistances et capacités
⌀ 1.0mm : Broches de connexion de la carte Arduino Uno et headers des différents modules (OLED, bluetooth, encodeur rotatoire)

## Code Arduino <a id="TroisiemeSection"></a>
### Lecture de la valeur de la Résistance <a id="TroisiemeSection1"></a>
### Gestion du BlueTooth <a id="TroisiemeSection2"></a>
### Gestion de l'affichage OLED <a id="TroisiemeSection3"></a>
## Application Smartphone APK <a id="QuatriemeSection"></a>
## Banc de test <a id="CinquiemeSection"></a>

Pour réaliser notre banc de test, nous avons utilisé le banc de test fourni par le Génie Physique : 7 demi-cercles en plastique, dont les diamètres varient de 1 cm à 2,5cm. Le test alors réalisé est plutôt simple : nous mesurons différentes valeurs de résistance en courbant notre capteur sur le banc de test. Nous utilisons 3 capteurs préparé à l'aide de 3 types de crayons différents à dureté variable : un 1B, un HB et un 4B.

<img width="252" alt="116738001-2dc50b00-a9f2-11eb-9315-dd29a9fe3ac9" src="https://github.com/MOSH-Insa-Toulouse/2022-2023-Conan-Pistre/assets/124299449/7a3ebfc8-85bd-400f-bcd3-adbc765b7827">

![Graph_tension](https://github.com/MOSH-Insa-Toulouse/2022-2023-Conan-Pistre/assets/124299449/2402a950-201b-4466-ad51-b090aa73c80d)

![Graph_Compression](https://github.com/MOSH-Insa-Toulouse/2022-2023-Conan-Pistre/assets/124299449/44c78554-b431-439e-996d-8f155e0b93ed)

Les résultats obtenus semblent cohérents. En effet, une mine 4B dépose plus de graphite qu'une mine 1B elle même plus généreuse qu'une mine HB. Le dépôt de graphite plus important entraine une résistance globale plus faible. Nos capteurs ont bien une résistance variable selon leur déformation comme attendus d'une jauge de contrainte. Petit bémol cependant à constater : l'espérance de vie du capteur est très faible, après la série de tests il n'est déjà quasi plus utilisable. Cela réduit bien evidemment ses chances d'utilisation à grande échelle.

## Datasheet <a id="SixiemeSection"></a> 
