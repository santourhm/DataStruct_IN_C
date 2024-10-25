import matplotlib.pyplot as plt

# Lire les données à partir du fichier temps.dat
data = {'words': [], 'memory_size': [], 'loading_time': [], 'verification_time': []}

# Ouvrir le fichier et extraire les données
with open('temps.dat', 'r') as f:
    for line in f:
        parts = line.split()
        if len(parts) == 4:
            words = int(parts[0])
            memory_size = float(parts[1])
            loading_time = float(parts[2])
            verification_time = float(parts[3])

            # Ajouter les données dans le dictionnaire
            data['words'].append(words)
            data['memory_size'].append(memory_size)
            data['loading_time'].append(loading_time)
            data['verification_time'].append(verification_time)

# Création de la figure et des axes
fig, ax1 = plt.subplots()

# Tracer la taille mémoire sur l'axe secondaire (y2)
ax2 = ax1.twinx()
ax1.plot(data['words'], data['loading_time'], 'b-', label='Temps de chargement (s)')
ax1.plot(data['words'], data['verification_time'], 'g-', label='Temps de vérification (s)')
ax2.plot(data['words'], data['memory_size'], 'r-', label='Taille mémoire (MB)')

# Configuration des labels et des titres
ax1.set_xlabel('Nombre de mots dans le dictionnaire')
ax1.set_ylabel('Temps (secondes)', color='black')
ax2.set_ylabel('Taille mémoire (MB)', color='red')
plt.title('Analyse des performances de chargement et vérification')

# Ajout des légendes
ax1.legend(loc='upper left')
ax2.legend(loc='upper right')

# Afficher la grille
ax1.grid(True)

# Afficher le graphique
plt.tight_layout()
plt.show()
