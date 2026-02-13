from cs50 import get_string

# 1. Obtener el texto
text = get_string("Text: ")

# 2. Inicializar contadores
letters = 0
sentences = 0
words = 0

# 3. Analizar el texto
# Para contar letras, iteramos sobre cada caracter
for char in text:
    if char.isalpha():
        letters += 1

# .split() crea una lista ['Hola', 'mundo'], len() nos dice cuántas hay
words = len(text.split())

# Para contar oraciones, buscamos los signos de puntuacion
sentences = text.count('.') + text.count('!') + text.count('?')

# 4. Calcular el indice Coleman-Liau
# L = letras por 100 palabras
L = (letters / words) * 100
# S = oraciones por 100 palabras
S = (sentences / words) * 100

index = 0.0588 * L - 0.296 * S - 15.8

# 5. Redondear al entero mas cercano
grade = round(index)

# 6. Imprimir el resultado segun las reglas
if grade < 1:
    print("Before Grade 1")
elif grade >= 16:
    print("Grade 16+")
else:
    print(f"Grade {grade}")
