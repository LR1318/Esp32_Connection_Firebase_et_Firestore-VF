**Readme du Script Arduino de Gestion de Dossiers avec Firebase**
En lien avec le projet https://github.com/LR1318/Projet_fin_Detude
---

**Description :**

Ce script Arduino est conçu pour se connecter à un réseau Wi-Fi, récupérer des données à partir d'une API externe, les afficher sur un écran LCD, et interagir avec la base de données en temps réel (RTDB) de Firebase. L'objectif principal est de fournir une solution de gestion de dossiers en temps réel, permettant de visualiser et de mettre à jour les informations sur un écran LCD à partir des données provenant d'une source externe.

---

**Configuration :**

1. **Connexion au réseau Wi-Fi :**
   - Assurez-vous de remplir les champs `WIFI_SSID` et `WIFI_PASSWORD` avec les informations de votre réseau Wi-Fi.

2. **Configuration Firebase :**
   - Remplacez la valeur de la constante `API_KEY` par la clé API de votre projet Firebase.
   - Remplacez la valeur de la constante `DATABASE_URL` par l'URL de votre base de données en temps réel Firebase.

3. **Écran LCD :**
   - Assurez-vous d'avoir correctement connecté et configuré votre écran LCD. Le script utilise la bibliothèque `LiquidCrystal_I2C` pour le contrôle de l'écran.

---

**Fonctionnement :**

1. Le script se connecte au réseau Wi-Fi spécifié et tente de s'authentifier auprès du service Firebase.

2. Une fois connecté et authentifié, le script récupère périodiquement des données à partir d'une API externe spécifiée dans la variable `serverName`.

3. Les données récupérées sont traitées au format JSON pour extraire les informations pertinentes, telles que le compteur de dossiers.

4. Les données sont affichées en temps réel sur l'écran LCD connecté.

5. Le script vérifie également périodiquement si un booléen spécifique dans la base de données RTDB de Firebase a été modifié.

6. Si le booléen est vrai, le script actualise les données à partir de l'API externe et met à jour l'écran LCD avec les nouvelles informations.

---

**Remarques :**

- Assurez-vous d'avoir correctement configuré votre environnement Arduino avec les bibliothèques nécessaires telles que Firebase_ESP_Client, LiquidCrystal_I2C, et Arduino_JSON.
- Veillez à remplir correctement les informations de configuration telles que le réseau Wi-Fi et les informations d'authentification Firebase.

---

**Merci d'utiliser notre solution de gestion de dossiers avec Firebase !**
