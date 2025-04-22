# Saint-Seiya
```markdown
# Guía Básica de Git
```
## 1. Configuración inicial
```bash
git config --global user.name "Tu Nombre"
git config --global user.email "tu@email.com"
```

## 2. Iniciar un repositorio
```bash
git init
```

## 3. Comandos básicos

### Ver estado de los archivos
```bash
git status
```

### Agregar archivos al área de preparación
```bash
git add nombre_archivo      # Agrega un archivo específico
git add .                   # Agrega todos los archivos
```

### Guardar cambios (commit)
```bash
git commit -m "Mensaje descriptivo del cambio"
```

### Enviar cambios a un repositorio remoto
```bash
git push origin main
```

### Actualizar repositorio local
```bash
git pull origin main
```

## 4. Trabajar con ramas (branches)

### Crear una nueva rama
```bash
git branch nombre-rama
```

### Cambiarse a una rama
```bash
git checkout nombre-rama
```

## 5. Comandos útiles

### Clonar un repositorio existente
```bash
git clone url-del-repositorio
```

### Ver historial de commits
```bash
git log
```

---

📌 **Nota básica:**  
- `origin` = nombre por defecto del repositorio remoto  
- `main` = nombre de la rama principal (antes se usaba `master`)
