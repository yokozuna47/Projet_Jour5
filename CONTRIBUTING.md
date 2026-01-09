# 🤝 Guide de Contribution

Merci de votre intérêt pour ce projet ! Ce document explique comment contribuer.

## 📋 Code de Conduite

- ✅ Être respectueux et constructif
- ✅ Reconnaître les contributions des autres
- ✅ Respecter les lois et réglementations
- ❌ Aucune discrimination
- ❌ Aucune activité malveillante

## 🚀 Comment Contribuer

### 1. Avant de commencer

Assurez-vous que :
- Vous avez lu [README.md](./README.md)
- Vous comprenez que ce projet est **ÉDUCATIF SEULEMENT**
- Vous respectez la [LICENSE](./LICENSE)

### 2. Forker et Cloner

```bash
# Fork sur GitHub, puis clone
git clone https://github.com/VOTRE_USERNAME/Projet_Jour5.git
cd Projet_Jour5
git remote add upstream https://github.com/yokozuna47/Projet_Jour5.git
```

### 3. Créer une branche

```bash
# Créer une branche descriptive
git checkout -b feature/description-courte
# Exemples :
# feature/add-c2-server
# fix/caesar-shift-negative
# docs/improve-readme
# test/add-unit-tests
```

### 4. Faire vos changements

- Suivre le **style de code existant**
- Ajouter des **commentaires** clairs
- Tester votre code
- Compiler sans warnings : `gcc -Wall -Wextra -I. -o ransomware ransomware.c modules.c`

### 5. Committer

```bash
# Commits clairs et descriptifs
git commit -m "fix: corriger le modulo négatif dans caesar_char"
git commit -m "feat: ajouter validation des paramètres en xor_buffer"
git commit -m "docs: mettre à jour la documentation MODULE 3"

# Format :
# feat:  nouvelle fonctionnalité
# fix:   correction de bug
# docs:  changement de documentation
# test:  ajout de tests
# perf:  amélioration de performance
# refactor: restructuration du code
```

### 6. Pusher et créer une Pull Request

```bash
git push origin feature/description-courte
```

Puis sur GitHub :
- Créer une Pull Request
- Décrire les changements clairement
- Linker les issues associées (#12, #34)
- Attendre la review

---

## 🔍 Types de Contributions Bienvenues

### 🐛 Bug Fixes
```c
// ❌ Avant (bug : ne gère pas les clés vides)
void xor_buffer(char *buffer, size_t size, const char *key, size_t key_len) {
    for (size_t i = 0; i < size; i++) {
        buffer[i] ^= key[i % key_len];  // Crash si key_len = 0
    }
}

// ✅ Après (validation ajoutée)
void xor_buffer(char *buffer, size_t size, const char *key, size_t key_len) {
    if (buffer == NULL || key == NULL || key_len == 0) {
        return;  // Validation
    }
    for (size_t i = 0; i < size; i++) {
        buffer[i] ^= key[i % key_len];
    }
}
```

### ✨ Améliorations
- Améliorer la performance
- Ajouter des validations
- Améliorer la gestion d'erreurs
- Ajouter des fonctionnalités éducatives

Exemples :
- Ajouter un serveur C2
- Implémentation d'AES (éducatif)
- Tests unitaires
- Benchmarks de performance

### 📚 Documentation
- Améliorer les commentaires
- Ajouter des exemples
- Traduire la documentation
- Créer des tutoriels

### 🧪 Tests
- Tests unitaires
- Scripts de test
- Test de regresison
- Benchmarks

---

## 📝 Standards de Code

### Style

```c
// ✅ Bon
int scan_directory(const char *path, char files[][MAX_PATH], int max_files) {
    if (path == NULL || max_files <= 0) {
        return 0;
    }
    
    // Code bien commenté
    DIR *dir = opendir(path);
    if (dir == NULL) {
        return 0;
    }
    
    // ... reste du code
    
    closedir(dir);
    return count;
}

// ❌ Mauvais
int scan_directory(const char *path, char files[][MAX_PATH], int max_files) {
    DIR *dir = opendir(path);  // Pas de validation
    // Code sans commentaire
    while ((entry = readdir(dir)) != NULL) {
        // ...
    }
}
```

### Commentaires

```c
// ✅ Clair et utile
// XOR chaque byte du buffer avec la clé (cycliquement)
for (size_t i = 0; i < size; i++) {
    buffer[i] ^= key[i % key_len];
}

// ❌ Inutile ou confus
// faire le xor
buffer[i] ^= key[i % key_len];
```

### Variables et Noms

```c
// ✅ Descriptif
uint32_t crc_value = 0xFFFFFFFF;
char encryption_key[128];
int file_count = 0;

// ❌ Vague
uint32_t x = 0xFFFFFFFF;
char k[128];
int n = 0;
```

---

## ✅ Checklist avant la PR

- [ ] Code compile sans erreurs
- [ ] Code compile sans warnings
- [ ] Code testé et fonctionne
- [ ] Commentaires clairs ajoutés
- [ ] Documentation mise à jour
- [ ] Commits clairs et descriptifs
- [ ] Pas de code morcelé ou débogué
- [ ] Respecte le style existant

---

## 📊 Processus de Review

1. **Automatisé** : Tests + Linting
2. **Manuel** : Revue du code par un mainteneur
3. **Feedback** : Commentaires et suggestions
4. **Modifications** : Appliquer les changements demandés
5. **Approbation** : Merge si tout est OK

---

## 🎓 Propositions de Projets

Si vous cherchez des idées de contribution :

### Facile
- [ ] Améliorer les commentaires
- [ ] Ajouter des exemples dans README
- [ ] Corriger des typos
- [ ] Ajouter des badges au README

### Moyen
- [ ] Ajouter des tests unitaires
- [ ] Implémenter un serveur C2 simple
- [ ] Ajouter de la validation des paramètres
- [ ] Optimiser la performance (benchmarks)

### Difficile
- [ ] Implémenter une crypto plus forte (éducatif)
- [ ] Multi-threading pour C2 server
- [ ] GUI/Interface web
- [ ] Documentation complète en PDF

---

## 🐛 Signaler un Bug

Créer une Issue avec :

```markdown
## Description
[Courte description du bug]

## Étapes de reproduction
1. ...
2. ...
3. ...

## Comportement attendu
[Décrire ce qui devrait se passer]

## Comportement réel
[Décrire ce qui se passe réellement]

## Environnement
- OS: [Linux/Windows/macOS]
- Compilateur: [GCC version, etc.]
- VM: [Vagrant/autre]

## Logs/Erreurs
[Copier-coller les erreurs exactes]
```

---

## 💡 Proposer une Fonctionnalité

Créer une Issue avec :

```markdown
## Description
[Décrivez la fonctionnalité demandée]

## Cas d'usage
[Pourquoi c'est utile ? Exemple concrèt]

## Solution proposée
[Comment vous proposez de l'implémenter]

## Alternatives considérées
[Autres approches possibles]

## Contexte éducatif
[Comment c'est utile pour apprendre ?]
```

---

## 🙏 Questions ?

- Ouvrir une **Discussion** sur GitHub
- Consulter les **Issues existantes**
- Vérifier la **Documentation**

---

## 📜 License

En contribuant, vous acceptez que vos contributions soient sous la même [LICENSE](./LICENSE).

---

**Merci de contribuer ! 🎉**

*Chaque contribution, même petite, aide le projet à être meilleur.*

---

**Dernière mise à jour** : 09/01/2026
